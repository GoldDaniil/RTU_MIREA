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
            # if task == '1':
            #     block_third_first(["1", "2", "3"])
            # elif task == '2':
            #     block_third_second([1, 2, 2, 3, 4])
            # elif task == '3':
            #     block_third_third([1, 2, 3, 4])
            # elif task == '4':
            #     block_third_fourth([1, 2, 3, 1, 2, 3], 2)
            # elif task == '5':
            #     block_third_fifth([1, 2, 3, 4, 5])
            # elif task == '6':
            #     block_third_sixth(["short", "longer", "longest"])
            # elif task == '7':
            #     block_third_seventh(18)
            # elif task == '8':
            #     block_third_eighth(10)
            # elif task == '9':
            #     block_third_ninth("ABBCCCDEF")
            # else:
                print("error - try again")
        elif block == '4':
            # if task == '1':
                # block_fourth_first()
            # elif task == '2':
                # block_fourth_second()
            # else:
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
  
