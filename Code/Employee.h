#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <vector>
#include <memory>  // For shared_ptr
#include "Leave.h"
#include "AttendanceRecord.h"
#include "LeaveFactory.h"

// Base Employee Class
class Employee {
protected:
    int employeeId;
    std::string name;
    float totalHoursWorked = 0;
    int casualLeaveBalance = 15;
    int earnedLeaveBalance = 21;
    std::vector<std::shared_ptr<Leave>> leaveHistory; // Store employee leave records using shared_ptr
    std::vector<AttendanceRecord> attendanceRecords; // Store employee attendance records

public:
    Employee(int id, const std::string& n) : employeeId(id), name(n) {}

    // Getters and Setters
    int getEmployeeId() const { return employeeId; }
    const std::string& getName() const { return name; }
    float getTotalHoursWorked() const { return totalHoursWorked; }
    int getCasualLeaveBalance() const { return casualLeaveBalance; }
    int getEarnedLeaveBalance() const { return earnedLeaveBalance; }

    void setTotalHoursWorked(float hours) { totalHoursWorked = hours; }
    void setCasualLeaveBalance(int balance) { casualLeaveBalance = balance; }
    void setEarnedLeaveBalance(int balance) { earnedLeaveBalance = balance; }

    // Methods to apply for leave and display leave details
    virtual void applyLeave(std::shared_ptr<Leave> leave) = 0;
    virtual void displayLeaveDetails() = 0;

    // Method to check leave balance
    bool hasSufficientLeave(const std::string& leaveType, int days);

    // Method to update leave balance (used after approval)
    void updateLeaveBalance(const std::string& leaveType, int days);

    // Virtual method to notify employee (Observer Pattern)
    virtual void notifyLeaveApproval(const std::string& status) = 0;

    // Virtual method to check leave requests (Supervisor/Director responsibility)
    virtual void checkLeaveRequests(std::vector<std::shared_ptr<Leave>>& leaveRequests) = 0;

    // Method to check leave status
    void checkLeaveStatus(int leaveId);

    // Method to generate leave report
    void generateLeaveReport() {
        std::cout << "Leave Report for Employee: " << name << "\n";
        for (const auto& leave : leaveHistory) {
            std::cout << "Leave Type: " << leave->getLeaveType() 
                      << ", Status: " << leave->getStatus()
                      << ", Duration: " << leave->getDuration() << " days\n";
        }
}

    // Method to generate attendance report
    void generateAttendanceReport();

    void requestLeave(const std::string& leaveType, const std::string& startDate, const std::string& endDate, const std::string& reason);

    // Method to add attendance record
    void addAttendanceRecord(const AttendanceRecord& record);
};

#endif // EMPLOYEE_H
