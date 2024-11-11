import unittest
#from dependency_visualizer import get_commits, get_parents, generate_plantuml
import argparse
import subprocess
from datetime import datetime
import unittest

class TestDependencyVisualizer(unittest.TestCase):
    def test_get_commits(self):
        #commits = get_commits("/path/to/repo", "main")
        #self.assertIsInstance(commits, list)

    def test_get_parents(self):
        #parents = get_parents("/path/to/repo", "a_commit_hash")
        #self.assertIsInstance(parents, list)

    def test_generate_plantuml(self):
        # Проверка генерации PlantUML кода
        commits = [("hash1", datetime.now(), "Author1")]
        #result = generate_plantuml(commits, "/path/to/repo")
        #self.assertIn("@startuml", result)
        #self.assertIn("@enduml", result)

if __name__ == "__main__":
    unittest.main()
