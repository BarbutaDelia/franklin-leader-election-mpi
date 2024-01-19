import matplotlib.pyplot as plt

# Datele: numarul de procese si timpul de executie corespunzator
numar_procese = [25, 50, 75, 100, 125, 150, 175, 200, 225, 250, 275, 300, 325, 350, 375, 400]
timp_executie = [0.003846, 0.006778, 0.042351, 0.057407, 0.141913, 0.218114, 0.364511, 0.640698, 1.120833, 2.998660, 2.931342, 1.746101, 1.416805, 1.861528, 1.497230, 1.762651]

# Crearea graficului
plt.figure(figsize=(10, 6))
plt.plot(numar_procese, timp_executie, marker='o')

# Adaugarea titlului si a etichetelor axelor
plt.title("Timpul de Execuție în Funcție de Numărul de Procese")
plt.xlabel("Numărul de Procese")
plt.ylabel("Timp de Execuție (secunde)")

# Afișarea graficului
plt.show()

