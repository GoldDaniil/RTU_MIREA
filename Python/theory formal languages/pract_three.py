RESERVED_WORDS = {
    "read": 1, "write": 2, "if": 3, "then": 4, "else": 5, "for": 6, "to": 7,
    "while": 8, "do": 9, "true": 10, "false": 11, "or": 12, "and": 13, "not": 14, "as": 15
}

DELIMITERS = {
    "{": 1, "}": 2, "%": 3, "!": 4, "$": 5, ",": 6, ";": 7, "[": 8, "]": 9,
    ":": 10, "(": 11, ")": 12, "+": 13, "-": 14, "*": 15, "/": 16, "=": 17,
    "<>": 18, ">": 19, "<": 20, "<=": 21, ">=": 22, "/*": 23, "*/": 24
}

def is_letter(ch):
    return ch.isalpha()

def is_digit(ch):
    return ch.isdigit()

def is_hex_digit(ch):
    return ch in "0123456789ABCDEFabcdef"

class LexerState:
    def __init__(self):
        self.current_state = "H"
        self.buffer = ""
        self.current_char = None
        self.position = 0
        self.input_text = ""
        self.output = []

    def set_input(self, input_text):
        self.input_text = input_text + "\n" 
        self.position = 0

    def get_char(self):
        if self.position < len(self.input_text):
            self.current_char = self.input_text[self.position]
            self.position += 1
        else:
            self.current_char = None

    def add_to_buffer(self):
        self.buffer += self.current_char

    def clear_buffer(self):
        self.buffer = ""

    def out(self, table, index):
        self.output.append((table, index))

    def look(self, table):
        if self.buffer in table:
            return table[self.buffer]
        return 0

    def put(self, table):
        if self.buffer not in table:
            table[self.buffer] = len(table) + 1
        return table[self.buffer]

def lexical_analysis(input_text):
    state = LexerState()
    state.set_input(input_text)

    while state.current_state != "V":
        state.get_char()
        
        if state.current_state == "H":
            if state.current_char is None:
                break  
            if state.current_char.isspace():
                continue  
            elif is_letter(state.current_char):
                state.clear_buffer()
                state.add_to_buffer()
                state.current_state = "I"
            elif state.current_char == "{":
                state.out(2, DELIMITERS["{"])
            elif state.current_char == "}":
                state.out(2, DELIMITERS["}"])
            elif state.current_char == "/":
                state.current_state = "C1"
            elif state.current_char == "<":
                state.current_state = "M1"
            elif state.current_char == ">":
                state.current_state = "M2"
            elif is_digit(state.current_char):
                if state.current_char in "01":
                    state.current_state = "N2"
                elif state.current_char in "234567":
                    state.current_state = "N8"
                elif state.current_char in "89":
                    state.current_state = "N10"
            elif state.current_char in "ABCDEFabcdef":
                state.current_state = "N16"
            elif state.current_char in "Ee":
                state.current_state = "E11"
            elif state.current_char == "*":
                state.current_state = "P1"

        elif state.current_state == "I":
            if is_letter(state.current_char) or is_digit(state.current_char):
                state.add_to_buffer()
            else:
                z = state.look(RESERVED_WORDS)
                if z != 0:
                    state.out(1, z)
                else:
                    z = state.put(RESERVED_WORDS)#или таблица идентификаторов
                    state.out(4, z)
                state.current_state = "H"

        elif state.current_state == "C1":
            if state.current_char == "*":
                state.current_state = "C2"
            else:
                state.out(2, DELIMITERS["/"])
                state.current_state = "H"

        elif state.current_state == "C2":
            if state.current_char == "*":
                state.current_state = "C3"
            elif state.current_char is None:
                raise ValueError("... EOF in comment")
            else:
                state.current_state = "C2"

        elif state.current_state == "C3":
            if state.current_char == "/":
                state.current_state = "H"
            elif state.current_char is None:
                raise ValueError("... EOF in comment")
            else:
                state.current_state = "C2"

        elif state.current_state == "M1":
            if state.current_char == ">":
                state.out(2, DELIMITERS["<>"])
                state.current_state = "H"
            elif state.current_char == "=":
                state.out(2, DELIMITERS["<="])
                state.current_state = "H"
            else:
                state.out(2, DELIMITERS["<"])
                state.current_state = "H"

        elif state.current_state == "M2":
            if state.current_char == "=":
                state.out(2, DELIMITERS[">="])
                state.current_state = "H"
            else:
                state.out(2, DELIMITERS[">"])
                state.current_state = "H"

        elif state.current_state == "N2":
            if state.current_char in "01":
                state.add_to_buffer()
            else:
                if all(ch in "01" for ch in state.buffer): 
                    state.out(3, int(state.buffer, 2))#бинарное значение
                else:
                    raise ValueError(f"err binary number: {state.buffer}")
                state.current_state = "H"
                state.position -= 1#возврат символа для повторной обработки

        elif state.current_state == "N8":
            if state.current_char in "01234567":
                state.add_to_buffer()
            else:
                if all(ch in "01234567" for ch in state.buffer):
                    state.out(3, int(state.buffer, 8))#восьмеричное значение
                else:
                    raise ValueError(f"err octal number: {state.buffer}")
                state.current_state = "H"

        elif state.current_state == "N10":
            if is_digit(state.current_char):
                state.add_to_buffer()
            else:
                if state.buffer.isdigit():  
                    state.out(3, int(state.buffer, 10))  
                else:
                    raise ValueError(f"err decimal number: {state.buffer}")
                state.current_state = "H"

        elif state.current_state == "N16":
            if is_hex_digit(state.current_char):
                state.add_to_buffer()
            else:
                if all(ch in "0123456789ABCDEFabcdef" for ch in state.buffer): 
                    state.out(3, int(state.buffer, 16)) 
                else:
                    raise ValueError(f"err hexadecimal number: {state.buffer}")
                state.current_state = "H"

        elif state.current_state == "E11":
            if state.current_char in "Ee":
                state.add_to_buffer()
            else:
                state.out(3, float(state.buffer))#экспоненциальная запись
                state.current_state = "H"

        elif state.current_state == "P1":
            if state.current_char == "*":
                state.add_to_buffer()
            else:
                state.out(2, DELIMITERS["*"])
                state.current_state = "H"

        elif state.current_state == "N2":
            if state.current_char in "01":
                state.add_to_buffer()
            elif state.current_char in "Bb":
                state.add_to_buffer()
                state.gc()  
                state.current_state = "B"
            elif state.current_char in "234567":
                state.add_to_buffer()
                state.gc()#переключение состояния
                state.current_state = "N8"
            elif state.current_char in "Oo":
                state.gc()
                state.current_state = "O"
            elif state.current_char in "Hh":
                state.current_state = "HX"
            elif state.current_char in "Dd":
                state.current_state = "D"
            elif state.current_char in "ABCDEFabcdef" or state.current_char in "Ff":
                state.add_to_buffer()
                state.gc() 
                state.current_state = "N16"
            elif state.current_char in "89":
                state.add_to_buffer()
                state.gc()
                state.current_state = "N10"
            elif state.current_char == "*":
                state.add_to_buffer()
                state.gc()
                state.current_state = "P1"
            elif state.current_char in "Ee":
                state.add_to_buffer()
                state.gc()
                state.current_state = "E11"
            elif state.current_char.isalpha():
                raise ValueError(f"... '{state.current_char}' in binary context")
            else:
                raise ValueError(f"err tsnst from N2 with character '{state.current_char}'")

        elif state.current_state == "B":
            if state.current_char.isalpha() and state.current_char not in "AFH":
                raise ValueError(f"err character '{state.current_char}' in state B")
            elif state.current_char in "Hh":
                state.current_state = "HX"
            elif state.current_char in "ABCDEFabcdef":
                state.add_to_buffer()
                state.gc()
                state.current_state = "N16"
            elif state.current_char in "Dd":
                state.current_state = "D"
            elif state.current_char is None:
                state.translate(2)
                state.put("TN")
                state.out(3, len(state.buffer))#вывод
                state.current_state = "H"

        elif state.current_state == "O":
            if state.current_char in "Oo":
                state.gc()
                state.current_state = "N8"
            elif state.current_char in "Dd":
                state.current_state = "D"
            elif state.current_char.isalpha() or is_digit(state.current_char):
                raise ValueError(f"err character '{state.current_char}' in state O")
            elif state.current_char in "89":
                state.add_to_buffer()
                state.gc()
                state.current_state = "N10"
            elif state.current_char in "ABCDEFabcdef":
                state.add_to_buffer()
                state.gc()
                state.current_state = "N16"
            elif state.current_char in "Ee":
                state.add_to_buffer()
                state.gc()
                state.current_state = "E11"
            elif state.current_char == "*":
                state.add_to_buffer()
                state.gc()
                state.current_state = "P1"

        elif state.current_state == "N8":
            if state.current_char in "01234567":
                state.add_to_buffer()
                state.gc()
            elif state.current_char in "Oo":
                state.gc()
                state.current_state = "O"
            elif state.current_char in "89":
                state.add_to_buffer()
                state.gc()
                state.current_state = "N10"
            elif state.current_char in "Dd":
                state.current_state = "D"
            elif state.current_char in "Hh":
                state.gc()
                state.current_state = "HX"
            elif state.current_char in "ABCDEFabcdef":
                state.add_to_buffer()
                state.gc()
                state.current_state = "N16"
            elif state.current_char in "Ee":
                state.add_to_buffer()
                state.gc()
                state.current_state = "E11"
            elif state.current_char == "*":
                state.add_to_buffer()
                state.gc()
                state.current_state = "P1"
            else:
                raise ValueError(f"err tsnst from N8 with character '{state.current_char}'")

        elif state.current_state == "N10":
            if state.current_char in "Hh":
                state.gc()
                state.current_state = "HX"
            elif state.current_char in "ABCDEFabcdef":
                state.add_to_buffer()
                state.gc()
                state.current_state = "N16"
            elif state.current_char in "Dd":
                state.current_state = "D"
            elif state.current_char in "Ee":
                state.add_to_buffer()
                state.gc()
                state.current_state = "E11"
            elif state.current_char == "*":
                state.add_to_buffer()
                state.gc()
                state.current_state = "P1"
            else:
                raise ValueError(f"err tsnst from N10 with character '{state.current_char}'")

        elif state.current_state == "D":
            if state.current_char in "89":
                state.add_to_buffer()
                state.gc()
                state.current_state = "N10"
            elif state.current_char in "Hh":
                state.gc()
                state.current_state = "HX"
            elif state.current_char in "ABCDEFabcdef":
                state.add_to_buffer()
                state.gc()
                state.current_state = "N16"
            elif state.current_char in "Ee":
                state.add_to_buffer()
                state.gc()
                state.current_state = "E11"
            elif state.current_char == "*":
                state.add_to_buffer()
                state.gc()
                state.current_state = "P1"
            else:
                raise ValueError(f"err tsnst from D with character '{state.current_char}'")
            
        elif state.current_state == "N16":
            if state.current_char in "Hh":
                state.gc()
                state.current_state = "HX"
            elif state.current_char in "ABCDEFabcdef":
                state.add_to_buffer()
                state.gc()
            else:
                raise ValueError(f"err tsnst from N16 with character '{state.current_char}'")

        elif state.current_state == "HX":
            if state.current_char.isalpha() or state.current_char.isdigit():
                state.gc()
                state.current_state = "Er"
            elif state.current_char in "Hh":
                state.gc()
                state.current_state = "N16"
            else:
                raise ValueError(f"err tsnst from HX with character '{state.current_char}'")

        elif state.current_state == "E11":
            if state.current_char.isdigit():
                state.add_to_buffer()
                state.gc()
                state.current_state = "E12"
            elif state.current_char.isalpha() or state.current_char == ".":
                state.gc()
                state.current_state = "ER"
            elif state.current_char in "+-":
                state.add_to_buffer()
                state.gc()
                state.current_state = "ZN"
            else:
                raise ValueError(f"err tsnst from E11 with character '{state.current_char}'")

        elif state.current_state == "E12":
            if state.current_char.isdigit():
                state.add_to_buffer()
                state.gc()
            elif state.current_char.isalpha() or state.current_char in "AFH":
                state.current_state = "ER"
            elif state.current_char == "H":
                state.convert()
                state.put("TN")
                state.out(3, state.buffer)
            else:
                raise ValueError(f"err tsnst from E12 with character '{state.current_char}'")

        elif state.current_state == "E13":
            if state.current_char.isdigit():
                state.add_to_buffer()
                state.gc()
            elif state.current_char.isalpha() or state.current_char in "AFH":
                state.current_state = "ER"
            elif state.current_char == "ZN":
                state.add_to_buffer()
                state.gc()
                state.current_state = "E13"
            elif state.current_char == "H":
                state.convert()
                state.put("TN")
                state.out(3, state.buffer)
            else:
                raise ValueError(f"err tsnst from E13 with character '{state.current_char}'")

        elif state.current_state == "ZN":
            if state.current_char.isdigit():
                state.add_to_buffer()
                state.gc()
                state.current_state = "E13"
            elif state.current_char.isalpha() or state.current_char in "AFH":
                state.current_state = "ER"
            elif state.current_char == "H":
                state.convert()
                state.put("TN")
                state.out(3, state.buffer)
            else:
                raise ValueError(f"err tsnst from ZN with character '{state.current_char}'")
            
        elif state.current_state == "P1":
            if state.current_char.isdigit():
                state.add_to_buffer()
                state.gc()
                state.current_state = "P2"
            else:
                state.current_state = "Er"

        #добавить еще
        elif state.current_state == "P2":
            if state.current_char.isdigit():
                state.add_to_buffer()
                state.gc()
                state.current_state = "P2"
            elif state.current_char in "Ee":
                state.add_to_buffer()
                state.gc()
                state.current_state = "E21"
            else:
                state.current_state = "Er"
                
        elif state.current_state == "E21":
            if state.current_char.isdigit():
                state.add_to_buffer()
                state.gc()
                state.current_state = "E22"
            elif state.current_char in "+-":
                state.add_to_buffer()
                state.gc()
                state.current_state = "ZN"
            elif state.current_char in "Ee":
                state.add_to_buffer()
                state.gc()
                state.current_state = "P2"
            else:
                state.current_state = "ER"
                
        elif state.current_state == "E22":
            if state.current_char.isdigit():
                state.add_to_buffer()
                state.gc()
                state.current_state = "E22"
            elif state.current_char in "Ee":
                state.add_to_buffer()
                state.gc()
                state.current_state = "E21"
            elif state.current_char == "H":
                state.convert()
                state.put("TN")
                state.out(3, state.buffer)
            elif state.current_char in "let.":
                state.current_state = "ER"
            else:
                state.current_state = "ER"
                
        elif state.current_state == "ZN":
            if state.current_char == "+":
                state.gc()
                state.out(2, state.buffer)
                state.current_state = "Z!=0"
            elif state.current_char == "-":
                state.gc()
                state.current_state = "ER"
            else:
                raise ValueError(f"err tsnst from ZN with character '{state.current_char}'")
            
        elif state.current_state == "Z!=0":
            if state.current_char == "+":
                state.gc()
                state.out(2, state.buffer)
            elif state.current_char == "-":
                state.current_state = "ER"
            else:
                raise ValueError(f"err tsnst from Z!=0 with character '{state.current_char}'")
            
        elif state.current_state == "OG":
            if state.current_char != "0":
                state.look("TL")
            else:
                raise ValueError(f"err tsnst from OG with character '{state.current_char}'")
            
        return state.output

if __name__ == "__main__":
    input_program = "a1b2c3"

    result = lexical_analysis(input_program)
    print(result)
