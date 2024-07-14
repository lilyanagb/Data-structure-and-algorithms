//1
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long N, M;
    cin >> N >> M;

    vector<long> paths(N+1);

    for (long i = 1; i <= N; i++) {
        paths[i] = i;
    }
    
    long from, to;
    long first, second;
    while (M--) {
        cin >> from >> to;
        first = paths[from];
        second = paths[to];

        for (long j = 1; j <= N; j++) {
            if (paths[j] == first) {
                paths[j] = second;
            }
        }
    }

    long Q;
    cin >> Q;

    long command;
    while (Q--) {
        cin >> command >> from >> to;

        if (command == 1) {
            cout << (paths[from] == paths[to]);
        }else if(command==2){
            first=paths[from];
            second = paths[to];

        for (long j = 1; j <= N; j++) {
            if (paths[j] == first) {
                paths[j] = second;
            }
        }
      }
    }
    return 0;
}