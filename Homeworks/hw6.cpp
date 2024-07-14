//1
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 1000001;
vector<int> tree[N];

void dfs(int v,int& count) {
    for (auto x : tree[v]) {
        dfs(x,++count);
    }
}

int main()
{
    int n;
    cin >> n;
    int a, b;
  
    n--;
    vector<int> arr;

    while (n--) {
        cin >> a >> b;
        tree[a].push_back(b);
        arr.push_back(a);
        arr.push_back(b);
    }
    sort(arr.begin(), arr.end());
    arr.erase(unique(arr.begin(), arr.end()), arr.end());

    int size = arr.size();
    int i = 0,count=0;

    while (i != size) {
        dfs(arr[i], count);
        cout << count << ' ';
        count = 0;
        i++;
    }
    return 0;
}

//2

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

int main() {
    long nodes;
    cin >> nodes;
    vector<pair<pair<long, long>, bool>> tree;

    for (long i = 0; i < 1000001; i++) {
        tree.push_back({ {0,0},false });
    }

    tree[0] = { {0,0},true };
    long left, right;


    for (long i = 0; i < nodes; i++) {
        cin >> left >> right;
        if (left != -1)
            tree[left] = { {tree[i].first.first - 1,left},true };
        if (right != -1)
            tree[right] = { {tree[i].first.first + 1,right},true };
    }
    sort(tree.begin(), tree.end());
    int skip = INT_MAX;
    long i = 0;
    for (; i < 1000000; i++) {
        if (tree[i].second == true) {

            if (skip == tree[i].first.first) continue;

            if (tree[i].first.first == tree[i + 1].first.first) {
                skip = tree[i].first.first;
            }
            cout << tree[i].first.second << ' ';
        }
    }
    if (tree[i - 1].first.first != tree[i].first.first)
        cout << tree[i].first.second;
    return 0;
}


//3
#include <iostream>
using namespace std;

class Node {
private:
    int data;
    Node* left;
    Node* right;
public:
    int getData() {
        return data;
    }
    Node() {
        data = 0;
        left = nullptr;
        right = nullptr;
    }

    Node(int value)
    {
        data = value;
        left = right = nullptr;
    }

    int height(Node* node) {
        if (node == nullptr) return 0;
        else {
            int left = height(node->left);
            int right = height(node->right);

            if (left > right)
                return (left + 1);
            else
                return (right + 1);
        }
    }

    void printCurr(Node* root, int level) {
        if (root == nullptr) return;
        if (level == 1) cout << root->data << " ";
        else if (level > 1) {
            printCurr(root->left, level - 1);
            printCurr(root->right, level - 1);
        }
    }

    void print(Node* root) {
        int heigth = height(root);

        for (int i = 1; i <= heigth; i++) printCurr(root, i);
    }

    Node* insert(Node* root, int value) {
        if (!root)
        {
            return new Node(value);
        }

        if (value > root->data)
        {
            root->right = insert(root->right, value);
        }
        else
        {
            root->left = insert(root->left, value);
        }
        return root;
    }

    Node* kthLargest(Node* root, int& count, int key) {
        if (root == nullptr) return nullptr;

        Node* left = kthLargest(root->right, count, key);

        if (left) return left;

        if (++count == key) return root;

        return kthLargest(root->left, count, key);
    }


    Node* findKthLargest(Node* root, int key) {
        int count = 0;
        return kthLargest(root, count, key);
    }

    Node* minValueNode(Node* node)
    {
        Node* current = node;

        while (current->left != nullptr)
            current = current->left;

        return current;
    }

    Node* deleteNode(Node* curr, int key) {
        if (curr == nullptr) return curr;

        if (key < curr->data)
            curr->left = deleteNode(curr->left, key);
        else if (key > curr->data)
            curr->right = deleteNode(curr->right, key);
        else {
            if (curr->left == nullptr) {
                Node* temp = curr->right;
                delete curr;
                return temp;
            }
            else if (curr->right == nullptr) {
                Node* temp = curr->left;
                delete curr;
                return temp;
            }
            Node* temp = minValueNode(curr->right);
            curr->data = temp->data;
            curr->right = deleteNode(curr->right, temp->data);
        }
        return curr;
    }
};

int main() {
    int count,key;
    cin>>count>>key;
    int input;
    Node b;
   
    Node* root = nullptr;
    cin >> input;
    root = b.insert(root, input);
    for(int i=1;i<count;i++){
        cin>>input;
        
        b.insert(root,input);
    }
    
    Node* node = b.findKthLargest(root, key);
    
    root=b.deleteNode(root,node->getData());
    b.print(root);
    
    return 0;
}