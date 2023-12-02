# --- Day 2: Cube Conundrum ---

if __name__ == '__main__':
    file = open("cube_conundrum_input", "r")
    lines = file.readlines()

    added_ids = 0
    added_powers = 0

    for line in lines:
        parts = line.split()

        parts.pop(0)
        game_id = int(parts.pop(0).replace(":", ""))
        amounts = {"red": 0, "green": 0, "blue": 0}

        for i in range(len(parts) // 2):
            amount = int(parts.pop(0))
            color = parts.pop(0).replace(",", "")
            color = color.replace(";", "")

            amounts[color] = max(amount, amounts[color])

        if amounts["red"] <= 12 and amounts["green"] <= 13 and amounts["blue"] <= 14:
            added_ids += game_id

        added_powers += amounts["red"] * amounts["green"] * amounts["blue"]

    print("Part 1: " + str(added_ids))
    print("Part 2: " + str(added_powers))
