# --- Day 19: Aplenty --- Part Two ---

from collections import deque

if __name__ == '__main__':
    with open('aplenty_input') as file:
        workflows = file.read().split("\n\n")[0].splitlines()

    categories = {'x': 0, 'm': 1, 'a': 2, 's': 3}

    workflow_dict = {}
    for workflow in workflows:
        name, works = workflow.replace('}', '').split('{')
        works = works.split(',')

        workflow_dict[name] = []
        for work in works:
            if ':' in work:
                rule, destination = work.split(':')
                category, comparison, operand = categories[rule[0]], rule[1], int(rule[2:])
                workflow_dict[name].append((category, comparison, operand, destination))
            else:
                workflow_dict[name].append([work])

    accepted_list = []
    part_queue = deque([['in', (1, 4001), (1, 4001), (1, 4001), (1, 4001)]])
    while part_queue:
        workflow, *part = part_queue.popleft()

        for rule in workflow_dict[workflow]:
            if len(rule) == 1:
                destination = rule[0]
                if destination == 'A':
                    accepted_list.append(part)
                elif destination != 'R':
                    part_queue.append([destination, *part])
                break

            category, operators, operand, destination = rule
            if operators == '>':
                filter_start = operand + 1
                filter_end = 4001
            else:
                filter_start = 0
                filter_end = operand

            part_start, part_end = part[category]
            start = max(part_start, filter_start)
            end = min(part_end, filter_end)

            if start < end:
                new_part = part.copy()
                new_part[category] = (start, end)
                if destination == 'A':
                    accepted_list.append(new_part)
                elif destination != 'R':
                    part_queue.append([destination, *new_part])

                if part_start < start:
                    new_part = part.copy()
                    new_part[category] = (part_start, start)
                    part_queue.append([workflow, *new_part])
                if part_end > end:
                    new_part = part.copy()
                    new_part[category] = (end, part_end)
                    part_queue.append([workflow, *new_part])
                break

    distinct_combinations = 0
    for accepted in accepted_list:
        combinations = 1
        for start, end in accepted:
            combinations *= end - start
        distinct_combinations += combinations

    print("Part 2:", distinct_combinations)
