# --- Day 3: Gear Ratios ---

if __name__ == '__main__':
    file = open("gear_ratios_input", "r")
    lines = file.readlines()

    symbols = "*-+/=%#&@!$?^~"

    sum_part_numbers = 0
    gear_ratios = {}

    for i in range(len(lines)):
        gear_at = ""
        number = ""
        is_number = False
        for j in range(len(lines[i])):
            if lines[i][j].isdigit():
                number += lines[i][j]

                for k in range(-1, 2, 1):
                    for n in range(-1, 2, 1):
                        if i + k < 0 or i + k >= len(lines) or j + n < 0 or j + n >= len(lines[i]):
                            continue
                        if lines[i + k][j + n] in symbols:
                            is_number = True
                            if lines[i + k][j + n] == "*":
                                gear_at = str(i + k) + "," + str(j + n)
            else:
                if is_number:
                    sum_part_numbers += int(number)
                    is_number = False

                    if len(gear_at) > 0:
                        if gear_at not in gear_ratios:
                            gear_ratios[gear_at] = []
                        gear_ratios[gear_at].append(int(number))
                        gear_at = ""
                number = ""

    gear_score = 0
    for key in gear_ratios:
        if len(gear_ratios[key]) == 2:
            gear_score += gear_ratios[key][0] * gear_ratios[key][1]

    print("Part 1: " + str(sum_part_numbers))
    print("Part 2: " + str(gear_score))
