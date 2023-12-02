# --- Day 7: No Space Left On Device ---

class Node:
    def __init__(self, name, parent):
        self.name = name
        self.size = 0
        self.children = []
        self.parent = parent


def set_directory_size(node):
    if len(node.children) != 0:
        for child in node.children:
            set_directory_size(child)
            node.size += child.size


def directory_size_list(node, size_list):
    for child in node.children:
        directory_size_list(child, size_list)
    size_list.append(node.size)


if __name__ == '__main__':
    file = open("no_space_left_on_device_input", "r")
    lines = file.readlines()

    root = Node("root", "")

    currentDirectory = root

    for line in lines:
        parts = line.strip().split()
        if parts[0] == "$":
            if parts[1] == "ls":
                continue
            elif parts[1] == "cd":
                if parts[2] == "..":
                    currentDirectory = currentDirectory.parent
                    continue
                else:
                    find = False
                    for directory in currentDirectory.children:
                        if parts[2] == directory.name:
                            currentDirectory = directory
                            find = True
                            break

                    if not find:
                        newDir = Node(parts[2], currentDirectory)
                        currentDirectory.children.append(newDir)
                        currentDirectory = newDir

        elif parts[0] == "dir":
            continue
        else:
            currentDirectory.size += int(parts[0])

    set_directory_size(root)

    directory_sizes = []
    directory_size_list(root, directory_sizes)

    total_directories_size = 0
    for size in directory_sizes:
        if size <= 100000:
            total_directories_size += size

    available_space = 70000000 - root.size
    needed_space = 30000000 - available_space

    deletion_size = root.size
    for directory_size in directory_sizes:
        if needed_space < directory_size < deletion_size:
            deletion_size = directory_size

    print("Part 1: " + str(total_directories_size))
    print("Part 2: " + str(deletion_size))
