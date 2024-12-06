

TW = ["read", "write", "if", "then", "else", "for", "to", "while", "do", "true", "false", "or", "and", "not", "as"]
TL = [",", ";", ".", ":", "(", ")", "{", "}", "[", "]"]
TI = ["sum", "x", "y", "var1"]
TN = ["1", "100", "99", "42"]
Operators = [":", ":="]

Bin_num = ['1', '0', 'B', 'b']
Oct_num = ['0', '1', '2', '3', '4', '5', '6', '7', 'O', 'o']
Dec_num = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'D', 'd']
Hex_num = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
           'A', 'B', 'C', 'D', 'E', 'F', 'a', 'b', 'c', 'd', 'e', 'f', 'H', 'h']
real_num = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'e', 'E']

written_lexems = set()

def out(n, k, lexem_value, token_name, filename="lexems.txt"):
    lexem = (n, k)
    if lexem not in written_lexems:
        with open(filename, "a") as file:
            file.write(f"out({n}, {k})\n")
        written_lexems.add(lexem)
        print(f"out({n}, {k}) записано в файл {filename}")
    else:
        print(f"out({n}, {k}) уже записано - пропускаем!")
    print(f"TOKEN name: {token_name}, TOKEN value: {lexem_value}")

#------------------------------------------------------------------------------------------------------------------------------------------------

def lexical_analysis():
    def get_unique_input(prompt, used_values, allow_duplicates=False):
        while True:
            value = input(prompt).strip()
            if allow_duplicates or value not in used_values:
                used_values.add(value)
                return value
            print(f"!ошибка: символ '{value}' уже занят! введите другой!")

    used_values = set()

    output_symbol = get_unique_input("введите символ, который будет выходным - наприме  р : '}': ", used_values)
    comment_start = get_unique_input("введите символ начала комментария -н апример : '/': ", used_values, allow_duplicates=True)
    comment_end = get_unique_input("введите символ конца комментария - например : '*': ", used_values, allow_duplicates=True)
    transition_symbol = get_unique_input("введите связующий символ между C1, C2 и C3 = например : 'A': ", used_values)

    m1_symbols = input("введите символы для M1 - например : '< <= !=': ").split()
    for symbol in m1_symbols:
        get_unique_input(f"проверка символа '{symbol}' для M1: ", used_values)

    m2_symbols = input("введите символы для M2 - например : '> >=': ").split()
    for symbol in m2_symbols:
        get_unique_input(f"проверка символа '{symbol}' для M2: ", used_values)

    operations_input = input("введите символы для группы операций (сложение вычитание дизъюнкция): ").split()

    if len(operations_input) < 3:
        print("!Ошибка: введите как минимум три символа (сложение, вычитание, дизъюнкция).")
        return
    for symbol in operations_input:
        get_unique_input(f"проверка символа '{symbol}' для операций: ", used_values)

    operation_tokens = {
        'сложение': operations_input[0],
        'вычитание': operations_input[1],
        'дизъюнкция': operations_input[2]
    }

    print("!распознанные операции:")
    for operation, token in operation_tokens.items():
        print(f"{operation}: {token}")

    #------------------------------------------------------------------------------------------------------------------------------------------------

    operations_input_multiplication = input("введите символы для группы операций (умножение, деление, конъюнкция): ").split()
    if len(operations_input_multiplication) < 3:
        print("ошибка: введите как минимум три символа (умножение, деление, конъюнкция)")
        return
    for symbol in operations_input_multiplication:
        get_unique_input(f"Проверка символа '{symbol}' для операций умножения: ", used_values)

    operation_tokens_multiplication = {
        'умножение': operations_input_multiplication[0],
        'деление': operations_input_multiplication[1],
        'конъюнкция': operations_input_multiplication[2]
    }

    print("!распознанные операции:")
    for operation_multiplication, token_multiplication in operation_tokens_multiplication.items():
        print(f"{operation_multiplication}: {token_multiplication}")

    print("\n!!все входные данные успешно введены и проверены на уникальность")


    #------------------------------------------------------------------------------------------------------------------------------------------------

    input_string = input("!введите строку для анализа: ")

    buffer = ""#буфер - формирование слов
    state = "H"#begin состояние

    for char in input_string:
        if char == output_symbol:
            print(f"!обнаружен выходной символ: {output_symbol} - завершение анализа!")
            break

        if state == "H":
            if char == comment_start:
                state = "C1"
                print(f"!переход в состояние C1: найден символ начала комментария '{comment_start}'")

            elif char == '0' or char == '1':
                buffer += char
            elif char != ' ':  
                buffer += char
            else:#если встретили пробел - обрабатываем буферр
                if buffer:
                    process_lexeme(buffer, m1_symbols, m2_symbols, operation_tokens, operation_tokens_multiplication)
                    buffer = ""#clear буфер

        elif state == "C1":
            if char == comment_end:
                state = "H" 
                print(f"коммент end - возврат в состояние H")
            elif char == transition_symbol:
                state = "C2" 
                print(f"!переход в состояние C2: найден символ '{transition_symbol}'")
            else:
                print(f"считываем символ в состоянии C1: {char}")

        elif state == "C2":
            if char == comment_end:
                state = "H" 
                print(f"коммент end - возврат в состояние H")
            elif char == transition_symbol:
                state = "C3"  
                print(f"!переход в состояние C3: найден символ '{transition_symbol}'")
            else:
                print(f"считываем символ в состоянии C2: {char}")

        elif state == "C3":
            if char == transition_symbol:
                state = "H" 
                print(f"!переход в состояние H: найден символ '{transition_symbol}'")
            else:
                print(f"считываем символ в состоянии C3: {char}")
            if char == comment_end:
                state = "H" 
                print(f"коммент end - возврат в состояние H")

    #clear буфер - если что то осталось
    if buffer:
        process_lexeme(buffer, m1_symbols, m2_symbols, operation_tokens, operation_tokens_multiplication)

def process_lexeme(buffer, m1_symbols, m2_symbols, operation_tokens, operation_tokens_multiplication):
    print(f"\n!!!обрабатываем лексему: {buffer}")

    if buffer in TW:#служебное слово
        z = TW.index(buffer) + 1
        out(1, z, buffer, "KWORD")

    elif buffer in TL:#ограничитель
        z = TL.index(buffer) + 1
        out(2, z, buffer, "DELIM")

    #elif buffer.isdigit():#проверка на число
    #    if buffer not in TN:
    #        TN.append(buffer)
    #    z = TN.index(buffer) + 1
    #    out(4, z, buffer, "NUM")

    elif (
            buffer.replace('.', '', 1).isdigit() or
            (buffer.startswith('-') and buffer[1:].replace('.', '', 1).isdigit())
    ) and buffer.count('.') == 1:
        parts = buffer.split('.')
        whole_part = parts[0]
        fractional_part = parts[1] if len(parts) > 1 and parts[1] else None
        if fractional_part == "0":
            if whole_part not in TN:
                TN.append(whole_part)
            z = TN.index(whole_part) + 1
            out(4, z, buffer, "P1")
        else:
            if buffer not in TN:
                TN.append(buffer)
            z = TN.index(buffer) + 1
            out(4, z, buffer, "P2")

    elif buffer in Operators:#oператоры
        z = Operators.index(buffer) + 1
        out(5, z, buffer, "OPER")

    elif buffer in m1_symbols:#M1 операторы
        z = m1_symbols.index(buffer) + 1
        out(6, z, buffer, "M1")

    elif buffer in m2_symbols:#M2 операторы
        z = m2_symbols.index(buffer) + 1
        out(7, z, buffer, "M2")

    elif buffer in operation_tokens.values():#символы операций : сложение, вычитание, дизъюнкция
        operation_name = [key for key, value in operation_tokens.items() if value == buffer][0]
        z = list(operation_tokens.values()).index(buffer) + 1
        out(8, z, buffer, f"OPER ({operation_name})")

    elif buffer in operation_tokens_multiplication.values():#символы умножений деление конъюнкция
        operation_name_multiplication = [key for key, value in operation_tokens_multiplication.items() if value == buffer][0]
        z = list(operation_tokens_multiplication.values()).index(buffer) + 1
        out(8, z, buffer, f"OPER ({operation_name_multiplication})")

    elif buffer[0].isalpha():#идентификатор
        if buffer not in TI:#чек - что идентификатор в допустимом списке
            print(f"ошибка: {buffer} - неизвестная лексема")
        else:
            if buffer not in TI:
                TI.append(buffer)
            z = TI.index(buffer) + 1
            out(3, z, buffer, "IDENT")

    elif buffer[0] in "01" and (buffer[-1] == 'b' or buffer[-1] == 'B') and all(c in "01" for c in buffer[:-1]):
        z = 8#примерный индекс
        out(4, z, buffer, "BIN")

    elif all(c in "01234567" for c in buffer[:-1]) and (buffer[-1].lower() == 'o') or all(c in "01234567" for c in buffer[:-1]) and (buffer[-1].lower() == 'O'):
        z = 9#примерный индекс
        out(4, z, buffer, "OCT")

    elif (all(c in "0123456789" for c in buffer[:-1]) and buffer[-1].lower() == 'd') or buffer.isdigit():
        z = 10#примерный индекс
        out(4, z, buffer, "DEC")

    elif buffer[0] in "0123456789" and all(c in "0123456789ABCDEFabcdef" for c in buffer[1:-1]) and (buffer[-1].lower() == 'h'):
        z = 16#примерный индекс числа
        out(4, z, buffer, "HEX")

    else:
        print(f"неизвестная лексема: {buffer}")

def is_binary_number(buffer):
    if all(c in '01' for c in buffer[:-1]) and (buffer[-1].lower() == 'b' or buffer[-1] == ''):
        return True
    return False

lexical_analysis()




#баг !введите строку для анализа: 5D 9O 45 1e+1

!!!обрабатываем лексему: 5D #верно
out(4, 10) записано в файл lexems.txt
TOKEN name: DEC, TOKEN value: 5D

!!!обрабатываем лексему: 9O #верно так как 01234567
неизвестная лексема: 9O

!!!обрабатываем лексему: 45 #верно
out(4, 5) записано в файл lexems.txt
TOKEN name: NUM, TOKEN value: 45

!!!обрабатываем лексему: 1e+1#отработать
неизвестная лексема: 1e+1

