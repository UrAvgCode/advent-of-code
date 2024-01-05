# --- Day 6: Lanternfish ---

if __name__ == '__main__':
    with open('lanternfish_input') as file:
        fish_list = list(map(int, file.read().split(',')))

    for _ in range(80):
        for i, fish in enumerate(fish_list):
            if fish > 0:
                fish_list[i] -= 1
            else:
                fish_list[i] = 6
                fish_list.append(9)

    print('Part 1:', len(fish_list))
