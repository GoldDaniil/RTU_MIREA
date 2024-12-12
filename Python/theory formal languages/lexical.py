import re

TW = ["read", "write", "if", "then", "else", "for", "to", "while", "do", "true", "false", "or", "and", "not", "as", "int", "float", "bool", "end", "begin", "next", "writeln", "readln"]
TL = [",", ";", ".", ":", "(", ")", "{", "}", "[", "]"]
TI = ["sum", "x", "y", "var1"]
TN = ["1", "100", "99", "42"]
Operators = [":", ":=", "+", "-", "*", "/", "==", "!=", "<", ">", "<=", ">=", "="]

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
                    if is_real_number(buffer):
                        process_lexeme(buffer, m1_symbols, m2_symbols, operation_tokens, operation_tokens_multiplication)
                    else:
                        process_lexeme(buffer, m1_symbols, m2_symbols, operation_tokens, operation_tokens_multiplication)
                    buffer = ""

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

    pattern = r'([\(\),;])\s*([a-zA-Z_][a-zA-Z0-9_]*)|([a-zA-Z_][a-zA-Z0-9_]*)\s*([\(\),;])'
    match = re.match(pattern, buffer)

    if match:
        if match.group(1) and match.group(2):
            tl_token = match.group(1)
            ident_token = match.group(2)

            if tl_token not in TL:
                TL.append(tl_token)
            z_tl = TL.index(tl_token) + 1
            out(2, z_tl, tl_token, "TL")

            if ident_token not in TI:
                TI.append(ident_token)
            z_ident = TI.index(ident_token) + 1
            out(3, z_ident, ident_token, "IDENT")

        elif match.group(3) and match.group(4):
            ident_token = match.group(3)
            tl_token = match.group(4)

            if ident_token not in TI:
                TI.append(ident_token)
            z_ident = TI.index(ident_token) + 1
            out(3, z_ident, ident_token, "IDENT")

            if tl_token not in TL:
                TL.append(tl_token)
            z_tl = TL.index(tl_token) + 1
            out(2, z_tl, tl_token, "TL")

        return

    pattern_dec_tl = r'([^\w\s])\s*(\d+)|(\d+)\s*([^\w\s])|(\d+)\s*([^\w\s])([^\w\s])'
    match = re.match(pattern_dec_tl, buffer)

    if match:
        if match.group(1) and match.group(2):
            tl_token = match.group(1)
            dec_token = match.group(2)

            if tl_token not in TL:
                TL.append(tl_token)
            z_tl = TL.index(tl_token) + 1
            out(2, z_tl, tl_token, "TL")

            if dec_token not in TN:
                TN.append(dec_token)
            z_dec = TN.index(dec_token) + 1
            out(4, z_dec, dec_token, "DEC")

        elif match.group(3) and match.group(4):
            dec_token = match.group(3)
            tl_token = match.group(4)

            if dec_token not in TN:
                TN.append(dec_token)
            z_dec = TN.index(dec_token) + 1
            out(4, z_dec, dec_token, "DEC")

            if tl_token not in TL:
                TL.append(tl_token)
            z_tl = TL.index(tl_token) + 1
            out(2, z_tl, tl_token, "TL")

        elif match.group(5) and match.group(6) and match.group(7):
            dec_token = match.group(5)
            tl_token1 = match.group(6)
            tl_token2 = match.group(7)

            if dec_token not in TN:
                TN.append(dec_token)
            z_dec = TN.index(dec_token) + 1
            out(4, z_dec, dec_token, "DEC")

            if tl_token1 not in TL:
                TL.append(tl_token1)
            z_tl1 = TL.index(tl_token1) + 1
            out(2, z_tl1, tl_token1, "TL")

            if tl_token2 not in TL:
                TL.append(tl_token2)
            z_tl2 = TL.index(tl_token2) + 1
            out(2, z_tl2, tl_token2, "TL")

        return

    pattern_oper_dec_tl = r'([^\w\s])\s*(\d+)\s*([^\w\s])'
    match = re.match(pattern_oper_dec_tl, buffer)

    if match:
        operator_token = match.group(1)
        dec_token = match.group(2)
        tl_token = match.group(3)

        if operator_token in operation_tokens:
            z_operator = operation_tokens.index(operator_token) + 1
            out(8, z_operator, operator_token, "OPER")

        if dec_token not in TN:
            TN.append(dec_token)
        z_dec = TN.index(dec_token) + 1
        out(4, z_dec, dec_token, "DEC")

        if tl_token not in TL:
            TL.append(tl_token)
        z_tl = TL.index(tl_token) + 1
        out(2, z_tl, tl_token, "TL")

        return

    #------------------------------------------------------------------------------------------------------------------------------------------------

        pattern_tw_tl_ident_op_ident = r'([a-zA-Z_][a-zA-Z0-9_]*)\s*([\(\)])\s*([a-zA-Z_][a-zA-Z0-9_]*)\s*([\+\-\*/])\s*([a-zA-Z_][a-zA-Z0-9_]*)'
        match = re.match(pattern_tw_tl_ident_op_ident, buffer)

        if match:
            tw_token = match.group(1)
            tl_token = match.group(2)
            ident1 = match.group(3)
            operator = match.group(4)
            ident2 = match.group(5)

            if tw_token not in TW:
                TW.append(tw_token)
            z_tw = TW.index(tw_token) + 1
            out(1, z_tw, tw_token, "TW")

            if tl_token not in TL:
                TL.append(tl_token)
            z_tl = TL.index(tl_token) + 1
            out(2, z_tl, tl_token, "TL")

            if ident1 not in TI:
                TI.append(ident1)
            z_ident1 = TI.index(ident1) + 1
            out(3, z_ident1, ident1, "IDENT")

            if operator in operation_tokens:
                z_operator = operation_tokens.index(operator) + 1
                out(8, z_operator, operator, "OPER")

            # IDENT 2
            if ident2 not in TI:
                TI.append(ident2)
            z_ident2 = TI.index(ident2) + 1
            out(3, z_ident2, ident2, "IDENT")

            return

    #------------------------------------------------------------------------------------------------------------------------------------------------

    #IDENTOPERREALDELIM
    if ":=" in buffer:
        match = re.match(r'^([a-zA-Z_][a-zA-Z0-9_]*)\s*(:=)\s*([+-]?\d*\.?\d+(?:[eE][+-]?\d+)?)\s*([,;])$', buffer)
        if match:
            ident = match.group(1)
            operator = match.group(2)
            real_number = match.group(3)
            delim = match.group(4)

            if ident not in TI:  
                TI.append(ident)
            z_ident = TI.index(ident) + 1
            out(3, z_ident, ident, "IDENT")

            if operator == ":=":
                z_operator = Operators.index(":=")  
                out(8, z_operator, operator, "OPER (assign)")

            if real_number not in TN:
                TN.append(real_number)
            z_real = TN.index(real_number) + 1
            out(4, z_real, real_number, "REAL")

            if delim in TL:
                z_delim = TL.index(delim) + 1
                out(2, z_delim, delim, "DELIM")
            return

    if buffer in TW:#служебное слово
        z = TW.index(buffer) + 1
        out(1, z, buffer, "KWORD")

    elif buffer in TL:#ограничитель
        z = TL.index(buffer) + 1
        out(2, z, buffer, "DELIM")

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

    elif re.fullmatch(r'[a-zA-Z_][a-zA-Z0-9_]*', buffer):
        if buffer not in TI:
            TI.append(buffer)
        z = TI.index(buffer) + 1
        out(3, z, buffer, "IDENT")

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

    elif is_real_number(buffer):
        if buffer not in TN:
            TN.append(buffer)
        z = TN.index(buffer) + 1
        out(4, z, buffer, "REAL")

    else:
        print(f"неизвестная лексема: {buffer}")

def is_binary_number(buffer):
    if all(c in '01' for c in buffer[:-1]) and (buffer[-1].lower() == 'b' or buffer[-1] == ''):
        return True
    return False

def is_real_number(string):
    if not string:
        return False

    index = 0
    length = len(string)

    if index < length and string[index].isdigit():
        index = check_numeric_part(string, index)

    if index < length and string[index] == '.':
        index += 1
        if index < length and string[index].isdigit():
            index = check_numeric_part(string, index)
        else:
            return False

    if index < length and string[index] in {'E', 'e'}:
        index += 1
        if index < length and string[index] in {'+', '-'}:
            index += 1
        if index < length and string[index].isdigit():
            index = check_numeric_part(string, index)
        else:
            return False

    return index == length

def check_numeric_part(string, index):
    while index < len(string) and string[index].isdigit():
        index += 1
    return index

def is_identifier(buffer):
    identifier_pattern = r"^[a-zA-Z_][a-zA-Z0-9_]*$"
    return re.match(identifier_pattern, buffer) is not None

lexical_analysis()
