#ifndef LIBRARY_SYSTEM_H
#define LIBRARY_SYSTEM_H
#include <string>

// Existing library request priority queue retained from the previous project.
struct BookRequestNode {
    int studentID; std::string studentName; int bookID; std::string bookTitle; int priority;
    BookRequestNode* next;
};
class PriorityQueue {
private: BookRequestNode* front; BookRequestNode* rear; int count;
public:
    PriorityQueue(); void Add(BookRequestNode* request); BookRequestNode* Remove();
    bool IsEmpty() const; bool IsNotEmpty() const; void PrintQueue() const; ~PriorityQueue();
};

// Lab 6: Circular list. tail is the pivot; tail->next is the first book.
struct BookNode { int bookID; std::string title; BookNode* next; };
class CircularLinkedList {
private:
    BookNode* tail; int count;
    BookNode* GetNodeAt(int index) const;
    int NormalizeIndex(int index) const;
    void Clear();
    void SwapData(BookNode* first, BookNode* second);
public:
    CircularLinkedList();
    CircularLinkedList(const CircularLinkedList& other);
    CircularLinkedList& operator=(const CircularLinkedList& other);
    ~CircularLinkedList();
    void Insert(BookNode* book);                 // insert at first node (next to pivot)
    BookNode* Remove();                         // remove first node (next to pivot)
    void InsertAt(BookNode* book, int index);
    BookNode* RemoveAt(int index);
    bool Swap(int index1, int index2);
    void Sort(); void Reverse(); void Print() const;
    bool IsEmpty() const; bool IsNotEmpty() const; int Size() const;
    bool MoveNext();                            // advance rotating display cursor
    void PrintCurrent() const;
private:
    BookNode* current;
};
BookNode* CreateBook(int id, const std::string& title);
#endif
