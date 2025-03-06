# Практическое занятие №3. Конфигурационные языки

П.Н. Советов, РТУ МИРЭА

Разобраться, что собой представляют программируемые конфигурационные языки (Jsonnet, Dhall, CUE).

## Задача 1

Реализовать на Jsonnet приведенный ниже пример в формате JSON. Использовать в реализации свойство программируемости и принцип DRY.

<img width="932" alt="Screenshot 2024-10-14 at 09 25 14" src="https://github.com/user-attachments/assets/af229cfb-75ba-411d-8aaa-603b8af6fedf">
<img width="585" alt="Screenshot 2024-10-14 at 09 25 43" src="https://github.com/user-attachments/assets/f5292801-10cd-4b2c-88a5-71202a635d2a">
<img width="449" alt="Screenshot 2024-10-14 at 09 26 33" src="https://github.com/user-attachments/assets/95d37d26-5514-4760-a558-da1c07d40d5d">
<img width="423" alt="Screenshot 2024-10-14 at 09 26 46" src="https://github.com/user-attachments/assets/28101ede-e1d0-4d19-9a9e-d7045a950e69">

## Задача 2

Реализовать на Dhall приведенный ниже пример в формате JSON. Использовать в реализации свойство программируемости и принцип DRY.

```
{
  "groups": [
    "ИКБО-1-20",
    "ИКБО-2-20",
    "ИКБО-3-20",
    "ИКБО-4-20",
    "ИКБО-5-20",
    "ИКБО-6-20",
    "ИКБО-7-20",
    "ИКБО-8-20",
    "ИКБО-9-20",
    "ИКБО-10-20",
    "ИКБО-11-20",
    "ИКБО-12-20",
    "ИКБО-13-20",
    "ИКБО-14-20",
    "ИКБО-15-20",
    "ИКБО-16-20",
    "ИКБО-17-20",
    "ИКБО-18-20",
    "ИКБО-19-20",
    "ИКБО-20-20",
    "ИКБО-21-20",
    "ИКБО-22-20",
    "ИКБО-23-20",
    "ИКБО-24-20"
  ],
  "students": [
    {
      "age": 19,
      "group": "ИКБО-4-20",
      "name": "Иванов И.И."
    },
    {
      "age": 18,
      "group": "ИКБО-5-20",
      "name": "Петров П.П."
    },
    {
      "age": 18,
      "group": "ИКБО-5-20",
      "name": "Сидоров С.С."
    },
    <добавьте ваши данные в качестве четвертого студента>
  ],
  "subject": "Конфигурационное управление"
}



```
<img width="834" alt="Screenshot 2024-10-20 at 18 59 29" src="https://github.com/user-attachments/assets/18eb7a87-8309-4bd9-9be9-43f4a1f6008b">
<img width="892" alt="Screenshot 2024-10-20 at 18 59 42" src="https://github.com/user-attachments/assets/0af709b6-40fd-41c2-baf5-fa995a315742">
<img width="446" alt="Screenshot 2024-10-20 at 19 00 03" src="https://github.com/user-attachments/assets/bedfdcc8-2af0-4af5-8d0c-510e50a9ffc3">
<img width="410" alt="Screenshot 2024-10-20 at 19 00 16" src="https://github.com/user-attachments/assets/9d7fbe88-622d-4e3d-8e8f-1e178d516bdb">


Для решения дальнейших задач потребуется программа на Питоне, представленная ниже. Разбираться в самом языке Питон при этом необязательно.

```Python
import random


def parse_bnf(text):
    '''
    Преобразовать текстовую запись БНФ в словарь.
    '''
    grammar = {}
    rules = [line.split('=') for line in text.strip().split('\n')]
    for name, body in rules:
        grammar[name.strip()] = [alt.split() for alt in body.split('|')]
    return grammar


def generate_phrase(grammar, start):
    '''
    Сгенерировать случайную фразу.
    '''
    if start in grammar:
        seq = random.choice(grammar[start])
        return ''.join([generate_phrase(grammar, name) for name in seq])
    return str(start)


BNF = '''
E = a
'''

for i in range(10):
    print(generate_phrase(parse_bnf(BNF), 'E'))

```

Реализовать грамматики, описывающие следующие языки (для каждого решения привести БНФ). Код решения должен содержаться в переменной BNF:

## Задача 3

Язык нулей и единиц.

```
10
100
11
101101
000
```

<img width="764" alt="Screenshot 2024-10-14 at 09 29 48" src="https://github.com/user-attachments/assets/b23a5cd7-47bd-43ec-ae8f-9866ba0acb2e">
<img width="447" alt="Screenshot 2024-10-14 at 09 30 21" src="https://github.com/user-attachments/assets/1790760f-9ca7-4d48-8fb6-0fd21a65ff33">

## Задача 4

Язык правильно расставленных скобок двух видов.

```
(({((()))}))
{}
{()}
()
{}
```

<img width="764" alt="Screenshot 2024-10-14 at 09 30 45" src="https://github.com/user-attachments/assets/caefbb24-1c39-4432-840b-2c490d69997c">
<img width="1676" alt="Screenshot 2024-10-14 at 09 31 03" src="https://github.com/user-attachments/assets/c7f190da-85a1-4103-84ec-75c80e9f409c">


## Задача 5

Язык выражений алгебры логики.

```
((~(y & x)) | (y) & ~x | ~x) & x
y & ~(y)
(~(y) & y & ~y)
~x
~((x) & y | (y) | (x)) & x | x | (y & ~y)
```
<img width="764" alt="Screenshot 2024-10-14 at 09 32 11" src="https://github.com/user-attachments/assets/80c49b20-2cd8-48a5-9e7a-992bef7df04a">
<img width="1692" alt="Screenshot 2024-10-14 at 09 31 51" src="https://github.com/user-attachments/assets/ae441f01-e30a-4d3a-94c3-0330a37e8477">


## Полезные ссылки

Configuration complexity clock: https://mikehadlow.blogspot.com/2012/05/configuration-complexity-clock.html

Json: http://www.json.org/json-ru.html

Язык Jsonnet: https://jsonnet.org/learning/tutorial.html

Язык Dhall: https://dhall-lang.org/

Учебник в котором темы построения синтаксических анализаторов (БНФ, Lex/Yacc) изложены подробно: https://ita.sibsutis.ru/sites/csc.sibsutis.ru/files/courses/trans/LanguagesAndTranslationMethods.pdf

Полезные материалы для разработчика (очень рекомендую посмотреть слайды и прочие ссылки, все это актуально и для других тем нашего курса): https://habr.com/ru/company/JetBrains-education/blog/547768/
