#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>

#define _DEBUG
#ifdef _DEBUG
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#endif

using namespace std;

// --- Enums & Exceptions (Unchanged) ---
enum BeltRank { White, Yellow, Green, Blue, Purple, Brown, Black };
string getRankName(BeltRank r) {
    string names[] = { "White", "Yellow", "Green", "Blue", "Purple", "Brown", "Black" };
    return (r >= 0 && r <= 6) ? names[r] : "White";
}

class DojoException : public std::runtime_error {
public:
    //create memory leak
    DojoException(const std::string& msg) : std::runtime_error(msg) {}
};

// --- Composition & Base Classes (Unchanged) ---
class FinancialRecord {
private:
    double baseRate;
    double gearCost;
    static constexpr double taxRate = 0.06;
public:
    FinancialRecord(double base = 0.0, double gear = 0.0) : baseRate(base), gearCost(gear) {}
    double calculateTotal() const { return (baseRate + gearCost) * (1.0 + taxRate); }
};

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

// --- TEMPLATE CLASS (Modified for Recursion) ---
template <typename T>
class DynamicArray {
private:
    T* items;
    int size;
    int capacity;

    void resize() {
        capacity *= 2;
        T* newItems = new T[capacity];
        for (int i = 0; i < size; i++) newItems[i] = items[i];
        delete[] items;
        this->items = newItems;
    }

public:
    DynamicArray(int cap = 2) : size(0), capacity(cap) {
        items = new T[capacity];
    }
    ~DynamicArray() {
        for (int i = 0; i < size; i++) delete items[i];
        delete[] items;
    }

    // NEW RECURSIVE MEMBER FUNCTION
    int findIndexRecursive(string target, int index = 0) const {
        // BASE CASE 1: Not found
        if (index >= size) return -1;
        // BASE CASE 2: Found
        if (items[index]->getName() == target) return index;
        // RECURSIVE CASE: Next index
        return findIndexRecursive(target, index + 1);
    }

    T& operator[](int index) {
        if (index < 0 || index >= size) throw DojoException("Invalid Index.");
        return items[index];
    }

    void operator+=(T item) {
        if (size >= capacity) resize();
        items[size++] = item;
    }

    void operator-=(int index) {
        if (index < 0 || index >= size) throw DojoException("Invalid Removal.");
        delete items[index];
        for (int i = index; i < size - 1; i++) items[i] = items[i + 1];
        size--;
    }

    int getSize() const { return size; }
};

#ifdef _DEBUG
TEST_CASE("Assignment 8: Recursion Verification") {
    DynamicArray<Participant*> da;
    da += new JuniorStudent("Tim", 1, White, "Jane", false);
    da += new SeniorStudent("Sarah", 5, Blue, "Bob", true);

    SUBCASE("Recursive Search Finds Target") {
        CHECK(da.findIndexRecursive("Sarah") == 1);
        CHECK(da.findIndexRecursive("Tim") == 0);
    }
    SUBCASE("Recursive Search Returns -1 for Missing") {
        CHECK(da.findIndexRecursive("Missing") == -1);
    }
}
#endif

int main(int argc, char** argv) {
    //memory leak going to the output window
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
        cout << "\n1. Add Junior\n2. Add Senior\n3. View\n4. Remove\n5. Search (Recursive)\n6. Exit\nSelection: ";
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
            int idx; cout << "Index: "; cin >> idx;
            try { manager -= idx; cout << "Removed.\n"; }
            catch (const DojoException& e) { cout << e.what() << endl; }
        }
        else if (choice == 5) {
            string sName; cout << "Enter name: "; cin.ignore(); getline(cin, sName);
            int idx = manager.findIndexRecursive(sName);
            if (idx != -1) cout << "Found at index " << idx << ": " << *manager[idx] << endl;
            else cout << "Not found." << endl;
        }
    } while (choice != 6);

    return 0;
}
