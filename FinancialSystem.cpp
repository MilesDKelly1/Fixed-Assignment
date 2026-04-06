#include "FinancialSystem.h"
#include <cstdlib>

double FinancialSystem::pricegen(int age, string gear) {
    //if age is under 16, they are a minor

    //if they said yes to needing gear, add gear to amount
    double StudentPrice;
    double youthStudentPrice;
    double adultStudentPrice;
    double unknownStudentPrice;
    double gearPrice = 125.0;

    if (age <= 16 && age > 6) //youth student age range
    {
        youthStudentPrice = 80.0;
        if (gear == "y" || gear == "yes" || gear == "Y" || gear == "Yes")
        {
            StudentPrice = youthStudentPrice + gearPrice;
        }
        else {
            StudentPrice = youthStudentPrice;
        }
    }
    else if (age > 17 && age <= 90) //adult student age range
    {
        adultStudentPrice = 120.0;
        if (gear == "y" || gear == "yes" || gear == "Y" || gear == "Yes")
        {
            StudentPrice = adultStudentPrice + gearPrice;
        }
        else {
            StudentPrice = adultStudentPrice;
        }
    }
    else {
        unknownStudentPrice = 0.0;
        gearPrice = 0.0;
        StudentPrice = gearPrice + unknownStudentPrice;
        //print age is wrong, gear price doesnt go into affect
    }
    return StudentPrice;
}

// --- FinancialRecord ---
//class FinancialRecord {
//private:
    //double baseRate;
    //double gearCost;
    //static constexpr double taxRate = 0.06;
//public:
    //FinancialRecord(double base = 0.0, double gear = 0.0) : baseRate(base), gearCost(gear) {}
    //double calculateTotal() const { return (baseRate + gearCost) * (1.0 + taxRate); }
//};
