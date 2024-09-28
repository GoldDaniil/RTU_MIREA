import os
import tarfile
import zipfile
import sys

class VShell:
    def __init__(self, filesystem_path):
        self.fs_path = filesystem_path
        self.current_dir = '/'
        self.fs = self.load_filesystem()

    def load_filesystem(self):
        if tarfile.is_tarfile(self.fs_path):
            return tarfile.open(self.fs_path, 'r')
        elif zipfile.is_zipfile(self.fs_path):
            return zipfile.ZipFile(self.fs_path, 'r')
        else:
            print("unsupported file format!!!")
            sys.exit(1)

    def pwd(self):
        print(self.current_dir)

    def ls(self):
        members = self.fs.namelist()
        for member in members:
            if member.startswith(self.current_dir.strip('/')):
                name = member[len(self.current_dir.strip('/')):].strip('/')
                if name:
                    print(name)

    def cd(self, path):
        if path == '/':
            self.current_dir = '/'
        elif path == '..':
            self.current_dir = os.path.dirname(self.current_dir.strip('/')) + '/'
        else:
            potential_dir = os.path.join(self.current_dir.strip('/'), path).strip('/')
            if any(member.startswith(potential_dir + '/') for member in self.fs.namelist()):
                self.current_dir = potential_dir + '/'
            else:
                print("no such directory!")

    def cat(self, filename):
        filepath = os.path.join(self.current_dir.strip('/'), filename).strip('/')
        if filepath in self.fs.namelist():
            with self.fs.open(filepath) as file:
                print(file.read().decode())
        else:
            print(f"{filename}: no such file")

    def execute(self, command_line):
        command_parts = command_line.strip().split()
        if len(command_parts) == 0:
            return

        command = command_parts[0]
        if command == 'pwd':
            self.pwd()
        elif command == 'ls':
            self.ls()
        elif command == 'cd':
            if len(command_parts) > 1:
                self.cd(command_parts[1])
            else:
                print("cd: missing argument")
        elif command == 'cat':
            if len(command_parts) > 1:
                self.cat(command_parts[1])
            else:
                print("cat: missing argument")
        else:
            print(f"{command}: command not found")

def run_script(vshell, script_file):
    try:
        with open(script_file, 'r') as f:
            for line in f:
                vshell.execute(line)
    except FileNotFoundError:
        print(f"script file {script_file} not found")

def test_vs():
    fs_path = 'test_fs.zip'
    vshell = VShell(fs_path)
    vshell.pwd()
    vshell.ls()
    vshell.cd('folder')
    vshell.ls()
    vshell.cat('file.txt')
    vshell.cd('..')
    vshell.pwd()

def main():
    if len(sys.argv) < 2:
        print("usage: python vshell.py <filesystem> [--script script_file]")
        sys.exit(1)

    filesystem_path = sys.argv[1]
    vshell = VShell(filesystem_path)

    if '--script' in sys.argv:
        script_idx = sys.argv.index('--script') + 1
        if script_idx < len(sys.argv):
            script_file = sys.argv[script_idx]
            run_script(vshell, script_file)
        else:
            print("error: Script file not specified")
    else:
        print("welcome to vshell! Type commands (pwd, ls, cd, cat) or 'exit' to quit.")
        while True:
            command = input('vshell> ')
            if command == 'exit':
                break
            vshell.execute(command)

if __name__ == "__main__":
    main()
