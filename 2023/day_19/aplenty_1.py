# --- Day 19: Aplenty --- Part One ---

import re

if __name__ == '__main__':
    with open("../../input/2023/day_19/input.txt") as file:
        workflows, parts = file.read().split("\n\n")

    workflows = workflows.splitlines()
    parts = [list(map(int, re.findall(r'\d+', part))) for part in parts.split("\n")]

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
    for part in parts:
        accepted = False
        current_workflow = "in"
        while not accepted:
            for rule in workflow_dict[current_workflow]:
                if len(rule) == 1:
                    next_workflow = rule[0]
                    if next_workflow == "A":
                        accepted_list.append(part)
                    accepted = next_workflow in ("A", "R")
                    current_workflow = next_workflow
                    break

                category, comparison, amount, next_workflow = rule
                if comparison == "<" and part[category] < amount or comparison == ">" and part[category] > amount:
                    if next_workflow == "A":
                        accepted_list.append(part)
                    accepted = next_workflow in ("A", "R")
                    current_workflow = next_workflow
                    break

    rating_numbers_sum = sum([sum(part) for part in accepted_list])
    print("Part 1:", rating_numbers_sum)
