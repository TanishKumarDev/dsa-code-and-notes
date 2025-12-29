/*
    Topic: STL - Container Adaptors
    
    Container Adaptors covered:
    1. stack
    2. queue
    3. priority_queue

    Key points:
    - Container adaptors restrict access
    - They do NOT allow iteration
    - Built on top of other containers
*/

#include <iostream>
#include <stack>
#include <queue>
#include <vector>

using namespace std;

int main()
{

    /*
    ===============================
    1. std::stack (LIFO)
    ===============================
    */

    // stack follows Last In First Out
    // Default underlying container: deque
    stack<int> st;

    // push elements
    st.push(10);
    st.push(20);
    st.push(30);

    // top() gives last inserted element
    cout << "stack top: " << st.top() << endl; // 30

    // remove top element
    st.pop();

    cout << "stack top after pop: " << st.top() << endl; // 20

    // size of stack
    cout << "stack size: " << st.size() << endl;

    /*
    Note:
    - No iteration allowed
    - No random access
    - Only top, push, pop
    */

    /*
    ===============================
    2. std::queue (FIFO)
    ===============================
    */

    // queue follows First In First Out
    // Default underlying container: deque
    queue<int> q;

    // push elements (goes to back)
    q.push(10);
    q.push(20);
    q.push(30);

    // front() gives first inserted element
    cout << "\nqueue front: " << q.front() << endl; // 10

    // back() gives last inserted element
    cout << "queue back: " << q.back() << endl; // 30

    // remove element from front
    q.pop();

    cout << "queue front after pop: " << q.front() << endl; // 20

    // size of queue
    cout << "queue size: " << q.size() << endl;

    /*
    Note:
    - No traversal allowed
    - Only front, back, push, pop
    */

    /*
    ===============================
    3. std::priority_queue (Heap)
    ===============================
    */

    // priority_queue by default is MAX HEAP
    // Default underlying container: vector
    priority_queue<int> pq;

    pq.push(10);
    pq.push(50);
    pq.push(20);
    pq.push(40);

    // top() always gives highest priority element
    cout << "\npriority_queue top (max heap): " << pq.top() << endl; // 50

    // remove highest priority element
    pq.pop();

    cout << "priority_queue top after pop: " << pq.top() << endl; // 40

    /*
    ===============================
    Min Heap Example
    ===============================
    */

    // To create a MIN HEAP
    priority_queue<int, vector<int>, greater<int>> minHeap;

    minHeap.push(10);
    minHeap.push(50);
    minHeap.push(20);

    cout << "\npriority_queue top (min heap): " << minHeap.top() << endl; // 10

    /*
    Important:
    - push: O(log n)
    - pop: O(log n)
    - top: O(1)
    */

    return 0;
}
