# --- Day 19: --- Part Two ---

import re
from collections import deque

categories = {'x': 0, 'm': 1, 'a': 2, 's': 3}

if __name__ == '__main__':
    with open('aplenty_input') as file:
        workflows, parts = file.read().split("\n\n")

    workflows = workflows.splitlines()
    workflow_dict = {}
    for workflow in workflows:
        name, works = workflow.replace('}', '').split('{')
        works = works.split(',')

        workflow_dict[name] = []
        for work in works:
            splits = work.split(':')
            if len(splits) == 2:
                category = categories[splits[0][0]]
                comparison = splits[0][1]
                amount = int(splits[0][2:])
                workflow_dict[name].append((category, comparison, amount, splits[1]))
            else:
                workflow_dict[name].append(splits)

    accepted_list = []
    part_queue = deque([['in', (1, 4001), (1, 4001), (1, 4001), (1, 4001)]])
    while part_queue:
        current_workflow, *part = part_queue.popleft()

        for rule in workflow_dict[current_workflow]:
            if len(rule) == 1:
                next_workflow = rule[0]
                if next_workflow == 'R':
                    pass
                elif next_workflow == 'A':
                    accepted_list.append(part)
                else:
                    part_queue.append([next_workflow, *part])
                break

            category, comparator, amount, new_workflow = rule
            if comparator == '>':
                filter_start = amount + 1
                filter_end = 4001
            else:
                filter_start = 0
                filter_end = amount

            part_start, part_end = part[category]

            start = max(part_start, filter_start)
            end = min(part_end, filter_end)

            if start < end:
                if new_workflow == 'R':
                    pass
                elif new_workflow == 'A':
                    new_part = part.copy()
                    new_part[category] = (start, end)
                    accepted_list.append(new_part)
                else:
                    new_part = part.copy()
                    new_part[category] = (start, end)
                    part_queue.append([new_workflow, *new_part])

                if part_start < start:
                    new_part = part.copy()
                    new_part[category] = (part_start, start)
                    part_queue.append([current_workflow, *new_part])
                if part_end > end:
                    new_part = part.copy()
                    new_part[category] = (end, part_end)
                    part_queue.append([current_workflow, *new_part])
                    pass
                break

    distinct_combinations = 0
    for accepted in accepted_list:
        combinations = 1
        for start, end in accepted:
            combinations *= end - start
        distinct_combinations += combinations

    print("Part 2:", distinct_combinations)
