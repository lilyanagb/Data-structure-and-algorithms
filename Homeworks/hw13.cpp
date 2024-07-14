//3
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const long N = 100001;
long degree[N];
long numberOfEdges = 0, numberOfVertices = 0;
vector<string> result;

int main() {
    long count;
    cin >> count;

    long from, to;
    while (count--) {
        long numberOfOddDegree = 0;
        cin >> numberOfVertices >> numberOfEdges;

        for (int i = 0; i < N; i++) {
            degree[i] = 0;
        }

        while (numberOfEdges) {
            cin >> from >> to;

            degree[to]++;
            degree[from]++;
            numberOfEdges--;
        }

        long counter = 0;
        for (int i = 0; i < N; i++) {

            if (degree[i] % 2 != 0) {
                numberOfOddDegree++;
            }

            if (degree[i] > 0) {
                counter++;
            }
        }


        if (counter != numberOfVertices) {
            result.push_back("none");
        }else if (numberOfOddDegree == 0) {
            result.push_back("ecycle");
        }
        else if (numberOfOddDegree == 0 || numberOfOddDegree == 2) {
            result.push_back("epath");
        }
        else {
            result.push_back("none");
        }
    }

    long resultSize = result.size();
    for (long i = 0; i < resultSize; i++) {
        cout << result[i] << endl;
    }

    return 0;
}