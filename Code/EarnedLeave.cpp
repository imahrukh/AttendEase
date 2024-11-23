#include "EarnedLeave.h"

EarnedLeave::EarnedLeave(int empId, const std::string& start, const std::string& end, const std::string& reason)
        : Leave(empId, "Earned", start, end, reason) {}

void EarnedLeave:: applyLeave() {
        std::cout << "Applying for Earned Leave\n";
        // Logic for applying earned leave
}

void EarnedLeave::displayLeaveDetails() {
        std::cout << "Earned Leave Details: " << "Employee ID: " << getEmployeeId() 
             << ", Start: " << getStartDate() << ", End: " << getEndDate() 
             << ", Reason: " << getReason() << "\n";
    }
