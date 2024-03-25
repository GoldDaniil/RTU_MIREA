class Tree:
    def __init__(self, data):
        self.left = None
        self.right = None
        self.data = data

    def insert(self, data):
        if data < self.data:
            if self.left is None:
                self.left = Tree(data)
            else:
                self.left.insert(data)
        elif data > self.data:
            if self.right is None:
                self.right = Tree(data)
            else:
                self.right.insert(data)

    def print_tree(self):
        if self.left:
            self.left.print_tree()
        print(self.data)
        if self.right:
            self.right.print_tree()


# Пример использования класса Tree
if __name__ == '__main__':
    root = Tree(5)
    root.insert(3)
    root.insert(7)
    root.insert(2)
    root.insert(4)
    root.insert(6)
    root.insert(8)
    
    print("Полное дерево:")
    root.print_tree()
