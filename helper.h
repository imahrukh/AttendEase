#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>

// Class to manage individual attendance records for employees
class Attendance {
private:
    std::string date;  // The date of attendance in the format YYYY-MM-DD
    float hoursWorked; // Hours worked on the specific date

public:
    Attendance(const std::string& date, float hours);
    const std::string& getDate() const; // Retrieve the date
    float getHoursWorked() const;       // Retrieve the hours worked on that date
    void displayAttendance() const;    // Print the attendance details
};

// Base class for managing different types of leaves
class Leave {
protected:
    static int leaveIdCounter; // Counter to generate unique leave IDs
    int leaveId;               // Unique ID for this leave
    int employeeId;            // ID of the employee requesting leave
    std::string leaveType;     // Type of leave (Casual, Earned, Official, Unpaid)
    std::string status;        // Current status of leave (Pending, Approved, Rejected)
    std::string startDate;     // Start date of the leave
    std::string endDate;       // End date of the leave
    std::string reason;        // Reason for requesting leave
    int duration;              // Duration of the leave in days
    std::string supervisorApproval;  // Approval from supervisor (Yes/No)
    std::string directorApproval;    // Approval from director (Yes/No or N/A)

public:
    Leave(int empId, const std::string& type, const std::string& start, const std::string& end, const std::string& reason);

    // Getters
    int getLeaveId() const;
    int getEmployeeId() const;
    const std::string& getLeaveType() const;
    const std::string& getStatus() const;
    const std::string& getStartDate() const;
    const std::string& getEndDate() const;
    const std::string& getReason() const;
    int getDuration() const;
    const std::string& getSupervisorApproval() const;
    const std::string& getDirectorApproval() const;

    // Setters
    void setStatus(const std::string& newStatus);      // Update the leave status
    void setSupervisorApproval(const std::string& approval); // Set supervisor's approval
    void setDirectorApproval(const std::string& approval);   // Set director's approval

    // Virtual methods for customization in derived leave types
    virtual void applyLeave() = 0;              // Logic for applying a leave
    virtual void displayLeaveDetails() = 0;    // Display full leave details

    // Display summary of the leave
    void displayLeaveSummary();
};

// Class to manage attendance records of employees
class AttendanceRecord {
private:
    int employeeId; // ID of the employee whose attendance is being tracked
    std::vector<Attendance> records; // List of attendance entries

public:
    // Constructor
    AttendanceRecord(int empId);

    // Add an attendance record for the employee
    void addAttendance(const std::string& date, float hoursWorked);

    // Calculate the total hours worked by the employee
    float getTotalHoursWorked() const;

    // Calculate the attendance percentage based on expected hours
    float calculateAttendancePercentage(float totalExpectedHours) const;

    // Display all attendance records for the employee
    void displayAllAttendance() const;

    // Get the attendance records
    const std::vector<Attendance>& getRecords() const;

    // Get the employee ID associated with this record
    int getEmployeeId() const;
};

// Base class for employees
class Employee {
protected:
    int employeeId;                  // Unique ID of the employee
    std::string name;                // Name of the employee
    std::string role;                // Role of the employee (Employee, Supervisor, Director)
    float totalHoursWorked = 0;      // Total hours worked
    int casualLeaveBalance = 15;     // Balance of casual leaves
    int earnedLeaveBalance = 21;     // Balance of earned leaves
    std::vector<std::shared_ptr<Leave>> leaveHistory; // Leave history of the employee
    std::vector<AttendanceRecord> attendanceRecords;  // Attendance history of the employee

public:
    Employee(int id, const std::string& n, const std::string& r = "Employee");

    // Getters and Setters for employee attributes
    int getEmployeeId() const;
    const std::string& getName() const;
    const std::string& getRole() const;
    float getTotalHoursWorked() const;
    int getCasualLeaveBalance() const;
    int getEarnedLeaveBalance() const;

    void setTotalHoursWorked(float hours);
    void setCasualLeaveBalance(int balance);
    void setEarnedLeaveBalance(int balance);

    // Methods for leave and attendance management
    virtual void applyLeave(std::shared_ptr<Leave> leave);
    virtual void displayLeaveDetails();
    bool hasSufficientLeave(const std::string& leaveType, int days);
    void updateLeaveBalance(const std::string& leaveType, int days);

    // Methods for reporting and notifications
    virtual void notifyLeaveApproval(const std::string& status);
    virtual void checkLeaveRequests(std::vector<std::shared_ptr<Leave>>& leaveRequests);
    void checkLeaveStatus(int leaveId);
    void generateLeaveReport();
    void generateAttendanceReport();
    void requestLeave(const std::string& leaveType, const std::string& startDate, const std::string& endDate, const std::string& reason);

    // Add an attendance record
    void addAttendanceRecord(const AttendanceRecord& record);

    virtual ~Employee() = default; // Virtual destructor for proper cleanup of derived classes
};

// Utility class for file operations
class FileHandler {
public:
    // Methods to read data from files
    static void readEmployeeData(std::vector<std::shared_ptr<Employee>>& employees);
    static void readAttendanceData(std::vector<AttendanceRecord>& attendanceRecords);
    static void readLeaveData(std::vector<std::shared_ptr<Leave>>& leaveRecords);

    // Methods to write data to files
    static void writeEmployeeData(const Employee& employee);
    static void writeAttendanceData(const AttendanceRecord& record);
    static void writeLeaveData(const Leave& leave);

    // Methods to update existing data in files
    static void updateLeaveStatus(int leaveId, const std::string& newStatus);
    static void updateAttendanceData(int employeeId, const AttendanceRecord& record);
    static void updateEmployeeData(const Employee& employee);

private:
    static const std::string employeeFile;   // Path to employee data file
    static const std::string attendanceFile; // Path to attendance data file
    static const std::string leaveFile;      // Path to leave data file
};

// File paths for the FileHandler class
const std::string FileHandler::employeeFile = "Employees.txt";
const std::string FileHandler::attendanceFile = "Attendance.txt";
const std::string FileHandler::leaveFile = "Leaves.txt";

#endif // HELPER_H
