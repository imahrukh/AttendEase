#include "CasualLeave.h"

 CasualLeave::CasualLeave (int empId, const string& start, const string& end, const string& reason)
        : Leave(empId, "Casual", start, end, reason) {}

void CasualLeave:: applyLeave() {
        cout << "Applying for Casual Leave\n";
        // Logic for applying casual leave
    }

void CasualLeave::displayLeaveDetails() {
        cout << "Casual Leave Details: " << "Employee ID: " << getEmployeeId() 
                  << ", Start: " << getStartDate() << ", End: " << getEndDate() 
                  << ", Reason: " << getReason() << "\n";
    }