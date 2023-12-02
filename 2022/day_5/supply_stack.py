# --- Day 5: Supply Stacks ---

if __name__ == '__main__':
    file = open("supply_stacks_input", "r")
    lines = file.readlines()

    stacks_one = []
    stacks_two = []

    for i in range(9):
        stack_pos_x = 1 + i * 4
        stack = []
        for line in range(8):
            crate = lines[line][stack_pos_x]
            if crate != " ":
                stack.append(crate)

        stack.reverse()
        stacks_one.append(stack)
        stacks_two.append(stack.copy())

    for line in lines[10:]:
        procedure = line.split()

        source = int(procedure[3]) - 1
        dest = int(procedure[5]) - 1
        repetitions = int(procedure[1])

        for i in range(repetitions):
            stacks_one[dest].append(stacks_one[source].pop())

        stacks_two[dest].extend(stacks_two[source][-repetitions:])
        stacks_two[source] = stacks_two[source][0:len(stacks_two[source]) - repetitions]

    top_crates_one = ""
    for stack in stacks_one:
        top_crates_one += stack[-1]

    top_crates_two = ""
    for stack in stacks_two:
        top_crates_two += stack[-1]

    print("Part 1: " + top_crates_one)
    print("Part 2: " + top_crates_two)
