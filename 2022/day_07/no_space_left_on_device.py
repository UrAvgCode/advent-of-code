# --- Day 7: No Space Left On Device ---

class Node:
    def __init__(self, parent=None):
        self.parent = parent
        self.children = dict()
        self.size = 0

    def __getitem__(self, item):
        if item == "..":
            return self.parent
        elif item not in self.children:
            self.children[item] = Node(self)
        return self.children[item]


def analyze_disk_usage(folder):
    for child in folder.children.values():
        folder.size += analyze_disk_usage(child)
    return folder.size


def directory_size_list(node):
    sizes = [child.size for child in node.children.values()]
    for child in node.children.values():
        sizes.extend(directory_size_list(child))
    return sizes


if __name__ == '__main__':
    with open("no_space_left_on_device_input") as file:
        commands = file.read().splitlines()

    current_dir = root = Node()
    for command in commands:
        ident, name = command.rsplit(' ', 1)
        if ident == "$ cd":
            current_dir = current_dir[name]
        elif ident.isnumeric():
            current_dir.size += int(ident)

    analyze_disk_usage(root)
    directory_sizes = directory_size_list(root)

    small_directories_size = sum(size for size in directory_sizes if size <= 100000)

    needed_space = root.size - 40000000
    deletion_size = min(size for size in directory_sizes if needed_space < size)

    print("Part 1:", small_directories_size)
    print("Part 2:", deletion_size)
