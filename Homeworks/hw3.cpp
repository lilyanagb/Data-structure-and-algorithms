//1
#include <vector>
#include <iostream>
using namespace std;


int main() {
    long long int number;
    cin >> number;
    long long int j = 1, counter = 0, br = 0,copy=number;
    while (j * j * j <= number) {
        j++;
        counter++;
 }
    while (number > 0){
        long long int cube = counter * counter * counter;
        if (cube <= number) {
            copy -= cube;
            number = copy;
            br++;
        }
        else {
           counter--;
        }
    }
    cout << br;
    return 0;
}

//2
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

long unsigned int getClosest(long unsigned int left, long unsigned int right, long unsigned int x)
{
    if (x - left > right - x) {
        return right;
    }
    return left;
}

long unsigned int binarySearch(const vector<pair<long unsigned int, long unsigned int>>& arr, long unsigned int x)
{
    long unsigned int start=0, mid=0, end=arr.size();
    if (x <= arr[0].first)  return arr[0].first;
    if (x >= arr[arr.size() - 1].first) return arr[arr.size() - 1].first;

    while (start < end) {
        mid = start + (end - start) / 2;

        if (arr[mid].first == x) {
            return arr[mid].first;
        }

        if (x < arr[mid].first) {

            if (mid > 0 && x > arr[mid - 1].first) {
                return getClosest(arr[mid - 1].first, arr[mid].first, x);
            }

            end = mid;
        }
        else {
            if (mid < arr.size() - 1 && x < arr[mid + 1].first) {
                return getClosest(arr[mid].first, arr[mid + 1].first, x);
            }

            start = mid + 1;
        }
    }

    return arr[mid].first;
}

bool compareByFirst(const pair<long unsigned int, long unsigned int>& a, const pair<long unsigned int, long unsigned int>& b) {

    return a.first < b.first;
}


int main()
{
    long unsigned int numberOfTopics;
    long unsigned int numberOfTeams;

    cin >> numberOfTopics >> numberOfTeams;

    vector<pair<long unsigned int, long unsigned int>> complexity;
    vector<pair<long unsigned int, long unsigned int>> knowledge;

    long unsigned int input;
    for (long unsigned int i = 0; i < numberOfTopics; i++) {
        cin >> input;
        complexity.push_back(make_pair(input, i));
    }

    for (long unsigned int i = 0; i < numberOfTeams; i++) {
        cin >> input;
        knowledge.push_back(make_pair(input, i));
    }

    sort(complexity.begin(), complexity.end(), compareByFirst);
    vector<pair<long unsigned int, long unsigned int>> copy;

    for (long unsigned int i = 0; i < numberOfTeams; i++) {
        copy.push_back(make_pair(knowledge[i].second,binarySearch(complexity, knowledge[i].first)));
    }

    for (long unsigned int i = 0; i < numberOfTeams; i++) {
        cout << copy[i].second << endl;
    }
    return 0;
}

//3

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
bool compareByFirst(const pair<long long, long long>& a, const pair<long long, long long>& b) {
    return (a.first < b.first);

}

bool compareBySecond(const pair<long long, long long>& a, const pair<long long, long long>& b) {
    if (a.first == b.first)
        return (a.second > b.second);

    return false;

}
long long lis(const vector<pair<long long, long long>>& arr) {
    long long len = arr.size();
    const int INF = 1e9;
    vector<long long> subs(len + 1, INF);
    subs[0] = -INF;

    for (long long i = 0; i < len; i++) {
        long long j = upper_bound(subs.begin(), subs.end(), arr[i].second) - subs.begin();
        if (subs[j - 1] < arr[i].second && arr[i].second < subs[j])
            subs[j] = arr[i].second;
    }

    long long counter = 0;
    for (long long i = 0; i <= len; i++) {
        if (subs[i] < INF)
            counter = i;
    }
    return counter;
}
int main() {
    long long numberOfMonsters;
    cin >> numberOfMonsters;

    vector<pair<long long, long long>> scores;
    pair<long long, long long> pairs;

    for (long long i = 0; i < numberOfMonsters; i++) {
        cin >> pairs.first >> pairs.second;
        scores.push_back(pairs);
    }
    stable_sort(scores.begin(), scores.end(), compareByFirst);
    stable_sort(scores.begin(), scores.end(), compareBySecond);
    cout << lis(scores);
    return 0;
}

//4
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

struct monster {
    long long first;
    long long second;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    long long elementsInRow, numberOfRequests;
    cin >> elementsInRow >> numberOfRequests;

    vector<long long> numbersInRow;
    vector<monster> pairs(numberOfRequests);
    long long input;

    for (long long i = 0; i < elementsInRow; i++) {
        cin >> input;
        numbersInRow.push_back(input);
    }

    for (long long i = 0; i < numberOfRequests; i++) {
        cin >> pairs[i].first >> pairs[i].second;
    }

    sort(numbersInRow.begin(), numbersInRow.end());

    long long len = numbersInRow.size(), jump = sqrt(len), start = 0, end = start + jump;
    long long sum = 0, copy = 0, added = 0, startIndex = 0;
    vector<long long> sumOfParts;

    while (end <= len)
    {
        if (start < end) {
            sum += numbersInRow[start];
            start++;
        }
        else {
            sumOfParts.push_back(sum);
            sum = 0;

            if (end == len) break;
           
            start = end;
            end += jump;

            if (end > len - 1)  end = len;
        }
    }

    for (long long i = 0; i < numberOfRequests; i++) {
        vector<long long>::iterator upper1 = upper_bound(numbersInRow.begin(), numbersInRow.end(), pairs[i].second);
        startIndex = upper1 - numbersInRow.begin();

        long long placeInVector = startIndex / jump;
        long long placeInPart = startIndex % jump;
        startIndex--;
        copy = startIndex;
        added = 0;

        while (pairs[i].first >= added && placeInPart > 0 && placeInVector >= 0) {
            added += numbersInRow[startIndex];
            if (pairs[i].first < added) {
                added -= numbersInRow[startIndex];
                break;
            }
            placeInPart--;
            startIndex--;
        }
        placeInVector--;

        while (pairs[i].first >= added && placeInVector >= 0) {
            added += sumOfParts[placeInVector];
            if (pairs[i].first < added) {
                added -= sumOfParts[placeInVector];
                break;
            }
            placeInVector--;
            startIndex -= jump;
        }

        while (pairs[i].first >= added && startIndex >= 0) {
            added += numbersInRow[startIndex];
            if (pairs[i].first < added) {
                added -= numbersInRow[startIndex];
                break;
            }
            startIndex--;
        }

      
     printf("%i \n",  copy - startIndex);
    }

    return 0;
}