#ifndef LEAVE_H
#define LEAVE_H

#include <string>
#include <iostream>
#include <vector>

class Leave {
protected:
    static int leaveIdCounter;  // Static counter for unique leave ID generation
    int leaveId;
    int employeeId;
    std::string leaveType;
    std::string status;  // Pending, Approved, Rejected
    std::string startDate;
    std::string endDate;
    std::string reason;
    int duration;  // in days

public:
    Leave(int empId, const std::string& type, const std::string& start, const std::string& end, const std::string& reason)
        : employeeId(empId), leaveType(type), startDate(start), endDate(end), reason(reason), status("Pending") {
        leaveId = ++leaveIdCounter;  // Generate a unique leave ID
        duration = std::stoi(endDate.substr(8, 2)) - std::stoi(startDate.substr(8, 2)) + 1;  // Simple duration calculation (can be enhanced)
    }

    // Getters and Setters
    int getLeaveId() const { return leaveId; }
    int getEmployeeId() const { return employeeId; }
    const std::string& getLeaveType() const { return leaveType; }
    const std::string& getStatus() const { return status; }
    const std::string& getStartDate() const { return startDate; }
    const std::string& getEndDate() const { return endDate; }
    const std::string& getReason() const { return reason; }
    int getDuration() const { return duration; }

    void setStatus(const std::string& newStatus) { status = newStatus; }

    // Virtual methods for each leave type's behavior
    virtual void applyLeave() = 0;
    virtual void displayLeaveDetails() = 0;

    // Method to display the leave request summary
    void displayLeaveSummary() {
        std::cout << "Leave ID: " << leaveId << ", Type: " << leaveType << ", Status: " << status
             << ", Duration: " << duration << " days, Reason: " << reason << "\n";
    }
};

int Leave::leaveIdCounter = 0;  // Initialize static variable

#endif // LEAVE_H
