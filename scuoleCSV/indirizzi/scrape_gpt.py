import requests
from bs4 import BeautifulSoup
import openai
import pandas as pd

# Inserisci qui la tua API Key OpenAI

def get_visible_text(url):
    """Scarica il contenuto della pagina ed estrae il testo visibile."""
    response = requests.get(url)
    response.raise_for_status()
    soup = BeautifulSoup(response.text, 'html.parser')

    # Rimuove script e CSS
    for tag in soup(["script", "style"]):
        tag.decompose()
    
    return soup.get_text(separator=' ')

def analyze_with_gpt(text):
    """Invia il testo a GPT e chiede di estrarre indirizzi e orari."""
    prompt = f"""
    Analizza il seguente testo e trova gli indirizzi scolastici e gli orari di apertura.
    Formatta la risposta in JSON con due chiavi: "indirizzi" e "orari".
    Testo:
    {text}
    """
    
    response = openai.ChatCompletion.create(
        model="gpt-4",
        messages=[{"role": "system", "content": "Sei un assistente esperto nell'estrazione di informazioni da siti web."},
                  {"role": "user", "content": prompt}],
        api_key=OPENAI_API_KEY
    )

    return response["choices"][0]["message"]["content"]

def save_to_csv(data, filename="output_info.csv"):
    """Salva i dati estratti in un CSV."""
    df = pd.DataFrame(data)
    df.to_csv(filename, index=False, encoding="utf-8")
    print(f"Dati salvati in {filename}")

def main():
    url = input("Inserisci l'URL del sito: ").strip()
    print("Scaricando contenuto da:", url)
    
    try:
        text = get_visible_text(url)
    except Exception as e:
        print("Errore durante il download:", e)
        return

    try:
        extracted_data = analyze_with_gpt(text)
        print("Risultati estratti:\n", extracted_data)
    except Exception as e:
        print("Errore durante l'analisi GPT:", e)
        return

    # Salva in CSV
    save_to_csv(extracted_data)

if __name__ == "__main__":
    main()
