проект позволяет создать граф зависимостей коммитов из локального репозитория Git и экспортировать его в формате PlantUML для визуализации

## описание
алгоритм строит граф коммитов, анализируя файлы объектов (`.git/objects/`) и ссылки на ветки (`.git/refs/heads`). каждый узел графа представляет коммит, включая его хеш, 
автора и дату. результат сохраняется в формате PlantUML, который можно визуализировать с помощью [PlantUML](https://plantuml.com) или установить плагин для JETBRAINS IDE
(например PyCharm)
[PlantUML](https://plugins.jetbrains.com/plugin/7017-plantuml-integration/versions/stable)

## индивидуальный вариант
![image](https://github.com/user-attachments/assets/4fce165a-aa8e-4c16-bb54-8ac84f989e76)

## структура проекта   
```text
homework2/
├── dependency_graph.txt   
├── git_dependency_graph.py  
├── output.puml            
├── requirements.txt     
```

## реализация
![image](https://github.com/user-attachments/assets/30090f47-83ec-4e59-89d3-7856e4c98381)
![image](https://github.com/user-attachments/assets/6fcff08b-4c27-4c24-8a4b-ee4e45da4919)
![image](https://github.com/user-attachments/assets/13674125-e8b9-465b-b0fa-a1326ee64e15)
```
```

![image](https://github.com/user-attachments/assets/1ec241dd-b539-430a-bfc3-1265965ba7ea)
```
```

gitpython
```
```

## особенности
- извлечение данных о коммитах из локального репозитория Git
- построение графа зависимостей коммитов, где связь указывает на родительский коммит
- экспорт графа в формате PlantUML для визуализации
- обработка повторяющихся коммитов для предотвращения дублирования узлов

### требования
- убедитесь, что у вас установлен Python (версия 3.8 или выше)
- локальный репозиторий Git должен быть доступен, а папка `.git` должна находиться в указанном пути
- убедитесь, что у вас установлен плагин PlantUML для JETBRAINS IDE

### установка
1. клонируйте этот репозиторий или скопируйте код в вашу рабочую папку
2. создайте виртуальное окружение и активируйте его или используйте уже существующее:
   #для linux/macOS
   ```bash
   python -m venv .venv
   source .venv/bin/activate
   ```
   #для Windows
   ```bash
   python -m venv .venv
   .venv\Scripts\activate
   ```
