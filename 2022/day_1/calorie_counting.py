# --- Day 1: Calorie Counting ---

if __name__ == '__main__':
    file = open("calorie_counting_input", "r")
    lines = file.readlines()

    calories_list = []
    calories = 0

    for line in lines:
        if line == "\n":
            calories_list.append(calories)
            calories = 0
        else:
            calories += int(line)

    calories_list.sort(reverse=True)

    print("Part 1: " + str(calories_list[0]))
    print("Part 2: " + str(calories_list[0] + calories_list[1] + calories_list[2]))
