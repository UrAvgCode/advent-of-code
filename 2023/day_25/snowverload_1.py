# --- Day 25: Snowverload --- Part One ---

import networkx as nx
import matplotlib.pyplot as plt

if __name__ == '__main__':
    with open('snowverload_input') as file:
        lines = file.read().splitlines()

    components = set()
    edges = set()
    for line in lines:
        this, others = line.split(': ')
        others = others.split()
        components.add(this)
        components.update(others)
        for other in others:
            edges.add((this, other))

    G = nx.Graph()
    G.add_nodes_from(components)
    G.add_edges_from(edges)

    pos = nx.spring_layout(G)
    nx.draw(G, pos, with_labels=True, node_size=700, node_color="skyblue", font_size=15, font_color="black",
            font_weight="bold", edge_color="gray", linewidths=1, alpha=0.7)
    plt.style.use('ggplot')
    plt.show()

    # manual input
    edges.remove(('qnd', 'mbk'))
    edges.remove(('rrl', 'pcs'))
    edges.remove(('ddl', 'lcm'))

    first_group = set()
    while True:
        for edge in edges:
            if not first_group:
                first_group.add(edge[0])
                first_group.add(edge[1])
                edges.remove(edge)
                break
            elif edge[0] in first_group or edge[1] in first_group:
                first_group.add(edge[0])
                first_group.add(edge[1])
                edges.remove(edge)
                break
        else:
            break

    print(len(first_group) * len(components - first_group))
