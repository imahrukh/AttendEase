#ifndef LEAVE_H
#define LEAVE_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Leave {
protected:
    static int leaveIdCounter;  // Static counter for unique leave ID generation
    int leaveId;
    int employeeId;
    string leaveType;
    string status;  // Pending, Approved, Rejected
    string startDate;
    string endDate;
    string reason;
    int duration;  // in days

public:
    Leave(int empId, const string& type, const string& start, const string& end, const string& reason)
        : employeeId(empId), leaveType(type), startDate(start), endDate(end), reason(reason), status("Pending") {
        leaveId = ++leaveIdCounter;  // Generate a unique leave ID
        duration = stoi(endDate.substr(8, 2)) - stoi(startDate.substr(8, 2)) + 1;  // Simple duration calculation (can be enhanced)
    }

    // Getters and Setters
    int getLeaveId() const { return leaveId; }
    int getEmployeeId() const { return employeeId; }
    const string& getLeaveType() const { return leaveType; }
    const string& getStatus() const { return status; }
    const string& getStartDate() const { return startDate; }
    const string& getEndDate() const { return endDate; }
    const string& getReason() const { return reason; }
    int getDuration() const { return duration; }

    void setStatus(const string& newStatus) { status = newStatus; }

    // Virtual methods for each leave type's behavior
    virtual void applyLeave() = 0;
    virtual void displayLeaveDetails() = 0;

    // Method to display the leave request summary
    void displayLeaveSummary() {
        cout << "Leave ID: " << leaveId << ", Type: " << leaveType << ", Status: " << status
             << ", Duration: " << duration << " days, Reason: " << reason << "\n";
    }
};

int Leave::leaveIdCounter = 0;  // Initialize static variable
