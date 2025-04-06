#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <set>
#include <cstdlib>
#include <list>
#include <vector>
using namespace std;

int main(){
	
	struct scuola{
	string COMUNE;
	string PROVINCIA;
	string REGIONE;
	string Codice_scuola;
	string Denominazione_istituto;
	string Tipologia_istituto;
	string Indirizzo; //(Via + numero civico)
    string Codice_Postale;
    string Telefono;
    string Fax;
    string Email;
    string PEC;
    string Sito_web;
    string Istituto_principale_riferimento; // (sede direzione)
    string Statale_Paritaria;
    
    
	};
	
	scuola s;
	fstream inputFileStream;
	string line;
	short int count=1;
    map<string, vector<string>> scuoleMap;

	
	inputFileStream.open("elenco_scuole_italiane_2018_sanitizzato1.csv");
	if(!inputFileStream.is_open()){
		cout<<"File non trovato."<<endl;
		return EXIT_FAILURE;
	}
	
	getline(inputFileStream, line);
	
	while(getline(inputFileStream, line)){
		count++;
		bool ActionCount=false;
		bool ThrillerCount=false;
		
		s.COMUNE = line.substr(0, line.find(";"));
		line = line.substr(line.find(";") + 1);
		
		s.PROVINCIA = line.substr(0, line.find(";"));
		line = line.substr(line.find(";") + 1);
		
		s.REGIONE = line.substr(0, line.find(";"));
		line = line.substr(line.find(";") + 1);
		
		s.Codice_scuola = line.substr(0, line.find(";"));
		line = line.substr(line.find(";") + 1);
		
		s.Denominazione_istituto = line.substr(0, line.find(";"));
		line = line.substr(line.find(";") + 1);
		
		s.Tipologia_istituto = line.substr(0, line.find(";"));
		line = line.substr(line.find(";") + 1);
		
		s.Indirizzo = line.substr(0, line.find(";"));
		line = line.substr(line.find(";") + 1);

        s.Codice_Postale = line.substr(0, line.find(";"));
		line = line.substr(line.find(";") + 1);

        s.Telefono = line.substr(0, line.find(";"));
		line = line.substr(line.find(";") + 1);

        s.Fax = line.substr(0, line.find(";"));
		line = line.substr(line.find(";") + 1);
        
        s.Email = line.substr(0, line.find(";"));
		line = line.substr(line.find(";") + 1);

        s.PEC = line.substr(0, line.find(";"));
		line = line.substr(line.find(";") + 1);

        s.Sito_web = line.substr(0, line.find(";"));
		line = line.substr(line.find(";") + 1);

        s.Istituto_principale_riferimento = line.substr(0, line.find(";"));
		line = line.substr(line.find(";") + 1);

        s.Statale_Paritaria = line.substr(0, line.find(";"));
		line = line.substr(line.find(";") + 1);

        scuoleMap[s.COMUNE].push_back(s.Denominazione_istituto);


    }
    string comuneInput;
    cout<<"Eseguire la ricerca di tutte le scuole di un comune con la sintassi esempio: Gazzaniga"<<endl;
    cin>>comuneInput;
    for (auto sc:scuoleMap[comuneInput])
    {
        cout<<sc<<endl;
    }
    
}