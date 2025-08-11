#include <bits/stdc++.h>
using namespace std;

bool dfsRec(unordered_map<char, vector<char>> &graph, 
            char node, char goal, 
            vector<char> &path, 
            unordered_set<char> &visited,
            unordered_set<char> &deadEnd) 
{
    if (deadEnd.count(node) || visited.count(node)) return false;

    visited.insert(node);
    path.push_back(node);

    if (node == goal) {
        for (char c : path) cout << c << " ";
        cout << "\n";
        return true;
    }

    bool found = false;
    for (char neigh : graph[node]) {
        if (!visited.count(neigh)) {
            if (dfsRec(graph, neigh, goal, path, visited, deadEnd)) {
                found = true;
                break;
            }
        }
    }

    if (!found) deadEnd.insert(node);

    path.pop_back();
    return found;
}

void dfsWithDeadEnds(unordered_map<char, vector<char>> &graph, char start, char goal) {
    vector<char> path;
    unordered_set<char> visited;
    unordered_set<char> deadEnd;
    dfsRec(graph, start, goal, path, visited, deadEnd);
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

    dfsWithDeadEnds(graph, 'S', 'G');
}
