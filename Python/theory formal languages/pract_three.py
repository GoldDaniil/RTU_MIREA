class LexicalAnalyzer:
    def __init__(self, input_string):#инициалзция
        self.state = "H"#начальное
        self.buffer = ""#буфер = накопление с лексемы
        self.z = 1#индекс лексемы
        self.input_string = input_string
        self.position = 0#текущая позиция в строке

    def out(self, code1, code2):
        print(f"OUT({code1}, {code2})")

    def put(self, lexeme):
        print(f"PUT({lexeme})")

    def process(self):
        while self.position <= len(self.input_string):
            char = self.input_string[self.position] if self.position < len(self.input_string) else None
            self.position += 1

            if self.state == "H":#начальное состояние
                if char and (char.isalpha() or char.isdigit()):
                    self.buffer += char
                    self.state = "I"
                elif char == "}":
                    self.out(2, 2)
                    self.state = "V"# в  V - завершение
                elif char == "/":
                    self.state = "C1"# в  C1 - начало коммента)
                elif char == "<":
                    self.state = "M1"# в  M1 - оператор
                elif char == ">":
                    self.state = "M2"# в M2 - оператор

            elif self.state == "I":# идентификатор
                if char and char.isalnum():
                    self.buffer += char
                else:
                    if self.buffer == "let":
                        self.put(self.buffer)
                        self.out(4, self.z)
                    else:
                        self.out(1, self.z)
                    self.z += 1
                    self.buffer = ""
                    self.state = "H"
                    if char:#возвращаем символ назад
                        self.position -= 1

            elif self.state == "C1":#комментарий (начало)
                if char == "*":
                    self.state = "C2"
                else:
                    print("ошибка: некорректный комментарий")
                    self.state = "H"

            elif self.state == "C2":#тело комментария
                if char == "*":
                    self.state = "C3"
                elif char is None:
                    print("ошибка: незакрытый комментарий")
                    self.state = "H"

            elif self.state == "C3":#завершение комментария
                if char == "/":
                    self.state = "H"
                elif char is None:
                    print("ошибка: незакрытый комментарий")
                    self.state = "H"
                else:
                    self.state = "C2"

            elif self.state == "M1":#оператор <
                if char == "=":
                    self.out(2, 16)
                elif char == ">":
                    self.out(2, 18)
                else:
                    self.out(2, 21)
                    self.position -= 1#вернуться на символ назад
                self.state = "H"

            elif self.state == "M2":#оператор >
                if char == "=":
                    self.out(2, 20)
                else:
                    self.out(2, 22)
                    self.position -= 1#вернуться на символ назад
                self.state = "H"

            elif self.state == "V":#завершение
                print("завершение обработки.")
                break

            if char is None and self.state != "H":
                #обрабатываем оставшиеся данные
                if self.state == "I" and self.buffer:
                    if self.buffer == "let":#завершаем лекс
                        self.put(self.buffer)
                        self.out(4, self.z)#OUT
                    else:
                        self.out(1, self.z)
                    self.z += 1
                elif self.state in {"M1", "M2"}:
                    print("ошибка: незавершённый оператор")
                elif self.state in {"C2", "C3"}:
                    print("ошибка: незакрытый комментарий")
                break


# input_string = "a < b"
# input_string = "varName123 another_var"
# input_string = "let > x"
# input_string = "a <= b"

# input_string = "/* комментарий */ let x"#выводится не до конца
# input_string = "/* незакрытый комментарий let x"#баг - не выводится

# input_string = "a < 100}"
# input_string = "a >= b}"
# input_string = "a *"
# input_string = "123abc"   # баг - не выводится
# input_string = "}"

# PUT(let)
# OUT(4, 1)
# OUT(1, 2)
# OUT(2, 22)
# OUT(1, 3)
# OUT(2, 16)
input_string = "let /* комментарий */ var123 > b <="
lexer = LexicalAnalyzer(input_string)
lexer.process()
