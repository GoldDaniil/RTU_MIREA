import tkinter as tk

class ShellGUI:
    def __init__(self, root, shell):
        self.root = root
        self.shell = shell
        self.root.title(f"{self.shell.user}@{self.shell.host}")

        self.output_text = tk.Text(root, height=20, width=80)
        self.output_text.pack()

        self.input_entry = tk.Entry(root, width=80)
        self.input_entry.bind('<Return>', self.process_command)
        self.input_entry.pack()

    def process_command(self, event):
        command = self.input_entry.get()
        self.input_entry.delete(0, tk.END)
        result = self.shell.execute(command)
        self.output_text.insert(tk.END, f"$ {command}\n{result}\n")
        self.output_text.yview(tk.END)

    def run(self):
        self.root.mainloop()
