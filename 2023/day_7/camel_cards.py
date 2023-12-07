# --- Day 7: Camel Cards ---

def get_card_amounts(cards):
    amounts = {}
    for card in cards:
        if card in amounts:
            amounts[card] += 1
        else:
            amounts[card] = 1
    return amounts


def get_type_score(amounts):
    match len(amounts):
        case 1:
            return 6
        case 2:
            for card in amounts:
                if amounts[card] == 4:
                    return 5
            return 4
        case 3:
            for card in amounts:
                if amounts[card] == 3:
                    return 3
            return 2
        case 4:
            return 1
        case _:
            return 0


def part_one(hands):
    order = "23456789TJQKA"
    bets = []
    for hand in hands:
        rank_value = 0
        for j, card in enumerate(reversed(hand[0])):
            rank_value += order.index(card) * (13 ** j)
        else:
            amounts = get_card_amounts(hand[0])
            rank_value += get_type_score(amounts) * (13 ** 5)
        bets.append((rank_value, hand[1]))

    bets.sort()
    solution = 0
    for i, bet in enumerate(bets):
        solution += (i + 1) * bet[1]
    return solution


def part_two(hands):
    order = "J23456789TQKA"
    bets = []
    for hand in hands:
        rank_value = 0
        for j, card in enumerate(reversed(hand[0])):
            rank_value += order.index(card) * (13 ** j)
        else:
            amounts = get_card_amounts(hand[0])
            if 'J' in amounts and len(amounts) != 1:
                j_count = amounts.pop('J')
                for card in amounts:
                    amounts[card] += j_count
            rank_value += get_type_score(amounts) * (13 ** 5)
        bets.append((rank_value, hand[1]))

    bets.sort()
    solution = 0
    for i, bet in enumerate(bets):
        solution += (i + 1) * bet[1]
    return solution


if __name__ == '__main__':
    with open("camel_cards_input") as file:
        lines = file.read().strip().split("\n")
    hands_list = [(line.split()[0], int(line.split()[1])) for line in lines]

    print("Part 1:", part_one(hands_list))
    print("Part 2:", part_two(hands_list))
