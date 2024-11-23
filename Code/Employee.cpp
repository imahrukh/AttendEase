#include "Employee.h"
#include "Leave.h"
#include "AttendanceRecord.h"

void Employee::checkLeaveStatus(int leaveId) {
    // Loop through leave history and check for the leave ID
    for (auto& leave : leaveHistory) {
        if (leave->getLeaveId() == leaveId) {
            std::cout << "Leave Status for Employee " << getName() << " (Leave ID: " << leaveId << "): "
                      << leave->getStatus() << "\n";
            return;
        }
    }
    std::cout << "Leave not found for Employee " << getName() << " (Leave ID: " << leaveId << ").\n";
}

void Employee::generateLeaveReport() {
    std::cout << "Leave Report for Employee: " << getName() << "\n";
    // Loop through the leave history and print all leave details
    for (const auto& leave : leaveHistory) {
        std::cout << "Leave Type: " << leave->getLeaveType() << ", Status: " << leave->getStatus()
                  << ", Duration: " << leave->getDuration() << " days\n";
    }
}

void Employee::generateAttendanceReport() {
    std::cout << "Attendance Report for Employee: " << getName() << "\n";
    // Loop through the attendance records and print all attendance details
    for (const auto& record : attendanceRecords) {
        std::cout << "Date: " << record.getDate() << ", Hours Worked: " << record.getHoursWorked() << "\n";
    }
}

void Employee::requestLeave(const std::string& leaveType, const std::string& startDate, const std::string& endDate, const std::string& reason) {
    // Check if the employee has sufficient leave balance
    int leaveDays = 0;
    if (leaveType == "Casual") {
        leaveDays = 2;  // Casual leave is for 2 days (can be adjusted)
    } else if (leaveType == "Earned" || leaveType == "Unpaid") {
        leaveDays = 5;  // Assume Earned/Unpaid leave is for 5 days (can be adjusted)
    }

    // Check leave balance before applying
    if (!hasSufficientLeave(leaveType, leaveDays)) {
        std::cout << "Not enough leave balance to request " << leaveType << " leave.\n";
        return;
    }

    // Create a new leave request object
    Leave* newLeave = new Leave(employeeId, leaveType, startDate, endDate, reason);

    // Add the leave request to the employee's leave history
    leaveHistory.push_back(newLeave);

    // Notify the employee that the leave has been requested
    std::cout << "Leave requested: " << leaveType << " leave from " << startDate << " to " << endDate << " for reason: " << reason << "\n";
}