# --- Day 19: Aplenty --- Part One ---

import re

if __name__ == '__main__':
    with open("aplenty_input") as file:
        workflows, parts = file.read().split("\n\n")

    parts = [list(map(int, re.findall(r'\d+', part))) for part in parts.split("\n")]
    workflows = workflows.splitlines()

    categories = {'x': 0, 'm': 1, 'a': 2, 's': 3}
    workflow_dict = {}
    for workflow in workflows:
        name, works = workflow.replace("}", "").split("{")
        works = works.split(",")

        workflow_dict[name] = []
        for work in works:
            splits = work.split(":")
            if len(splits) == 2:
                category = categories[splits[0][0]]
                comparison = splits[0][1]
                amount = int(splits[0][2:])
                workflow_dict[name].append((category, comparison, amount, splits[1]))
            else:
                workflow_dict[name].append(splits)

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
                        accepted = True
                    elif next_workflow == "R":
                        accepted = True
                    else:
                        current_workflow = next_workflow
                    break

                category, comparison, amount, next_workflow = rule
                if comparison == "<":
                    if part[category] < amount:
                        if next_workflow == "A":
                            accepted_list.append(part)
                            accepted = True
                        elif next_workflow == "R":
                            accepted = True
                        else:
                            current_workflow = next_workflow
                        break
                elif comparison == ">":
                    if part[category] > amount:
                        if next_workflow == "A":
                            accepted_list.append(part)
                            accepted = True
                        elif next_workflow == "R":
                            accepted = True
                        else:
                            current_workflow = next_workflow
                        break

    rating_numbers_sum = sum([sum(part) for part in accepted_list])
    print("Part 1:", rating_numbers_sum)
