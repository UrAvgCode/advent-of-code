# --- Day 24: Never Tell Me The Odds --- Part One ---

def line_intersection(hailstone1, hailstone2):
    (x1, y1), (vx1, vy1) = hailstone1
    (x2, y2), (vx2, vy2) = hailstone2

    xdiff = (-vx1, -vx2)
    ydiff = (-vy1, -vy2)

    def det(a, b):
        return a[0] * b[1] - a[1] * b[0]

    div = det(xdiff, ydiff)
    if div == 0:
        return -1, -1

    d = (det(*hailstone1), det(*hailstone2))
    x = det(d, xdiff) / div
    y = det(d, ydiff) / div

    if (x - x1) * vx1 >= 0 and (y - y1) * vy1 >= 0 and (x - x2) * vx2 >= 0 and (y - y2) * vy2 >= 0:
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
    for i, hailstone1, in enumerate(hailstones):
        for hailstone2 in hailstones[i + 1:]:
            x, y = line_intersection(hailstone1, hailstone2)
            if at_least <= x <= at_most and at_least <= y <= at_most:
                intersections += 1

    print('Part 1:', intersections)
