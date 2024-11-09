import subprocess

def get_commit_log(git_path, branch):
    command = ["git", "-C", git_path, "log", "--pretty=format:%h %p %an %ad", "--date=short"]
    result = subprocess.run(command, capture_output=True, text=True)

    if result.returncode != 0:
        raise Exception("ошибка = git log")

    return result.stdout

def generate_dependency_graph(git_path, branch):
    log = get_commit_log(git_path, branch)

    graph = "@startuml\n"
    graph += "digraph G {\n"

    commits = log.strip().split("\n")

    for commit in commits:
        parts = commit.strip().split(" ")
        commit_hash = parts[0]#хеш коммита
        parents = parts[1:-2]#родители коммита (все элементы до имени автора) + включая сорс
        author = parts[-2]#автор коммита
        date = parts[-1]#дата коммита

        graph += f'"{commit_hash}" [label="{commit_hash}\\n{author}\\n{date}"];\n'

        for parent in parents:#ток если есть зависимость
            if parent:
                graph += f'"{parent}" -> "{commit_hash}";\n'

    graph += "}\n@enduml"

    return graph

def save_graph(graph, output_file):
    with open(output_file, "w") as f:
        f.write(graph)
    print(f"граф успешно сохранен в {output_file}")

git_path = "C:/Users//Desktop/localip/konfig/homework2"
branch = "master"#ветка
output_file = "C:/Users//Desktop/output.txt"
#dependency_visualizer.py
graph = generate_dependency_graph(git_path, branch)

save_graph(graph, output_file)
