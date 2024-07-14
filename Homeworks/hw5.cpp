//1
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    string s;
    cin >> s;

    long size = s.size();

    vector<pair<char, long>> elements;
    for (int i = 48; i < 123; i++) {
        if (i > 57 && i < 65) {
            elements.push_back({ ' ',0 });
            continue;
        }

        if (i > 90 && i < 97) {
            elements.push_back({ ' ',0 });
            continue;
        }

        elements.push_back({ i,0 });
     }


    for (int i = 0; i < size; i++) {
        int curEl = s[i];
        elements[curEl-48].second ++;
    }

    for (int i = 0; i < size; i++) {
        int el = s[i];
        if (elements[el-48].second == 1) {
            cout << i << " ";
        }
    }
    return 0;
}

//2
#include <vector>
#include <iostream>
#include <stack>
using namespace std;

int main() {
    long players;
    cin >> players;

    long power;
    stack<long> right;
    vector<long> final;
    stack<long> final2;
    cin >> power;

    while (power < 0) {
        final.push_back(power);
        players--;
        if (players == 0) break;
        cin >> power;
    }

    while (power > 0) {

        right.push(power);
        players--;
        if (players == 0) break;
        cin >> power;
        
    }

    while (players > 0) {
        if (!right.empty() && power < 0 && abs(power) < right.top()) {
            cin >> power;
            players--;
        }
        else if (power > 0) {
            right.push(power);
            players--;
            if (players == 0) break;
            cin >> power;
        }
        else if (!right.empty() && abs(power) == right.top()) {
            right.pop();
            cin >> power;
            players--;
        }
        else if (!right.empty() && abs(power) > right.top()) {
            right.pop();
        }
        else {
            final.push_back(power);
            cin >> power;
            players--;
        }
    }

    while (!right.empty()) {
        final2.push(right.top());
        right.pop();
    }

    long size = final.size();
    for (long i = 0; i < size; i++) cout << final[i] << " ";

    while (!final2.empty()) {
        cout << final2.top()<<" ";
        final2.pop();
    }
    return 0;
}

//3
#include <algorithm>
#include <deque>
#include <vector>
#include <iostream>

using namespace std;

long minSum(vector<long>& arr, long k)
{
    deque<long> window;
    long n = arr.size();

    long minSum = 0;
    long minEl = arr[0];
    window.push_back(arr[0]);
    
    for (long i = 1; i < k; i++) {
        if (arr[i] < minEl) {
            minEl = arr[i];
        }
        window.push_back(arr[i]);
    }

    minSum += minEl;

    for (long i = k; i < n; i++) {
        long popped = window.front();
        window.pop_front();
        window.push_back(arr[i]);

        if (minEl != popped) {
            minEl = min(minEl, window.back());
        }
        else {
            deque<long>::iterator it = min_element(window.begin(), window.end());
            minEl= *it;
        }
        minSum += minEl;
    }

    return minSum;
}

int main()
{
    long count;
        cin >> count;
    
        long k;
        cin >> k;
    
        long input;
        vector<long> v;
        for (long i = 0; i < count; i++) {
            cin >> input;
            v.push_back(input);
        }
        
        cout << minSum(v, k);
        return 0;
}


//4
#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int n;
    cin >> n;
    vector<int> hungerPoints(n);
    for (int competitor = 0; competitor < n; competitor++) cin >> hungerPoints[competitor];
 
    stack<pair<int, int>> s;
    int daysToFinal = 0;
    for (int competitor = hungerPoints.size() - 1; competitor >= 0; competitor--) {
 
        int days = 0;
        while (!s.empty() && hungerPoints[competitor] < hungerPoints[s.top().first]) {
            days = max(days + 1, s.top().second);
            s.pop();
        }
 
        s.push({ competitor,days });
        daysToFinal = max(daysToFinal, days);
 
    }
    cout << daysToFinal;
    return 0;
}