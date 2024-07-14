//1
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cmath>
using namespace std;

const long long N = 100001;
pair<long long,long long> dist[N];
vector<pair<long long, long long>> adj[N];

void shortestPath(long long v) {    
    for (long long i = 0; i < N; i++) {
        dist[i].first = LONG_MAX;
        dist[i].second = 0;
    }
    dist[v].first = 0;
    dist[v].second = 1;

    priority_queue< pair<long long, long long>, vector <pair<long long, long long>>, greater<pair<long long, long long>> > pq;
    pq.push({ 0,v });

    while (!pq.empty()) {
        long long curr = pq.top().second;
        long long weight = pq.top().first;
        pq.pop();

        if (weight > dist[curr].first) continue;

        for (pair<long long, long long> neighbour : adj[curr]) {
            long long child = neighbour.first;
            long long weightChildCurr = neighbour.second;

            if (dist[child].first > weight + weightChildCurr) {
                dist[child].first = weight + weightChildCurr;
                dist[child].second = dist[curr].second%1000000007;
                pq.push({ weightChildCurr + weight, child });
            }
            else if (dist[child].first == weight + weightChildCurr) {
                dist[child].second = (dist[child].second+dist[curr].second)%1000000007;
            }

        }
    }
}

int main() {
    long long numberOfEdges = 0, numberOfVertices = 0, costToChildOfCurrent = 0;
    long long from = 0, to = 0;
    cin >> numberOfVertices >> numberOfEdges;

    while (numberOfEdges) {
        cin >> from >> to >> costToChildOfCurrent;
        adj[from].push_back({ to, costToChildOfCurrent });
        numberOfEdges--;
    }

    shortestPath(1);

    if (dist[numberOfVertices].second%1000000007)
        cout << dist[numberOfVertices].first << " "<<dist[numberOfVertices].second%1000000007;
    else
        cout << -1 << " " << 0;

    return 0;
}

//2
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct Tunnel {
    long long to, kilos, weight;

    Tunnel(long long to, long long w, long long c = 0) : to(to), kilos(c), weight(w) {}
};

struct Compare {
    bool operator()(const Tunnel& a, const Tunnel& b) {
        return a.weight > b.weight;
    }
};

vector<long long> shortestPath(const vector<vector<Tunnel>>& adj, long long s, long long max) {
    priority_queue<Tunnel, vector<Tunnel>, Compare> pq;
    vector<long long> dist(adj.size(), LONG_MAX);
    vector<bool> isOut(adj.size());

    dist[s] = 0;
    pq.emplace(s, 0);

    while (!pq.empty()) {
        long long curr = pq.top().to;
        pq.pop();

        if (isOut[curr]) continue;

        for (auto x : adj[curr])
            if (x.kilos <= max && dist[x.to] > dist[curr] + x.weight) {
                dist[x.to] = dist[curr] + x.weight;
                pq.emplace(x.to, dist[x.to]);
            }
        isOut[curr] = true;
    }
    return dist;
}

long long binarySearch(const vector<vector<Tunnel>>& adj, long long min, long long max, long long T) {
    long long tmp = LONG_MAX;

    while (min <= max) {
        long long mid = (min + max) / 2;
        long long dist = shortestPath(adj, 0, mid).back();

        if (dist <= T) {
            tmp = mid;
            max = mid - 1;
        }
        else {
            min = mid + 1;
        }
    }

    if (tmp != LONG_MAX) return tmp;
    return -1;
}

int main() {
    long long numberOfEdges, numberOfVertices, time;
    cin >> numberOfEdges >> numberOfVertices >> time;

    vector<vector<Tunnel>> adj(numberOfEdges);
    while (numberOfVertices--) {
        long long from, to, kilos, weight;
        cin >> from >> to >> kilos >> weight;

        adj[from - 1].emplace_back(to - 1, weight, kilos);
    }

    cout << binarySearch(adj, 1, 1000000, time) << endl;
    return 0;
}

//3
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

vector<vector<pair<int, int>>> adj;
vector<int> dist;

void shortestPath(int v) {
    priority_queue< pair<int, int>, vector< pair<int, int>>, greater< pair<int, int>>> pq;
    pq.push({ 0, v });
    dist[v] = 0;

    while (!pq.empty()) {
        int v = pq.top().second;
        pq.pop();

        for (auto neighbour : adj[v]) {
            if (dist[neighbour.second] > dist[v] + neighbour.first) {
                dist[neighbour.second] = dist[v] + neighbour.first;
                pq.push({ dist[neighbour.second], neighbour.second });
            }
        }
    }
}

int main() {
    int numberOfEdges, numberOfVertices;
    cin >> numberOfEdges >> numberOfVertices;

    adj.assign(numberOfEdges + 1, vector< pair<int, int>>());
    dist.assign(numberOfEdges + 1, INT_MAX);

    int firstVertice, secondVertices, weight;
    while (numberOfVertices--) {
        cin >> firstVertice >> secondVertices >> weight;

        adj[firstVertice].push_back({ weight, secondVertices });
        adj[secondVertices].push_back({ weight, firstVertice });
    }

    int que;
    cin >> numberOfVertices;
    while (numberOfVertices--) {
        cin >> que;

        adj[que].push_back({ 0, numberOfEdges });
        adj[numberOfEdges].push_back({ 0, que });
    }


    shortestPath(numberOfEdges);

    int numTop;
    cin >> numberOfVertices;
    while (numberOfVertices--) {
        cin >> numTop;
        cout << dist[numTop]<<endl;
    }

    return 0;
}