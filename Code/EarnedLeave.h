#ifndef EARNEDLEAVE_H
#define EARNEDLEAVE_H

#include "Leave.h"

using namespace std;
class EarnedLeave : public Leave {
public:
    EarnedLeave(int empId, const string& start, const string& end, const string& reason)
        : Leave(empId, "Earned", start, end, reason) {}

    void applyLeave() override {
        cout << "Applying for Earned Leave\n";
        // Logic for applying earned leave
    }

    void displayLeaveDetails() override {
        cout << "Earned Leave Details: " << "Employee ID: " << getEmployeeId() 
             << ", Start: " << getStartDate() << ", End: " << getEndDate() 
             << ", Reason: " << getReason() << "\n";
    }
};
#endif // EARNEDLEAVE_H
