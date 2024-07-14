//1
SinglyLinkedListNode* insertNodeAtPosition(SinglyLinkedListNode* llist, int data, int position) {

    SinglyLinkedListNode* node=new SinglyLinkedListNode(data);
    
    if(position == 0){
        node->next=llist;
        llist=node;
        return llist;
}
    SinglyLinkedListNode* cur=llist;
    
    for(int i=0;i<position-1;i++){
        if(cur != nullptr){
            cur=cur->next;
        }else{
            return llist;
        }
    
    }
    node->next=cur->next;
    cur->next=node;
    return llist;

}

//2
int length(SinglyLinkedListNode* node){
    int size=0;
    while(node != nullptr){
        size++;
        node=node->next;
    }
    return size;
}

int findMergeNode(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2) {
    int sizeOfHead1=length(head1);
    int sizeOfHead2=length(head2);
    int diff=0;
    
    if(sizeOfHead2>sizeOfHead1){
        diff=sizeOfHead2-sizeOfHead1;
        
        for(int i=0;i<diff;i++){
            head2=head2->next;
        }
    }else{
        diff=sizeOfHead1-sizeOfHead2;
        
        for(int i=0;i<diff;i++){
            head1=head1->next;
        }
    }
    while(head1 != nullptr && head2 != nullptr){
        if(head1==head2) return head1->data;
        
        head1=head1->next;
        head2=head2->next;
    }
    return 0;
}

//3
SinglyLinkedListNode* deleteNode(SinglyLinkedListNode* llist, int position) {
    SinglyLinkedListNode* node=llist;

    if(position == 0){
      llist=llist->next;
        
      return llist;
    }
    for(int i=0;i<position-1;i++){
        if(node==nullptr){
            return llist;
        }else{
            node=node->next;
        }
    }
    if(node->next != nullptr){
        node->next=node->next->next;
        
        return llist;
    }
    return llist;
}

//4
#include <iostream>
#include <string>

using namespace std;

struct Node {
    Node* prev;
    Node* next;
    long long data;
};


class DoublyLinkedList {
private:
    Node* head;
    Node* middle;
    Node* tail;
    long long size;
public:

    DoublyLinkedList() {
        head = nullptr;
        middle = nullptr;
        tail = nullptr;
        size = 0;

    }

    void updateMiddle(bool added) {
        if (size == 0) middle = nullptr;
        else if (size == 1) middle = head;
        else {
            long long midEl = size % 2;
            if (added) {
                if (midEl == 0 && size > 2) middle = middle->next;
            }
            else {
                if (midEl == 1 && size > 2) middle = middle->prev;
            }
        }
            
    }

    void add(long long input) {
        Node* newNode = new Node();
        newNode->data = input;
        newNode->next = nullptr;
        newNode->prev = nullptr;
        if (tail != nullptr) {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;

        }
        else {
            head = newNode;
            tail = newNode;
        
        }
        size++;
        updateMiddle(true);
    }

    void remove() {
        if (tail != nullptr) {
            if (tail->prev != nullptr) {
                tail->prev->next = nullptr;
            }
            Node* prev = tail->prev;
            tail->prev = nullptr;
            delete tail;
            tail = prev;
        }
        else {
            return;
        }
        size--;
        updateMiddle(false);
    }

    void reverse() {
        if (head->next == nullptr) return;
        
            Node* p1 = middle->next; 
            Node* p2 = tail; 
            if(size % 2 != 0) p2=tail->prev;
                middle->next->prev = nullptr;
                middle->next = nullptr;
                tail->next = head;
                head = p1;
                tail->next->prev = tail;
                tail = middle;
                middle = p2;
    }

    void print() {
        Node* tmp = head;

        if (size==0 || tmp == nullptr) {
            cout << 0;
            return;
        }
        cout << size << endl;
        while (tmp != nullptr) {
            cout << tmp->data << " ";
            tmp = tmp->next;
        }
    }
};
int main() {
    long long countOfActions;
    cin >> countOfActions;

    DoublyLinkedList llist;
    string action;
    long long number;

    for (long long i = 0; i < countOfActions; i++) {
        cin >> action;
        if (action == "gun") {
            llist.remove();
        }
        else if (action == "milen") {
            llist.reverse();
        }
        else {
            cin >> number;

            llist.add(number);
        }
    }
    llist.print();
    return 0;
}


//5
#include <iostream>
#include <algorithm>
#include <list>
using namespace std;

struct Ball
{
    size_t color = 0;
    size_t index = 0;
};

size_t eraseAndCount(list<Ball>& balls, list<Ball>::iterator itBall, bool repeated = false)
{
    bool beginAccountedFor = false;
    auto itLeft = itBall, itRight = next(itBall);

    if ((itRight == balls.end() || itLeft->color != itRight->color) && repeated)
        return 0;

    size_t count = 0;

    while (itLeft->color == itBall->color)
    {
        ++count;

        if (itLeft == balls.begin())
        {
            beginAccountedFor = true;
            break;
        }

        --itLeft;
    }

    while (itRight != balls.end() && itRight->color == itBall->color)
    {
        ++count;
        ++itRight;
    }

    if (count < 3)
        return 0;

    if (itLeft == balls.begin() && beginAccountedFor)
    {
        balls.erase(itLeft, itRight);
        return count;
    }

    balls.erase(next(itLeft), itRight);
    return count + eraseAndCount(balls, itLeft, true);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    list<Ball> balls;

    size_t n, q;
    cin >> n;

    size_t color;
    for (size_t i = 0; i < n; i++)
    {
        cin >> color;
        balls.push_back(Ball{color, i});
    }

    cin >> q;
    size_t index;

    list<Ball>::iterator* indices = new list <Ball>::iterator[n + q];
    for (auto it = balls.begin(); it != balls.end(); ++it)
        indices[it->index] = it;

    Ball tempBall;

    for (size_t i = 0; i < q; i++)
    {
        if (balls.empty())
        {
            cout << "Game Over" << '\n';
            continue;
        }

        cin >> index >> color;
        tempBall = Ball{ color, n + i };
        auto itBall = indices[tempBall.index] = balls.insert(next(indices[index]), tempBall);

        cout << eraseAndCount(balls, itBall) << '\n';
    }

    if (balls.empty())
        cout << -1;
    else for (auto ball = balls.begin(); ball != balls.end(); ++ball)
        cout << ball->color << ' ';

    delete[] indices;
    
    return 0;
}