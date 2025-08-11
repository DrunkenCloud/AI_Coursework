#include <bits/stdc++.h>
using namespace std;

void britishMuseumSearch(unordered_map<char, vector<char>> &graph, char start, char goal) {
    auto cmp = [](const pair<char, vector<char>> &a, const pair<char, vector<char>> &b) {
        return (a.first != b.first) ? a.first > b.first : a.second.size() > b.second.size();
    };

    priority_queue<pair<char, vector<char>>, vector<pair<char, vector<char>>>, decltype(cmp)> pq(cmp);
    pq.push({start, {start}});

    while (!pq.empty()) {
        auto [node, path] = pq.top();
        pq.pop();

        if (node == goal) {
            for (char c : path) cout << c << " ";
            cout << "\n";
            continue;
        }

        for (char neigh : graph[node]) {
            if (find(path.begin(), path.end(), neigh) == path.end()) {
                vector<char> new_path = path;
                new_path.push_back(neigh);
                pq.push({neigh, new_path});
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

    britishMuseumSearch(graph, 'S', 'G');
}
