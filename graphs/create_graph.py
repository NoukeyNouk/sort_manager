import pandas as pd
import matplotlib.pyplot as plt
import os

dct = {'tables/dots1.csv': 'comb sort',
       'tables/dots2.csv': 'selection sort',
       'tables/dots3.csv': 'quick sort'}
# --- НАСТРОЙКИ ---
FILES = ['tables/dots1.csv', 'tables/dots2.csv', 'tables/dots3.csv'] # Список файлов
COLORS = ['blue', 'green', 'red']                # Цвета для линий
Y_MIN = 0                                        # Минимум по Y (None для авто)
Y_MAX = 0.0006                                  # Максимум по Y (None для авто)
DELIMITER = ';'                                  # Разделитель в CSV
DECIMAL = ','                                    # Разделитель дроби
# -----------------

def process_graphs():
    # 1. Сначала строим индивидуальные графики
    for i, filename in enumerate(FILES):
        if not os.path.exists(filename):
            print(f"Файл {filename} не найден, пропускаем.")
            continue
            
        # Чтение данных
        df = pd.read_csv(filename, sep=DELIMITER, decimal=DECIMAL, header=None, names=['X', 'Y'])
        
        # Настройка рисунка
        plt.figure(figsize=(8, 5))
        plt.plot(df['X'], df['Y'], marker='o', linestyle='-', color=COLORS[i % len(COLORS)])
        
        plt.title(f'График: {dct[filename]}')
        plt.xlabel('Аргумент (X)')
        plt.ylabel('Функция (Y)')
        plt.grid(True)
        
        # Установка границ, если заданы
        if Y_MIN is not None and Y_MAX is not None:
            plt.ylim(Y_MIN, Y_MAX)
            
        # Сохранение
        output_name = filename.replace('.csv', '.png').replace('tables', 'graphs')
        plt.savefig(output_name)
        plt.close() # Закрываем, чтобы очистить память
        print(f"Сохранен график: {output_name}")

    # 2. Теперь строим ОБЩИЙ график
    plt.figure(figsize=(10, 6))
    
    found_any = False
    for i, filename in enumerate(FILES):
        if not os.path.exists(filename): continue
        found_any = True
        
        df = pd.read_csv(filename, sep=DELIMITER, decimal=DECIMAL, header=None, names=['X', 'Y'])
        # label=filename добавляет имя файла в легенду
        plt.plot(df['X'], df['Y'], marker='o', linestyle='-', 
                 color=COLORS[i % len(COLORS)], label=dct[filename])

    if found_any:
        plt.title('Сводный график всех файлов')
        plt.xlabel('Аргумент (X)')
        plt.ylabel('Функция (Y)')
        plt.grid(True)
        plt.legend() # Показать легенду с именами файлов
        
        if Y_MIN is not None and Y_MAX is not None:
            plt.ylim(Y_MIN, Y_MAX)
            
        plt.savefig('graphs/combined_plot.png')
        print("Сохранен общий график: combined_plot.png")
    else:
        print("Нет данных для общего графика.")

if __name__ == "__main__":
    process_graphs()
