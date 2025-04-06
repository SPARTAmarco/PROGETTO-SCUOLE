#include <iostream>
#include <fstream>
#include <vector>
#include <curl/curl.h>

// Funzione di callback per scrivere i dati ricevuti (scarta il contenuto, serve solo per il check)
size_t ScriviDati(void* buffer, size_t size, size_t nmemb, void* userp) {
    return size * nmemb;
}

// Struttura per contenere informazioni su ogni richiesta
struct Sito {
    std::string url;
    CURL* handle;
    bool accessibile;
};

// Numero massimo di connessioni simultanee
const int MAX_CONNESSIONI = 100;

// Funzione che verifica più siti web in parallelo
void verificaSitiWeb(const std::vector<std::string>& siti) {
    CURLM* multi_handle = curl_multi_init();
    std::vector<Sito> richieste;
    int ancora_in_esecuzione = 0;

    // Aggiunge siti al pool fino a raggiungere il massimo delle connessioni
    auto it = siti.begin();
    while (it != siti.end() || !richieste.empty()) {
        // Aggiunge nuove richieste fino al limite massimo
        while (it != siti.end() && richieste.size() < MAX_CONNESSIONI) {
            Sito s;
            s.url = *it;
            s.handle = curl_easy_init();
            s.accessibile = false;

            curl_easy_setopt(s.handle, CURLOPT_URL, s.url.c_str());
            curl_easy_setopt(s.handle, CURLOPT_NOBODY, 1L); // Solo HEAD request
            curl_easy_setopt(s.handle, CURLOPT_WRITEFUNCTION, ScriviDati); // Non scaricare il contenuto
            curl_multi_add_handle(multi_handle, s.handle);

            richieste.push_back(std::move(s));
            ++it;
        }

        // Esegue le richieste in parallelo
        curl_multi_perform(multi_handle, &ancora_in_esecuzione);

        // Controlla le richieste completate
        int num_finiti;
        CURLMsg* msg;
        while ((msg = curl_multi_info_read(multi_handle, &num_finiti))) {
            if (msg->msg == CURLMSG_DONE) {
                for (auto& s : richieste) {
                    if (s.handle == msg->easy_handle) {
                        long codice;
                        curl_easy_getinfo(s.handle, CURLINFO_RESPONSE_CODE, &codice);
                        s.accessibile = (codice == 200);

                        std::cout << s.url << " -> " << (s.accessibile ? "OK" : "NO") << std::endl;

                        // Rimuove la richiesta completata
                        curl_multi_remove_handle(multi_handle, s.handle);
                        curl_easy_cleanup(s.handle);
                        richieste.erase(std::remove_if(richieste.begin(), richieste.end(),
                        [&](const Sito& sito) { return sito == s; }), richieste.end());

                        break;
                    }
                }
            }
        }
    }

    curl_multi_cleanup(multi_handle);
}

int main() {
    std::vector<std::string> siti;

    // Carica l'elenco dei siti web da un file
    std::ifstream file("siti.txt");
    std::string url;
    while (std::getline(file, url)) {
        siti.push_back(url);
    }
    file.close();

    // Verifica tutti i siti
    verificaSitiWeb(siti);

    return 0;
}
