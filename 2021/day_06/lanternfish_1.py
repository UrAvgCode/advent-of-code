# --- Day 6: Lanternfish --- Part One ---

if __name__ == '__main__':
    with open('../../input/2021/day_06/input.txt') as file:
        fish_list = list(map(int, file.read().split(',')))

    for _ in range(80):
        for i, fish in enumerate(fish_list.copy()):
            if fish > 0:
                fish_list[i] -= 1
            else:
                fish_list[i] = 6
                fish_list.append(8)

    print('Part 1:', len(fish_list))
