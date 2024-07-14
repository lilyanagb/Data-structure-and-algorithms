//1
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void decToBinary(long n,vector<string>& num)
{
    int binaryNum[32];

    int i = 0;
    while (n > 0) {
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }

    string s="";
    for (int j = i - 1; j >= 0; j--)
        s+= to_string(binaryNum[j]);

    num.push_back(s);
}

void print(string str, size_t index,vector<string>& s) {
    if (index == str.size())
    {
        str.erase(0, str.find_first_not_of('0'));
        s.push_back(str);
        return;
    }

    if (str[index] == '1')
    {
        str[index] = '0';
        print(str, index + 1,s);

        str[index] = '1';
        print(str, index + 1,s);
    }
    else
        print(str, index + 1,s);
}

int main() {
    long sizeOfArray;
    cin >> sizeOfArray;
    long input;

    vector<string> numbers;
    while (sizeOfArray--) {
        cin >> input;
        decToBinary(input, numbers);
    }

    vector<string> s;
    size_t i = 0;

    while (i != numbers.size()) {
        print(numbers[i], 0, s);
        i++;
    }
   
   sort(s.begin(), s.end());
   s.erase(unique(s.begin(), s.end()), s.end());
   
   cout << s.size();
    return 0;
}

//2
#include <iostream>
#include <bitset>
#include <iterator>
#include <set>
#include <vector>
using namespace std;

int main() {
    vector<int> result;
    
    int count;
    cin >> count;

    set<int> n;
    n.insert(0);
    
    int input;
    int min = 0;

    while (count--) {
        cin >> input;
        n.insert(input);
        int n_max = *n.rbegin();
        int n_size=n.size();
        
        if ((n_size != 2) && (n_max == input)) {
            auto before = --n.lower_bound(input);
            int beforeSum=(*(before) ^ input);
            if (min > beforeSum) {
                min = beforeSum;
            }

            result.push_back(min);
            continue;
        }
        
        if (n_size > 2) {
            auto after = n.upper_bound(input);
            auto before = --n.upper_bound(input);
            --before;
            
            int beforeSum=(*(before) ^ input);
            int afterSum=(*(after) ^ input);
            
            if (afterSum < beforeSum) {
                if(min> afterSum)
                min = afterSum;
            }
            else {
                if (min > beforeSum)
                min = beforeSum;
            }
        }
        else {
            min = 0 ^ input;
        }
        result.push_back(min);
    }

    int len=result.size();
    for (int i = 0; i < len; i++) {
        cout << result[i] << endl;
    }
    return 0;
}

//3
#include<cstdio>
#include<vector>
#include<map>

using namespace std;

int n,k,arr[500009],ans[500009];
map<int, vector<int>> nums;

void init(){
    scanf("%d %d",&n,&k);

    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
}

void solve(){
    fill(ans,ans+n,-1);

    for(int i=n-1;i>=0;i--){
        auto it = nums.upper_bound(arr[i]);
        vector<int>toDel;

        while(it != nums.end() && (*it).first - arr[i] <= k){
            for(int ind : (*it).second){
                ans[ind] = i;
            }
            
            toDel.push_back((*it).first);
            it++;
        }

        for(auto del:toDel)nums.erase(del);

        nums[arr[i]].push_back(i);
    }
}

void print(){
    printf("%d",ans[0]);
    for(int i=1;i<n;i++){
        printf(" %d",ans[i]);
    }
    printf("\n");
}

int main(){
    init();
    solve();
    print();
}