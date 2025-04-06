#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cctype>

// Funzione per rimuovere gli spazi all'inizio e alla fine di una stringa
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    return (first == std::string::npos) ? "" : str.substr(first, (last - first + 1));
}

// Funzione per ridurre più spazi consecutivi a uno solo
std::string reduceSpaces(const std::string& str) {
    std::string result;
    bool inSpace = false;

    for (char c : str) {
        if (std::isspace(c)) {
            if (!inSpace) {
                result += ' ';  // Aggiungi uno spazio solo se non è già presente
                inSpace = true;
            }
        } else {
            result += c;  // Aggiungi il carattere non spaziale
            inSpace = false;
        }
    }

    return result;
}

// Funzione per rimuovere tutte le virgolette da una stringa
std::string removeQuotes(const std::string& str) {
    std::string result;
    for (char c : str) {
        if (c != '"') {
            result += c;  // Aggiungi solo i caratteri che non sono virgolette
        }
    }
    return result;
}

// Funzione per aggiungere uno spazio dopo ogni punto e virgola, se necessario
std::string addSpaceAfterSemicolon(const std::string& str) {
    std::string result;
    for (size_t i = 0; i < str.length(); ++i) {
        result += str[i];
        
        // Se il carattere è un punto e virgola, controlla se c'è uno spazio dopo
        if (str[i] == ';') {
            if (i + 1 < str.length() && str[i + 1] != ' ') {
                result += ' ';  // Aggiungi uno spazio se non c'è già
            }
        }
    }
    return result;
}

// Funzione per leggere e "sanitizzare" il file CSV
void sanitizeCSV(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream input(inputFile);
    std::ofstream output(outputFile);
    
    if (!input.is_open()) {
        std::cerr << "Errore nell'aprire il file di input!" << std::endl;
        return;
    }
    
    if (!output.is_open()) {
        std::cerr << "Errore nell'aprire il file di output!" << std::endl;
        return;
    }
    
    std::string line;
    while (getline(input, line)) {
        std::stringstream ss(line);
        std::string field;
        bool first = true;
        
        // Elabora ogni campo nella riga
        while (getline(ss, field, ',')) {
            if (!first) {
                output << ",";
            }
            first = false;
            
            // Rimuovi virgolette, spazi extra, riduci gli spazi consecutivi e aggiungi spazio dopo punto e virgola
            field = removeQuotes(field);
            field = trim(field);
            field = reduceSpaces(field);
            field = addSpaceAfterSemicolon(field);
            
            // Scrivi il campo "sanitizzato" nel file di output
            output << field;
        }
        output << "\n";
    }

    input.close();
    output.close();
}

int main() {
    // Esegui la sanitizzazione del file CSV
    std::string inputFile = "elenco_scuole_italiane_2018.csv";  // Nome del file di input
    std::string outputFile = "elenco_scuole_italiane_2018_sanitizzato1.csv";  // Nome del file di output
    
    sanitizeCSV(inputFile, outputFile);  // Funzione che sanitizza il file
    std::cout << "File sanitizzato e salvato in: " << outputFile << std::endl;

    return 0;
}
