#include "Employee.h"
#include "Leave.h"
#include <iostream>

// Constructor
Employee::Employee(int id, const std::string& n) : employeeId(id), name(n) {}

// Generate leave report
void Employee::generateLeaveReport() {
    std::cout << "Leave Report for Employee: " << name << "\n";
    for (const auto& leave : leaveHistory) {
        std::cout << "Leave Type: " << leave->getLeaveType() 
                  << ", Status: " << leave->getStatus()
                  << ", Duration: " << leave->getDuration() << " days\n";
    }
}

// Generate attendance report
void Employee::generateAttendanceReport() {
    std::cout << "Attendance Report for Employee: " << name << "\n";
    for (const auto& record : attendanceRecords) {
        std::cout << "Date: " << record.getDate() << ", Hours Worked: " << record.getHoursWorked() << "\n";
    }
}

//requestLeave method to request leave
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

    // Create a new leave request object using LeaveFactory and store it as a shared pointer
    std::shared_ptr<Leave> newLeave = LeaveFactory::createLeave(leaveType, employeeId, startDate, endDate, reason);

    // Add the leave request to the employee's leave history
    if (newLeave) {
        leaveHistory.push_back(newLeave);
        // Notify the employee that the leave has been requested
        std::cout << "Leave requested: " << leaveType << " leave from " << startDate << " to " << endDate << " for reason: " << reason << "\n";
    } else {
        std::cout << "Invalid leave type requested.\n";
    }
}

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


// Add attendance record
void Employee::addAttendanceRecord(const AttendanceRecord& record) {
    attendanceRecords.push_back(record);
    totalHoursWorked += record.getTotalHoursWorked();
}

// Method to check if the employee has sufficient leave balance
bool Employee::hasSufficientLeave(const std::string& leaveType, int days) {
    if (leaveType == "Casual" && casualLeaveBalance >= days) {
        return true;
    } else if (leaveType == "Earned" && earnedLeaveBalance >= days) {
        return true;
    }
    return false;
}

// Method to update leave balance after leave approval
void Employee::updateLeaveBalance(const std::string& leaveType, int days) {
    if (leaveType == "Casual") {
        casualLeaveBalance -= days;
    } else if (leaveType == "Earned") {
        earnedLeaveBalance -= days;
    }
}

// Virtual method to notify employee when leave status changes (To be implemented in Supervisor/Director)
void Employee::notifyLeaveApproval(const std::string& status) {
    std::cout << "Employee " << name << " has been notified of leave status: " << status << "\n";
}

// Check leave requests (To be implemented in Supervisor/Director)
void Employee::checkLeaveRequests(std::vector<std::shared_ptr<Leave>>& leaveRequests) {
    std::cout << "Employee checking leave requests...\n";
    // Logic for the Employee to check leave requests
}

