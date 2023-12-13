# --- Day 13: Point of Incidence --- Part Two ----

from collections import deque


def get_reflection_sum(accuracy=0):
    reflection_sum = 0
    for pattern in patterns:
        transposed_pattern = list(zip(*pattern))

        for is_horizontal, directed_pattern in enumerate((transposed_pattern, pattern)):
            for mirror_position in range(1, len(directed_pattern)):
                reality = deque(directed_pattern[:mirror_position])
                reflection = deque(directed_pattern[mirror_position:])
                difference = 0

                while reality and reflection:
                    opposites = zip(reality.pop(), reflection.popleft())
                    difference += sum(a != b for a, b in opposites)

                    if difference > accuracy:
                        break
                else:
                    if difference == accuracy:
                        reflection_sum += mirror_position * 100 if is_horizontal else mirror_position
                        break

    return reflection_sum


if __name__ == '__main__':
    with open("point_of_incidence_input") as file:
        patterns = [p.splitlines() for p in file.read().split("\n\n")]

    print("Part 1:", get_reflection_sum())
    print("Part 2:", get_reflection_sum(1))
