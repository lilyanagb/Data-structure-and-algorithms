//1
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


void merge(vector<int>& vec, int start, int mid, int end) {
    int i = start, j = mid + 1;
    vector<int> temp;

    while (i <= mid && j <= end) {

        if (vec[i] <= vec[j]) {
            temp.push_back(vec[i]);
            i++;
        }
        else {
            temp.push_back(vec[j]);
            j++;
        }

    }

    while (i <= mid) {
        temp.push_back(vec[i]);
        i++;
    }

    while (j <= end) {
        temp.push_back(vec[j]);
        j++;
    }

    for (int i = start; i <= end; i++) {
        vec[i] = temp[i - start];
    }
}
void sortPrices(vector<int>& vec, int start, int end) {
    if (start >= end) {
        return;
    }
        int mid = (start + end) / 2;
        sortPrices(vec, start, mid);
        sortPrices(vec, mid + 1, end);
        merge(vec, start, mid, end);
}

int main() {
    int countOfPresents;
    vector<int> vec;
    int employees;

    cin >> countOfPresents;
    int input;
    for (int i = 0; i < countOfPresents; i++) {
        cin >> input;
        vec.push_back(input);
    }

    cin >> employees;

    sortPrices(vec, 0, countOfPresents - 1);

    int i = 0;
    long count = 0;

    while (i < employees) {
        count += vec[i];
        i++;
    }
    cout << count;
    return 0;
}


//2
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct date {
    long day;
    long month;
    long year;
    long seconds;
    long index;
};

bool compare(const date& a,const date& b) {

    if (a.year == b.year) {
        if (a.month == b.month) {
            if (a.day == b.day) {
                if (a.seconds == b.seconds) return false;

                return (a.seconds < b.seconds);
            }
            return (a.day < b.day);
        }
        return (a.month < b.month);
    }
    return (a.year < b.year);
}

int main() {
    long count;
    cin >> count;

    vector <pair<string, string>> vec;
    pair<string, string> input;

    for (long i = 0; i < count; i++) {
        cin >> input.first >> input.second;
        vec.push_back(input);
    }

    vector<date> d(count);

    for (long i = 0; i < count; i++) {
        d[i].day = (vec[i].second[0] - '0') * 10 + (vec[i].second[1] - '0');
        d[i].month = (vec[i].second[3] - '0') * 10 + (vec[i].second[4] - '0');
        d[i].year = (vec[i].second[6] - '0') * 1000 + (vec[i].second[7] - '0') * 100 + (vec[i].second[8] - '0') * 10 + (vec[i].second[9] - '0');
        d[i].index = i + 1;
        d[i].seconds = ((vec[i].first[0] - '0') * 10 + (vec[i].first[1] - '0')) * 3600 + ((vec[i].first[3] - '0') * 10 + (vec[i].first[4] - '0')) * 60 + ((vec[i].first[6] - '0') * 10 + (vec[i].first[7] - '0'));
    }

    stable_sort(d.begin(), d.end(), compare);

    for (long i = 0; i < count; i++) {
        cout << d[i].index << endl;
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

int main() {
    int count;
    cin >> count;
    string s;
    cin >> s;
    vector<char> copy;

    stable_sort(s.begin(), s.end());
    for (int l = 0; l < count; l++) {
        if (s[l] >= 'A' && s[l] <= 'Z') {
            copy.push_back(s[l]);
        }
        else {
            cout << s[l];
        }
    }
    for (size_t l = 0; l < copy.size(); l++) {
        cout << copy[l];
    }
    return 0;
}

//4
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

bool compare(const pair<pair<double, double>, long>& a, const pair<pair<double, double>, long>& b) {
    if (a.first.second == b.first.second) {
        return (a.first.first > b.first.first);
    }
    else {
        return (a.first.second > b.first.second);
    }
}

int main() {
    long people;
    cin >> people;

    pair<double, double> input;
    vector<pair<pair<double, double>, long>> w;
    vector<pair<pair<double, double>, long>> duplicate;

    for (long i = 0; i < people; i++) {
        cin >> input.first >> input.second;
        w.push_back(make_pair(input, i + 1));
    }

    for (long i = 0; i < people; i++) {
        w[i].first.second = ((w[i].first.first * w[i].first.first) / (4 * w[i].first.second));
    }

    sort(w.begin(), w.end(), compare);

    for (long i = 0; i < people; i++) {
        cout << w[i].second << ' ';
    }

    return 0;
}