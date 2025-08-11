#include <bits/stdc++.h>

using namespace std;

bool beam_search(unordered_map<char, vector<pair<char, int>>>& graph,
                 unordered_map<char, int>& hill_approx,
                 char start, char goal, size_t beam_width)
{
    
    auto compare_nodes = [&](const pair<char, vector<char>>& a, const pair<char, vector<char>>& b) {
        return hill_approx.at(a.first) > hill_approx.at(b.first);
    };

    priority_queue<pair<char, vector<char>>, vector<pair<char, vector<char>>>, decltype(compare_nodes)> current_level(compare_nodes);
    current_level.push({start, {start}});

    while (!current_level.empty()) {
        priority_queue<pair<char, vector<char>>, vector<pair<char, vector<char>>>, decltype(compare_nodes)> next_level(compare_nodes);

        while (!current_level.empty()) {
            pair<char, vector<char>> current = current_level.top();
            current_level.pop();

            char current_id = current.first;
            vector<char> current_path = current.second;

            if (current_id == goal) {
                cout << "Path found: ";
                for (char n : current_path) {
                    cout << n << " ";
                }
                cout << endl;
                return true;
            }

            for (auto& neighbor : graph.at(current_id)) {
                auto new_path = current_path;
                new_path.push_back(neighbor.first);
                next_level.push({neighbor.first, new_path});
            }
        }

        vector<pair<char, vector<char>>> pruned_nodes;
        while (!next_level.empty() && pruned_nodes.size() < beam_width) {
            pruned_nodes.push_back(next_level.top());
            next_level.pop();
        }

        for (const auto& node : pruned_nodes) {
            current_level.push(node);
        }

        if (current_level.empty()) {
            break;
        }
    }

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

    size_t beam_width = 2;
    if (!beam_search(graph, hill_approx, 'S', 'G', beam_width)) {
        cout << "Goal not reachable." << endl;
    }

    return 0;
}