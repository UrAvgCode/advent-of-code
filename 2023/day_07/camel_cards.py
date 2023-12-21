# --- Day 7: Camel Cards ---

from collections import Counter

types = ["high card", "pair", "two pair", "three", "full house", "four", "five"]


def get_type_score(amounts):
    match len(amounts):
        case 0 | 1:
            return "five"
        case 2:
            if 4 in amounts.values():
                return "four"
            return "full house"
        case 3:
            if 3 in amounts.values():
                return "three"
            return "two pair"
        case 4:
            return "pair"
        case _:
            return "high card"


def calculate_winnings(hands, strengths, joker=False):
    bets = []
    for hand, bid in hands:
        card_counts = Counter(hand)
        if joker:
            joker_count = card_counts.pop('J', 0) if joker else 0
            for card in card_counts:
                card_counts[card] += joker_count
        sort_rank = [get_type_score(card_counts)] + list(hand)
        bets.append((sort_rank, bid))

    sort_order = {card: i for i, card in enumerate(strengths + types)}
    bets.sort(key=lambda sort_key: [sort_order[card] for card in sort_key[0]])
    return sum(rank * bet for rank, (_, bet) in enumerate(bets, 1))


if __name__ == '__main__':
    with open("camel_cards_input") as file:
        lines = file.read().splitlines()
    hands = [(hand, int(bid)) for hand, bid in (line.split() for line in lines)]

    strengths_one = ['2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A']
    strengths_two = ['J', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'Q', 'K', 'A']

    print("Part 1:", calculate_winnings(hands, strengths_one))
    print("Part 2:", calculate_winnings(hands, strengths_two, True))
