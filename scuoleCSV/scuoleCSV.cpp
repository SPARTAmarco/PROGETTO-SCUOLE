#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <set>
#include <cstdlib>
#include <list>
#include <vector>
#include <curl/curl.h> // Libreria per effettuare richieste HTTP
using namespace std;

// void nextField(string &line, string stri){
//     stri = line.substr(0, line.find(";"));
// 	line = line.substr(line.find(";") + 1);
// }


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



int main(){
	
	struct scuola{
        string annoScolastico;
        string areaGeografica;
        string regione;
        string provincia;
        string codiceIstitutoRiferimento;
        string denominazioneIstitutoRiferimento;
        string codiceScuola;
        string denominazioneScuola;
        string indirizzoScuola;
        string capScuola;
        string codiceComuneScuola;
        string descrizioneComune;
        string descrizioneCaratteristicaScuola;
        string descrizioneTipologiaGradoIstruzione;
        string indicazioneSedeDirettivo;
        string indicazioneSedeOmnicomprensivo;
        string indirizzoEmailScuola;
        string indirizzoPECScuola;
        string sitoWebScuola;
        string sedeScolastica;
	};
	
	scuola s;
	fstream inputFileStream;
	string line;
    map<string, vector<string>> scuoleMap;

    int funziona=0;
    int nonFunziona=0;
	
	inputFileStream.open("SCUANAGRAFESTAT20242520240901.csv");
	if(!inputFileStream.is_open()){
		cout<<"File non trovato."<<endl;
		return EXIT_FAILURE;
	}
	
	getline(inputFileStream, line);
	
	while(getline(inputFileStream, line)){

        // nextField(line, s.annoScolastico);
        // nextField(line, s.areaGeografica);
        // nextField(line, s.regione);
        // nextField(line, s.provincia);
        // nextField(line, s.codiceIstitutoRiferimento);
        // nextField(line, s.denominazioneIstitutoRiferimento);
        // nextField(line, s.codiceScuola);
        // nextField(line, s.denominazioneScuola);
        // nextField(line, s.indirizzoScuola);
        // nextField(line, s.capScuola);
        // nextField(line, s.codiceComuneScuola);
        // nextField(line, s.descrizioneComune);
        // nextField(line, s.descrizioneCaratteristicaScuola);
        // nextField(line, s.descrizioneTipologiaGradoIstruzione);
        // nextField(line, s.indicazioneSedeDirettivo);
        // nextField(line, s.indicazioneSedeOmnicomprensivo);
        // nextField(line, s.indirizzoEmailScuola);
        // nextField(line, s.indirizzoPECScuola);
        // nextField(line, s.sitoWebScuola);
        // nextField(line, s.sedeScolastica);

        s.annoScolastico = line.substr(0, line.find(",")); 
        line = line.substr(line.find(",") + 1);

        s.areaGeografica = line.substr(0, line.find(",")); 
        line = line.substr(line.find(",") + 1);

        s.regione = line.substr(0, line.find(",")); 
        line = line.substr(line.find(",") + 1);

        s.provincia = line.substr(0, line.find(",")); 
        line = line.substr(line.find(",") + 1);

        s.codiceIstitutoRiferimento = line.substr(0, line.find(",")); 
        line = line.substr(line.find(",") + 1);

        s.denominazioneIstitutoRiferimento = line.substr(0, line.find(",")); 
        line = line.substr(line.find(",") + 1);

        s.codiceScuola = line.substr(0, line.find(",")); 
        line = line.substr(line.find(",") + 1);

        s.denominazioneScuola = line.substr(0, line.find(",")); 
        line = line.substr(line.find(",") + 1);

        s.indirizzoScuola = line.substr(0, line.find(",")); 
        line = line.substr(line.find(",") + 1);

        s.capScuola = line.substr(0, line.find(",")); 
        line = line.substr(line.find(",") + 1);

        s.codiceComuneScuola = line.substr(0, line.find(",")); 
        line = line.substr(line.find(",") + 1);

        s.descrizioneComune = line.substr(0, line.find(",")); 
        line = line.substr(line.find(",") + 1);

        s.descrizioneCaratteristicaScuola = line.substr(0, line.find(",")); 
        line = line.substr(line.find(",") + 1);

        s.descrizioneTipologiaGradoIstruzione = line.substr(0, line.find(",")); 
        line = line.substr(line.find(",") + 1);

        s.indicazioneSedeDirettivo = line.substr(0, line.find(",")); 
        line = line.substr(line.find(",") + 1);

        s.indicazioneSedeOmnicomprensivo = line.substr(0, line.find(",")); 
        line = line.substr(line.find(",") + 1);

        s.indirizzoEmailScuola = line.substr(0, line.find(",")); 
        line = line.substr(line.find(",") + 1);

        s.indirizzoPECScuola = line.substr(0, line.find(",")); 
        line = line.substr(line.find(",") + 1);

        s.sitoWebScuola = line.substr(0, line.find(",")); 
        line = line.substr(line.find(",") + 1);

        s.sedeScolastica = line.substr(0, line.find(",")); 
        line = line.substr(line.find(",") + 1);

        scuoleMap[s.descrizioneComune].push_back(s.denominazioneScuola);

        if(verificaSitoWeb(s.sitoWebScuola)){
            funziona++;}
        // } else {nonFunziona++;}
        
    cout<<funziona;
    }
    // string comuneInput;
    // cout<<"Eseguire la ricerca di tutte le scuole di un comune con la sintassi esempio: GAZZANIGA"<<endl;
    // cin>>comuneInput;
    // string testo;
    // comuneInput = (cin, testo);
    // cout<<comuneInput;
    // for (string sc:scuoleMap[comuneInput])
    // {
    //     cout<<sc<<endl;

    cout<<funziona;
    cout<<nonFunziona;
}
