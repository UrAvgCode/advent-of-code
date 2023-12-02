# --- Day 8: Treetop Tree House ---

if __name__ == '__main__':
    file = open("treetop_tree_house_input", "r")
    lines = file.readlines()

    for i in range(len(lines)):
        lines[i] = lines[i].strip()

    forest_size = len(lines[0])
    visible_forest = [[False for _ in range(forest_size)] for _ in range(forest_size)]
    scenic_scores = []

    for i in range(forest_size):
        tree_size = -1
        for y in range(forest_size):
            if int(lines[y][i]) > tree_size:
                visible_forest[i][y] = True
                tree_size = int(lines[y][i])

        tree_size = -1
        for y in range(forest_size - 1, -1, -1):
            if int(lines[y][i]) > tree_size:
                visible_forest[i][y] = True
                tree_size = int(lines[y][i])

        tree_size = -1
        for x in range(forest_size):
            if int(lines[i][x]) > tree_size:
                visible_forest[x][i] = True
                tree_size = int(lines[i][x])

        tree_size = -1
        for x in range(forest_size - 1, -1, -1):
            if int(lines[i][x]) > tree_size:
                visible_forest[x][i] = True
                tree_size = int(lines[i][x])

    for x in range(forest_size):
        for y in range(forest_size):
            tree_size = int(lines[y][x])

            trees_downwards = 0
            for delta_y in range(y + 1, forest_size):
                trees_downwards += 1
                if int(lines[delta_y][x]) >= tree_size:
                    break

            trees_upwards = 0
            for delta_y in range(y - 1, -1, -1):
                trees_upwards += 1
                if int(lines[delta_y][x]) >= tree_size:
                    break

            trees_rightwards = 0
            for delta_x in range(x + 1, forest_size):
                trees_rightwards += 1
                if int(lines[y][delta_x]) >= tree_size:
                    break

            trees_leftwards = 0
            for delta_x in range(x - 1, -1, -1):
                trees_leftwards += 1
                if int(lines[y][delta_x]) >= tree_size:
                    break

            scenic_scores.append(trees_downwards * trees_upwards * trees_rightwards * trees_leftwards)

    visible_trees = sum([sum(x) for x in visible_forest])
    scenic_score = max(scenic_scores)

    print("Part 1: " + str(visible_trees))
    print("Part 2: " + str(scenic_score))
