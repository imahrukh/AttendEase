#include "OfficialLeave.h"

OfficialLeave::OfficialLeave(int empId, const std::string& start, const std::string& end, const std::string& reason)
    : Leave(empId, "Official", start, end, reason) {}

void OfficialLeave::applyLeave() {
    std::cout << "Applying for Official Leave\n";
    // Logic for applying official leave
    }

void OfficialLeave::displayLeaveDetails() {
    std::cout << "Official Leave Details: " << "Employee ID: " << getEmployeeId() 
         << ", Start: " << getStartDate() << ", End: " << getEndDate() 
         << ", Reason: " << getReason() << "\n";
    }