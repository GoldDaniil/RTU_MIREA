#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "использование: $0 <входной файл> <выходной файл>"
    exit 1
fi

input_file="$1"
output_file="$2"

if [ ! -f "$input_file" ]; then
    echo "ошибка: входной файл '$input_file' не найден"
    exit 1
fi

sed 's/    /\t/g' "$input_file" > "$output_file"

if [ $? -eq 0 ]; then
    echo "ошибоок ненет - выходной файл: $output_file"
else
    echo "щшибка при обработке файла"
fi


#/Users/gold/PycharmProjects/bash/scripts/task9.sh /Users/gold/PycharmProjects/bash/scripts/input.txt /Users/gold/PycharmProjects/bash/scripts/output.txt
