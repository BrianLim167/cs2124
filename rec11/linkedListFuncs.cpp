/*
  functions for use with CS2124 rec11
  -jbs
*/

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// Node to be used a part of linked list
struct Node {
  Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
  int data;
  Node* next;
};

// listAddHead: adds a data item to the beginning of a [possibly empty] list
void listAddHead(Node*& headPtr, int entry) {
  headPtr = new Node(entry, headPtr);
}

// listClear: frees up all the nodes in a list
void listClear(Node*& headPtr) {
  while (headPtr) {
    Node* next = headPtr->next;
    delete headPtr;
    headPtr = next;
  }
}

// listBuild: constructs a list from a vector of data items. Note that
// you can use a curly-braced sequence.
// This may be useful for setting up test cases. Feel free to use it
// or not as you like. 
// Example of using would be:
//    Node* myList = listBuild({1, 4, 9, 16}); // builds a list of: 1 4 9 16
Node* listBuild(const vector<int>& vals) {
  Node* result = nullptr;
  for (size_t index = vals.size(); index > 0; --index) {
    listAddHead(result, vals[index-1]);
  }
  return result;
}

ostream& operator<<(ostream& os, const Node* list) {
  if (!list) {
    return os;
  }
  os << list->data << " " << list->next;
  return os;
}

void splice(Node*& adding, Node*& location) {
  Node* last = adding;
  while (last->next) {
    last = last->next;
  }
  last->next = location->next;
  location->next = adding;
}

bool match(Node* find, Node* part) {
  while (find && part) {
    if (find->data != part->data) return false;
    find = find->next;
    part = part->next;
  }
  return !find;
}

Node* isSubList(Node*& find, Node*& search) {
  Node* part = search;
  while (part) {
    if (match(find,part)) return part;
    part = part->next;
  }
  return nullptr;
}

Node* sharedListBruteForce(Node*& h1, Node*& h2) {
  Node* l1 = h1;
  Node* l2 = h2;
  while (l1) {
    Node* part = l2;
    while (part) {
      if (l1 == part) return l1;
      part = part->next;
    }
    l1 = l1->next;
  }
  return nullptr;
}

Node* sharedListUsingSet(Node*& h1, Node*& h2) {
  Node* l1 = h1;
  Node* l2 = h2;
  unordered_set<Node*> s1;
  while (l1) {
    s1.insert(l1);
    l1 = l1->next;
  }
  while(l2) {
    if (s1.find(l2) != s1.end()) return l2;
    l2 = l2->next;
  }
  return nullptr;
}

void test2(Node* target, Node* match) {
  cout << "Attempted match: " << match << endl;
  Node* result = isSubList(match, target);
  if (result) {
    cout << result << endl;
  } else {
    cout << "Failed to match" << endl;
  }
  cout << endl;
}

void test3(Node* h1, Node* h2, Node* shared) {
  Node* l1 = h1;
  Node* l2 = h2;
  
  cout << "L1 (without shared): " << h1 << endl;
  cout << "L2 (without shared): " << h2 << endl;

  Node* last = l1;
  while (last->next) {
    last = last->next;
  }
  splice(shared, last);
  last = l2;
  while(last->next) {
    last = last->next;
  }
  splice(shared, last);

  cout << "L1 (with shared): " << h1 << endl;
  cout << "L2 (with shared): " << h2 << endl;
  cout << "shared: " << shared << endl;
  Node* t1 = sharedListBruteForce(h1, h2);
  Node* t2 = sharedListUsingSet(h1, h2);
  cout << "Brute Force: ";
  if (t1) {
    cout << t1 << endl;
  } else {
    cout << "Failed to match" << endl;
  }
  cout << "Using Set: ";
  if (t2) {
    cout << t2 << endl;
  } else {
    cout << "Failed to match" << endl;
  }
  cout << endl;
}
    
  

int main() {
  cout << "Part One:" << endl;
  cout << endl;
  Node* l1 = listBuild({5,7,9,1});
  Node* l2 = listBuild({6,3,2});
  cout << "" << endl;
  cout << "L1: " << l1 << endl;
  cout << "L2: " << l2 << endl;
  cout << "Target: " << l1->next << endl;
  cout << "Splicing L2 at target in L1" << endl;
  splice(l2, l1->next);
  cout << "L1: " << l1 << endl;
  cout << "L2: " << l2 << endl;
  cout << "=====================" << endl;
  cout << endl;
  
  cout << "Part two: " << endl;
  cout << endl;
  Node* target = listBuild({1,2,3,2,3,2,4,5,6});
  cout << "Target: " << target << endl;
  cout << endl;
  test2(target, listBuild({1}));
  test2(target, listBuild({3,9}));
  test2(target, listBuild({2,3}));
  test2(target, listBuild({2,4,5,6}));
  test2(target, listBuild({2,3,2,4}));
  test2(target, listBuild({5,6,7}));
  cout << "=====================" << endl;
  cout << endl;

  cout << "Part three: " << endl;
  cout << endl;
  test3(listBuild({2,3}), listBuild({2,3,3}), listBuild({4,5}));
  cout << "=====================" << endl;
  cout << endl;
}
