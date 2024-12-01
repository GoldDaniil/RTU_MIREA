import tkinter as tk
from tkinter import font


class ShellGUI:
    def __init__(self, root, shell):
        self.root = root
        self.shell = shell
        self.root.title(f"{self.shell.user}@{self.shell.host}")#доступ к атрибутам shell
        self.root.geometry("800x600")

        self.text_font = font.nametofont('TkTextFont')
        self.text_font.config(size=12)

        self.entry_font = font.nametofont('TkFixedFont')
        self.entry_font.config(size=14)

        self.root.configure(bg='#2e2e2e')

        self.output_frame = tk.Frame(root, bg='#333333', padx=10, pady=10)
        self.output_frame.pack(fill=tk.BOTH, expand=True, padx=20, pady=10)

        self.output_text = tk.Text(self.output_frame, height=15, width=80, bg='#1e1e1e', fg='white',
                                   font=self.text_font, wrap=tk.WORD, bd=0, padx=10, pady=10)
        self.output_text.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        self.output_text.config(state=tk.DISABLED)#запрет на редактирование

        self.input_frame = tk.Frame(root, bg='#2e2e2e', padx=10, pady=10)#панель для ввода
        self.input_frame.pack(fill=tk.X, padx=20, pady=10)

        self.input_entry = tk.Entry(self.input_frame, width=80, font=self.entry_font, bd=0, fg='white',
                                    bg='#1e1e1e', insertbackground='white', relief=tk.FLAT)
        self.input_entry.bind('<Return>', self.process_command)
        self.input_entry.pack(fill=tk.X)

        self.input_entry.focus()

    def process_command(self, event):
        command = self.input_entry.get()
        self.input_entry.delete(0, tk.END)
        result = self.shell.execute(command)

        # редакт + добав рез + блок редакт
        self.output_text.config(state=tk.NORMAL)

        if command.startswith("ls"):
            color = "#00FF00"
        elif command.startswith("cd"):
            color = "#FFA500"
        elif command.startswith("who"):
            color = "#ADD8E6"
        elif command.startswith("mv"):
            color = "#FFFF00"
        elif command.startswith("wc"):
            color = "#FF6347"
        else:
            color = "#FFFFFF"

        self.output_text.insert(tk.END, f"$ {command}\n", "command")

        self.output_text.insert(tk.END, f"{result}\n", "output")

        self.output_text.tag_configure("command", foreground=color, font=("Courier", 12, "bold"))
        self.output_text.tag_configure("output", foreground="#D3D3D3", font=("Courier", 12))

        self.output_text.yview(tk.END)
        self.output_text.config(state=tk.DISABLED)

    def run(self):
        self.root.mainloop()

    def clear_gui_output(self):
        self.output_text.config(state=tk.NORMAL)
        self.output_text.delete(1.0, tk.END)
        self.output_text.config(state=tk.DISABLED)
