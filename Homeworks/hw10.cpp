//1
#include <iostream>
#include <vector>
#include <list>
#include<queue>
using namespace std;

class Graph {
    long long v;
    list< long long>* adj;

public:
    
    Graph( long long v){
    this->v = v;
    adj = new list< long long>[v];
}
    
    void addEdge( long long start,  long long end){
    adj[start].push_back(end);
}
    
    bool isCycle(){
    vector< long long> degree(v, 0);
    for ( long long i = 0; i < v; i++) {
        for (auto v : adj[i]){
            degree[v]++;
        }
    }
    queue< long long> q;
    for ( long long i = 0; i < v; i++)
        if (degree[i] == 0){
            q.push(i);
        }

     long long counter = 0;
    vector< long long> top_order;
    while (!q.empty()) {
        long long u = q.front();
        q.pop();
        top_order.push_back(u);

        list<long long>::iterator itr;
        for (itr = adj[u].begin(); itr != adj[u].end(); itr++){
            if (--degree[*itr] == 0){
                q.push(*itr);
            }
        }
        counter++;
    }

    if (counter != v) return true;
       return false;
}
};

int main(){
     long long countGraphs;
    cin >> countGraphs;

     long long input, start, end;
    while (countGraphs--) {
        cin >> input;
        Graph g1(100001);
        while (input--) {
            cin >> start >> end;
            g1.addEdge(start, end);
        }
        if (g1.isCycle()) {
            cout << "1 ";
        }
        else {
            cout << "0 ";
        }
    }
    return 0;
}


//2
#include <iostream>
#include <queue>
using namespace std;

long rows, cols, len;
long seats = 0;
long actualseats = 0;
long spreadVirusSeats = 0;

bool isValidPosition(pair<long, long>* position, bool** spread){
    if (position->first > rows || position->second > cols){
        return false;
    }
    else if (position->first <= 0 || position->second <= 0) {
        return false;
    }
    else if (spread[position->first - 1][position->second - 1] == 1){
        return false;
    }
    return true;
}

void virus(queue<pair<long, long>>* seat, pair<long, long> currentPosition, bool** sick){
    pair<long, long> position;
    position.first = currentPosition.first + 1;
    position.second = currentPosition.second;
    if (isValidPosition(&position, sick)) {
        sick[position.first - 1][position.second - 1] = 1;
        actualseats++;
        seat->push(position);
    }

    position.first -= 2;
    if (isValidPosition(&position, sick)) {
        sick[position.first - 1][position.second - 1] = 1;
        actualseats++;
        seat->push(position);
    }

    position.first++;
    position.second++;
    if (isValidPosition(&position, sick)){
        sick[position.first - 1][position.second - 1] = 1;
        actualseats++;
        seat->push(position);
    }

    position.second -= 2;
    if (isValidPosition(&position, sick)){
        sick[position.first - 1][position.second - 1] = 1;
        actualseats++;
        seat->push(position);
    }
}

int main(){
    queue<pair<long, long>> s;

    cin >> rows >> cols;
    cin >> len;

    bool** sick = new bool*[rows];

    for (long i = 0; i < rows; i++) {
        sick[i] = new bool[cols];
    }

    for (long i = 0; i < rows; i++) {
        for (long j = 0; j < cols; j++) {
            sick[i][j] = 0;
        }
    }

   long row, column;
   pair<long, long> position;
    
   long count;
   cin >> count;
    
    while (count--) {
        cin >> row >> column;
        position.first = row;
        position.second = column;
        s.push(position);
        sick[row - 1][column - 1] = 1;
        seats++;
        spreadVirusSeats++;
    }

    while (!s.empty() && len > 0){
        while (seats > 0){
            virus(&s, s.front(), sick);
            s.pop();
            seats--;
        }
        seats = actualseats;
        actualseats = 0;
        spreadVirusSeats += seats;
        len--;
    }

    cout << rows * cols - spreadVirusSeats;
    return 0;
}

//3
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>
using namespace std;

int main() {
    int countOfWords;
    cin >> countOfWords;

    string s;
    vector<string> v;
    while (countOfWords--) {
        cin >> s;
        v.push_back(s);
    }

    map<char, long> count;
    map<char, vector<char>> adj;
    long len = v.size();

  for (auto word : v) {
        for (auto c : word) {
            count[c] = 0;
        }
    }

   for (long i = 1; i < len; i++){
            long k = 0, len1 = v[i - 1].size(), len2 = v[i].size();

            while (v[i - 1][k] == v[i][k]) {
                k++;
            }

            if (k >= min(len1, len2)) continue;

            count[v[i][k]]++;
            adj[v[i - 1][k]].push_back(v[i][k]);
        }

    string result;
    queue<char> tmp;
    map<char, long>::iterator it = count.begin();
    while (it != count.end()) {
        if (it->second == 0) {
            tmp.push(it->first);
        }
        it++;
    }
    while (!tmp.empty()) {
        char x = tmp.front();
        tmp.pop();
        result += x;
        vector<char>::iterator it2 = adj[x].begin();
        while (it2 != adj[x].end()) {
            count[*it2]--;
            if (count[*it2] == 0) {
                tmp.push(*it2);
            }
            it2++;
        }
    }
    if (result.size() == count.size()) {
        long length= result.size();
        for (long i = 0; i <length; i++) {
            cout << result[i] << ' ';
        }
    }
}