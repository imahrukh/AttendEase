#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <vector>
#include "Leave.h"
#include "AttendanceRecord.h"

// Base Employee Class
class Employee {
protected:
    int employeeId;
    std::string name;
    float totalHoursWorked = 0;
    int casualLeaveBalance = 15;
    int earnedLeaveBalance = 21;
    std::vector<Leave*> leaveHistory; // Store employee leave records
    std::vector<AttendanceRecord> attendanceRecords; // Store employee attendance records

public:
    Employee(int id, const std::string& n) : employeeId(id), name(n) {}

    // Getters and Setters
    int getEmployeeId() const { return employeeId; }
    const std::string& getName() const { return name; }
    float getTotalHoursWorked() const { return totalHoursWorked; }

    // Methods to apply for leave and display leave details
    virtual void applyLeave(Leave* leave) = 0;
    virtual void displayLeaveDetails() = 0;

    // Method to check leave balance
    bool hasSufficientLeave(const std::string& leaveType, int days) {
        if (leaveType == "Casual" && days <= casualLeaveBalance) return true;
        if (leaveType == "Earned" && days <= earnedLeaveBalance) return true;
        return false;
    }

    // Method to update leave balance (used after approval)
    void updateLeaveBalance(const std::string& leaveType, int days) {
        if (leaveType == "Casual") casualLeaveBalance -= days;
        if (leaveType == "Earned") earnedLeaveBalance -= days;
    }

    // Virtual method to notify employee (Observer Pattern)
    virtual void notifyLeaveApproval(const std::string& status) = 0;

    // Virtual method to check leave requests (Supervisor/Director responsibility)
    virtual void checkLeaveRequests(std::vector<Leave*>& leaveRequests) = 0;

    // Method to check leave status
    void checkLeaveStatus(int leaveId);

    // Method to generate leave report (show leave history)
    void generateLeaveReport();

    // Method to generate attendance report
    void generateAttendanceReport();

    void requestLeave(const std::string& leaveType, const std::string& startDate, const std::string& endDate, const std::string& reason);
};
#endif // EMPLOYEE_H