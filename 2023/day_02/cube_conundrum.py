# --- Day 2: Cube Conundrum ---

def get_cube_counts(games):
    cube_counts = []
    for game in games:
        color_counts = {"red": 0, "green": 0, "blue": 0}
        for count_str, color in (cube.split() for cube in game):
            count = int(count_str)
            color_counts[color] = max(count, color_counts[color])
        cube_counts.append((color_counts["red"], color_counts["green"], color_counts["blue"]))
    return cube_counts


if __name__ == '__main__':
    with open("cube_conundrum_input") as file:
        games = [game.split(": ")[1].split(', ') for game in file.read().replace(';', ',').splitlines()]

    cube_counts = get_cube_counts(games)
    cube_products = sum(red * green * blue for red, green, blue in cube_counts)
    valid_game_ids = sum(game_id for game_id, (red, green, blue) in enumerate(cube_counts, 1)
                         if red <= 12 and green <= 13 and blue <= 14)

    print("Part 1:", valid_game_ids)
    print("Part 2:", cube_products)
