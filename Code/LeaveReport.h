#ifndef LEAVEREPORT_H
#define LEAVEREPORT_H

#include "Reportable.h"
#include "Leave.h"
#include <vector>
#include <iostream>

class LeaveReport : public Reportable {
private:
    std::vector<Leave*> leaveRequests;  // For unapproved leave report
    std::vector<Leave*> leaveHistory;  // For employee leave details report

public:
    // Constructor
    LeaveReport(const std::vector<Leave*>& requests = {}, const std::vector<Leave*>& history = {})
        : leaveRequests(requests), leaveHistory(history) {}

    // Add leave request for unapproved leave reporting
    void addLeaveRequest(Leave* leave) {
        leaveRequests.push_back(leave);
    }

    // Add leave history for employee leave details
    void addLeaveHistory(Leave* leave) {
        leaveHistory.push_back(leave);
    }

    // Generate report for unapproved leaves
    void generateUnapprovedLeaveReport() {
        std::cout << "Unapproved Leave Report\n";
        for (const auto& leave : leaveRequests) {
            if (leave->getStatus() == "Pending" || leave->getStatus().empty()) {
                std::cout << "Employee ID: " << leave->getEmployeeId()
                          << ", Leave Type: " << leave->getLeaveType()
                          << ", Status: " << leave->getStatus()
                          << ", Reason: " << leave->getReason() << "\n";
            }
        }
    }

    // Generate leave details report
    void generateEmployeeLeaveDetailsReport() {
        std::cout << "Leave Details Report\n";
        for (const auto& leave : leaveHistory) {
            leave->displayLeaveSummary();
        }
    }

    // Interface implementation for Reportable
    void generateReport() override {
        std::cout << "Leave Report: This is a combined report class. Call specific report methods as needed.\n";
    }
};

#endif // LEAVEREPORT_H
