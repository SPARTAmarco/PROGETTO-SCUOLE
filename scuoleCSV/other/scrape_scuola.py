import requests
from bs4 import BeautifulSoup
import re
import pandas as pd

def estrai_testo(url):
    """Scarica e analizza il testo della pagina"""
    headers = {"User-Agent": "Mozilla/5.0"}
    response = requests.get(url, headers=headers)
    if response.status_code != 200:
        print("Errore nel caricamento della pagina")
        return ""
    soup = BeautifulSoup(response.text, 'html.parser')
    return soup.get_text(separator=' ', strip=True)

def trova_indirizzi_e_orari(testo):
    """Trova indirizzi e orari nel testo usando regex ed euristiche"""
    indirizzi = re.findall(r'Via [A-Z][a-z]+.*?\d{1,3}', testo)
    orari = re.findall(r'\b(?:Luned\ì|Marted\ì|Mercoled\ì|Gioved\ì|Venerd\ì|Sabato|Domenica) .*?\d{1,2}:\d{2}', testo)
    return indirizzi, orari

def salva_csv(dati, nome_file="scuole.csv"):
    """Salva i dati in un file CSV"""
    df = pd.DataFrame(dati, columns=["Indirizzo", "Orario"])
    df.to_csv(nome_file, index=False)
    print(f"Dati salvati in {nome_file}")

if __name__ == "__main__":
    url = input("Inserisci il sito della scuola: ")
    testo = estrai_testo(url)
    indirizzi, orari = trova_indirizzi_e_orari(testo)
    dati = list(zip(indirizzi, orari + [""] * (len(indirizzi) - len(orari))))
    salva_csv(dati)
