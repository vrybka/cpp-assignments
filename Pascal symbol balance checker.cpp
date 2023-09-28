/*
Symbol balance checker function for the Pascal programming language.  Pascal allows for the following pairs: {}, (), [], begin end .  
All programs will begin with the word "begin" and end  with the word "end".  
Function should receive an ifstream object which is already open and will return true, all of the symbols match, or false, they do not.  
*/

#include <iostream>
#include <fstream>
#include <list>

using namespace std;

void openInputFile(ifstream& inFile);
bool symbolMatch(ifstream& inFile);

template <class T>
class Stack {
    list<T> data;
public:
    void push(T newItem) { data.push_front(newItem); }
    void pop() { return data.pop_front(); }
    T top() const { return *data.begin(); }
    bool isEmpty() const { return data.size() == 0; }
    int size() const { return data.size(); }
    void clear() { data.clear(); }
};

int main()
{
    ifstream inFile;
    openInputFile(inFile);

    if (symbolMatch(inFile)) {
        cout << "Symbols are matched." << endl;
    }
    else {
        cout << "Symbols are NOT matched." << endl;
    }

    return 0;
}

void openInputFile(ifstream& inFile) {
    string name;
    cout << "Enter file name: ";
    cin >> name;
    inFile.open(name);
    while (!inFile) {
        cout << "Input file opening failed!" << endl;
        cout << "Enter the file name: ";
        cin >> name;
        inFile.open(name);
    }
}

bool symbolMatch(ifstream& inFile) {
    Stack<char> stack;
    char c;
    while (inFile >> c) {
        if ((c == '{') || (c == '(') || (c == '[')) {
            stack.push(c);
        }
        else if ((c == '}') || (c == ')') || (c == ']')) {
            if ((stack.top() == '{') && (c != '}')) {
                return false;
            }
            else if ((stack.top() == '(') && (c != ')')) {
                return false;
            }
            else if ((stack.top() == '[') && (c != ']')) {
                return false;
            }
            else {
                stack.pop();
            }
        }
    }
    if (stack.isEmpty()) {
        return true;
    }
    else {
        return false;
    }
}