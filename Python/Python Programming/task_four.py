import re

def launcher():
    while True:
        print("\nвыберите номер блока или 'exit' для завершения:")
        print(" 1 - блок 1")
        print(" 2 - блок 2")
        print(" 3 - блок 3")
        print(" 4 - блок 4")
        print(" 5 - блок 5")

        block = input("номер блока: ").strip()
        if block.lower() == "exit":
            print("пока")
            break
        elif block in ['1', '2', '3', '4', '5']:
            tasks_menu(block)
        else:
            print("неверный номер блока - введите еще раз")

def block_first_first():
    class MyClass:
        def __init__(self):
            self.name = "Test"
            self.value = 123
            self._private = "hidden"

        def method(self):
            pass

    obj = MyClass()
    fields = [attr for attr in dir(obj) if not attr.startswith("__") and not callable(getattr(obj, attr))]
    print("поля объекта (без служебных и методов):", fields)

def block_first_second():
    class MyClass:
        def hello(self):
            print("привет из метода hello!")

        def bye(self):
            print("пока из метода bye!")

    obj = MyClass()
    method_name = input("Введите имя метода (например, 'hello' или 'bye'): ").strip()
    if hasattr(obj, method_name):
        method = getattr(obj, method_name)
        if callable(method):
            method()
        else:
            print(f"'{method_name}' — это не метод")
    else:
        print(f"метод '{method_name}' не найден")

def block_first_third():
    print("исходный код:")
    print("class A: pass")
    print("class B(A): pass")
    print("class C(A, B): pass")
    print("\nОшибка: класс C наследует A и B, но B уже наследует A, возникает конфликт MRO (Method Resolution Order).")
    print("исправление: достаточно наследовать только от B, т.к. он уже включает A.")
    print("правильно:")
    print("class A: pass")
    print("class B(A): pass")
    print("class C(B): pass")

def block_first_fourth():
    def get_inheritance(cls):
        return ' -> '.join(c.__name__ for c in cls.__mro__)

    class_name = input("введите имя встроенного класса (например, 'OSError'): ").strip()
    try:
        cls = eval(class_name)
        print(get_inheritance(cls))
    except NameError:
        print("класс с таким именем не найден")

class MyHashTable:
    def __init__(self):
        self._data = []

    def __setitem__(self, key, value):
        for i, (k, v) in enumerate(self._data):
            if k == key:
                self._data[i] = (key, value)
                return
        self._data.append((key, value))

    def __getitem__(self, key):
        for k, v in self._data:
            if k == key:
                return v
        raise KeyError(key)

    def __len__(self):
        return len(self._data)

    def __contains__(self, key):
        return any(k == key for k, _ in self._data)

    def __delitem__(self, key):
        for i, (k, _) in enumerate(self._data):
            if k == key:
                del self._data[i]
                return
        raise KeyError(key)

    def __iter__(self):
        return (k for k, _ in self._data)

    def items(self):
        return iter(self._data)

    def keys(self):
        return (k for k, _ in self._data)

    def values(self):
        return (v for _, v in self._data)

def block_second_first():
    print("тестирование чтения, записи и размера хэш-таблицы:")
    table = MyHashTable()
    table["a"] = 1
    table["b"] = 2
    assert table["a"] == 1
    assert table["b"] == 2
    assert len(table) == 2
    print("все базовые тесты пройдены")

def block_second_second():
    print("тест интерфейса dict: __contains__, __delitem__, keys(), values(), items()")
    table = MyHashTable()
    table["x"] = 10
    table["y"] = 20
    assert "x" in table
    assert "z" not in table
    assert table["y"] == 20
    del table["x"]
    assert "x" not in table
    keys = list(table.keys())
    values = list(table.values())
    items = list(table.items())
    print("ключи:", keys)
    print("значения:", values)
    print("пары:", items)
    print("интерфейс dict реализован корректно")

def block_second_third():
    print("проверка итератора и вложенных циклов:")
    table = MyHashTable()
    for i in range(5):
        table[f"k{i}"] = i * i

    for key in table:
        for k, v in table.items():
            print(f"{key} вложенно видит: {k} -> {v}")
    print("итерация и вложенные циклы работают корректно")

class Num:
    def __init__(self, value):
        self.value = value

class Add:
    def __init__(self, left, right):
        self.left = left
        self.right = right

class Mul:
    def __init__(self, left, right):
        self.left = left
        self.right = right

class PrintVisitor:
    def visit(self, node):
        method_name = 'visit_' + node.__class__.__name__
        method = getattr(self, method_name)
        return method(node)

    def visit_Num(self, node):
        return str(node.value)

    def visit_Add(self, node):
        return f"({self.visit(node.left)} + {self.visit(node.right)})"

    def visit_Mul(self, node):
        return f"({self.visit(node.left)} * {self.visit(node.right)})"

class CalcVisitor:
    def visit(self, node):
        method = getattr(self, f"visit_{node.__class__.__name__}")
        return method(node)

    def visit_Num(self, node):
        return node.value

    def visit_Add(self, node):
        return self.visit(node.left) + self.visit(node.right)

    def visit_Mul(self, node):
        return self.visit(node.left) * self.visit(node.right)

class StackVisitor:
    def visit(self, node):
        method = getattr(self, f"visit_{node.__class__.__name__}")
        return method(node)

    def visit_Num(self, node):
        return f"PUSH {node.value}"

    def visit_Add(self, node):
        left = self.visit(node.left)
        right = self.visit(node.right)
        return f"{left}\n{right}\nADD"

    def visit_Mul(self, node):
        left = self.visit(node.left)
        right = self.visit(node.right)
        return f"{left}\n{right}\nMUL"

def block_third_first():
    print("3.1: создание дерева выражения")
    ast = Add(Num(7), Mul(Num(3), Num(2)))
    print("AST создан: Add(Num(7), Mul(Num(3), Num(2)))")

def block_third_second():
    print("3.2: печать выражения через PrintVisitor")
    ast = Add(Num(7), Mul(Num(3), Num(2)))
    pv = PrintVisitor()
    print("результат:", pv.visit(ast))  # -> (7 + (3 * 2))

def block_third_third():
    print("3.3: вычисление выражения через CalcVisitor")
    ast = Add(Num(7), Mul(Num(3), Num(2)))
    cv = CalcVisitor()
    print("результат:", cv.visit(ast))  # -> 13

def block_third_fourth():
    print("3.4: генерация кода стековой машины через StackVisitor")
    ast = Add(Num(7), Mul(Num(3), Num(2)))
    sv = StackVisitor()
    print("код:")
    print(sv.visit(ast))

class HTML:
    def __init__(self):
        self.code = []
        self.indent = 0

    def _add_line(self, line):
        self.code.append(" " * self.indent + line)

    def get_code(self):
        return "\n".join(self.code)

    def body(self):
        return Tag(self, "body")

    def div(self):
        return Tag(self, "div")

    def p(self, text):
        self._add_line(f"<p>{text}</p>")

class Tag:
    def __init__(self, html, tag):
        self.html = html
        self.tag = tag

    def __enter__(self):
        self.html._add_line(f"<{self.tag}>")
        self.html.indent += 4

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.html.indent -= 4
        self.html._add_line(f"</{self.tag}>")

def block_fourth_first():
    html = HTML()
    with html.body():
        with html.div():
            with html.div():
                html.p('1 строка')
                html.p('2 строка')
            with html.div():
                html.p('3 строка')

    print("сгенерированный HTML:\n")
    print(html.get_code())

def tasks_menu(block):
    while True:
        print(f"\nвыберите задание из блока {block} или 'exit' для возврата к выбору блока:")
        if block == '1':
            print("1")
            print("2")
            print("3")
            print("4")
        elif block == '2':
            print("1")
            print("2")
            print("3")
        if block == '3':
            print("1")
            print("2")
            print("3")
            print("4")
        if block == '4':
            print("1")
        if block == '5':
            print("1")
            print("2")
            print("3")
            print("4")
            print("5")
            print("6")

        task = input("номер задания: ").strip()

        if task.lower() == "exit":
            break

        if block == '1':
            if task == '1':
                block_first_first()
            elif task == '2':
                block_first_second()
            elif task == '3':
                block_first_third()
            elif task == '4':
                block_first_fourth()
            else:
                print("error - try again")
        elif block == '2':
            if task == '1':
                block_second_first()
            elif task == '2':
                block_second_second()
            elif task == '3':
                block_second_third()
            else:
                print("error - try again")
        elif block == '3':
            if task == '1':
                block_third_first()
            elif task == '2':
                block_third_second()
            elif task == '3':
                block_third_third()
            elif task == '4':
                block_third_fourth()
            else:
                print("error - try again")
        elif block == '4':
            if task == '1':
                block_fourth_first()
            else:
                print("error - try again")
        elif block == '5':
            # if task == '1':
                # block_fifth_first()
            # elif task == '2':
                # block_fifth_second()
            # elif task == '3':
                # block_fifth_third()
            # elif task == '4':
                # block_fifth_fourth()
            # elif task == '5':
                # block_fifth_five()
            # elif task == '6':
                # block_fifth_six()
            # elif task == '7':
                # block_fifth_seventh()
            # else:
                print("error - try again")

def main():
    launcher()

if __name__ == '__main__':
    main()
