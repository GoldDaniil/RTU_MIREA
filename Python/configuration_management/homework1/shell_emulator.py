import xml.etree.ElementTree as ET
from shell import Shell
from shell_gui import ShellGUI
import tkinter as tk


def main():
    tree = ET.parse('config.xml')
    root = tree.getroot()

    config = {
        'user': root.find('user').text,
        'host': root.find('host').text,
        'vfs_path': root.find('vfs_path').text,
    }

    shell = Shell(config)

    root = tk.Tk()
    gui = ShellGUI(root, shell)#передаем объект shell в ShellGUI
    shell.shell_gui = gui#устанавливаем ссылку на GUI в объект Shell

    gui.run()


if __name__ == "__main__":
    main()
