#!/bin/bash

echo "ЗАДАЧА 8"

    if [ -z "$1" ] || [ -z "$2" ]; then
        echo "использование: $0 <путь> <расширение>"
        exit 1
    fi

    search_path="$1"
    extension="$2"
    archive_name="archive_$extension.tar"

    if [ ! -d "$search_path" ]; then
        echo "путь $search_path не существует или не является директорией"
        exit 1
    fi

    echo "архивирование файлов с расширением $extension из $search_path в $archive_name..."
    find "$search_path" -type f -name "*.$extension" | tar -cvf "$archive_name" -T -

    echo "
архив $archive_name создан"

#/Users/gold/PycharmProjects/bash/scripts/task8.sh /Users/gold/PycharmProjects/bash/duplicatesTASK7 txt
