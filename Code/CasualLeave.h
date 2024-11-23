#ifndef CASUALLEAVE_H
#define CASUALLEAVE_H

#include "Leave.h"

using namespace std;    

class CasualLeave : public Leave {
public:
    CasualLeave(int empId, const string& start, const string& end, const string& reason)
        : Leave(empId, "Casual", start, end, reason) {}

    void applyLeave() override {
        cout << "Applying for Casual Leave\n";
        // Logic for applying casual leave
    }

    void displayLeaveDetails() override {
        cout << "Casual Leave Details: " << "Employee ID: " << getEmployeeId() 
                  << ", Start: " << getStartDate() << ", End: " << getEndDate() 
                  << ", Reason: " << getReason() << "\n";
    }
};
