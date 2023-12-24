# --- Day 24: Never Tell Me The Odds --- Part One ---


def line_intersection(line1, line2):
    xdiff = (line1[0][0] - line1[1][0], line2[0][0] - line2[1][0])
    ydiff = (line1[0][1] - line1[1][1], line2[0][1] - line2[1][1])

    def det(a, b):
        return a[0] * b[1] - a[1] * b[0]

    div = det(xdiff, ydiff)
    if div == 0:
       return -1, -1

    d = (det(*line1), det(*line2))
    x = det(d, xdiff) / div
    y = det(d, ydiff) / div

    if min(line1[0][0], line1[1][0]) <= x <= max(line1[0][0], line1[1][0]) and min(line1[0][1], line1[1][1]) <= y <= max(line1[0][1], line1[1][1]) and min(line2[0][0], line2[1][0]) <= x <= max(line2[0][0], line2[1][0]) and min(line2[0][1], line2[1][1]) <= y <= max(line2[0][1], line2[1][1]):
        return x, y
    else:
        return -1, -1


if __name__ == '__main__':
    with open('never_tell_me_the_odds_input') as file:
        lines = file.read().splitlines()

    hailstones = []
    for line in lines:
        position, velocity = line.split('@')
        px, py, pz = map(int, position.split(','))
        vx, vy, vz = map(int, velocity.split(','))
        hailstones.append((px, py, vx, vy))

    at_least = 200000000000000
    at_most = 400000000000000

    intersections = 0
    for i, hailstone, in enumerate(hailstones):
        for hailstone2 in hailstones[i + 1:]:
            x1, y1, vx1, vy1 = hailstone
            x2, y2, vx2, vy2 = hailstone2

            x1_2 = x1 + vx1 * 400000000000000
            y1_2 = y1 + vy1 * 400000000000000
            x2_2 = x2 + vx2 * 400000000000000
            y2_2 = y2 + vy2 * 400000000000000

            x, y = line_intersection(((x1, y1), (x1_2, y1_2)), ((x2, y2), (x2_2, y2_2)))

            if at_least <= x <= at_most and at_least <= y <= at_most:
                intersections += 1

    print('Part 1:', intersections)
