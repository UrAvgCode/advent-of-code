# --- Day 4: Camp Cleanup ---

if __name__ == '__main__':
    file = open("camp_cleanup_input", "r")
    lines = file.readlines()

    contains_other = 0
    overlaps_other = 0

    for line in lines:
        ranges = line.strip().replace(",", "-").split("-")
        asgmnt_one = set(range(int(ranges[0]), int(ranges[1]) + 1))
        asgmnt_two = set(range(int(ranges[2]), int(ranges[3]) + 1))

        if asgmnt_one.issubset(asgmnt_two) or asgmnt_two.issubset(asgmnt_one):
            contains_other += 1

        if asgmnt_one.intersection(asgmnt_two):
            overlaps_other += 1

    print("Part 1: " + str(contains_other))
    print("Part 2: " + str(overlaps_other))
