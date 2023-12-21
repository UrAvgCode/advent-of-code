# --- Day 1: Calorie Counting ---

if __name__ == '__main__':
    with open("calorie_counting_input") as file:
        elves = file.read().strip().split("\n\n")

    list_of_calories = [sum(int(calories) for calories in meals.split("\n")) for meals in elves]
    list_of_calories.sort(reverse=True)

    print("Part 1:", list_of_calories[0])
    print("Part 2:", sum(list_of_calories[:3]))
