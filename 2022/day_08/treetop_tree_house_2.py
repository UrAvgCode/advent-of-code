# --- Day 8: Treetop Tree House --- Part Two ---

def get_scenic_score(forest):
    forest_size = len(forest)
    scenic_scores = []
    for x in range(forest_size):
        for y in range(forest_size):
            tree_size = int(forest[y][x])

            trees_downwards = 0
            for dy in range(y + 1, forest_size):
                trees_downwards += 1
                if int(forest[dy][x]) >= tree_size:
                    break

            trees_upwards = 0
            for dy in range(y - 1, -1, -1):
                trees_upwards += 1
                if int(forest[dy][x]) >= tree_size:
                    break

            trees_rightwards = 0
            for dx in range(x + 1, forest_size):
                trees_rightwards += 1
                if int(forest[y][dx]) >= tree_size:
                    break

            trees_leftwards = 0
            for dx in range(x - 1, -1, -1):
                trees_leftwards += 1
                if int(forest[y][dx]) >= tree_size:
                    break

            scenic_scores.append(trees_downwards * trees_upwards * trees_rightwards * trees_leftwards)

    return max(scenic_scores)


if __name__ == '__main__':
    with open("../../input/2022/day_08/input.txt") as file:
        forest = file.read().splitlines()

    print("Part 2:", get_scenic_score(forest))
