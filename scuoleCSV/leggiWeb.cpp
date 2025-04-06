#include <iostream>
#include <curl/curl.h>

// Funzione di callback per scrivere i dati ricevuti
size_t ScriviDati(void* buffer, size_t size, size_t nmemb, std::string* dati) {
    dati->append((char*)buffer, size * nmemb);
    return size * nmemb;
}

std::string leggiContenutoSito(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string contenuto;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());   // Imposta l'URL
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, ScriviDati);  // Imposta la funzione di callback
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &contenuto);  // Passa la stringa dove salvare i dati

        res = curl_easy_perform(curl);  // Esegue la richiesta HTTP

        if (res != CURLE_OK) {
            std::cerr << "Errore cURL: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return contenuto;  // Ritorna il contenuto scaricato
}

int main() {
    std::string url = "http://www.istitutovalleseriana.edu.it";  // URL della pagina da leggere
    std::string contenuto = leggiContenutoSito(url);

    std::cout << "Contenuto della pagina:\n" << contenuto << std::endl;

    return 0;
}
