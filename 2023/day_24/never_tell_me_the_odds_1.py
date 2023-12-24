# --- Day 24: Never Tell Me The Odds --- Part One ---


def line_intersection(position1, velocity1, position2, velocity2):
    x1, y1 = position1
    vx1, vy1 = velocity1

    x3, y3 = position2
    vx2, vy2 = velocity2

    xdiff = (-vx1, -vx2)
    ydiff = (-vy1, -vy2)

    def det(a, b):
        return a[0] * b[1] - a[1] * b[0]

    div = det(xdiff, ydiff)
    if div == 0:
        return -1, -1

    d = (det(position1, velocity1), det(position2, velocity2))
    x = det(d, xdiff) / div
    y = det(d, ydiff) / div

    if (x - x1) * vx1 >= 0 and (y - y1) * vy1 >= 0 and (x - x3) * vx2 >= 0 and (y - y3) * vy2 >= 0:
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
        hailstones.append(((px, py), (vx, vy)))

    at_least = 200000000000000
    at_most = 400000000000000

    intersections = 0
    for i, hailstone, in enumerate(hailstones):
        for hailstone2 in hailstones[i + 1:]:
            position1, velocity1 = hailstone
            position2, velocity2 = hailstone2

            x, y = line_intersection(position1, velocity1, position2, velocity2)

            if at_least <= x <= at_most and at_least <= y <= at_most:
                intersections += 1

    print('Part 1:', intersections)
