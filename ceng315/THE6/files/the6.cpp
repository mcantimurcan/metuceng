#include "the6.h"

// do not add extra libraries here

std::vector<int> dijkstra(int source, 
                          const std::vector<std::vector<std::pair<int, int>>>& network,
                          std::vector<std::vector<int>>& memoized_distances) 
{
    if (!memoized_distances[source].empty()) {
        return memoized_distances[source];
    }

    int size = network.size();
    std::vector<int> distances(size, INT_MAX);
    distances[source] = INT_MAX;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> dijkstra_queue;
    dijkstra_queue.push({0, source});

    while (!dijkstra_queue.empty()) {
        int current_dist = dijkstra_queue.top().first;
        int current_node = dijkstra_queue.top().second;
        dijkstra_queue.pop();

        for (const auto& [neighbor, weight] : network[current_node]) {
            int new_dist = current_dist + weight;
            if (new_dist < distances[neighbor]) {
                distances[neighbor] = new_dist;
                dijkstra_queue.push({new_dist, neighbor});
            }
        }
    }

    memoized_distances[source] = distances;
    return distances;
}

int calculate_shortest_path_1(int vertex, 
                              const std::vector<std::vector<std::pair<int, int>>>& network,
                              std::vector<std::vector<int>>& memoized_distances) 
{
    std::vector<int> distances = dijkstra(vertex, network, memoized_distances);
    int size = distances.size();
    int shortest_path = INT_MAX;

    for (int i = 0; i < size; i++) {
        if (distances[i] < shortest_path) {
            shortest_path = distances[i];
        }
    }

    return shortest_path;
}

int calculate_shortest_path_2(int vertex_1,
                              int vertex_2,
                              const std::vector<std::vector<std::pair<int, int>>>& network,
                              std::vector<std::vector<int>>& memoized_distances) 
{
    std::vector<int> distances = dijkstra(vertex_1, network, memoized_distances);
    return distances[vertex_2];
}

std::vector<std::vector<float>> get_friendship_scores(const std::vector<std::vector<std::pair<int, int>>>& network) {
    int size = network.size();
    std::vector<std::vector<int>> memoized_distances(size);
    std::vector<std::vector<float>> friendship_scores;

    for (int idx = 0; idx < size; idx++) {
        std::vector<float> friendship_score_vertex;
        for (int idy = 0; idy <= idx; idy++) {
            float sp1_idx = calculate_shortest_path_1(idx, network, memoized_distances);
            float sp1_idy = calculate_shortest_path_1(idy, network, memoized_distances);
            float sp2_idx_idy = calculate_shortest_path_2(idx, idy, network, memoized_distances);
            float sp2_idy_idx = calculate_shortest_path_2(idy, idx, network, memoized_distances);

            if (sp2_idx_idy == INT_MAX && sp2_idy_idx == INT_MAX) {
                friendship_score_vertex.push_back(-1);
            } else if (sp2_idx_idy == INT_MAX || sp2_idy_idx == INT_MAX) {
                friendship_score_vertex.push_back(0);
            } else {
                float score1 = sp1_idx / sp2_idx_idy;
                float score2 = sp1_idy / sp2_idy_idx;
                float final_score = score1 * score2;
                friendship_score_vertex.push_back(final_score);
            }
        }
        friendship_scores.push_back(friendship_score_vertex);
    }

    return friendship_scores;
}