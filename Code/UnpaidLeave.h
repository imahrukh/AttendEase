#ifndef UNPAIDLEAVE_H
#define UNPAIDLEAVE_H

#include "Leave.h"

using namespace std;

class UnpaidLeave : public Leave {
public:
    UnpaidLeave(int empId, const string& start, const string& end, const string& reason)
        : Leave(empId, "Unpaid", start, end, reason) {}

    void applyLeave() override {
        cout << "Applying for Unpaid Leave\n";
        // Logic for applying unpaid leave
    }

    void displayLeaveDetails() override {
        cout << "Unpaid Leave Details: " << "Employee ID: " << getEmployeeId() 
             << ", Start: " << getStartDate() << ", End: " << getEndDate() 
             << ", Reason: " << getReason() << "\n";
    }
};

#endif // UNPAIDLEAVE_H
