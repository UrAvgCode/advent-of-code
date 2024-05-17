# --- Day 20: Pulse Propagation --- Part One ---

from collections import deque

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

    low_pulses = 0
    high_pulses = 0

    for _ in range(1000):
        pulse_queue = deque([['button', 'broadcaster', 0]])
        while pulse_queue:
            source, destination, pulse = pulse_queue.popleft()

            if pulse:
                high_pulses += 1
            else:
                low_pulses += 1

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

    print("Part 1:", low_pulses * high_pulses)
