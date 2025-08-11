#include <bits/stdc++.h>
using namespace std;

bool dls(unordered_map<char, vector<char>> &graph, char current, char goal, int limit, vector<char> &path) {
    path.push_back(current);

    if (current == goal) {
        return true;
    }

    if (limit <= 0) {
        path.pop_back();
        return false;
    }

    vector<char> neighbors = graph[current];
    sort(neighbors.begin(), neighbors.end());

    for (char neighbor : neighbors) {
        if (find(path.begin(), path.end(), neighbor) == path.end()) {
            if (dls(graph, neighbor, goal, limit - 1, path)) {
                return true;
            }
        }
    }
    path.pop_back();
    return false;
}

void iddfs(unordered_map<char, vector<char>> &graph, char start, char goal) {
    int depth = 0;
    while (true) {
        vector<char> path;
        if (dls(graph, start, goal, depth, path)) {
            for (char c : path) {
                cout << c << " ";
            }
            cout << "\n";
            return;
        }
        depth++;
    }
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

    iddfs(graph, 'S', 'G');
    return 0;
}