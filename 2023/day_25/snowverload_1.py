# --- Day 25: Snowverload --- Part One ---

import networkx as nx
from time import perf_counter

if __name__ == '__main__':
    with open('../../input/2023/day_25/input.txt') as file:
        lines = file.read().splitlines()

    start_time = perf_counter()

    edges = set()
    components = set()
    for line in lines:
        this, others = line.split(': ')
        others = others.split()
        components.add(this)
        components.update(others)
        for other in others:
            edges.add((this, other))

    Graph = nx.Graph()
    Graph.add_nodes_from(components)
    Graph.add_edges_from(edges)
    removed_edges = nx.minimum_edge_cut(Graph)

    for edge in removed_edges:
        if edge in edges:
            edges.remove(edge)
        else:
            edges.remove((edge[1], edge[0]))

    group = set()
    while True:
        for edge in edges:
            if not group:
                group.update(edge)
                edges.remove(edge)
                break
            elif edge[0] in group or edge[1] in group:
                group.update(edge)
                edges.remove(edge)
                break
        else:
            break

    print('Part 2:', len(group) * len(components - group))
    print('Time:', perf_counter() - start_time)
