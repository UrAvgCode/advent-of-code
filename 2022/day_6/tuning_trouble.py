# --- Day 6: Tuning Trouble ---

def marker_at(signal, marker_length):
    for i in range(len(signal)):
        for j in range(marker_length - 1):
            if signal[i + j] in signal[i + j + 1:i + marker_length]:
                break
            elif j == marker_length - 2:
                return i + marker_length


if __name__ == '__main__':
    file = open("tuning_trouble_input", "r")
    line = file.readlines()[0].strip()

    print("Part 1: " + str(marker_at(line, 4)))
    print("Part 2: " + str(marker_at(line, 14)))
