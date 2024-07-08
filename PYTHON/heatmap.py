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

def interpolate_ber_data(ber_data, time_shifts, amplitude_shifts):
    # Ustalanie nowych wartości x i y dla interpolacji
    new_time_shifts = np.linspace(-0.5, 0.5, 300)
    new_amplitude_shifts = np.linspace(-1, 1, 300)

    # Tworzenie siatki
    X, Y = np.meshgrid(time_shifts, amplitude_shifts)
    new_X, new_Y = np.meshgrid(new_time_shifts, new_amplitude_shifts)

    # Interpolacja danych BER
    interpolator = interpolate.interp2d(X, Y, ber_data, kind='cubic')
    interpolated_ber = interpolator(new_time_shifts, new_amplitude_shifts)

    return interpolated_ber, new_time_shifts, new_amplitude_shifts

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

# Tworzenie wykresu konturowego
# Interpolacja danych BER
interpolated_ber, new_time_shifts, new_amplitude_shifts = interpolate_ber_data(ber_data, time_shifts, amplitude_shifts)

# Tworzenie wykresu konturowego z interpolacją
plt.figure(figsize=(10, 8))
contour_levels = np.linspace(0.4, 0.6, 11)  # Poziomy od 0.4 do 0.6 z krokiem 0.02
contour = plt.contourf(new_time_shifts, new_amplitude_shifts, interpolated_ber, levels=contour_levels, cmap='Blues')
plt.colorbar(contour, label='BER', orientation='horizontal')
plt.xlabel('Time Shift')
plt.ylabel('Amplitude Shift')
plt.title('Kontur - Diagram Oka z interpolacją')
plt.show()