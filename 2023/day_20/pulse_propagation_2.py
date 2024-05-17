# --- Day 20: Pulse Propagation --- Part Two ---

from collections import deque
from math import lcm


def get_conjunction_time(modules, name):
    rounds = 0
    while True:
        rounds += 1
        pulse_queue = deque([['button', 'broadcaster', 0]])
        while pulse_queue:
            source, destination, pulse = pulse_queue.popleft()

            if not pulse and destination == name:
                for module in modules.values():
                    if module[0] == '&':
                        for key in module[1]:
                            module[1][key] = 0
                    elif module[0] == '%':
                        module[1] = False
                return rounds

            if destination not in modules:
                continue

            if destination == 'broadcaster':
                for module in modules[destination]:
                    pulse_queue.append([destination, module, pulse])
            elif modules[destination][0] == '%':
                if not pulse:
                    modules[destination][1] = not modules[destination][1]
                    for module in modules[destination][2:]:
                        pulse_queue.append([destination, module, modules[destination][1]])
            elif modules[destination][0] == '&':
                modules[destination][1][source] = pulse
                if all(modules[destination][1].values()):
                    for module in modules[destination][2:]:
                        pulse_queue.append([destination, module, 0])
                else:
                    for module in modules[destination][2:]:
                        pulse_queue.append([destination, module, 1])


if __name__ == '__main__':
    with open('../../input/2023/day_20/input.txt') as file:
        lines = file.read().splitlines()

    modules = {}
    conjunctions = set()
    for line in lines:
        source, destination = line.split(' -> ')

        destinations = destination.split(', ')
        if source == 'broadcaster':
            modules[source] = destinations
        elif source[0] == '%':
            modules[source[1:]] = [source[0], False, *destinations]
        elif source[0] == '&':
            conjunctions.add(source[1:])
            modules[source[1:]] = [source[0], {}, *destinations]

    for source, destination in modules.items():
        for module in destination[2:]:
            if module in conjunctions:
                modules[module][1][source] = 0

    rx_conjunctions = []
    for module in modules.values():
        if module[-1] == 'rx':
            rx_conjunctions.extend(module[1])
            break

    conjunction_times = [get_conjunction_time(modules, x) for x in rx_conjunctions]

    print("Part 2:", lcm(*conjunction_times))
