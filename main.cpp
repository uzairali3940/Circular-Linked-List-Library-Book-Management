#include "LibrarySystem.h"
#include <iostream>
#include <limits>
using namespace std;
int readInt(const string& prompt) {
    int x; while (true) { cout << prompt; if (cin >> x) return x;
        cout << "Invalid input. Enter a number.\n"; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
}
void addBookAtIndex(CircularLinkedList& books) {
    int id = readInt("Enter Book ID: "); string title; cout << "Enter Book Title: "; getline(cin >> ws, title);
    int index = readInt("Enter index (0 to " + to_string(books.Size()) + "): ");
    books.InsertAt(CreateBook(id, title), index); cout << "Book added to circular collection.\n";
}
int main() {
    PriorityQueue requests; CircularLinkedList books; int choice;
    // Familiar sample data retained, but all collection operations are now menu-driven.
    books.InsertAt(CreateBook(103, "Operating Systems"), 0);
    books.InsertAt(CreateBook(101, "Data Structures"), 1);
    books.InsertAt(CreateBook(105, "Computer Networks"), 2);
    books.InsertAt(CreateBook(102, "Database Systems"), 3);
    books.InsertAt(CreateBook(104, "Software Engineering"), 4);
    do {
        cout << "\n========================================\n  CIRCULAR LIBRARY BOOK DISPLAY SYSTEM\n========================================\n"
             << "1. Display All Books\n2. Insert Book at Head\n3. Remove Book from Head\n4. Insert Book at Index\n"
             << "5. Remove Book at Index\n6. Swap Books\n7. Sort Books by ID\n8. Reverse Book Collection\n"
             << "9. Move to Next Book\n10. Check Collection Status\n11. Exit\n"
             << "\n--- Existing Library Request Features ---\n12. Add Book Request\n13. Process Highest Priority Request\n"
             << "14. Display All Requests\n15. Check Request Queue Status\n";
        choice = readInt("Enter your choice: ");
        switch (choice) {
        case 1: books.Print(); break;
        case 2: { int id = readInt("Enter Book ID: "); string title; cout << "Enter Book Title: "; getline(cin >> ws, title); books.Insert(CreateBook(id, title)); cout << "Book inserted at head.\n"; break; }
        case 3: { BookNode* b = books.Remove(); if (!b) cout << "Collection is empty.\n"; else { cout << "Removed: " << b->bookID << " - " << b->title << '\n'; delete b; } break; }
        case 4: addBookAtIndex(books); break;
        case 5: { int i = readInt("Enter index to remove: "); BookNode* b = books.RemoveAt(i); if (!b) cout << "Collection is empty.\n"; else { cout << "Removed: " << b->bookID << " - " << b->title << '\n'; delete b; } break; }
        case 6: { int a = readInt("Enter first index: "), b = readInt("Enter second index: "); cout << (books.Swap(a,b) ? "Books swapped.\n" : "Collection is empty.\n"); break; }
        case 7: books.Sort(); cout << "Books sorted by ID.\n"; break;
        case 8: books.Reverse(); cout << "Book collection reversed.\n"; break;
        case 9: if (books.MoveNext()) books.PrintCurrent(); else cout << "Collection is empty.\n"; break;
        case 10: cout << (books.IsEmpty() ? "Collection is empty.\n" : "Collection is not empty.\n"); cout << "Total books: " << books.Size() << "\nCircular link intact: " << (books.IsEmpty() ? "N/A" : "YES") << '\n'; break;
        case 11: cout << "Exiting Library System.\n"; break;
        case 12: { BookRequestNode* r = new BookRequestNode{}; r->studentID = readInt("Enter Student ID: "); cout << "Enter Student Name: "; getline(cin >> ws, r->studentName); r->bookID = readInt("Enter Book ID: "); cout << "Enter Book Title: "; getline(cin >> ws, r->bookTitle); r->priority = readInt("Enter Priority (1=Urgent, 2=Assignment, 3=Normal): "); if (r->priority < 1 || r->priority > 3) { cout << "Invalid priority; request not added.\n"; delete r; } else { requests.Add(r); cout << "Book request added successfully.\n"; } break; }
        case 13: { BookRequestNode* r = requests.Remove(); if (!r) cout << "Request queue is empty.\n"; else { cout << "Processed request: " << r->studentName << " - " << r->bookTitle << " (priority " << r->priority << ")\n"; delete r; } break; }
        case 14: requests.PrintQueue(); break;
        case 15: cout << (requests.IsEmpty() ? "Request queue is empty.\n" : "Request queue is not empty.\n"); break;
        default: cout << "Invalid choice. Select 1-15.\n";
        }
    } while (choice != 11);
    return 0;
}
