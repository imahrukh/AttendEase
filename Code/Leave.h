#ifndef LEAVE_H
#define LEAVE_H

#include <string>
#include <iostream>
#include <vector>

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
    Leave(int empId, const std::string& type, const std::string& start, const std::string& end, const std::string& reason)
        : employeeId(empId), leaveType(type), startDate(start), endDate(end), reason(reason), status("Pending"),
          supervisorApproval("N/A"), directorApproval("N/A") {
        leaveId = ++leaveIdCounter;
        duration = std::stoi(endDate.substr(8, 2)) - std::stoi(startDate.substr(8, 2)) + 1;
    }

    // Getters
    int getLeaveId() const { return leaveId; }
    int getEmployeeId() const { return employeeId; }
    const std::string& getLeaveType() const { return leaveType; }
    const std::string& getStatus() const { return status; }
    const std::string& getStartDate() const { return startDate; }
    const std::string& getEndDate() const { return endDate; }
    const std::string& getReason() const { return reason; }
    int getDuration() const { return duration; }
    const std::string& getSupervisorApproval() const { return supervisorApproval; }
    const std::string& getDirectorApproval() const { return directorApproval; }

    // Setters
    void setStatus(const std::string& newStatus) { status = newStatus; }
    void setSupervisorApproval(const std::string& approval) { supervisorApproval = approval; }
    void setDirectorApproval(const std::string& approval) { directorApproval = approval; }

    // Virtual methods
    virtual void applyLeave() = 0;
    virtual void displayLeaveDetails() = 0;

    void displayLeaveSummary() {
        std::cout << "Leave ID: " << leaveId << ", Type: " << leaveType << ", Status: " << status
                  << ", Duration: " << duration << " days, Reason: " << reason
                  << ", Supervisor Approval: " << supervisorApproval
                  << ", Director Approval: " << directorApproval << "\n";
    }
};

int Leave::leaveIdCounter = 0;

#endif // LEAVE_H
