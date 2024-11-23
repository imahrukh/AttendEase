#include "UnpaidLeave.h"

UnpaidLeave::UnpaidLeave(int empId, const std::string& start, const std::string& end, const std::string& reason)
    : Leave(empId, "Unpaid", start, end, reason) {}

void UnpaidLeave::applyLeave() {
    std::cout << "Applying for Unpaid Leave\n";
    // Logic for applying unpaid leave
}

void UnpaidLeave::displayLeaveDetails() {
    std::cout << "Unpaid Leave Details: " << "Employee ID: " << getEmployeeId() 
              << ", Start: " << getStartDate() << ", End: " << getEndDate() 
              << ", Reason: " << getReason() << "\n";
}
