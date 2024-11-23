#ifndef OFFICIALLEAVE_H
#define OFFICIALLEAVE_H

#include "Leave.h"

using namespace std;

class OfficialLeave : public Leave {
public:
    OfficialLeave(int empId, const string& start, const string& end, const string& reason)
        : Leave(empId, "Official", start, end, reason) {}

    void applyLeave() override {
        cout << "Applying for Official Leave\n";
        // Logic for applying official leave
    }

    void displayLeaveDetails() override {
        cout << "Official Leave Details: " << "Employee ID: " << getEmployeeId() 
             << ", Start: " << getStartDate() << ", End: " << getEndDate() 
             << ", Reason: " << getReason() << "\n";
    }
};
