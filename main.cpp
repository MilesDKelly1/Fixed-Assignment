#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>    // NEW: Required for std::vector
#include <algorithm> // For std::swap

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

using namespace std;

// --- Enums & Exceptions (Unchanged) ---
enum BeltRank { White, Yellow, Green, Blue, Purple, Brown, Black };
string getRankName(BeltRank r) {
    string names[] = { "White", "Yellow", "Green", "Blue", "Purple", "Brown", "Black" };
    return (r >= 0 && r <= 6) ? names[r] : "White";
}

class DojoException : public std::runtime_error {
public:
    DojoException(const std::string& msg) : std::runtime_error(msg) {}
};

// --- FinancialRecord (Unchanged) ---
class FinancialRecord {
private:
    double baseRate;
    double gearCost;
    static constexpr double taxRate = 0.06;
public:
    FinancialRecord(double base = 0.0, double gear = 0.0) : baseRate(base), gearCost(gear) {}
    double calculateTotal() const { return (baseRate + gearCost) * (1.0 + taxRate); }
};

// --- Participant Base (Unchanged) ---
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

// --- Derived Classes (Unchanged) ---
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

// --- TEMPLATE CLASS (UPGRADED FOR WEEK 09) ---
template <typename T>
class DynamicArray {
private:
    // Requirement: Replace raw array with std::vector
    std::vector<T> items;

public:
    DynamicArray() {}

    // Requirement: Cleanup manual pointers inside the vector
    ~DynamicArray() {
        for (size_t i = 0; i < items.size(); i++) {
            delete items.at(i);
        }
        items.clear();
    }

    // Requirement: Use .push_back()
    void operator+=(T item) {
        items.push_back(item);
    }

    // Requirement: Use .at() and .erase()
    void operator-=(int index) {
        if (index < 0 || index >= static_cast<int>(items.size()))
            throw DojoException("Invalid Removal Index.");

        delete items.at(index);
        items.erase(items.begin() + index);
    }

    T& operator[](int index) {
        if (index < 0 || index >= static_cast<int>(items.size()))
            throw DojoException("Invalid Index Access.");
        return items.at(index);
    }

    int getSize() const { return static_cast<int>(items.size()); }

    // Requirement: Sequential (Linear) Search (Manual implementation)
    int sequentialSearch(string target) const {
        for (int i = 0; i < items.size(); i++) {
            if (items.at(i)->getName() == target) return i;
        }
        return -1;
    }

    // Requirement: Sorting Algorithm (Bubble Sort - Manual implementation)
    void bubbleSort() {
        if (items.empty()) return;
        for (size_t i = 0; i < items.size() - 1; i++) {
            for (size_t j = 0; j < items.size() - i - 1; j++) {
                if (items.at(j)->getName() > items.at(j + 1)->getName()) {
                    std::swap(items.at(j), items.at(j + 1));
                }
            }
        }
    }

    // Requirement: Binary Search (Manual implementation using low/mid/high)
    int binarySearch(string target) {
        // Requirement: Must be sorted first
        bubbleSort();

        int low = 0;
        int high = static_cast<int>(items.size()) - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (items.at(mid)->getName() == target) return mid;

            if (items.at(mid)->getName() < target)
                low = mid + 1;
            else
                high = mid - 1;
        }
        return -1;
    }
};

// --- Updated Doctests ---
#ifdef _DEBUG
TEST_CASE("Assignment 9: Search and Sort Verification") {
    DynamicArray<Participant*> da;
    da += new SeniorStudent("Zelda", 5, Blue, "Contact1", true);
    da += new JuniorStudent("Alice", 1, White, "Guardian1", false);

    SUBCASE("Linear Search finds Alice at index 1") {
        CHECK(da.sequentialSearch("Alice") == 1);
    }

    SUBCASE("Binary Search sorts and finds Zelda") {
        // Binary search will call bubbleSort first
        int result = da.binarySearch("Zelda");
        CHECK(result == 1); // After sorting: Alice[0], Zelda[1]
        CHECK(da[0]->getName() == "Alice");
    }

    SUBCASE("Search returns -1 for missing element") {
        CHECK(da.sequentialSearch("Missing") == -1);
        CHECK(da.binarySearch("Missing") == -1);
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

    DynamicArray<Participant*> manager;
    int choice;

    do {
        cout << "\n--- Dojo Management (Week 09) ---" << endl;
        cout << "1. Add Junior\n2. Add Senior\n3. View All\n4. Remove Student\n"
            << "5. Linear Search\n6. Sort (Bubble)\n7. Binary Search\n8. Exit\nSelection: ";
        cin >> choice;

        if (choice == 1 || choice == 2) {
            string name, extra; int m, r; char g;
            cout << "Name: "; cin.ignore(); getline(cin, name);
            cout << "Months: "; cin >> m;
            cout << "Rank (0-6): "; cin >> r;
            cout << "Gear (y/n): "; cin >> g;
            if (choice == 1) {
                cout << "Guardian: "; cin.ignore(); getline(cin, extra);
                manager += new JuniorStudent(name, m, (BeltRank)r, extra, (g == 'y'));
            }
            else {
                cout << "Emergency: "; cin.ignore(); getline(cin, extra);
                manager += new SeniorStudent(name, m, (BeltRank)r, extra, (g == 'y'));
            }
        }
        else if (choice == 3) {
            for (int i = 0; i < manager.getSize(); i++) cout << "[" << i << "] " << *manager[i] << endl;
        }
        else if (choice == 4) {
            int idx; cout << "Enter index to remove: "; cin >> idx;
            try { manager -= idx; cout << "Student removed.\n"; }
            catch (const DojoException& e) { cout << e.what() << endl; }
        }
        else if (choice == 5) {
            string sName; cout << "Enter name to search: "; cin.ignore(); getline(cin, sName);
            int idx = manager.sequentialSearch(sName);
            if (idx != -1) cout << "Found at index " << idx << endl;
            else cout << "Not found.\n";
        }
        else if (choice == 6) {
            manager.bubbleSort();
            cout << "List sorted alphabetically by name.\n";
        }
        else if (choice == 7) {
            string sName; cout << "Enter name for binary search: "; cin.ignore(); getline(cin, sName);
            int idx = manager.binarySearch(sName);
            if (idx != -1) cout << "Found at index " << idx << " (List was auto-sorted)\n";
            else cout << "Not found.\n";
        }

    } while (choice != 8);

    return 0;
}
