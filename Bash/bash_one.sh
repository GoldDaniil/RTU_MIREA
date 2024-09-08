#!/bin/bash

task1() {
    echo "
    ЗАДАЧА 1. Вывести отсортированный в алфавитном порядке список имен пользователей в файле passwd (вам понадобится grep)."
    grep '^[^#]' /etc/passwd | cut -d ':' -f 1 | sort
}

task2() {
    echo "
    ЗАДАЧА 2. Вывести данные /etc/protocols в отформатированном и отсортированном порядке для 5 наибольших портов, как показано в примере ниже:
    [root@localhost etc]# cat /etc/protocols ...
    142 rohc
    141 wesp
    140 shim6
    139 hip
    138 manet
    "

    cat /etc/protocols | awk '{print $NF " " $1}' | sort -nr | head -5
}

task3() {
    echo "
    ЗАДАЧА 3. Написать программу banner средствами bash для вывода текстов, как в следующем примере (размер баннера должен меняться!):
    [root@localhost ~]# ./banner 'Hello from RTU MIREA!'
    "
    echo "введите текст для баннера:"
    read -r banner_text
    width=$(( ${#banner_text} + 4 ))

    echo "+"$(printf -- '-%.0s' $(seq 1 $width))"+"

    echo "| $banner_text |"

    echo "+"$(printf -- '-%.0s' $(seq 1 $width))"+"
}

task4() {
    echo "
    ЗАДАЧА 4. Написать программу для вывода всех идентификаторов (по правилам C/C++ или Java) в файле (без повторений).

    "
#    grep -o '\b[A-Za-z_][A-Za-z0-9_]*\b' hello.c | sort -u
    grep -oE '\b[A-Za-z_][A-Za-z0-9_]*\b' hello.cpp | sort -u

}

task5() {
    echo "
    ЗАДАЧА 5."
    if [ -z "$1" ]; then
      echo "укаажите имя программы для регистрации: "
      exit 1
    fi

    prog_name="$1"
    dest="/usr/local/bin/$prog_name"

    # проверка- существует ли программа
    if [ ! -f "$prog_name" ]; then
      echo "Файл $prog_name не найден."
      exit 1
    fi

    # копирование в /usr/local/bin и установка прав доступа
    sudo cp "$prog_name" "$dest"
    sudo chmod 755 "$dest"

    echo "Программа $prog_name успешно зарегистрирована в /usr/local/bin."
}

task6() {
    echo "
    ЗАДАЧА 6. "
    for file in *.{c,js,py}; do
      if [ -f "$file" ]; then
        first_line=$(head -n 1 "$file")
        if [[ "$first_line" == /* ]] || [[ "$first_line" == \#* ]] || [[ "$first_line" == "//"* ]]; then
          echo "$file: комментарий найден в первой строке."
        else
          echo "$file: комментарий не найден."
        fi
      fi
    done
}

task7() {
    echo "
    ЗАДАЧА 7. "
    if [ -z "$1" ]; then
      echo "Укажите путь для поиска файлов-дубликатов."
      exit 1
    fi

    find "$1" -type f -exec md5sum {} + | sort | uniq -w32 -dD
}

task8() {
    echo "
    ЗАДАЧА 8. "
    if [ -z "$1" ]; then
      echo "Укажите расширение файлов для архивирования."
      exit 1
    fi

    extension="$1"
    archive_name="archive_$extension.tar"

    # Поиск файлов и добавление их в архив
    tar -cvf "$archive_name" *."$extension"

    echo "Файлы с расширением $extension были архивированы в $archive_name."
}

while true; do
    echo "
    выберите задание (от 1 до 8) или введите 'exit' для выхода:"
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
        7)
            task7 "$2"
            ;;
        8)
            task8 "$2"
            ;;
        exit)
            echo "
    эх...печально:("
            break
            ;;
        *)
            echo "
    неверный выбор. введите число от 1 до 8 или 'exit' для выхода."
            ;;
    esac
done
