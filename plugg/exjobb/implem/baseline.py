"""
Baseline algorithm 
A version of Dijkstra and Dials alg.
"""
from random import expovariate
from collections import defaultdict
import networkx as nx

def get_and_nodes(graph):
    and_node_set = graph.nodes(data = "and_node")
    return and_node_set

def set_cost_and_node(graph, u):
    parents = list(graph.predecessors(u))
    weights = []
    for p in parents:
        weights.append(graph.get_edge_data(p, u)["weight"]) 
    return max(weights)


def set_cost(graph, source):
    cost = {}
    and_node_set = get_and_nodes(graph)
    for n in graph:
        if and_node_set[n] == True:
            cost[n] = set_cost_and_node(graph, n)
        else:
            cost[n] = float('inf')
    cost[source] = 0
    return cost, and_node_set


def shortest_path(graph, source, target):
    cost, and_node_set = set_cost(graph, source)
    print(f"COST:  {cost}")
    priority_queue ={source: 0}
    visited = set()
    previous = {}
    
    while priority_queue:
        current_node = min(priority_queue, key = lambda k: priority_queue[k])
        visited.add(current_node)
        if current_node == target:
            return cost, previous

        del priority_queue[current_node]
        for node in graph.neighbors(current_node):
            node_in_visited =  all(elem in visited for elem in graph.predecessors(node))
            if not node_in_visited and and_node_set[node]:
                continue
            elif node_in_visited and and_node_set[node]:
                previous[node] = current_node
                cost[node] = cost[current_node] + set_cost_and_node(graph, node)
                priority_queue[node] = cost[node]
            else:
                dict_weight = graph.get_edge_data(current_node, node)
                weight = dict_weight["weight"]
                if cost[node] > weight + cost[current_node]:
                    cost[node] = weight + cost[current_node]
                    priority_queue[node] = cost[node]
                    previous[node] = current_node
        
    return (cost, previous)

def find_shortest_path(graph, source, target):
    dist, prev = shortest_path(graph, source, target)
    path = []

    if dist[target] == float('inf'): return path
    current_node = target
    while current_node != source:
        path.insert(0, current_node)
        value = prev.get(current_node)
        current_node = value
    path.insert(0, source)

    for node in path:
        print(f"Source Node {source} -> Destination Node({node}) : {dist[node]}")
    return path, dist
        

 
def main():
    exp = expovariate(1/4)
    G = nx.DiGraph()
    G.add_weighted_edges_from([(1, 3, 8), (2, 3, exp), (2, 4, exp), (3, 4, 5)])

    G_2 = nx.DiGraph()
    G_2.add_weighted_edges_from([(1, 2, 0), (1, 3, 0), (1, 4, 100), (2, 3, 0), (2, 5, 8),(2, 7, 0), (3, 5, 0), (3, 4, 2), (4, 5, 2), (4, 6, 2), (5, 6, 3),(7, 5, 1), (8, 7, 0)])
    G_2.add_node(3, and_node=True)
    G_3 = nx.DiGraph()
    G_3.add_weighted_edges_from([(1, 2, 2), (1,4, exp), (2, 3, 2), (2, 4, 100), (3, 4, 6), (4, 5, 1)])
    G_3.add_node(4, and_node=True)
    print(G_2.nodes.data())
    path, val = find_shortest_path(G_3, 1, 5)
    print(f"the path:{path}")
    print(f"the value:{val}")
    print("NEXT: ")
    print(nx.shortest_path(G_2,source=1,target=5, weight='weight'))
    #print(G.dijkstra_path(G_2, 1,6))
    
    print(f"graph: {list(G_3.adjacency())}")
#     exp = expovariate(1/4)
#     G = Graph(4)
#     G.add_node(0, Node(3, 8))
#     G.add_node(1, Node(3, exp))
#     G.add_node(1, Node(4, exp))
#     G.add_node(3, Node(4, 5))
#     G.shortest_path(1)

if __name__ == "__main__":
     main()