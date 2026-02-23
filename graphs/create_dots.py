import subprocess
import csv


def exec_lab(args):
    try:
        result = subprocess.run(
            args,
            capture_output=True,  # Перехватить вывод (stdout и stderr)
            text=True,            # Декодировать байты в строку (автоматически utf-8)
            check=True            # Вызвать ошибку, если C-программа вернет не 0
        )
        return result.stdout
    except subprocess.CalledProcessError as e:
        print(f"Ошибка выполнения C-программы (код {e.returncode}).")
        print("Вывод ошибки (stderr):", e.stderr)

    except FileNotFoundError:
        print(f"Файл {executable_path} не найден.")
    return ""


sort_type = 1
arrays = 100
elements = 1000
field = 2
executable_path = "./lab6"

args = [executable_path, "-i", "-m", "-s", str(sort_type), "-a", str(arrays), "-e", str(elements), "-f", str(field)]

# print(*args)

# print(exec_lab(args))

dct = {0: [], 1: [], 2: []}

for sort_type in range(3):
    for elements in range(10, 1000, 10):
        args = [executable_path, "-im", "-s", str(sort_type), "-a", str(arrays), "-e", str(elements), "-f", str(field)]
        output = exec_lab(args).split('\n')[-3:-1]
        dot = [output[1].split()[1], output[0].split()[1].replace('.', ',')]
        dct[sort_type].append(dot)
        # break

with open('tables/dots1.csv', 'w', newline='', encoding='utf-8-sig') as f:
    writer = csv.writer(f, delimiter=';')
    writer.writerows(dct[0])


with open('tables/dots2.csv', 'w', newline='', encoding='utf-8-sig') as f:
    writer = csv.writer(f, delimiter=';')
    writer.writerows(dct[1])


with open('tables/dots3.csv', 'w', newline='', encoding='utf-8-sig') as f:
    writer = csv.writer(f, delimiter=';')
    writer.writerows(dct[2])

#
# with open('dots1.csv', 'w') as f:
#     f.write('\n'.join(dct[0]))
#
# with open('dots2.csv', 'w') as f:
#     f.write('\n'.join(dct[1]))
#
# with open('dots3.csv', 'w') as f:
#     f.write('\n'.join(dct[2]))

print(*dct[0], sep='\n')

print(*dct[1], sep='\n')

print(*dct[2], sep='\n')


