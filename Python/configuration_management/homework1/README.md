# проект: разработать эмулятор для языка оболочки ОС

## описание
проект позволяет создать виртуальную файловую систему с поддержкой архивации файлов в формате `.tar`. пользователь может добавлять, извлекать файлы, очищать коммандую строку, выводить содержимое текущего каталога, перемещать файлы.




## индивидуальный вариант
<img width="700" alt="Screenshot 2024-12-02 at 10 08 33" src="https://github.com/user-attachments/assets/64fe513b-9470-4629-a049-1b94493a3138">





## структура проекта
<img width="1000" alt="Screenshot 2024-12-02 at 09 41 22" src="https://github.com/user-attachments/assets/97db5a59-2bae-4fed-a4b8-f29558e16536">





## реализация
<img width="700" alt="Screenshot 2024-12-02 at 09 57 05" src="https://github.com/user-attachments/assets/add50c7a-a2e8-43c3-a4b1-9bf4dce2bdc4">
<img width="700" alt="Screenshot 2024-12-02 at 09 57 39" src="https://github.com/user-attachments/assets/41fccc4f-dea9-4922-87af-c9ca6a15300b">
<img width="700" alt="Screenshot 2024-12-02 at 09 57 32" src="https://github.com/user-attachments/assets/b3b3b328-e5bb-4b46-bc90-361c4f39a65b">
<img width="700" alt="Screenshot 2024-12-02 at 09 57 26" src="https://github.com/user-attachments/assets/1894bea0-0707-47a6-adb5-56fc11b983a7">
<img width="700" alt="Screenshot 2024-12-02 at 09 57 15" src="https://github.com/user-attachments/assets/fa619435-26ca-426c-9702-bafb504e2659">
<img width="700" alt="Screenshot 2024-12-02 at 09 57 10" src="https://github.com/user-attachments/assets/877e94b5-bd9b-40ba-ae4e-80154bc055a0">


<img width="799" alt="Screenshot 2024-12-02 at 10 01 36" src="https://github.com/user-attachments/assets/69cf3b73-38fb-4d5d-98ee-204d2b985ad6">

<img width="802" alt="Screenshot 2024-12-02 at 10 08 17" src="https://github.com/user-attachments/assets/440ae7ab-7525-4ed0-866c-3b5d9e6db9d9">











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
