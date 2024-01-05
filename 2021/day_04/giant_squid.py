# --- Day 4: Giant Squid ---

def find_final_scores(numbers, boards):
    final_scores = []

    for number in numbers:
        for board in reversed(boards):
            for i, row in enumerate(board):
                for j, cell in enumerate(row):
                    if cell == number:
                        board[i][j] = 'X'

            for row in board:
                if all(cell == 'X' for cell in row):
                    final_scores.append(get_board_sum(board, number))
                    boards.remove(board)
                    break
            else:
                for j in range(5):
                    if all(board[i][j] == 'X' for i in range(5)):
                        final_scores.append(get_board_sum(board, number))
                        boards.remove(board)
                        break

    return final_scores


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

    final_scores = find_final_scores(numbers, boards)

    print('Part 1:', final_scores[0])
    print('Part 2:', final_scores[-1])
