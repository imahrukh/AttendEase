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
    string name;
    float totalHoursWorked = 0;
    int casualLeaveBalance = 15;
    int earnedLeaveBalance = 21;
    vector<Leave*> leaveHistory; // Store employee leave records
    vector<AttendanceRecord> attendanceRecords; // Store employee attendance records

public:
    Employee(int id, const string& n) : employeeId(id), name(n) {}

    // Getters and Setters
    int getEmployeeId() const { return employeeId; }
    const string& getName() const { return name; }
    float getTotalHoursWorked() const { return totalHoursWorked; }

    // Methods to apply for leave and display leave details
    void applyLeave(Leave* leave)=0 ;
    virtual void displayLeaveDetails() = 0;

    // Method to check leave balance
    bool hasSufficientLeave(const string& leaveType, int days) {
        if (leaveType == "Casual" && days <= casualLeaveBalance) return true;
        if (leaveType == "Earned" && days <= earnedLeaveBalance) return true;
        return false;
    }

    // Method to update leave balance (used after approval)
    void updateLeaveBalance(const string& leaveType, int days) {
        if (leaveType == "Casual") casualLeaveBalance -= days;
        if (leaveType == "Earned") earnedLeaveBalance -= days;
    }

    // Virtual method to notify employee (Observer Pattern)
    virtual void notifyLeaveApproval(const string& status) = 0;

    // Virtual method to check leave requests (Supervisor/Director responsibility)
    virtual void checkLeaveRequests(std::vector<Leave*>& leaveRequests) = 0;

    // Method to check leave status
    void checkLeaveStatus(int leaveId);

    // Method to generate leave report (show leave history)
    void generateLeaveReport();

    // Method to generate attendance report
    void generateAttendanceReport();

    void requestLeave(const string& leaveType, const string& startDate, const string& endDate, const string& reason);
};

#endif // EMPLOYEE_H
