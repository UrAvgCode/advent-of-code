# --- Day 4: Camp Cleanup ---

if __name__ == '__main__':
    with open("camp_cleanup_input") as file:
        pairs = file.read().strip().split("\n")

    contains = 0
    overlaps = 0
    for line in pairs:
        first, second = [tuple([int(bound) for bound in assignment.split("-")]) for assignment in line.split(",")]
        overlap = (max(first[0], second[0]), min(first[1], second[1]))
        contains += overlap == first or overlap == second
        overlaps += overlap[0] <= overlap[1]

    print("Part 1:", contains)
    print("Part 2:", overlaps)
