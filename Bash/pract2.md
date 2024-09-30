# Практическое занятие №2. Менеджеры пакетов

## Задача 1

Вывести служебную информацию о пакете matplotlib (Python). Разобрать основные элементы содержимого файла со служебной информацией из пакета. Как получить пакет без менеджера пакетов, прямо из репозитория?

<img width="800" alt="Screenshot 2024-09-30 at 09 24 29" src="https://github.com/user-attachments/assets/68cf885a-bb0c-40fc-8ac5-c94d5d16f2c9">
<img width="800" alt="Screenshot 2024-09-30 at 09 24 54" src="https://github.com/user-attachments/assets/f37ea8c7-8a31-470e-8c33-5e72abbd9dc7">
<img width="400" height="500" alt="Screenshot 2024-09-30 at 09 25 09" src="https://github.com/user-attachments/assets/5638d3e1-d51d-4785-af0e-9ae73763a181">
<img width="500" alt="Screenshot 2024-09-30 at 09 25 19" src="https://github.com/user-attachments/assets/bc0738a3-554d-44b7-8027-39249eabc32a">

## Задача 2

Вывести служебную информацию о пакете express (JavaScript). Разобрать основные элементы содержимого файла со служебной информацией из пакета. Как получить пакет без менеджера пакетов, прямо из репозитория?

<img width="1000" alt="Screenshot 2024-09-30 at 09 27 43" src="https://github.com/user-attachments/assets/6199eb62-41c5-44ee-bbda-2239bf91069f">
<img width="1200" alt="Screenshot 2024-09-30 at 09 28 19" src="https://github.com/user-attachments/assets/f7c438e8-fb9d-46b1-94f3-6a09ec307004">
<img width="1200" alt="Screenshot 2024-09-30 at 09 28 29" src="https://github.com/user-attachments/assets/ec346c1c-0237-4586-9177-cda7a7eef61c">

## Задача 3

Сформировать graphviz-код и получить изображения зависимостей matplotlib и express.
<img width="911" alt="Screenshot 2024-09-30 at 09 30 14" src="https://github.com/user-attachments/assets/979a9155-d32f-40ac-9820-1b3712c5a4de">
<img width="580" alt="Screenshot 2024-09-30 at 09 30 57" src="https://github.com/user-attachments/assets/a3728fa8-23dc-4e5a-bbf3-af8dcc970bb7">
<img width="970" alt="Screenshot 2024-09-30 at 09 31 18" src="https://github.com/user-attachments/assets/a4d87b2a-cf78-48d3-88ef-e93ffebf1064">
<img width="1341" alt="Screenshot 2024-09-30 at 09 31 42" src="https://github.com/user-attachments/assets/132958a0-8cf2-4d2f-bdce-06eeff898f72">

## Задача 4

**Следующие задачи можно решать с помощью инструментов на выбор:**

* Решатель задачи удовлетворения ограничениям (MiniZinc).
* SAT-решатель (MiniSAT).
* SMT-решатель (Z3).

Изучить основы программирования в ограничениях. Установить MiniZinc, разобраться с основами его синтаксиса и работы в IDE.

Решить на MiniZinc задачу о счастливых билетах. Добавить ограничение на то, что все цифры билета должны быть различными (подсказка: используйте all_different). Найти минимальное решение для суммы 3 цифр.

<img width="671" alt="Screenshot 2024-09-30 at 09 34 38" src="https://github.com/user-attachments/assets/416a2f1a-2c55-4864-94e4-93800cb78c0d">
<img width="496" alt="Screenshot 2024-09-30 at 09 35 54" src="https://github.com/user-attachments/assets/3d587043-b9e7-4b39-ac0f-c47a6bf8d406">
<img width="485" alt="Screenshot 2024-09-30 at 09 39 02" src="https://github.com/user-attachments/assets/c35d55eb-1be1-489b-88d9-90cd51815b16">


## Задача 5

Решить на MiniZinc задачу о зависимостях пакетов для рисунка, приведенного ниже.

![](images/pubgrub.png)

## Задача 6

Решить на MiniZinc задачу о зависимостях пакетов для следующих данных:

```
root 1.0.0 зависит от foo ^1.0.0 и target ^2.0.0.
foo 1.1.0 зависит от left ^1.0.0 и right ^1.0.0.
foo 1.0.0 не имеет зависимостей.
left 1.0.0 зависит от shared >=1.0.0.
right 1.0.0 зависит от shared <2.0.0.
shared 2.0.0 не имеет зависимостей.
shared 1.0.0 зависит от target ^1.0.0.
target 2.0.0 и 1.0.0 не имеют зависимостей.
```

## Задача 7

Представить задачу о зависимостях пакетов в общей форме. Здесь необходимо действовать аналогично реальному менеджеру пакетов. То есть получить описание пакета, а также его зависимости в виде структуры данных. Например, в виде словаря. В предыдущих задачах зависимости были явно заданы в системе ограничений. Теперь же систему ограничений надо построить автоматически, по метаданным.

## Полезные ссылки

Semver: https://devhints.io/semver

Удовлетворение ограничений и программирование в ограничениях: http://intsys.msu.ru/magazine/archive/v15(1-4)/shcherbina-053-170.pdf

Скачать MiniZinc: https://www.minizinc.org/software.html

Документация на MiniZinc: https://www.minizinc.org/doc-2.5.5/en/part_2_tutorial.html

Задача о счастливых билетах: https://ru.wikipedia.org/wiki/%D0%A1%D1%87%D0%B0%D1%81%D1%82%D0%BB%D0%B8%D0%B2%D1%8B%D0%B9_%D0%B1%D0%B8%D0%BB%D0%B5%D1%82
