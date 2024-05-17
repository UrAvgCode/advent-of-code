# --- Day 3: Binary Diagnostic --- Part Two ---

from collections import Counter

if __name__ == '__main__':
    with open('../../input/2021/day_03/input.txt') as file:
        report = file.read().splitlines()

    oxygen_ratings = report.copy()
    co2_ratings = report.copy()

    i = 0
    while len(oxygen_ratings) > 1:
        counts = Counter([row[i] for row in oxygen_ratings])
        most_common_bit = '1' if counts['1'] >= counts['0'] else '0'
        oxygen_ratings = [row for row in oxygen_ratings if row[i] == most_common_bit]
        i += 1

    i = 0
    while len(co2_ratings) > 1:
        counts = Counter([row[i] for row in co2_ratings])
        least_common_bit = '0' if counts['1'] >= counts['0'] else '1'
        co2_ratings = [row for row in co2_ratings if row[i] == least_common_bit]
        i += 1

    print('Part 2:', int(oxygen_ratings[0], 2) * int(co2_ratings[0], 2))
