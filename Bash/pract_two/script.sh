#!/bin/bash

task1() {
  echo "
  Задача 1. Вывести служебную информацию о пакете matplotlib (Python). Разобрать основные элементы содержимого файла со служебной информацией из пакета. Как получить пакет без менеджера пакетов, прямо из репозитория?"

  pip install matplotlib
  pip show matplotlib
}

task2() {
    echo "Задача 2
    Вывести служебную информацию о пакете express (JavaScript). Разобрать основные элементы содержимого файла со служебной информацией из пакета. Как получить пакет без менеджера пакетов, прямо из репозитория?
    "
    git clone https://github.com/expressjs/express.git
    cd express
    cat package.json
}

task3() {
    echo "Задача 3: Сформировать graphviz-код и получить изображения зависимостей matplotlib и express."

    echo "генерация зависимостей matplotlib"

    pip install graphviz
    # генерация графа зависимостей matplotlib
    pipdeptree --packages matplotlib --graph-output dot > matplotlib_deps.dot
    dot -Tpng matplotlib_deps.dot -o matplotlib_deps.png
    echo "зависимости matplotlib сохранены в 'matplotlib_deps.png'"

    echo "генерация зависимостей express"

    # проверка - что express был клонирован
    if [ ! -d "express" ]; then
        echo "клонирование репозитория express"
        git clone https://github.com/expressjs/express.git
    fi

    cd express

    cat <<EOF > express_deps.dot
    digraph G {
      node [shape=box];
      express -> 'accepts';
      express -> 'body-parser';
      express -> 'content-disposition';
      express -> 'content-type';
      express -> 'cookie';
      express -> 'cookie-signature';
      express -> 'debug';
      express -> 'depd';
      express -> 'encodeurl';
      express -> 'etag';
      express -> 'finalhandler';
      express -> 'fresh';
      express -> 'http-errors';
      express -> 'merge-descriptors';
      express -> 'methods';
      express -> 'mime-types';
      express -> 'on-finished';
      express -> 'once';
      express -> 'parseurl';
      express -> 'qs';
      express -> 'range-parser';
      express -> 'router';
      express -> 'safe-buffer';
      express -> 'send';
      express -> 'serve-static';
      express -> 'setprototypeof';
      express -> 'statuses';
      express -> 'type-is';
      express -> 'utils-merge';
      express -> 'vary';
    }
EOF

    dot -Tpng express_deps.dot -o express_deps.png
#    echo "зависимости express сохранены в 'express_deps.png'."

    cd ..
}

task4() {
    MINIZINC_PATH="/Applications/MiniZincIDE.app/Contents/Resources/minizinc"

    PLAYGROUND_PATH="/Users/gold/Desktop/Playground.mzn"

    if [ ! -f "$PLAYGROUND_PATH" ]; then
        echo "файл Playground.mzn не найден по пути: $PLAYGROUND_PATH"
        return
    fi

    # запуск через MiniZinc
    echo "запуск Playground.mzn через MiniZinc"
    "$MINIZINC_PATH" "$PLAYGROUND_PATH"
}


while true; do
    echo -e "\033[35mвыберите задание (от 1 до 6) или введите 'exit' для выхода:\033[0m"

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
            echo -e "\033[36mэх...печально:(\033[0m"

            break
            ;;
        *)
            echo "
    неверный выбор. введите число от 1 до 6 или 'exit' для выхода."
            ;;
    esac
done
