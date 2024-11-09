import argparse
import subprocess

def get_commits(git_path, branch):
    print(f"запуск команды git log для пути: {git_path} и ветки: {branch}")
    command = ["git", "-C", git_path, "log", branch, "--pretty=format:%H|%an|%ad"]
    result = subprocess.run(command, capture_output=True, text=True)

    if result.returncode != 0:
        print("ошибка команды git log:", result.stderr)
        return []

    commits = result.stdout.strip().split("\n")
    print("полученные коммиты:", commits)  
    return commits


def create_dependency_graph(commits):
    if not commits:
        print("нет коммитов для создания графа")
        return "@startuml\n@enduml"

    lines = ["@startuml", "digraph G {"]
    previous_commit = None

    for commit in commits:
        #в случае лойала сайтнуть хешап(test.py)
        print(f"обработка коммита: {commit}")
        commit_hash, author, date = commit.split("|")
        node = f'"{commit_hash}" [label="{author}\n{date}"];'
        lines.append(node)

        if previous_commit:
            edge = f'"{previous_commit}" -> "{commit_hash}";'
            lines.append(edge)

        previous_commit = commit_hash

    lines.append("}")
    lines.append("@enduml")
    graph = "\n".join(lines)
    print("сгенерированный граф:", graph)
    return graph


def save_graph(graph, output_file):
    print(f"сохранение графа в файл: {output_file}")
    try:
        with open(output_file, "w") as file:
            file.write(graph)
        print("граф успешно сохранен")
    except Exception as e:
        print("ошибка - сохранен граф:", e)

def main():
    parser = argparse.ArgumentParser(description="визуализатор = git-репозиторий")
    parser.add_argument("--git-path", required=True, help="путь - репозиторий")
    parser.add_argument("--output-file", required=True, help="путь - рез")
    parser.add_argument("--branch", required=True, help="имя ветки - репозиторий")
    args = parser.parse_args()

    commits = get_commits(args.git_path, args.branch)

    graph = create_dependency_graph(commits)

    save_graph(graph, args.output_file)

if __name__ == "__main__":
    main()
