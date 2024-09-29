import os
import tarfile
import xml.etree.ElementTree as ET
import subprocess

# функция для загрузки конфигурационного файла
def load_config(config_file):
    tree = ET.parse(config_file)
    root = tree.getroot()

    computer_name = root.find('computer_name').text
    tar_path = root.find('tar_path').text
    start_script_path = root.find('start_script').text

    return computer_name, tar_path, start_script_path

# функция для извлечения виртуальной файловой системы
def extract_tar(tar_path, extract_path="virtual_fs"):
    with tarfile.open(tar_path, "r") as tar:
        tar.extractall(extract_path)
    return extract_path

# основная функция для выполнения команд
def shell_prompt(computer_name, virtual_fs_path):
    current_dir = virtual_fs_path

    while True:
        command = input(f"{computer_name}:{current_dir}$ ").strip()

        if command == "exit":
            print("exit...")
            break
        elif command == "ls":
            print("\n".join(os.listdir(current_dir)))
        elif command.startswith("cd"):
            parts = command.split()
            if len(parts) > 1:
                new_dir = os.path.join(current_dir, parts[1])
                if os.path.exists(new_dir) and os.path.isdir(new_dir):
                    current_dir = new_dir
                else:
                    print(f"error: directory '{parts[1]}' not found!")
            else:
                print("error: specify the directory")
        elif command.startswith("mv"):
            parts = command.split()
            if len(parts) > 2:
                src = os.path.join(current_dir, parts[1])
                dst = os.path.join(current_dir, parts[2])
                try:
                    os.rename(src, dst)
                except Exception as e:
                    print(f"error when moving: {e}")
            else:
                print("error: not enought arguments")
        elif command == "clear":
            subprocess.run('clear' if os.name == 'posix' else 'cls', shell=True)
        elif command == "who":
            print("user: gold")
        else:
            print(f"command '{command}' not found")

# функция для выполнения стартового скрипта
def run_start_script(start_script_path, virtual_fs_path):
    try:
        with open(start_script_path, 'r') as script:
            commands = script.readlines()
            for command in commands:
                command = command.strip()
                if command:
                    print(f"in progress: {command}")
                    # выполнение команд из скрипта
                    if command.startswith("cd"):
                        parts = command.split()
                        if len(parts) > 1:
                            virtual_fs_path = os.path.join(virtual_fs_path, parts[1])
                    elif command == "clear":
                        subprocess.run('clear' if os.name == 'posix' else 'cls', shell=True)
                    else:
                        print(f"skip: the '{command}' command is not supported yet")
    except FileNotFoundError:
        print("error: the startup script was not found")

# основная функция запуска эмулятора
def main():
    config_file = "config.xml"  # путь к конфигурационному файлу
    computer_name, tar_path, start_script_path = load_config(config_file)

    # извлечение виртуальной файловой системы
    virtual_fs_path = extract_tar(tar_path)

    # выполнение стартового скрипта
    run_start_script(start_script_path, virtual_fs_path)

    # запуск эмулятора
    shell_prompt(computer_name, virtual_fs_path)

if __name__ == "__main__":
    main()
