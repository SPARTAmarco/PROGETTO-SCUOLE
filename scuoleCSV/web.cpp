#include <iostream> // Libreria per input/output
#include <curl/curl.h> // Libreria per effettuare richieste HTTP

// Funzione che verifica se un sito web è accessibile
bool verificaSitoWeb(const std::string& url) {
    CURL* curl; // Puntatore a un'istanza di CURL
    CURLcode res; // Variabile per il codice di ritorno della richiesta
    bool esito = false; // Variabile booleana per memorizzare l'esito della verifica

    curl_global_init(CURL_GLOBAL_DEFAULT); // Inizializza la libreria cURL
    curl = curl_easy_init(); // Crea un'istanza di CURL

    if(curl) { // Verifica se l'istanza di CURL è stata creata correttamente
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // Imposta l'URL da verificare
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L); // Effettua una richiesta HEAD senza scaricare il contenuto

        res = curl_easy_perform(curl); // Esegue la richiesta HTTP

        if(res == CURLE_OK) { // Se la richiesta è andata a buon fine
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code); // Ottiene il codice di risposta HTTP
            if(response_code == 200) { // Se il codice di risposta è 200 (OK)
                esito = true; // Il sito è accessibile
            }
        }

        curl_easy_cleanup(curl); // Libera la memoria occupata da CURL
    }

    curl_global_cleanup(); // Pulisce le risorse globali di CURL
    return esito; // Restituisce il risultato della verifica
}

int main() {
    std::string url = "https://www.isissronca.edu.it"; // URL del sito da verificare
    
    // Chiama la funzione verificaSitoWeb e stampa il risultato
    if(verificaSitoWeb(url)) {
        std::cout << "Il sito \212 accessibile." << std::endl;
    } else {
        std::cout << "Il sito non \212 accessibile." << std::endl;
    }
    
    return 0; // Termina il programma con codice di successo
}
