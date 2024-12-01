import os
import subprocess
import shutil
import datetime
from vfs import VFS

class Shell:
    def __init__(self, config):
        self.config = config
        self.vfs = VFS(config['vfs_path'])
        self.current_path = '/'
        self.user = config['user']
        self.host = config['host']

    def execute(self, command):
        parts = command.strip().split()
        if not parts:
            return ''

        cmd = parts[0]
        args = parts[1:]

        if cmd == 'ls':
            return self.ls()
        elif cmd == 'cd':
            return self.cd(args[0]) if args else 'cd: missing argument'
        elif cmd == 'exit':
            return self.exit()
        elif cmd == 'mv':
            return self.mv(args[0], args[1]) if len(args) == 2 else 'mv: missing arguments'
        elif cmd == 'clear':
            return self.clear()
        elif cmd == 'who':
            return self.who()
        elif cmd == 'wc':
            return self.wc(args[0]) if args else 'wc: missing file'
        else:
            return f"unknown command: {cmd}"

    def ls(self):
        try:
            contents = self.vfs.list_dir(self.current_path)
            if contents:
                return '\n'.join(contents)
            return 'empty directory'
        except Exception as e:
            return f"ls: error listing directory: {str(e)}"

    def cd(self, path):
        try:
            if path == '..':#на уровень выше
                new_path = os.path.dirname(self.current_path.rstrip('/'))
                self.current_path = new_path if new_path else '/'
            else:
                new_path = os.path.join(self.current_path, path).replace('\\', '/')
                if self.vfs.directory_exists(new_path):
                    self.current_path = new_path
                else:
                    return f"cd: no such directory: {path}"
            return f"changed directory to {self.current_path}"
        except Exception as e:
            return f"cd: error changing directory: {str(e)}"

    def exit(self):
        self.vfs.close()
        return "exiting..."

    def mv(self, source, destination):
        try:
            if not self.vfs.file_exists(source):#существует ли исходный файл
                return f"mv: source file '{source}' not found"

            dest_dir = os.path.dirname(destination)#существует ли директория назначения
            if not self.vfs.directory_exists(dest_dir):
                return f"mv: target directory '{dest_dir}' not found"

            content = self.vfs.read_file(source)#чтение исходного файла

            self.vfs.write_file(destination, content)#запись файла в новое место

            self.vfs.delete_file(source)#удаляем исходный файл

            return f"Moved {source} to {destination}"
        except Exception as e:
            return f"mv: error moving file: {str(e)}"

    def clear(self):
        return "\033c"#ANSI

    def who(self):
        try:
            return subprocess.getoutput("who")
        except Exception as e:
            return f"who: error executing command: {str(e)}"

    def wc(self, filename):
        try:
            content = self.vfs.read_file(filename)
            lines = content.splitlines()
            words = content.split()
            characters = len(content)
            return f"{len(lines)} {len(words)} {characters} {filename}"
        except KeyError:
            return f"wc: file '{filename}' not found"
        except Exception as e:
            return f"wc: error processing file '{filename}': {str(e)}"

