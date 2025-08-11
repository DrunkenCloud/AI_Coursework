#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <climits>
#include <algorithm>

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

using State = pair<int, pair<int, pair<char, vector<char>>>>;

int a_star_search(unordered_map<char, vector<pair<char, int>>>& graph,
                  unordered_map<char, int>& heuristic,
                  char start, char goal, int bound)
{
    priority_queue<State, vector<State>, greater<State>> pq;

    int initial_h = heuristic[start];
    vector<char> initial_path = {start};
    
    pq.push({initial_h, {0, {start, initial_path}}});

    unordered_set<char> visited;
    int best_cost = INT_MAX;

    while (!pq.empty()) {
        auto [f_cost, state_data] = pq.top();
        auto [g_cost, node_data] = state_data;
        auto [current, path] = node_data;
        pq.pop();

        if (g_cost > best_cost || f_cost > bound) {
            continue;
        }
        
        if (current == goal) {
            if (g_cost < best_cost) {
                best_cost = g_cost;
            }
            cout << "Path found: ";
            for (char node : path) cout << node << " ";
            cout << "| Distance: " << g_cost << endl;
            continue;
        }

        if (visited.count(current)) {
            continue;
        }
        visited.insert(current);

        for (auto& neighbor : graph[current]) {
            char next_node = neighbor.first;
            int edge_weight = neighbor.second;
            
            if (!visited.count(next_node)) {
                int new_g = g_cost + edge_weight;
                int new_h = heuristic[next_node];
                int new_f = new_g + new_h;

                if (new_g < best_cost) {
                    vector<char> new_path = path;
                    new_path.push_back(next_node);
                    pq.push({new_f, {new_g, {next_node, new_path}}});
                }
            }
        }
    }
    
    return (best_cost == INT_MAX) ? -1 : best_cost;
}

int main() {
    unordered_map<char, vector<pair<char, int>>> graph;
    graph['S'] = {{'A', 3}, {'B', 5}};
    graph['A'] = {{'D', 3}, {'B', 4}};
    graph['B'] = {{'A', 4}, {'C', 4}};
    graph['C'] = {{'E', 6}};
    graph['D'] = {{'A', 3}, {'G', 5}};
    graph['E'] = {{'C', 6}};
    graph['G'] = {{'D', 5}};

    unordered_map<char, int> hill_approx = {
        {'S', 10}, {'A', 7}, {'B', 6}, {'C', 7}, {'D', 5}, {'E', 6}, {'G', 0}
    };
    
    char start_node = 'S';
    char goal_node = 'G';

    cout << "--- British Museum Search (Oracle) ---\n";
    vector<char> path = {start_node};
    int oracle_distance = british_museum_recursive(graph, start_node, goal_node, path, 0);

    if (oracle_distance == INT_MAX) {
        cout << "Goal not reachable by oracle." << endl;
        return -1;
    } else {
        cout << "Smallest path distance (oracle): " << oracle_distance << endl;
    }

    cout << "\n--- A* Search ---\n";
    int result = a_star_search(graph, hill_approx, start_node, goal_node, oracle_distance);
    
    if (result == -1)
        cout << "Goal not reachable by A*.\n";
    else
        cout << "Best path cost via A* search: " << result << endl;

    return 0;
}