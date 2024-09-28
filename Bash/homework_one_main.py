import os
import zipfile
import tarfile
import sys

def pwd():
    print(os.getcwd())

def ls():
    for item in os.listdir(os.getcwd()):
        print(item)

def cd(path):
    try:
        os.chdir(path)
    except FileNotFoundError:
        print(f"каталог {path} не найден")

def cat(filename):
    try:
        with open(filename, 'r') as f:
            print(f.read())
    except FileNotFoundError:
        print(f"файл {filename} не найден")

def run_script(file):
    try:
        with open(file, 'r') as f:
            commands = f.readlines()
            for command in commands:
                run_command(command.strip())
    except FileNotFoundError:
        print(f"файл {file} не найден")

def run_command(command):
    parts = command.split()
    if not parts:
        return
    cmd = parts[0]

    if cmd == "pwd":
        pwd()
    elif cmd == "ls":
        ls()
    elif cmd == "cd" and len(parts) > 1:
        cd(parts[1])
    elif cmd == "cat" and len(parts) > 1:
        cat(parts[1])
    else:
        print(f"команда {cmd} не поддерживается")

def open_filesystem(fs_path):
    if zipfile.is_zipfile(fs_path):
        with zipfile.ZipFile(fs_path, 'r') as zip_ref:
            zip_ref.extractall('/tmp/vshell_fs')
    elif tarfile.is_tarfile(fs_path):
        with tarfile.open(fs_path, 'r') as tar_ref:
            tar_ref.extractall('/tmp/vshell_fs')
    else:
        print(f"файл {fs_path} не поддерживается")

def main():
    if len(sys.argv) < 2:
        print("использование: vshell файл_системы [--script имя_файла]")
        return

    fs_path = sys.argv[1]
    open_filesystem(fs_path)

    os.chdir('/tmp/vshell_fs')

    if len(sys.argv) == 4 and sys.argv[2] == "--script":
        run_script(sys.argv[3])
    else:
        while True:
            command = input("> ")
            if command in ("exit", "quit"):
                break
            run_command(command)

if __name__ == "__homework_one_main__":
    main()
