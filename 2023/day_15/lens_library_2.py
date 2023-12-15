# --- Day 15: Lens Library --- Part Two ---

def get_hash(string):
    current_value = 0
    for char in string:
        current_value = ((current_value + ord(char)) * 17) % 256
    return current_value


if __name__ == '__main__':
    with open("lens_library_input") as file:
        lines = file.read().strip().split(',')

    boxes_list = [{} for _ in range(256)]

    for line in lines:
        if line[-1] == '-':
            label = line[:-1]
            box = boxes_list[get_hash(label)]
            if label in box:
                box.pop(label)
        else:
            label, number = line.split('=')
            number = int(number)
            box = boxes_list[get_hash(label)]
            box[label] = number

    focusing_power_sum = 0
    for box_num, box in enumerate(boxes_list):
        for slot_num, focal_length in enumerate(box.values(), 1):
            focusing_power_sum += (box_num + 1) * slot_num * focal_length

    print("Part 2:", focusing_power_sum)
