#include <bits/stdc++.h>
using namespace std;

bool dfsRec(unordered_map<char, vector<char>> &graph, char node, char goal, vector<char> &path, unordered_set<char> &visited) {
    if (node == goal) {
        for (char c : path) cout << c << " ";
        cout << "\n";
        return true;
    }

    vector<char> neighbors = graph[node];
    sort(neighbors.begin(), neighbors.end());

    for (char neigh : neighbors) {
        if (!visited.count(neigh)) {
            visited.insert(neigh);
            path.push_back(neigh);
            if (dfsRec(graph, neigh, goal, path, visited)) return true;
            path.pop_back();
            visited.erase(neigh);
        }
    }
    return false;
}

void dfsSearch(unordered_map<char, vector<char>> &graph, char start, char goal) {
    vector<char> path;
    unordered_set<char> visited;

    visited.insert(start);
    path.push_back(start);

    dfsRec(graph, start, goal, path, visited);
}

int main() {
    unordered_map<char, vector<char>> graph;
    graph['S'] = {'A', 'B'};
    graph['A'] = {'D', 'B', 'S'};
    graph['B'] = {'A', 'C', 'S'};
    graph['C'] = {'E', 'B'};
    graph['D'] = {'A', 'G'};
    graph['E'] = {'C'};
    graph['G'] = {'D'};

    dfsSearch(graph, 'S', 'G');
}
