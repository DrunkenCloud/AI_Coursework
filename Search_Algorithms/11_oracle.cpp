#include <bits/stdc++.h>
using namespace std;

int british_museum_recursive(unordered_map<char, vector<pair<char, int>>>& graph,
                              char current, char goal,
                              vector<char>& path, int cost)
{
    if (current == goal) {
        cout << "Path found: ";
        for (char node : path) cout << node << " ";
        cout << "| Distance: " << cost << endl;
        return cost;
    }

    int best = INT_MAX;

    for (auto& neighbor : graph[current]) {
        if (find(path.begin(), path.end(), neighbor.first) == path.end()) {
            path.push_back(neighbor.first);
            best = min(best, british_museum_recursive(graph, neighbor.first, goal, path, cost + neighbor.second));
            path.pop_back();
        }
    }
    return best;
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

    vector<char> path = {'S'};

    int oracle_distance = british_museum_recursive(graph, 'S', 'G', path, 0);

    if (oracle_distance == INT_MAX) {
        cout << "Goal not reachable." << endl;
    } else {
        cout << "Smallest path distance (oracle): " << oracle_distance << endl;
    }

    return 0;
}
