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
    ЗАДАЧА 5. Написать программу для регистрации пользовательской команды (правильные права доступа и копирование в /usr/local/bin).
  Например, пусть программа называется reg:
  ./reg banner
  В результате для banner задаются правильные права доступа и сам banner копируется в /usr/local/bin.

  "

    if [ -z "$1" ]; then
      echo "реализация задания с помощью команд "
        #ls -l /usr/local/bin/reg
  #reg banner
      exit 1
    fi

    prog_name="$1"
    dest="/usr/local/bin/$prog_name"

    # проверка- существует ли программа
    if [ ! -f "$prog_name" ]; then
      echo "файл $prog_name не найден."
      exit 1
    fi

    # копирование в /usr/local/bin и установка прав доступа
    sudo cp "$prog_name" "$dest"
    sudo chmod 755 "$dest"

    echo "
    пфрограмма $prog_name успешно зарегистрирована в /usr/local/bin.
    "

  #ls -l /usr/local/bin/reg
  #reg banner
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
    #test.py - убираем добавляем #
}

task7() {
    echo "ЗАДАЧА 7 в файле find_duplicates.sh
    "

    #find_duplicates.sh
}

task8() {
    echo "ЗАДАЧА 8 в файле task8.sh
    "

    #/Users/gold/PycharmProjects/bash/scripts/task8.sh /Users/gold/PycharmProjects/bash/duplicatesTASK7 txt
}

task9() {
  echo "ЗАДАЧА 9 в файле task9.sh"

  #/Users/gold/PycharmProjects/bash/scripts/task9.sh /Users/gold/PycharmProjects/bash/scripts/input.txt /Users/gold/PycharmProjects/bash/scripts/output.txt

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
