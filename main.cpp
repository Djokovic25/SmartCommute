

    
#include <unordered_map>
#include <queue>
#include <string>
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;
#include<unordered_set>
unordered_set<int> blockedStations;

class history {
    queue<pair<string, string>> q;
    const int MAX_SIZE = 3;

public:
    void addtohistory(pair<string, string> a) {
        if (q.size() == MAX_SIZE) q.pop();  // maintain only last 3
        q.push(a);
    }

    void showhistory() {
        if (q.empty()) {
            cout << "No recent routes.\n";
            return;
        }
        cout << "\nRecent Routes:\n";
        queue<pair<string, string>> temp = q;
        while (!temp.empty()) {
            auto p = temp.front();
            temp.pop();
            cout << "- " << p.first << " → " << p.second << endl;
        }
    }
};

class graphs {
    

public:
    unordered_map<int, string> idtostation;
    unordered_map<string, int> stationtoid;
    history h;

    void buildgraph(vector<pair<int, int>> adj[]) {
        // Considering the graph as undirected
        adj[0].push_back({1, 4});
        adj[1].push_back({0, 4});

        adj[1].push_back({2, 5});
        adj[2].push_back({1, 5});

        adj[2].push_back({3, 6});
        adj[3].push_back({2, 6});

        adj[0].push_back({4, 3});
        adj[4].push_back({0, 3});

        adj[0].push_back({5, 7});
        adj[5].push_back({0, 7});

        adj[5].push_back({6, 5});
        adj[6].push_back({5, 5});

        adj[6].push_back({7, 4});
        adj[7].push_back({6, 4});

        adj[7].push_back({8, 6});
        adj[8].push_back({7, 6});

        adj[0].push_back({9, 10});
        adj[9].push_back({0, 10});

        adj[1].push_back({4, 6});
        adj[4].push_back({1, 6});

        adj[2].push_back({5, 8});
        adj[5].push_back({2, 8});

        adj[9].push_back({6, 15});
        adj[6].push_back({9, 15});

        adj[1].push_back({7, 12});
        adj[7].push_back({1, 12});
    }

    void load_station() {
        vector<string> stations = {
            "Majestic", "MG Road", "Indiranagar", "Baiyappanahalli",
            "Vidhana Soudha", "Kempegowda Metro Station", "Yeshwanthpur",
            "Rajajinagar", "Jalahalli", "Banashankari"};

        for (int i = 0; i < stations.size(); i++) {
            idtostation[i] = stations[i];
            stationtoid[stations[i]] = i;
        }
    }

    void dijkstra(vector<pair<int, int>> adj[]) {
        cout << "\nAvailable stations:\n";
        for (auto &s : stationtoid) cout << "- " << s.first << '\n';

        string src, destination;
        cout << "Enter source station: ";
        cin.ignore();  // Clear newline from previous input
        getline(cin, src);
        cout << "Enter destination station: ";
        getline(cin, destination);

        // auto trim = [](string &s) {
        //     s.erase(s.find_last_not_of(" \n\r\t") + 1);
        //     s.erase(0, s.find_first_not_of(" \n\r\t"));
        // };
        // trim(src);
        // trim(destination);

        // if (stationtoid.find(src) == stationtoid.end()) {
        //     cout << " Source station not found!\n";
        //     return;
        // }
        // if (stationtoid.find(destination) == stationtoid.end()) {
        //     cout << " Destination station not found!\n";
        //     return;
        // }

        int n = stationtoid.size();
        vector<int> result(n, INT_MAX);
        vector<int> parent(n, -1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        int srcId = stationtoid[src];
        int destId = stationtoid[destination];
        result[srcId] = 0;
        pq.push({0, srcId});

        while (!pq.empty()) {
            int dist = pq.top().first;
            int node = pq.top().second;
            pq.pop();
            for (auto it : adj[node]) {
                int adjnode = it.first;
                int weight = it.second;
                    if (blockedStations.count(node) || blockedStations.count(adjnode)) continue;

                if (dist + weight < result[adjnode]) {
                    result[adjnode] = dist + weight;
                    parent[adjnode] = node;
                    pq.push({result[adjnode], adjnode});
                }
            }
        }

        if (result[destId] == INT_MAX) {
            cout << " No path exists between " << src << " and " << destination << ".\n";
            return;
        }

        vector<int> path;
        for (int at = destId; at != -1; at = parent[at])
            path.push_back(at);
        reverse(path.begin(), path.end());

        cout << "\n Shortest path from " << src << " to " << destination << ":\n";
        for (int i = 0; i < path.size(); ++i) {
            cout << idtostation[path[i]];
            if (i != path.size() - 1) cout << " -> ";
        }
        cout << "\n  Total Distance: " << result[destId] << " units\n";

        h.addtohistory({src, destination});
    }
};

int main() {
    vector<pair<int, int>> adj[10];
    graphs g;
    g.load_station();
    g.buildgraph(adj);

    while (true) {
        cout << "\nDISPLAY MENU\n1. See shortest route\n2. See history\n3. Block station\n4. Exit\nEnter choice: ";
        int choice;
        cin >> choice;
        cin.ignore(); // Clear newline after reading choice

        string stationName; // Declare before switch

        switch (choice) {
            case 1:
                g.dijkstra(adj);
                break;
            case 2:
                g.h.showhistory();
                break;
            case 3:
                cout << "Enter station to block: ";
                getline(cin, stationName);
                if (g.stationtoid.count(stationName)) {
                    blockedStations.insert(g.stationtoid[stationName]);
                    cout << stationName << " has been blocked.\n";
                } else {
                    cout << "Invalid station!\n";
                }
                break;
            case 4:
                blockedStations.clear();
                cout << "All stations unblocked.\n";
                break;

            case 5:
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }
}