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
    echo " Задача 3
    Сформировать graphviz-код и получить изображения зависимостей matplotlib и express."

    if ! command -v dot &> /dev/null; then
        echo "
        graphviz- не установлен - установите graphviz для продолжения"
        echo "
        для установки используйте команду - sudo apt install graphviz"
        return
    fi

    echo "
    генерация зависимостей matplotlib"

    pip install pipdeptree

    pipdeptree --graph-output dot > matplotlib_dependencies.dot
    echo "
    файл matplotlib_dependencies.dot с зависимостями создан"

    dot -Tpng matplotlib_dependencies.dot -o matplotlib_dependencies.png
    echo "
    изображение matplotlib_dependencies.png создано"

    echo "
    ненерация зависимостей express"

    npm ls --json > express_dependencies.json

    echo 'digraph express_dependencies {' > express_dependencies.dot
    jq -r '.dependencies | to_entries[] | .key as $pkg | .value.dependencies | to_entries[] | "  \"" + $pkg + "\" -> \"" + .key + "\";"' express_dependencies.json >> express_dependencies.dot
    echo '}' >> express_dependencies.dot

    dot -Tpng express_dependencies.dot -o express_dependencies.png
    echo "изображение express_dependencies.png создано."
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
