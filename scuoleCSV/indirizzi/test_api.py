import openai


try:
    response = openai.completions.create(
        model="gpt-4",  # Usa il modello appropriato
        prompt="Dimmi una curiosità su Python.",  # Il testo di input
        max_tokens=50  # Numero massimo di token nella risposta
    )
    print(response['choices'][0]['text'])
except Exception as e:
    print("Errore:", e)
