//1
#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

int main()
{
    long N;
    cin>>N;

    queue<pair<long, long>> roomKey;
    unordered_map<long, long> keyMap;
    long* k = new long[N];
    long door,key;

    for (int i = 0; i < N; i++)
    {
        cin>>key;
        k[i] = key;
    }

    for (int i = 0; i < N; i++)
    {
        cin>>door;
        roomKey.push(pair<long, long>(k[i], door));
    }

    long result = 0;
    for (long i = 0; i < N; i++)
    {
        ++keyMap[roomKey.front().first];
        if (keyMap[roomKey.front().second] == 0)
        {
            ++result;
        }
        else
        {
           --keyMap[roomKey.front().second];
        }
        roomKey.pop();
    }

    cout << result;

    return 0;
}

//2
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

long countGP(vector<long> arr, long key) {
    unordered_map<long, long> prev;
    unordered_map<long, long> next;

    for (long el : arr) {
        next[el]++;
    }
    long sum = 0;
    long len = arr.size();
    for (long i = 0; i < len; i++) {
        long cur = arr[i];
        long right = 0, left = 0;
        next[cur]--;

        if (prev.find(cur / key) != prev.end() && cur % key == 0) {
            left = prev[cur / key];
        }
        if (next.find(cur * key) != next.end()) {
            right = next[cur * key];
        }
        sum += right * left;
        prev[cur]++;

    }
    return sum;
}
int main() {
    long N, K;
    cin >> N >> K;

    vector<long> llist;
    long input;
    for (long i = 0; i < N; i++) {
        cin >> input;
        llist.push_back(input);
    }
    cout<<countGP(llist, K);

    return 0;
}

//3
