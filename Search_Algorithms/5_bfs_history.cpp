#include <bits/stdc++.h>
using namespace std;

void bfsLevelGlobalVisited(unordered_map<char, vector<char>> &graph, char start, char goal) {
    queue<vector<char>> q;
    unordered_set<char> visited;

    q.push({start});
    visited.insert(start);

    while (!q.empty()) {
        int levelSize = q.size();

        for (int i = 0; i < levelSize; i++) {
            auto path = q.front();
            q.pop();

            char node = path.back();

            if (node == goal) {
                for (char c : path) cout << c << " ";
                cout << "\n";
                return;
            }

            for (char neigh : graph[node]) {
                if (!visited.count(neigh)) {
                    visited.insert(neigh);
                    auto newPath = path;
                    newPath.push_back(neigh);
                    q.push(newPath);
                }
            }
        }
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

    bfsLevelGlobalVisited(graph, 'S', 'G');
}
