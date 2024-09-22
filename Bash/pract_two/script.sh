#!/bin/bash

task1() {
  echo "
  Задача 1. Вывести служебную информацию о пакете matplotlib (Python). Разобрать основные элементы содержимого файла со служебной информацией из пакета. Как получить пакет без менеджера пакетов, прямо из репозитория?"
    pip show matplotlib
    echo "
    загрузка пакетов:"
    wget https://github.com/matplotlib/matplotlib/archive/refs/tags/v3.5.2.tar.gz
    echo "
  архив matplotlib загружен - распакуйте его с помощью команды tar:"
    echo "
  tar -xvzf v3.5.2.tar.gz"
}

task2() {
    echo "Получение служебной информации о пакете express..."
    npm view express

    echo "Загрузка пакета express без менеджера пакетов:"
    wget https://github.com/expressjs/express/archive/refs/tags/4.18.2.tar.gz
    echo "Архив express загружен. Распакуйте его с помощью команды tar:"
    echo "tar -xvzf 4.18.2.tar.gz"
}

while true; do
    echo "
    выберите задание (от 1 до 6) или введите 'exit' для выхода:"
    read -r choice

    case $choice in
        1)
            task1
            ;;
        2)
            task2
            ;;
        3)
            task3
            ;;
        4)
            task4
            ;;
        5)
            task5 "$2"
            ;;
        6)
            task6
            ;;
        exit)
            echo "
    эх...печально:("
            break
            ;;
        *)
            echo "
    неверный выбор. введите число от 1 до 6 или 'exit' для выхода."
            ;;
    esac
done
