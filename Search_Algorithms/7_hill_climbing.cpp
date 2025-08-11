#include <bits/stdc++.h>

using namespace std;

bool dfs_hill(unordered_map<char, vector<pair<char, int>>>& graph,
              unordered_map<char, int>& hill_approx,
              char current_node, char goal,
              vector<char>& path) 
{
    path.push_back(current_node);

    if (current_node == goal) {
        return true;
    }

    vector<pair<char, int>> neighbors = graph[current_node];
    sort(neighbors.begin(), neighbors.end(),
         [&](auto& a, auto& b) {
             return hill_approx[a.first] < hill_approx[b.first];
         });

    for (auto& neighbor : neighbors) {
        char next_node = neighbor.first;
        if (dfs_hill(graph, hill_approx, next_node, goal, path)) {
            return true;
        }
    }

    path.pop_back();
    return false;
}

int main() {
    unordered_map<char, vector<pair<char, int>>> graph;
    graph['S'] = {{'A', 3}, {'B', 5}};
    graph['A'] = {{'D', 3}, {'B', 4}, {'S', 3}};
    graph['B'] = {{'A', 4}, {'C', 4}, {'S', 5}};
    graph['C'] = {{'E', 6}, {'B', 6}};
    graph['D'] = {{'A', 3}, {'G', 5}};
    graph['E'] = {{'C', 6}};
    graph['G'] = {{'D', 5}};

    unordered_map<char, int> hill_approx = {
        {'S', 10}, {'A', 7}, {'B', 6}, {'C', 7}, {'D', 5}, {'E', 6}, {'G', 0}
    };

    vector<char> path;

    if (dfs_hill(graph, hill_approx, 'S', 'G', path)) {
        cout << "Path found: ";
        for (char node : path) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "Goal not reachable." << endl;
    }

    return 0;
}
