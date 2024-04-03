import string
import re

def parse_text(input_file, output_file):
    try:
        with open(input_file, 'r') as file:
            text = file.read()
            # Удаляем знаки препинания
            translator = str.maketrans('', '', string.punctuation)
            text = text.translate(translator)
            # Удаляем числа и специальные символы
            text = re.sub(r'[\d\W_]+', ' ', text)
            # Разделяем текст на слова
            words = text.split()
            # Записываем слова в новый файл
            with open(output_file, 'w') as out_file:
                for word in words:
                    out_file.write(word + '\n')
            print("Текст успешно записан в файл:", output_file)
    except FileNotFoundError:
        print("Файл не найден.")

input_file_path = 'start_text.txt'
output_file_path = 'finish_text.txt'
parse_text(input_file_path, output_file_path)
