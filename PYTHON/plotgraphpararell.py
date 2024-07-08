import threading
import matplotlib.pyplot as plt
from queue import Queue

def input_and_print():
    while True:
        user_input = input("Wątek 1 - Wpisz coś: ")
        print(f"Wątek 1 - Wpisałeś: {user_input}")

def plot_graph(queue):
    def plot_thread():
        fig, ax = plt.subplots()
        ax.plot([1, 2, 3], [4, 5, 6])
        ax.set_title('Wykres')

        # Wyświetlenie wykresu bez blokowania głównego wątku
        plt.show()

    # Umieszczamy funkcję plot_thread w kolejce do uruchomienia w głównym wątku
    queue.put(plot_thread)

if __name__ == "__main__":
    # Tworzymy kolejkę do komunikacji między wątkami
    queue = Queue()

    # Tworzenie wątku dla funkcji input_and_print
    thread1 = threading.Thread(target=input_and_print)
    thread1.start()

    # Uruchamiamy funkcję plot_graph() w osobnym wątku
    thread_plot = threading.Thread(target=plot_graph, args=(queue,))
    thread_plot.start()

    print('Dalej wykonuję instrukcje programu.')

    # Pobieramy funkcję plot_thread z kolejki i uruchamiamy ją w głównym wątku
    plot_function = queue.get()
    plot_function()

    # Można dodać tutaj inne instrukcje programu, które mają być wykonywane równocześnie z wykresem

    # Czekamy na zakończenie wątku z wykresem
    thread_plot.join()

    print('Program kończy działanie.')
