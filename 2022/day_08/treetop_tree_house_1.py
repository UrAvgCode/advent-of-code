# --- Day 8: Treetop Tree House --- Part One ---

def get_visible_trees(forest):
    forest_size = len(forest)
    visible_forest = [[False] * forest_size for _ in range(forest_size)]

    for i, field_of_view in enumerate(visible_forest):
        tree_size_left_to_right = -1
        tree_size_right_to_left = -1
        tree_size_top_to_bottom = -1
        tree_size_bottom_to_top = -1

        for distance in range(len(visible_forest)):
            # Check from top to bottom
            current_tree_size = forest[distance][i]
            if current_tree_size > tree_size_top_to_bottom:
                field_of_view[distance] = True
                tree_size_top_to_bottom = current_tree_size

            # Check from bottom to top
            current_tree_size = forest[forest_size - 1 - distance][i]
            if current_tree_size > tree_size_bottom_to_top:
                field_of_view[forest_size - 1 - distance] = True
                tree_size_bottom_to_top = current_tree_size

            # Check from left to right
            current_tree_size = forest[i][distance]
            if current_tree_size > tree_size_left_to_right:
                field_of_view[distance] = True
                tree_size_left_to_right = current_tree_size

            # Check from right to left
            current_tree_size = forest[i][forest_size - 1 - distance]
            if current_tree_size > tree_size_right_to_left:
                field_of_view[forest_size - 1 - distance] = True
                tree_size_right_to_left = current_tree_size

    return sum(sum(row) for row in visible_forest)


if __name__ == '__main__':
    with open("treetop_tree_house_input") as file:
        forest = [list(map(int, line)) for line in file.read().splitlines()]

    print("Part 1:", get_visible_trees(forest))
