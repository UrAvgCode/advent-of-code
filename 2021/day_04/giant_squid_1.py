# --- Day 4: Giant Squid --- Part One ---

def find_bingo(numbers, boards):
    for number in numbers:
        for board in boards:
            for i, row in enumerate(board):
                for j, cell in enumerate(row):
                    if cell == number:
                        board[i][j] = 'X'

            for row in board:
                if all(cell == 'X' for cell in row):
                    return get_board_sum(board, number)

            for j in range(5):
                if all(board[i][j] == 'X' for i in range(5)):
                    return get_board_sum(board, number)


def get_board_sum(board, number):
    board_sum = 0
    for row in board:
        board_sum += sum([x for x in row if x != 'X'])
    return board_sum * number


if __name__ == '__main__':
    with open('giant_squid_input') as file:
        numbers, *boards = file.read().split('\n\n')

    numbers = tuple(map(int, numbers.split(',')))
    for i, board in enumerate(boards):
        boards[i] = [list(map(int, line.split())) for line in board.splitlines()]

    print('Part 1:', find_bingo(numbers, boards))
