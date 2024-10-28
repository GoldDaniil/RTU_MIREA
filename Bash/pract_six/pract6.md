# Практическое задание №4. Системы автоматизации сборки

П.Н. Советов, РТУ МИРЭА

Работа с утилитой Make.

Изучить основы языка утилиты make. Распаковать в созданный каталог [make.zip](make.zip), если у вас в в системе нет make.

Создать приведенный ниже Makefile и проверить его работоспособность.

```
dress: trousers shoes jacket
    @echo "All done. Let's go outside!"

jacket: pullover
    @echo "Putting on jacket."

pullover: shirt
    @echo "Putting on pullover."

shirt:
    @echo "Putting on shirt."

trousers: underpants
    @echo "Putting on trousers."

underpants:
    @echo "Putting on underpants."

shoes: socks
    @echo "Putting on shoes."

socks: pullover
    @echo "Putting on socks."
```




Визуализировать файл [civgraph.txt](civgraph.txt).



<img width="435" alt="Screenshot 2024-10-21 at 12 54 39" src="https://github.com/user-attachments/assets/ac90b265-62e4-4fe7-879c-a42acf7fc28d">
<img width="404" alt="Screenshot 2024-10-21 at 12 55 18" src="https://github.com/user-attachments/assets/cb954ceb-18ed-4747-b616-9e667f3d7ffd">

## Задача 1

Написать программу на Питоне, которая транслирует граф зависимостей civgraph в makefile в духе примера выше. Для мало знакомых с Питоном используется упрощенный вариант civgraph: [civgraph.json](civgraph.json).

Пример:

```
> make mathematics
mining
bronze_working
sailing
astrology
celestial_navigation
pottery
writing
code_of_laws
foreign_trade
currency
irrigation
masonry
early_empire
mysticism
drama_poetry
mathematics

```
<img width="812" alt="Screenshot 2024-10-21 at 12 56 30" src="https://github.com/user-attachments/assets/817bf9c5-e223-4810-a9f0-9ff77f73b79a">
<img width="952" alt="Screenshot 2024-10-21 at 12 56 47" src="https://github.com/user-attachments/assets/9655a8a7-305b-4fae-b71c-0209116f8506">
<img width="889" alt="Screenshot 2024-10-21 at 12 57 26" src="https://github.com/user-attachments/assets/20af7e35-f6c9-4bdb-8e35-821af451ae31">
<img width="442" alt="Screenshot 2024-10-21 at 13 03 06" src="https://github.com/user-attachments/assets/9a71e087-bee0-4354-aa51-4dba4f6a4e4d">
<img width="601" alt="Screenshot 2024-10-21 at 13 03 25" src="https://github.com/user-attachments/assets/f49276e8-0503-434a-ae55-d658b1275ccb">


```
```

## Задача 2

Реализовать вариант трансляции, при котором повторный запуск make не выводит для civgraph на экран уже выполненные "задачи".

<img width="857" alt="Screenshot 2024-10-21 at 13 04 14" src="https://github.com/user-attachments/assets/a5608c48-a0a0-4866-b580-52e67f21c60a">
<img width="440" alt="Screenshot 2024-10-21 at 13 06 47" src="https://github.com/user-attachments/assets/9db86670-c8df-4a8b-8b7d-404c2ade75f1">
<img width="778" alt="Screenshot 2024-10-21 at 13 04 40" src="https://github.com/user-attachments/assets/f70d846e-e377-4b2b-b2b4-cd6fa8d82eb4">
<img width="899" alt="Screenshot 2024-10-21 at 13 04 55" src="https://github.com/user-attachments/assets/b0e0c0f8-34c2-4a5f-abc9-f5c0383e062a">

## Задача 3

Добавить цель clean, не забыв и про "животное".

## Задача 4

Написать makefile для следующего скрипта сборки:

```
gcc prog.c data.c -o prog
dir /B > files.lst
7z a distr.zip *.*
```

Вместо gcc можно использовать другой компилятор командной строки, но на вход ему должны подаваться два модуля: prog и data.
Если используете не Windows, то исправьте вызовы команд на их эквиваленты из вашей ОС.
В makefile должны быть, как минимум, следующие задачи: all, clean, archive.
Обязательно покажите на примере, что уже сделанные подзадачи у вас не перестраиваются.

## Полезные ссылки

Описание (рус.): https://unix1.jinr.ru/faq_guide/programming/make/make.html

Шпаргалка: https://devhints.io/makefile

Топологическая сортировка: https://ru.wikipedia.org/wiki/Топологическая_сортировка
