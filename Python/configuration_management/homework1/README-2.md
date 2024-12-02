# проект: разработать эмулятор для языка оболочки ОС

## описание
проект позволяет создать виртуальную файловую систему с поддержкой архивации файлов в формате `.tar`. пользователь может добавлять, извлекать файлы, очищать коммандую строку, выводить содержимое текущего каталога, перемещать файлы.




## индивидуальный вариант
![Screenshot 2024-12-02 at 09.55.52.png](..%2F..%2F..%2Fvar%2Ffolders%2Fmv%2Fgjx66vzd2db8kjn12x6n_0wm0000gn%2FT%2FTemporaryItems%2FNSIRD_screencaptureui_vVK30F%2FScreenshot%202024-12-02%20at%2009.55.52.png)






## структура проекта
![Screenshot 2024-12-02 at 09.56.20.png](..%2F..%2F..%2Fvar%2Ffolders%2Fmv%2Fgjx66vzd2db8kjn12x6n_0wm0000gn%2FT%2FTemporaryItems%2FNSIRD_screencaptureui_zCoGE1%2FScreenshot%202024-12-02%20at%2009.56.20.png)





## реализация
![Screenshot 2024-12-02 at 09.57.39.png](..%2FDesktop%2FScreenshot%202024-12-02%20at%2009.57.39.png)


![Screenshot 2024-12-02 at 09.57.32.png](..%2FDesktop%2FScreenshot%202024-12-02%20at%2009.57.32.png)


![Screenshot 2024-12-02 at 09.57.26.png](..%2FDesktop%2FScreenshot%202024-12-02%20at%2009.57.26.png)


![Screenshot 2024-12-02 at 09.57.15.png](..%2FDesktop%2FScreenshot%202024-12-02%20at%2009.57.15.png)


![Screenshot 2024-12-02 at 09.57.10.png](..%2FDesktop%2FScreenshot%202024-12-02%20at%2009.57.10.png)


![Screenshot 2024-12-02 at 09.57.05.png](..%2FDesktop%2FScreenshot%202024-12-02%20at%2009.57.05.png)


![Screenshot 2024-12-02 at 10.01.36.png](..%2FDesktop%2FScreenshot%202024-12-02%20at%2010.01.36.png)


![Screenshot 2024-12-02 at 10.01.48.png](..%2F..%2F..%2Fvar%2Ffolders%2Fmv%2Fgjx66vzd2db8kjn12x6n_0wm0000gn%2FT%2FTemporaryItems%2FNSIRD_screencaptureui_ECZWkT%2FScreenshot%202024-12-02%20at%2010.01.48.png)

## особенности
- поддержка работы с архивами `.tar`, включая добавление и извлечение файлов
- поддержка работы с XML-файлами для конфигурации:
  - используется модуль `xml.etree.ElementTree` для парсинга и обработки конфигурационных данных
- создано графическое пользовательское интерфейсное приложение (GUI) на основе библиотеки `tkinter`:
  - управление осуществляется через `ShellGUI`, созданный в модуле `shell_gui`
- основная функциональность управления файловой системой реализована в модуле `shell`

### требования
- Python версии 3.7 или выше установлен
- локальный репозиторий Git должен быть доступен, а папка `.git` должна находиться в указанном пути
- установлены библиотеки `GitPython` и другие зависимости, указанные в `requirements.txt`

### установка
1. клонируйте этот репозиторий или скопируйте код в вашу рабочую папку:
   ```bash
   git clone https://github.com/ваш-репозиторий.git
   cd ваш-репозиторий
   
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