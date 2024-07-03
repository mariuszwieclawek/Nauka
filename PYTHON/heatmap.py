import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt

# Generowanie syntetycznych danych BER
def generate_ber_data(time_shifts, amplitude_shifts):
    ber = np.zeros((len(amplitude_shifts), len(time_shifts)))
    
    for i, amp_shift in enumerate(amplitude_shifts):
        for j, time_shift in enumerate(time_shifts):
            # Syntetyczna funkcja BER w zależności od przesunięcia czasu i amplitudy
            ber[i, j] = np.exp(-(time_shift**2 + amp_shift**2)) * (1 + 0.1 * np.random.randn())

    # Normalizacja do zakresu od 0 do 1
    ber = (ber - np.min(ber)) / (np.max(ber) - np.min(ber))
    return ber

# Parametry diagramu oka
time_shifts = np.linspace(-0.5, 0.5, 128)
amplitude_shifts = np.linspace(-1, 1, 128)

# Generowanie danych BER
ber_data = generate_ber_data(time_shifts, amplitude_shifts)

# Tworzenie heatmapy
plt.figure(figsize=(10, 8))
sns.heatmap(ber_data, cmap='hot', cbar_kws={'label': 'BER'}, xticklabels=np.round(time_shifts, 2), yticklabels=np.round(amplitude_shifts, 2))
plt.xlabel('Time Shift')
plt.ylabel('Amplitude Shift')
plt.title('Heatmapa BER')
#plt.show()


# Tworzenie wykresu konturowego
plt.figure(figsize=(10, 8))
contour_levels = [0.5]
contour = plt.contour(time_shifts, amplitude_shifts, ber_data, levels=contour_levels, colors='blue')
plt.clabel(contour, inline=1, fontsize=10)
plt.xlabel('X')
plt.ylabel('Y')
plt.title('Kontur - Diagram Oka')
plt.grid(True)
plt.show()