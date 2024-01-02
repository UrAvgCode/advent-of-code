# --- Day 3: Binary Diagnostic --- Part One ---

from collections import Counter

if __name__ == '__main__':
    with open('binary_diagnostic_input') as file:
        columns = list(zip(*file.read().splitlines()))

    gamma_rate = ''
    epsilon_rate = ''

    for column in columns:
        counts = Counter(column)
        if counts['0'] > counts['1']:
            gamma_rate += '0'
            epsilon_rate += '1'
        else:
            gamma_rate += '1'
            epsilon_rate += '0'

    print('Part 1:', int(gamma_rate, 2) * int(epsilon_rate, 2))
