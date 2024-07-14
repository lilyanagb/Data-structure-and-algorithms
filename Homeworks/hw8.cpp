//1
#include <bits/stdc++.h>
using namespace std;

priority_queue<int> bottom;
priority_queue<int,deque<int>,greater<int>> top;

void change() {
    if (bottom.size() == top.size()) return;

    if (bottom.size() < top.size()){
        bottom.push(top.top());
        top.pop();
    }
    else {
        top.push(bottom.top());
        bottom.pop();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int count;
    cin >> count;

    int input;
    cin >> input;
    bottom.push(input);

    double median;
    median = input;
    printf("%.1f \n", median);

    for (int i = 1; i < count; i++) {
        cin >> input;

        if (input < bottom.top()) {
            bottom.push(input);
            change();
        }
        else {
            top.push(input);
            change();
        }


        if (bottom.size() == top.size())
        {
            median = (bottom.top() + top.top()) / 2.0;
        }
        else if (bottom.size() > top.size())
        {
            median = bottom.top();
        }
        else {
            median = top.top();
        }

        printf("%.1f \n", median);
    }

    return 0;
}

//2
#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

struct compareBySecond {
    bool operator() (pair<pair<long long, long long>, long long>& a, pair<pair<long long, long long>, long long>& b) {
        if (a.first.second == b.first.second) {
            return a.second > b.second;
      }
        return a.first.second > b.first.second;
    }
};

priority_queue<pair<pair<long long, long long>, long long>, vector<pair<pair<long long, long long>, long long>>, compareBySecond> que;
vector<pair<pair<long long, long long>, long long>> v;

int main() {
    long long countOfTasks;
    cin >> countOfTasks;

    for (long long i = 0; i < countOfTasks; i++) {
        long long startTime, neededTime;
        cin >> startTime >> neededTime;
        v.push_back({ { startTime,neededTime },i });
    }

    sort(v.begin(), v.end());
    long long cur = 0, index = 0;
    vector<long long> result;

    while (1) {
        long long i;
        for (i = index; i < countOfTasks; i++) {
            if (v[i].first.first <= cur) {
                que.push(v[i]);
            }
            else {
                index = i;
                break;
            }
        }

        if (i == countOfTasks) {
            index = countOfTasks;
        }

        if (!que.empty()) {

            pair<pair<long long, long long>, long long> tmp = que.top();
            result.push_back(tmp.second);
            cur += tmp.first.second;
            que.pop();
        }
        else {
            if (index != countOfTasks)
                cur = v[index].first.first;
        }

        if (index == countOfTasks && que.empty()) break;
    }

    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i] << ' ';
    }
    return 0;
}

//3
#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

struct compareBySecond{
    bool operator() (pair<long, long>& a, pair<long, long>& b){
        return a.second > b.second;
    }
};

priority_queue<pair<long, long>, vector<pair<long, long>>, compareBySecond> que;
vector<pair<long, long>> s;

int main(){
    long students;
    cin >> students;

    for (long i = 0; i < students; i++){
        long submitTime,linesCode;
        cin >> submitTime >> linesCode;
        s.push_back({ submitTime,linesCode });
    }

    sort(s.begin(), s.end());
    long cur = 0, sumWaiting = 0, index = 0,i=0;

    while (1){
        if (index == students && que.empty()) break;
        
        for (i = index; i < students; i++){
            if (s[i].first <= cur) {
                que.push(s[i]);
            }
            else{
                index = i;
                break;
            }
        }

        if (i == students) {
            index = students;
        }

        if (!que.empty()){
            pair<long,long> tmp = que.top();
            sumWaiting += cur + tmp.second - tmp.first;
            cur += tmp.second;
            que.pop();
        }
        else{
            if (index != students)
                cur = s[index].first;
        }
    }

    cout << sumWaiting / students << endl;
    return 0;
}

//4
#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

vector <long long> pq;
vector<pair<long long, long long>> operatorsFreeCheck;

int main() {
    long long calls, operators;
    cin >> calls >> operators;

    long long startCall, neededTimeToEnd;
    for (long long i = 0; i < calls; i++) {
        cin >> startCall >> neededTimeToEnd;

        if (i < operators) {
            operatorsFreeCheck.push_back({ 1, i });
            pq.push_back(neededTimeToEnd + startCall);
        }
        else {
            long long op = i % operators;
          
            long search = 0;
            while (1) {
                if (pq[op] <= startCall) {
                    pq[op] = startCall + neededTimeToEnd;
                    operatorsFreeCheck[op].first++;
                    break;
                }
                else if (op == operators - 1) {
                    op = 0;
                }
                else {
                    op++;
                }

                search++;
                if (search == operators) break;
            }
        }
    }
  
    sort(operatorsFreeCheck.begin(), operatorsFreeCheck.end());
    long long max = operatorsFreeCheck[operators - 1].first;

    for (long long i = 0; i < operators; i++) {
        if (operatorsFreeCheck[i].first == max) {
            cout << operatorsFreeCheck[i].second << " ";
        }
    }
    return 0;
}