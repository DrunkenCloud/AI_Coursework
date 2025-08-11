#include <bits/stdc++.h>
using namespace std;

void bfsSearch(unordered_map<char, vector<char>> &graph, char start, char goal) {
    queue<pair<char, vector<char>>> q;
    q.push({start, {start}});
    bool found = false;

    while (!q.empty()) {
        int levelSize = q.size();
        vector<vector<char>> levelPaths;

        for (int i = 0; i < levelSize; i++) {
            auto [node, path] = q.front();
            q.pop();

            if (node == goal) {
                found = true;
                levelPaths.push_back(path);
                continue;
            }

            if (!found) {
                for (char neigh : graph[node]) {
                    if (find(path.begin(), path.end(), neigh) == path.end()) {
                        vector<char> new_path = path;
                        new_path.push_back(neigh);
                        q.push({neigh, new_path});
                    }
                }
            }
        }

        if (found) {
            for (auto &p : levelPaths) {
                for (char c : p) cout << c << " ";
                cout << "\n";
            }
            break;
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

    bfsSearch(graph, 'S', 'G');
}
