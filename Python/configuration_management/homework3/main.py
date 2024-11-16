import re

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

        open_tags = re.findall(r"<(\w+)>", line)#проверка xml тегов
        close_tags = re.findall(r"</(\w+)>", line)

        for tag in open_tags:#закрыт открыт теги
            tag_stack.append(tag)
        for tag in close_tags:
            if not tag_stack or tag_stack.pop() != tag:
                raise SyntaxError(f"ошибка синтаксиса - неверный закрывающий тег </{tag}>")

    if tag_stack:#теги остались в стеке
        raise SyntaxError(f"ошибка синтаксиса - незакрытые теги: {tag_stack}")

    return True

def transform_to_output_format(input_text):#входной текст - выходной текст
    output = []
    indent = 0
    for line in input_text.splitlines():
        line = line.strip()

        if line.startswith("*") or line.startswith("{{!") or line.endswith("}}"):#пропуск комментов
            output.append(line)

        elif match := re.match(r"<(\w+)>(.*?)</\1>", line):#xml - конфигурацион формат
            tag, value = match.groups()
            output.append(f"{'  ' * indent}{tag}: {value}")
        elif match := re.match(r"<(\w+)>", line):#открыт тег
            tag = match.group(1)
            output.append(f"{'  ' * indent}{tag}:")
            indent += 1
        elif re.match(r"</(\w+)>", line):#закрыт тег
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
