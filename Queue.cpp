/*
Although a queue is "best" implemented with a list, it can be implemented with a vector if you take into account the starting position of the queue.  
For example, if five elements are pushed onto the queue, the start of the queue is at position zero and the end is at position 4.  
If we, then, pop two elements, the start would be at position 2 and the end at position 4.  
The two "popped" elements are not really removed from the vector, and that avoids the O(N) time problem for the pop function.
Implement a class which uses a vector to store the queue. 
*/

#include <iostream>
#include <vector>

using namespace std;

template <class T>
class Queue {
    vector<T> v;
    int front = 0;
public:
    void enqueue(T newItem) { v.push_back(newItem); }
    void dequeue() { front++; }
    T top() const { return v[front]; }
    T back() const { return v.back(); }
    bool isEmpty() const { return v.size() == 0; }
    int size() const { return v.size() - front; }
    void clear() { v.clear(); front = 0; }

};

int main()
{
    Queue <int> test_queue;

    for (int i = 0; i < 10; i++) {
        test_queue.enqueue(i);
    }
    cout << "Size after adding 10 digits: " <<test_queue.size() << endl;
    cout << "First element in the queue: " << test_queue.top() << endl;
    cout << "Last element in the queue: " << test_queue.back() << endl << endl;

    
    for (int i = 0; i < 3; i++) {
        test_queue.dequeue();
    }
    cout << "Size after removing first 3 digits: " << test_queue.size() << endl;
    cout << "First element in the queue: " << test_queue.top() << endl;
    cout << "Last element in the queue: " << test_queue.back() << endl << endl;

    cout << "Is queue empty?" << endl;
    cout << test_queue.isEmpty() << endl << endl;

    cout << "Lets clear queue!" << endl;
    test_queue.clear();

    cout << "Is queue empty?" << endl;
    cout << test_queue.isEmpty() << endl;

    return 0;
}