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

int branch_and_bound_pq_heuristic(unordered_map<char, vector<pair<char, int>>>& graph,
                                  unordered_map<char, int>& hill_approx,
                                  char start, char goal, int bound)
{
    using State = pair<pair<int, int>, pair<char, vector<char>>>;
    priority_queue<State, vector<State>, greater<State>> pq;

    int initial_estimate = hill_approx[start]; 
    pq.push({{initial_estimate, 0}, {start, {start}}});

    unordered_set<char> visited;

    while (!pq.empty()) {
        auto [costs, nodePath] = pq.top();
        auto [est_cost, g_cost] = costs;
        auto [current, path] = nodePath;
        pq.pop();

        if (g_cost > bound) return -1;

        if (current == goal) {
            cout << "Path found: ";
            for (char node : path) cout << node << " ";
            cout << "| Distance: " << g_cost << endl;
            return g_cost;
        }

        visited.insert(current);

        for (auto& neighbor : graph[current]) {
            if (!visited.count(neighbor.first)) {
                int new_g = g_cost + neighbor.second;
                int new_est = new_g + hill_approx[neighbor.first];
                vector<char> newPath = path;
                newPath.push_back(neighbor.first);
                pq.push({{new_est, new_g}, {neighbor.first, newPath}});
            }
        }
    }
    return -1;
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

    vector<char> path = {'S'};

    int oracle_distance = british_museum_recursive(graph, 'S', 'G', path, 0);

    if (oracle_distance == INT_MAX) {
        cout << "Goal not reachable." << endl;
        return -1;
    } else {
        cout << "Smallest path distance (oracle): " << oracle_distance << endl;
    }

    cout << "\n--- Branch and Bound with Heuristic ---\n";
    int result = branch_and_bound_pq_heuristic(graph, hill_approx, 'S', 'G', oracle_distance);

    if (result == -1)
        cout << "Goal not reachable.\n";
    else
        cout << "Best path cost via Branch and Bound + Heuristic: " << result << endl;

    return 0;
}
