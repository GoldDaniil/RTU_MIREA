import re

constants = {}#словарь - значения констант

def read_input():#читаем текст построчно
    input_lines = []
    while True:
        line = input()
        if line.strip().lower() == 'end':
            break
        input_lines.append(line)
    return "\n".join(input_lines)

def check_syntax(input_text):#проверка синтаксиса входного текста
    tag_stack = []
    for line in input_text.splitlines():
        line = line.strip()

        if line.startswith("*") or line.startswith("{{!") or line.endswith("}}"):#пропуск комментов
            continue

        if match := re.match(r"'\(.*\)'", line):#проверка синтаксис массивов
            array_content = match.group(0)[2:-2].strip()#извлекаем
            elements = array_content.split()#разделяем элементы
            for element in elements:
                if not re.match(r"^\d+(\.\d+)?$", element) and not re.match(r"^\".*\"$", element):
                    raise SyntaxError(f"ошибка синтаксиса - неверное значение в массиве: {element}")

        elif match := re.match(r"^[a-z][a-z0-9_]*$", line):#проверка имен
            continue

        elif re.match(r"^\d+(\.\d+)?$", line):#проверка чисел и строк
            continue

        elif match := re.match(r"^\".*\"$", line):#если строка
            continue

        elif re.match(r"\[\[.*\]\]", line):#проверка на формат
            continue

        open_tags = re.findall(r"<(\w+)>", line)#проверка xml тегов
        close_tags = re.findall(r"</(\w+)>", line)

        for tag in open_tags:#закрыт открыт теги
            tag_stack.append(tag)
        for tag in close_tags:
            if not tag_stack or tag_stack.pop() != tag:
                raise SyntaxError(f"ошибка синтаксиса - неверный закрывающий тег </{tag}>")

    if tag_stack:  # теги остались в стеке
        raise SyntaxError(f"ошибка синтаксиса - незакрытые теги: {tag_stack}")

    return True

def transform_to_output_format(input_text):#входной текст - выходной текст
    output = []
    indent = 0
    for line in input_text.splitlines():
        line = line.strip()

        if line.startswith("*") or line.startswith("{{!") or line.endswith("}}"):#пропуск комментов
            output.append(line)

        elif re.match(r"\[\[(.*)\]\]", line):#строка - формат
            match = re.match(r"\[\[(.*)\]\]", line)
            output.append(f"string: \"{match.group(1)}\"")

        elif line.startswith("<array>") and line.endswith("</array>"):#массив - формат
            array_content = line[len("<array>"):-len("</array>")].strip()#внутри тега 

            array_content = array_content.strip("'()\"")#убираем скобки - кавычки
            formatted_elements = []

            i = 0
            while i < len(array_content):
                char = array_content[i]

                if char == " ":#скип лишние
                    formatted_elements.append(" ")
                    i += 1
                    continue

                if char.isdigit() or (char == "." and i + 1 < len(array_content) and array_content[i + 1].isdigit()):#если цифру или точку
                    num_start = i
                    while i < len(array_content) and (array_content[i].isdigit() or array_content[i] == "."):
                        i += 1
                    formatted_elements.append(array_content[num_start:i])
                    continue

                if char == "\"":#буквы
                    str_start = i
                    i += 1
                    while i < len(array_content) and array_content[i] != "\"":
                        i += 1
                    i += 1#скип завершающую кавычку
                    formatted_elements.append(f"\"{array_content[str_start + 1:i - 1]}\"")#с кавычками
                    continue

                i += 1

            output.append(f"array: {' '.join(formatted_elements)}")

        elif re.match(r"^[a-z][a-z0-9_]*$", line):#имена
            output.append(f"name: {line}")

        elif re.match(r"^\d+(\.\d+)?$", line):#числа - строки
            output.append(f"number: {line}")

        elif match := re.match(r"^\"(.*)\"$", line):#строка
            output.append(f"string: \"{match.group(1)}\"")

        elif match := re.match(r"^def (\w+) (.+);$", line):#обьявление конст
            name, value = match.groups()
            constants[name] = value
            output.append(f"constant declared: {name} = {value}")

        elif match := re.match(r"^\$(\w+)\$", line):#выч конст
            name = match.group(1)
            if name in constants:
                output.append(f"constant value: {constants[name]}")
            else:
                output.append(f"error - constant {name} not defined")

        elif match := re.match(r"<(\w+)>(.*?)</\1>", line):#xml - конф формат
            tag, value = match.groups()
            output.append(f"{'  ' * indent}{tag}: {value}")
        elif match := re.match(r"<(\w+)>", line):#открывающий тег
            tag = match.group(1)
            output.append(f"{'  ' * indent}{tag}:")
            indent += 1
        elif re.match(r"</(\w+)>", line):#закрывающий тег
            indent -= 1

    return "\n".join(output)

def main():
    try:
        print("введи текст конфигурации - для завершения ввода введи 'end':")
        input_text = read_input()

        check_syntax(input_text)

        output_text = transform_to_output_format(input_text)#преобразование

        print("выходной текст:\n")
        print(output_text)

    except SyntaxError as e:
        print(f"ошибка синтаксиса - {e}")
    except Exception as e:
        print(f"произошла ошибка - {e}")

if __name__ == "__main__":
    main()
