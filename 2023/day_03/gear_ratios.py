# --- Day 3: Gear Ratios ---

if __name__ == "__main__":
    with open("gear_ratios_input") as file:
        schematic = ["." + line + "." for line in file.read().splitlines()]

    schematic.append("." * len(schematic[0]))
    schematic.insert(0, "." * len(schematic[0]))

    symbols = set("*-+/=%#&@$")

    part_numbers_sum = 0
    gear_ratios = {}
    for y in range(1, len(schematic) - 1):
        gear_at = ()
        number = ""
        is_number = False
        for x in range(len(schematic[y])):
            if schematic[y][x].isdigit():
                number += schematic[y][x]

                for dy in (-1, 0, 1):
                    for dx in (-1, 0, 1):
                        if schematic[y + dy][x + dx] in symbols:
                            is_number = True
                            if schematic[y + dy][x + dx] == "*":
                                gear_at = (y + dy, x + dx)
            else:
                if is_number:
                    part_numbers_sum += int(number)
                    is_number = False

                    if len(gear_at) > 0:
                        if gear_at not in gear_ratios:
                            gear_ratios[gear_at] = []
                        gear_ratios[gear_at].append(int(number))
                        gear_at = ()
                number = ""

    gear_score = 0
    for part_numbers in gear_ratios.values():
        if len(part_numbers) == 2:
            gear_score += part_numbers[0] * part_numbers[1]

    print("Part 1:", part_numbers_sum)
    print("Part 2:", gear_score)
