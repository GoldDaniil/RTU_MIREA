#!/bin/bash

if [ -z "$1" ]; then
    echo "укажите путь для поиска файлов-дубликатов."
    exit 1
fi

search_path="$1"

find "$search_path" -type f -exec md5 -r {} + | awk '{print $1}' | sort | uniq -d | while read -r hash; do
    find "$search_path" -type f -exec md5 -r {} + | awk -v hash="$hash" '$1 == hash {print $2}'
done

#/Users/gold/PycharmProjects/bash/scripts/find_duplicates.sh /Users/gold/PycharmProjects/bash/duplicatesTASK7
