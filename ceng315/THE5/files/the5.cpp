#include "the5.h"

std::vector<int> adjacencies(int vertex,
                             const std::vector< std::vector<bool> > &dependencies)
{
    int vertex_count = dependencies.size();
    std::vector<int> result;
    for(int i = 0; i < vertex_count; i++){
        if(dependencies[vertex][i] && i != vertex){
            result.push_back(i);
        }
    }
    return result;
}

std::vector< std::vector<bool> > transpose_graph(const std::vector< std::vector<bool> > &dependencies)
{
    int vertex_count = dependencies.size();
    std::vector< std::vector<bool> > transposed_graph(vertex_count, std::vector<bool>(vertex_count, false));

    for (int i = 0; i < vertex_count; i++) {
        for (int j = 0; j < vertex_count; j++) {
            transposed_graph[j][i] = dependencies[i][j];
        }
    }

    return transposed_graph;
}

std::vector<int> sorted_vertices(int vertex_count,
                                 std::vector<int> &finish_time)
{
    std::vector<int> sorted_vertices(vertex_count);
    for (int i = 0; i < vertex_count; i++) {
        sorted_vertices[i] = i;
    }
    
    for (int i = 0; i < vertex_count - 1; i++) {
        for (int j = 0; j < vertex_count - i - 1; j++) {
            if (finish_time[sorted_vertices[j]] < finish_time[sorted_vertices[j + 1]]) {
                int temp = sorted_vertices[j];
                sorted_vertices[j] = sorted_vertices[j + 1];
                sorted_vertices[j + 1] = temp;
            }
        }
    }
    return sorted_vertices;
}

void dfs_visit(int vertex,
               int &process_time, 
               std::vector<int> &color, 
               std::vector<int> &finish_time,
               const std::vector< std::vector<bool> > &dependencies)
{
    color[vertex] = 1;
    process_time++;
    std::vector<int> adjacencies_of_vertex = adjacencies(vertex, dependencies);
    int adjacency_count = adjacencies_of_vertex.size();
    
    for (int i = adjacency_count-1; i >= 0; i--) {
        if (color[adjacencies_of_vertex[i]] == 2) {
            dfs_visit(adjacencies_of_vertex[i], process_time, color, finish_time, dependencies);
        }
    }
    
    color[vertex] = 0;
    process_time++;
    finish_time[vertex] = process_time;
}

void dfs_visit_transposed(int vertex, 
                          std::vector<int>& color, 
                          std::vector<int>& scc, 
                          std::vector<std::vector<bool>>& transposed) 
{
    color[vertex] = 1;
    scc.push_back(vertex);
    std::vector<int> adjacencies_of_vertex = adjacencies(vertex, transposed);
    int adjacency_count = adjacencies_of_vertex.size();

    for (int i = 0; i < adjacency_count; i++) {
        if (color[adjacencies_of_vertex[i]] == 2) {
            dfs_visit_transposed(adjacencies_of_vertex[i], color, scc, transposed);
        }
    }

    color[vertex] = 0;
}

void dfs_transposed(std::vector<int> &new_vertex_list,
                    std::vector<int> &color,
                    std::vector< std::vector<int> > &sccs,
                    std::vector< std::vector<bool> > &transposed_graph)
{
    int vertex_count = transposed_graph.size();

    for (int i = 0; i < vertex_count; i++) {
        if (color[new_vertex_list[i]] == 2) {
            std::vector<int> scc;
            dfs_visit_transposed(new_vertex_list[i], color, scc, transposed_graph);
            sccs.push_back(scc);
        }
    }
}

void dfs(std::vector<int> &color, 
         std::vector<int> &finish_time,
         const std::vector< std::vector<bool> > &dependencies)
{
    int vertex_count = dependencies.size();
    int process_time = 0;
    
    for (int i = vertex_count-1; i >= 0; i--) {
        if (color[i] == 2) {
            dfs_visit(i, process_time, color, finish_time, dependencies);
        }
    }
}

std::vector< std::vector<int> > strongly_connected_components(const std::vector< std::vector<bool> > &dependencies)
{
    int vertex_count = dependencies.size();
    
    std::vector<int> color(vertex_count, 2);
    std::vector<int> finish_time(vertex_count, 0);
    
    dfs(color, finish_time, dependencies);
    
    std::vector<std::vector<bool>> transposed_graph = transpose_graph(dependencies);
    
    std::vector<std::vector<int>> sccs;
    std::vector<int> new_vertex_list = sorted_vertices(vertex_count, finish_time);
    
    for (int i = 0; i < vertex_count; i++) {
        color[i] = 2;
    }
    
    dfs_transposed(new_vertex_list, color, sccs, transposed_graph);
    
    return sccs;
}

std::vector< std::vector<bool> > convert_to_dag(const std::vector< std::vector<int> > &sccs,
                                                const std::vector< std::vector<bool> > &dependencies)
{
    int scc_count = sccs.size();
    std::vector< std::vector<bool> > converted_dag(scc_count, std::vector<bool>(scc_count, false));

    std::vector<int> vertex_to_scc(dependencies.size(), -1);
    for (int i = 0; i < scc_count; i++) {
        int scc_length = sccs[i].size();
        for (int j = 0; j < scc_length; j++) {
            vertex_to_scc[sccs[i][j]] = i;
        }
    }

    for (int i = 0; i < dependencies.size(); i++) {
        for (int j = 0; j < dependencies.size(); j++) {
            if (dependencies[i][j]) {
                int from_scc = vertex_to_scc[i];
                int to_scc = vertex_to_scc[j];
                if (from_scc != to_scc) {
                    converted_dag[from_scc][to_scc] = true;
                }
            }
        }
    }

    return converted_dag;
}

void sort_scc_ids(std::vector<int> &scc_ids, std::vector<std::vector<int>> &sccs) {
    int scc_count = scc_ids.size();

    for (int i = 0; i < scc_count - 1; i++) {
        for (int j = 0; j < scc_count - i - 1; j++) {
            if (scc_ids[j] > scc_ids[j + 1]) {
                int temp = scc_ids[j];
                scc_ids[j] = scc_ids[j + 1];
                scc_ids[j + 1] = temp;

                std::vector<int> temp_scc = sccs[j];
                sccs[j] = sccs[j + 1];
                sccs[j + 1] = temp_scc;
            }
        }
    }
}

std::vector< std::vector<int> > find_work_order(const std::vector< std::vector<bool> > &dependencies){
    std::vector< std::vector<int> > sccs = strongly_connected_components(dependencies);
    std::vector<int> scc_ids(sccs.size());
    for (int i = 0; i < sccs.size(); i++) {
        int smallest_vertex = sccs[i][0];
        for (int j = 1; j < sccs[i].size(); j++) {
            if (sccs[i][j] < smallest_vertex) {
                smallest_vertex = sccs[i][j];
            }
        }
        scc_ids[i] = smallest_vertex;
    }
    
    sort_scc_ids(scc_ids, sccs);
    
    std::vector< std::vector<bool> > converted_dag = convert_to_dag(sccs, dependencies);
    int vertex_count = converted_dag.size();
    
    std::vector<int> color(vertex_count, 2);
    std::vector<int> finish_time(vertex_count, 0);
    
    dfs(color, finish_time, converted_dag);
    std::vector<int> new_vertex_list = sorted_vertices(vertex_count, finish_time);
    
    std::vector< std::vector<int> > work_order;
    for (int i = 0; i < vertex_count; i++){
        work_order.push_back(sccs[new_vertex_list[i]]);
    }
    
    return work_order;
}




