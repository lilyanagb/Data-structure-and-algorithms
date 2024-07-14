//1
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

void arrang(string options, char givenOpt) {
    int lengthOfArr = options.length();
    vector<int> distance;
    int j = 0,counter = 0;
    
    while (options[j] != givenOpt) {
        distance.push_back(lengthOfArr);
        j++;
    }
    
    for (int i = j; i < lengthOfArr; i++) {
        if (options[i] != givenOpt) {
            counter++;
            distance.push_back(counter);
        }else{
            counter = 0;
            distance.push_back(counter);
        }
    }
 

    for (int i = distance.size() - 1; i >0 ; i--)
    {
        if (distance[i] + 1 < distance[i-1] ) {
            distance[i -1] = distance[i] +1;
        }
    }

  
       for (size_t i = 0; i < distance.size(); i++) {
        cout << distance[i] << ' ';
    }
}
int main() {
    string options;
    char givenOpt;
    cin >> options >> givenOpt;
    arrang(options, givenOpt);
    return 0;
}


//2
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int missingNumber(int countOfNumbers, vector<int> arr) {
    sort(arr.begin(), arr.end());
    size_t i = 0;

    vector<int> subvector;
    int curr = 0;
    for (int j = 0; j < arr.size(); j++) {
        if (arr[j] > 0) {
            curr = j;
            break;
        }
  }
    subvector = { arr.begin() + curr, arr.end() };
     
      

  if (subvector.size() == 0 || subvector[0] != 1) {
        return 1;
    }

    for (; i < subvector.size() - 1; i++) {
        if (subvector[i] > 0 && subvector[i] + 1 < subvector[i + 1]) {
            return subvector[i] + 1;
        }
    }
    return subvector[i] + 1;

}

int main() {
    int count;
    cin >> count;
    vector<int> arr;
    int input;
    for (int i = 0; i < count; i++) {
        cin >> input;
        arr.push_back(input);
    }
    cout << missingNumber(count, arr);
    return 0;
}

//3
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;


int repeatedSymbol(string word, int countOfRep, char w) {
    int lengthOfWord = word.size();

    size_t n = std::count(word.begin(), word.end(), w);

    int fullWord = countOfRep / lengthOfWord;
    int partWord = countOfRep % lengthOfWord;

    string lastPartOfString = word.substr(0, partWord);
    size_t foundInPart = std::count(lastPartOfString.begin(), lastPartOfString.end(), w);


    return fullWord * n + foundInPart;
}
int main() {
    string word;
    char w;
    int number;
    cin >> word >> number >> w;
    cout << repeatedSymbol(word, number, w);
}