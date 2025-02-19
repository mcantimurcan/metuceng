#include "the7.h"

bool is_cyclic_graph_helper(const std::vector<std::vector<std::pair<int, int>>>& graph, 
                            int starting_node, 
                            std::vector<bool>& visited, 
                            std::vector<bool>& explored)
{
    int size = graph.size();
    visited[starting_node] = true;
    explored[starting_node] = true;

    for (const auto& neighbor : graph[starting_node]) {
        int next_node = neighbor.first;
        if (!visited[next_node] && is_cyclic_graph_helper(graph, next_node, visited, explored)) {
            return true;
        } 
        else if (visited[next_node] && explored[next_node]) {
            return true;
        }
    }

    explored[starting_node] = false;

    return false;
}

bool is_cyclic_graph(const std::vector<std::vector<std::pair<int, int>>>& graph) 
{
    int size = graph.size();
    std::vector<bool> visited(size, false);
    std::vector<bool> explored(size, false);

    for (int i = 0; i < size; i++) {
        if (!visited[i] && is_cyclic_graph_helper(graph, i, visited, explored)) {
            return true;
        }
    }

    return false;
}

void topo_sort(int node, 
               const std::vector<std::vector<std::pair<int, int>>>& graph, 
               std::vector<bool>& visited, 
               std::stack<int>& topo_sort_stack)
{
    visited[node] = true;
    for (const auto& edge : graph[node]) {
        int neighbor = edge.first;
        if (!visited[neighbor]) {
            topo_sort(neighbor, graph, visited, topo_sort_stack);
        }
    }
    topo_sort_stack.push(node);
}

void exhaustive_search(const std::vector<std::vector<std::pair<int, int>>>& graph,
                       int current_node,
                       int destination_node,
                       std::vector<bool>& visited,
                       long current_length,
                       std::vector<int>& current_path,
                       std::vector<int>& longest_path,
                       long& length_of_longest_path)
{
    visited[current_node] = true;
    current_path.push_back(current_node);

    if (current_node == destination_node) {
        if (current_length > length_of_longest_path) {
            length_of_longest_path = current_length;
            longest_path = current_path;
        }
    } else {
        for (const auto& neighbor : graph[current_node]) {
            int next_node = neighbor.first;
            int edge_weight = neighbor.second;

            if (!visited[next_node]) {
                exhaustive_search(graph, next_node, destination_node, visited, 
                current_length + edge_weight, current_path, longest_path, length_of_longest_path);
            }
        }
    }

    visited[current_node] = false;
    current_path.pop_back();
}

std::vector<int> find_longest_path_cyclic(const std::vector<std::vector<std::pair<int, int> > >& graph,
                                          int starting_node,
                                          int destination_node,
                                          long& length_of_longest_path)
{
    int size = graph.size();
    std::vector<bool> visited(graph.size(), false);
    std::vector<int> current_path;
    std::vector<int> longest_path;

    exhaustive_search(graph, starting_node, destination_node, visited, 0, current_path, longest_path, length_of_longest_path);

    return longest_path;
}

std::vector<int> find_longest_path_dag(const std::vector<std::vector<std::pair<int, int> > >& graph,
                                       int starting_node,
                                       int destination_node,
                                       long& length_of_longest_path)
{
    int size = graph.size();
    std::vector<bool> visited(size, false);
    std::stack<int> topo_sort_stack;
    
    for (int i = 0; i < size; i++) {
        if (!visited[i]) {
            topo_sort(i, graph, visited, topo_sort_stack);
        }
    }
    
    std::vector<int> distances(size, INT_MIN);
    std::vector<int> predecessors(size, -1);
    distances[starting_node] = 0;
    
    while (!topo_sort_stack.empty()) {
        int node = topo_sort_stack.top();
        topo_sort_stack.pop();

        if (distances[node] != INT_MIN) {
            for (const auto& edge : graph[node]) {
                int neighbor = edge.first;
                int weight = edge.second;
                if (distances[node] + weight > distances[neighbor]) {
                    distances[neighbor] = distances[node] + weight;
                    predecessors[neighbor] = node;
                }
            }
        }
    }
    
    length_of_longest_path = distances[destination_node];
    std::vector<int> longest_path;

    if (length_of_longest_path == INT_MIN) {
        return longest_path;
    }

    for (int at = destination_node; at != -1; at = predecessors[at]) {
        longest_path.push_back(at);
    }
    
    std::reverse(longest_path.begin(), longest_path.end());

    return longest_path;
}

std::vector<int> find_longest_path(const std::vector<std::vector<std::pair<int, int> > >& graph,
                                   int starting_node,
                                   int destination_node,
                                   long& length_of_longest_path)
{
    std::vector<int> longest_path;
    
    if(is_cyclic_graph(graph)){
        longest_path = find_longest_path_cyclic(graph, starting_node, destination_node, length_of_longest_path);
    } else {
        longest_path = find_longest_path_dag(graph, starting_node, destination_node, length_of_longest_path);
    }
    
    return longest_path;
}