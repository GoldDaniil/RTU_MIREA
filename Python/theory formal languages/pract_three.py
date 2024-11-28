class LexicalAnalyzer:
    def __init__(self, input_string):#инициалзция
        self.state = "H"#начальное 
        self.buffer = ""#буфер = накопление с лексемы
        self.z = 1#индекс лексемы
        self.input_string = input_string
        self.position = 0#текущая позиция в строке

    def out(self, code1, code2):
        print(f"OUT({code1}, {code2})")#OUT

    def put(self, lexeme):
        print(f"PUT({lexeme})")#PUT

    def process(self):#обработка строки
        while self.position < len(self.input_string):
            char = self.input_string[self.position]
            self.position += 1

            if self.state == "H":
                if char.isalpha() or char.isdigit():
                    self.buffer += char
                    self.state = "I"# в I
                elif char == "}":
                    self.out(2, 2)
                    self.state = "V"#в  V - завершение
                elif char == "/":
                    self.state = "C1"#в  C1 - начало коммента)
                elif char == "<":
                    self.state = "M1"#в  M1 - оператор
                elif char == ">":
                    self.state = "M2"#в M2 - оператор

            elif self.state == "V":#заверш обработку
                print("end")
                break

            elif self.state == "I":# I - идент
                if char.isalnum():
                    self.buffer += char#эд символ в буфер
                else:
                    if self.buffer == "let":#завершаем лекс
                        self.put(self.buffer)
                        self.out(4, self.z)#OUT
                        self.z += 1
                    else:
                        self.out(1, self.z)#OUT для обычной лексемы
                        self.z += 1
                    self.buffer = ""
                    self.state = "H"

                    if char != " " and not char.isalnum():#не   и не идент часть
                        if self.buffer:
                            self.out(1, self.z)
                            self.buffer = ""
                    if char != " ":
                        self.position -= 1

            elif self.state == "C1":
                if char == "*":
                    self.state = "C2"#в C2

            elif self.state == "C2":
                if char == "*":
                    self.state = "C3"#в C3
                elif char != "}":
                    self.state = "C2"#остаетмся в C2
                else:
                    self.state = "ER"#в  ER (ошибка)

            elif self.state == "C3":#C3
                if char == "/":
                    self.state = "H"#в начальное H
                else:
                    self.state = "C2"#в  C2 

            elif self.state == "ER":#ER (ошибка)
                print("Ошибка: некорректный комментарий")
                self.state = "H"#в H

            elif self.state == "M1":#M1 (оператор <)
                if char == "=":
                    self.out(2, 16)
                elif char == ">":
                    self.out(2, 18)
                else:
                    self.out(2, 21)
                self.state = "H"#в начальное  H

            elif self.state == "M2":#M2 (оператор >)
                if char == "=":
                    self.out(2, 20)
                else:
                    self.out(2, 22)

                if self.buffer:
                    self.out(1, self.z)
                self.state = "H"

#input_string = "a < b"
#input_string = "varName123 another_var"
#input_string = "let > x"
#input_string = "a <= b"

input_string = "a <> b"#не до конца

#input_string = "/* комментарий */ let x"#выводится не до конца
#input_string = "/* незакрытый комментарий let x"#баг - не выводится

#input_string = "a < 100}"
#input_string = "a >= b}"
#input_string = "a *"
#input_string = "123abc"   # баг - не выводится
#input_string = "}"

#input_string = "let /* коммент */ var123 > b <="
#PUT(let)
#OUT(4, 1)
#OUT(1, 2)
#OUT(2, 22)
#OUT(1, 3)
#OUT(2, 16)

lexer = LexicalAnalyzer(input_string)
lexer.process()
