#include "LibrarySystem.h"
#include <iostream>
#include <utility>

PriorityQueue::PriorityQueue() : front(nullptr), rear(nullptr), count(0) {}
void PriorityQueue::Add(BookRequestNode* request) {
    if (!request) return; request->next = nullptr;
    if (!front) front = rear = request;
    else if (request->priority < front->priority) { request->next = front; front = request; }
    else { BookRequestNode* p = front; while (p->next && p->next->priority <= request->priority) p = p->next;
        request->next = p->next; p->next = request; if (!request->next) rear = request; }
    ++count;
}
BookRequestNode* PriorityQueue::Remove() {
    if (!front) return nullptr; BookRequestNode* item = front; front = front->next;
    if (!front) rear = nullptr; item->next = nullptr; --count; return item;
}
bool PriorityQueue::IsEmpty() const { return front == nullptr; }
bool PriorityQueue::IsNotEmpty() const { return front != nullptr; }
void PriorityQueue::PrintQueue() const {
    if (IsEmpty()) { std::cout << "No pending book requests.\n"; return; }
    for (BookRequestNode* p = front; p; p = p->next)
        std::cout << "\nStudent ID: " << p->studentID << "\nStudent Name: " << p->studentName
                  << "\nBook ID: " << p->bookID << "\nBook Title: " << p->bookTitle
                  << "\nPriority: " << p->priority << "\n-----------------------------\n";
}
PriorityQueue::~PriorityQueue() { while (front) { BookRequestNode* t = front; front = front->next; delete t; } rear = nullptr; }

CircularLinkedList::CircularLinkedList() : tail(nullptr), count(0), current(nullptr) {}
BookNode* CircularLinkedList::GetNodeAt(int index) const {
    if (IsEmpty() || index < 0 || index >= count) return nullptr;
    BookNode* p = tail->next; while (index--) p = p->next; return p;
}
int CircularLinkedList::NormalizeIndex(int index) const {
    if (count == 0) return 0;
    return ((index % count) + count) % count;
}
void CircularLinkedList::SwapData(BookNode* a, BookNode* b) {
    std::swap(a->bookID, b->bookID); std::swap(a->title, b->title);
}
void CircularLinkedList::Clear() {
    while (IsNotEmpty()) delete Remove();
    current = nullptr;
}
CircularLinkedList::CircularLinkedList(const CircularLinkedList& other) : tail(nullptr), count(0), current(nullptr) {
    BookNode* p = other.IsEmpty() ? nullptr : other.tail->next;
    for (int i = 0; i < other.count; ++i) { InsertAt(CreateBook(p->bookID, p->title), count); p = p->next; }
}
CircularLinkedList& CircularLinkedList::operator=(const CircularLinkedList& other) {
    if (this == &other) return *this; Clear();
    BookNode* p = other.IsEmpty() ? nullptr : other.tail->next;
    for (int i = 0; i < other.count; ++i) { InsertAt(CreateBook(p->bookID, p->title), count); p = p->next; }
    return *this;
}
CircularLinkedList::~CircularLinkedList() { Clear(); }
bool CircularLinkedList::IsEmpty() const { return count == 0; }
bool CircularLinkedList::IsNotEmpty() const { return count > 0; }
int CircularLinkedList::Size() const { return count; }
void CircularLinkedList::Insert(BookNode* book) {
    if (!book) return;
    if (!tail) { tail = book; book->next = book; }
    else { book->next = tail->next; tail->next = book; }
    if (!current) current = book;
    ++count;
}
BookNode* CircularLinkedList::Remove() {
    if (IsEmpty()) return nullptr;
    BookNode* first = tail->next;
    if (first == tail) { tail = nullptr; current = nullptr; }
    else { tail->next = first->next; if (current == first) current = first->next; }
    first->next = nullptr; --count; return first;
}
void CircularLinkedList::InsertAt(BookNode* book, int index) {
    if (!book) return;
    if (IsEmpty()) { tail = current = book; book->next = book; count = 1; return; }
    // As specified in the lab, negative and over-range indexes wrap around.
    if (index < 0) index = NormalizeIndex(index);
    if (index > count) index %= count;
    if (index == 0) { Insert(book); return; }
    if (index == count) { book->next = tail->next; tail->next = book; tail = book; ++count; return; }
    BookNode* previous = GetNodeAt(index - 1); book->next = previous->next; previous->next = book; ++count;
}
BookNode* CircularLinkedList::RemoveAt(int index) {
    if (IsEmpty()) return nullptr;
    index = NormalizeIndex(index);
    if (index == 0) return Remove();
    BookNode* previous = GetNodeAt(index - 1); BookNode* target = previous->next;
    previous->next = target->next;
    if (target == tail) tail = previous;
    if (target == current) current = target->next;
    target->next = nullptr; --count; return target;
}
bool CircularLinkedList::Swap(int a, int b) {
    if (IsEmpty()) return false; a = NormalizeIndex(a); b = NormalizeIndex(b);
    if (a == b) return true; SwapData(GetNodeAt(a), GetNodeAt(b)); return true;
}
void CircularLinkedList::Sort() {
    if (count < 2) return;
    BookNode* first = tail->next;
    for (int i = 0; i < count - 1; ++i) { BookNode* a = first; for (int k = 0; k < i; ++k) a = a->next;
        BookNode* b = a->next; for (int j = i + 1; j < count; ++j) { if (a->bookID > b->bookID) SwapData(a, b); b = b->next; } }
}
void CircularLinkedList::Reverse() {
    if (count < 2) return;
    BookNode* oldTail = tail; BookNode* oldFirst = tail->next;
    BookNode* previous = oldTail; BookNode* p = oldFirst;
    while (p != oldTail) { BookNode* next = p->next; p->next = previous; previous = p; p = next; }
    oldTail->next = previous; tail = oldFirst;
}
void CircularLinkedList::Print() const {
    if (IsEmpty()) { std::cout << "No books in the collection.\n"; return; }
    BookNode* p = tail->next; std::cout << "\nIndex\tBook ID\tTitle\n-----------------------------------\n";
    for (int i = 0; i < count; ++i) { std::cout << i << '\t' << p->bookID << '\t' << p->title << '\n'; p = p->next; }
    std::cout << "Total books: " << count << "\nLast book links back to first: YES\n";
}
bool CircularLinkedList::MoveNext() {
    if (IsEmpty()) return false;
    if (!current) current = tail->next; else current = current->next;
    return true;
}
void CircularLinkedList::PrintCurrent() const {
    if (IsEmpty() || !current) { std::cout << "No current book to display.\n"; return; }
    std::cout << "Now displaying: [" << current->bookID << "] " << current->title << '\n';
}
BookNode* CreateBook(int id, const std::string& title) { return new BookNode{id, title, nullptr}; }
