#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <iostream>
#include<vector>
#include<memory>
#include<fstream>
#include <sstream>

class Attendance {
private:
    std::string date;  // Format: YYYY-MM-DD
    float hoursWorked;

public:
    Attendance(const std::string& date, float hours);
    const std::string& getDate() const;
    float getHoursWorked() const;
    void displayAttendance() const;
};


class Leave {
protected:
    static int leaveIdCounter;
    int leaveId;
    int employeeId;
    std::string leaveType;
    std::string status;  // Pending, Approved, Rejected
    std::string startDate;
    std::string endDate;
    std::string reason;
    int duration;
    std::string supervisorApproval;  // Yes/No
    std::string directorApproval;    // Yes/No or N/A

public:
    Leave(int empId, const std::string& type, const std::string& start, const std::string& end, const std::string& reason);

    // Getters
    int getLeaveId() const;
    int getEmployeeId() const ;
    const std::string& getLeaveType()const ;
    const std::string& getStatus() const ;
    const std::string& getStartDate() const ;
    const std::string& getEndDate() const ;
    const std::string& getReason() const ;
    int getDuration() const ;
    const std::string& getSupervisorApproval() const ;
    const std::string& getDirectorApproval() const ;

    // Setters
    void setStatus(const std::string& newStatus) ;
    void setSupervisorApproval(const std::string& approval) ;
    void setDirectorApproval(const std::string& approval) ;

    // Virtual methods
    virtual void applyLeave() = 0;
    virtual void displayLeaveDetails() = 0;

    void displayLeaveSummary() ;
};
int Leave::leaveIdCounter = 0;

class AttendanceRecord {
private:
    int employeeId;
    std::vector<Attendance> records;  // Store attendance entries

public:
    // Constructor
    AttendanceRecord(int empId);

    // Add an attendance record
    void addAttendance(const std::string& date, float hoursWorked);

    // Get total hours worked
    float getTotalHoursWorked() const;
    // Calculate attendance percentage
    float calculateAttendancePercentage(float totalExpectedHours) const;

    // Display all attendance records
    void displayAllAttendance() const;

    // Getter for the attendance records
    const std::vector<Attendance>& getRecords() const;

    // Getter for employee ID
    int getEmployeeId() const;
};


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
    Employee(int id, const std::string& n);

    // Getters and Setters
    int getEmployeeId() const ;
    const std::string& getName() const ;
    float getTotalHoursWorked() const;
    int getCasualLeaveBalance() const ;
    int getEarnedLeaveBalance() const ;

    void setTotalHoursWorked(float hours) ;
    void setCasualLeaveBalance(int balance) ;
    void setEarnedLeaveBalance(int balance) ;

    // Methods to apply for leave and display leave details
    virtual void applyLeave(std::shared_ptr<Leave> leave) ;
    virtual void displayLeaveDetails();

    // Method to check leave balance
    bool hasSufficientLeave(const std::string& leaveType, int days) ;
    
    // Method to update leave balance (used after approval)
    void updateLeaveBalance(const std::string& leaveType, int days);

    // Virtual method to notify employee (Observer Pattern)
    virtual void notifyLeaveApproval(const std::string& status);

    // Virtual method to check leave requests (Supervisor/Director responsibility)
    virtual void checkLeaveRequests(std::vector<std::shared_ptr<Leave>>& leaveRequests);

    // Method to check leave status
    void checkLeaveStatus(int leaveId);

    // Method to generate leave report
    void generateLeaveReport() ;
    // Method to generate attendance report
    void generateAttendanceReport();

    void requestLeave(const std::string& leaveType, const std::string& startDate, const std::string& endDate, const std::string& reason);

    // Method to add attendance record
    void addAttendanceRecord(const AttendanceRecord& record);
};

class FileHandler {
public:
    static void readEmployeeData(std::vector<std::shared_ptr<Employee>>& employees) ;
    static void writeEmployeeData(const Employee& employee);
    static void readAttendanceData(std::vector<AttendanceRecord>& attendanceRecords, int employeeId);
    static void writeAttendanceData(const AttendanceRecord& record);
    static void readLeaveData(std::vector<std::shared_ptr<Leave>>& leaveRecords) ;
    static void writeLeaveData(const Leave& leave) ;
    static void updateLeaveStatus(int leaveId, const std::string& newStatus) ;
    static void updateAttendanceData(int employeeId, const AttendanceRecord& record);

private:
    static const std::string employeeFile;
    static const std::string attendanceFile;
    static const std::string leaveFile;
};
const std::string FileHandler::employeeFile = "Employees.txt";
const std::string FileHandler::attendanceFile = "Attendance.txt";
const std::string FileHandler::leaveFile = "Leaves.txt";
#endif // HELPER_H