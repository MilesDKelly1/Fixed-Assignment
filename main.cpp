#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

using namespace std;

// --- Enums & Exceptions ---
enum BeltRank { White, Yellow, Green, Blue, Purple, Brown, Black };
string getRankName(BeltRank r) {
    string names[] = { "White", "Yellow", "Green", "Blue", "Purple", "Brown", "Black" };
    return (r >= 0 && r <= 6) ? names[r] : "White";
}

class DojoException : public std::runtime_error {
public:
    DojoException(const std::string& msg) : std::runtime_error(msg) {}
};

// --- FinancialRecord ---
class FinancialRecord {
private:
    double baseRate;
    double gearCost;
    static constexpr double taxRate = 0.06;
public:
    FinancialRecord(double base = 0.0, double gear = 0.0) : baseRate(base), gearCost(gear) {}
    double calculateTotal() const { return (baseRate + gearCost) * (1.0 + taxRate); }
};

// --- Participant Base ---
class Participant {
protected:
    int monthsEnrolled;
    string name;
    BeltRank rank;
public:
    Participant(string n = "N/A", int m = 0, BeltRank r = White) : name(n), monthsEnrolled(m), rank(r) {}
    virtual ~Participant() {}
    virtual string getStudentType() const = 0;
    string getName() const { return name; }
    friend ostream& operator<<(ostream& os, const Participant& p) {
        p.print(os);
        return os;
    }
    virtual void print(ostream& out) const {
        out << "Name: " << name << " | Type: " << getStudentType();
    }
};

// --- Derived Classes ---
class JuniorStudent : public Participant {
private:
    string guardianName;
    FinancialRecord finance;
public:
    JuniorStudent(string n, int m, BeltRank r, string g, bool gear)
        : Participant(n, m, r), guardianName(g), finance(80.0, gear ? 125.0 : 0.0) {
    }
    string getStudentType() const override { return "Junior"; }
    void print(ostream& out) const override {
        Participant::print(out);
        out << " | Guardian: " << guardianName << " | Total: $" << fixed << setprecision(2) << finance.calculateTotal();
    }
};

class SeniorStudent : public Participant {
private:
    string emergencyContact;
    FinancialRecord finance;
public:
    SeniorStudent(string n, int m, BeltRank r, string e, bool gear)
        : Participant(n, m, r), emergencyContact(e), finance(120.0, gear ? 125.0 : 0.0) {
    }
    string getStudentType() const override { return "Senior"; }
    void print(ostream& out) const override {
        Participant::print(out);
        out << " | Emergency: " << emergencyContact << " | Total: $" << fixed << setprecision(2) << finance.calculateTotal();
    }
};

// --- WEEK 10: CUSTOM LINKED LIST ADT ---
template <typename T>
class CustomLinkedList {
private:
    // REQUIREMENT: Node structure
    struct Node {
        T data;
        Node* next;
    };
    Node* head;
    int size;

public:
    // REQUIREMENT: Linked List Iterator as a class
    class ListIterator {
    private:
        Node* current;
    public:
        ListIterator(Node* ptr) : current(ptr) {} // Initialized to front
        bool isValid() const { return current != nullptr; }
        void next() { if (current) current = current->next; } // Advancing
        T& getData() { return current->data; } // Accessing data
    };

    CustomLinkedList() : head(nullptr), size(0) {}

    // Destructor: Clean up manual memory to avoid leaks
    ~CustomLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp->data; // Delete actual Student object
            delete temp;       // Delete Node container
        }
    }

    // REQUIREMENT: Ordered Insert (Maintains sorted order by Name)
    void insert(T item) {
        Node* newNode = new Node{ item, nullptr };
        if (!head || item->getName() < head->data->getName()) {
            newNode->next = head;
            head = newNode;
        }
        else {
            Node* curr = head;
            while (curr->next && curr->next->data->getName() < item->getName()) {
                curr = curr->next;
            }
            newNode->next = curr->next;
            curr->next = newNode;
        }
        size++;
    }

    // REQUIREMENT: Delete node by index
    void remove(int index) {
        if (index < 0 || index >= size) throw DojoException("Invalid Index.");
        Node* temp;
        if (index == 0) {
            temp = head;
            head = head->next;
        }
        else {
            Node* curr = head;
            for (int i = 0; i < index - 1; i++) curr = curr->next;
            temp = curr->next;
            curr->next = temp->next;
        }
        delete temp->data;
        delete temp;
        size--;
    }

    // REQUIREMENT: Search (Sequential)
    int search(string name) const {
        Node* curr = head;
        int idx = 0;
        while (curr) {
            if (curr->data->getName() == name) return idx;
            curr = curr->next;
            idx++;
        }
        return -1;
    }

    // REQUIREMENT: Print/Traverse using the Iterator
    void displayAll() {
        ListIterator it = getIterator();
        int idx = 0;
        while (it.isValid()) {
            cout << "[" << idx++ << "] " << *(it.getData()) << endl;
            it.next();
        }
    }

    ListIterator getIterator() { return ListIterator(head); }
    int getSize() const { return size; }
};

// --- Updated Doctests ---
#ifdef _DEBUG
TEST_CASE("Week 10: Linked List ADT Verification") {
    CustomLinkedList<Participant*> list;

    // 1. Test Sorted Insertion (Add in reverse/random order)
    list.insert(new SeniorStudent("Zelda", 5, Blue, "Contact Z", true));
    list.insert(new JuniorStudent("Alice", 1, White, "Guardian A", false));
    list.insert(new SeniorStudent("Charlie", 3, Green, "Contact C", true));

    SUBCASE("Ordered Insertion: Elements must be alphabetical by name") {
        // Alice (A) should be first, Charlie (C) second, Zelda (Z) third
        CHECK(list.search("Alice") == 0);
        CHECK(list.search("Charlie") == 1);
        CHECK(list.search("Zelda") == 2);
    }

    SUBCASE("ListIterator: Correctly traverses the sorted list") {
        auto it = list.getIterator();

        // First element should be Alice
        REQUIRE(it.isValid());
        CHECK(it.getData()->getName() == "Alice");

        it.next(); // Advance
        REQUIRE(it.isValid());
        CHECK(it.getData()->getName() == "Charlie");

        it.next(); // Advance
        REQUIRE(it.isValid());
        CHECK(it.getData()->getName() == "Zelda");
    }

    SUBCASE("Search and Removal") {
        CHECK(list.search("Charlie") == 1);
        list.remove(1); // Remove Charlie
        CHECK(list.search("Charlie") == -1); // Should no longer exist
        CHECK(list.search("Zelda") == 1);    // Zelda shifts up to index 1
    }
}
#endif

int main(int argc, char** argv) {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

#ifdef _DEBUG
    doctest::Context context;
    context.applyCommandLine(argc, argv);
    int res = context.run();
    if (context.shouldExit()) return res;
#endif

    CustomLinkedList<Participant*> manager;
    int choice;

    do {
        cout << "\n--- Dojo Management (Week 10 - Linked List) ---" << endl;
        cout << "1. Add Junior\n2. Add Senior\n3. View All (Iterator)\n4. Remove Student\n5. Search\n6. Exit\nSelection: ";
        cin >> choice;

        if (choice == 1 || choice == 2) {
            string name, extra; int m, r; char g;
            cout << "Name: "; cin.ignore(); getline(cin, name);
            cout << "Months: "; cin >> m;
            cout << "Rank (0-6): "; cin >> r;
            cout << "Gear (y/n): "; cin >> g;
            if (choice == 1) {
                cout << "Guardian: "; cin.ignore(); getline(cin, extra);
                manager.insert(new JuniorStudent(name, m, (BeltRank)r, extra, (g == 'y')));
            }
            else {
                cout << "Emergency: "; cin.ignore(); getline(cin, extra);
                manager.insert(new SeniorStudent(name, m, (BeltRank)r, extra, (g == 'y')));
            }
        }
        else if (choice == 3) {
            manager.displayAll();
        }
        else if (choice == 4) {
            int idx; cout << "Enter index to remove: "; cin >> idx;
            try { manager.remove(idx); cout << "Removed.\n"; }
            catch (const DojoException& e) { cout << e.what() << endl; }
        }
        else if (choice == 5) {
            string sName; cout << "Search name: "; cin.ignore(); getline(cin, sName);
            int idx = manager.search(sName);
            if (idx != -1) cout << "Found at index " << idx << endl;
            else cout << "Not found.\n";
        }
    } while (choice != 6);

    return 0;
}
