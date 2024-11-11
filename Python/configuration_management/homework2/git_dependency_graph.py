import os
import zlib
from datetime import datetime

class GitDependencyGraph:
    def __init__(self, repo_path, branch_name, output_file):
        self.repo_path = repo_path
        self.branch_name = branch_name
        self.output_file = output_file
        self.commits = {}

    def parse_commit(self, commit_hash):
        obj_path = os.path.join(self.repo_path, '.git', 'objects', commit_hash[:2], commit_hash[2:])

        with open(obj_path, 'rb') as f:
            decompressed_data = zlib.decompress(f.read()).decode()
            lines = decompressed_data.splitlines()

            parent = None
            author = None
            date = None

            for line in lines:
                if line.startswith("parent"):
                    parent = line.split()[1]

                elif line.startswith("author"):
                    author = line.split("author ")[1].split(" <")[0]

                elif line.startswith("committer"):
                    date_str = line.split()[-2]
                    date = datetime.utcfromtimestamp(int(date_str)).strftime('%Y-%m-%d %H:%M:%S')

            return parent, author, date

    def build_commit_graph(self):
        branch_ref_path = os.path.join(self.repo_path, '.git', 'refs', 'heads', self.branch_name)

        with open(branch_ref_path, 'r') as f:
            current_commit = f.read().strip()

        while current_commit:
            parent, author, date = self.parse_commit(current_commit)
            self.commits[current_commit] = {"parent": parent, "author": author, "date": date}
            current_commit = parent

    def generate_plantuml_code(self):
        lines = ["@startuml"]
        added_nodes = set()#отслеж добавленных узлов

        for commit, info in self.commits.items():
            node_label = f"{commit[:7]}\\n{info['author']}\\n{info['date']}"#уникальная метка для узла

            if node_label not in added_nodes:#добав узел - если не был добавлен еще
                lines.append(f'"{node_label}"')
                added_nodes.add(node_label)

            if info["parent"]:#если коммит есть - добав связь с предками
                parent_info = self.commits.get(info["parent"])
                
                if parent_info:
                    parent_label = f"{info['parent'][:7]}\\n{parent_info['author']}\\n{parent_info['date']}"

                    if parent_label not in added_nodes:#добав род узел - если еще не был добавлен
                        lines.append(f'"{parent_label}"')
                        added_nodes.add(parent_label)

                    lines.append(f'"{node_label}" --> "{parent_label}"')#эд связь

        lines.append("@enduml")

        with open(self.output_file, 'w') as f:
            f.write("\n".join(lines))
        print(f"сохранен {self.output_file}")


if __name__ == "__main__":
    repo_path = "C:\\Users\\Albina\\Desktop\\localip\\konfig\\homework2"
    branch_name = "master"
    output_file = "C:\\Users\\Albina\\Desktop\\localip\\konfig\\homework2\\output.puml"

    graph = GitDependencyGraph(repo_path, branch_name, output_file)
    graph.build_commit_graph()
    graph.generate_plantuml_code()
