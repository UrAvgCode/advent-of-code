# --- Day 3: Rucksack Reorganization ---

if __name__ == '__main__':
    file = open("rucksack_reorganization_input", "r")
    lines = file.readlines()

    prioList = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

    priorities_one = 0
    priorities_two = 0

    for i in range(len(lines)):
        line = lines[i].strip()

        compartment_size = len(line) // 2
        for j in range(compartment_size):
            if line[j] in lines[i][compartment_size:]:
                priorities_one += prioList.index(line[j]) + 1
                break

        if i % 3 == 0:
            for j in range(len(lines[i])):
                if line[j] in lines[i + 1] and lines[i][j] in lines[i + 2]:
                    priorities_two += prioList.index(line[j]) + 1
                    break

    print("Part 1: " + str(priorities_one))
    print("Part 2: " + str(priorities_two))
