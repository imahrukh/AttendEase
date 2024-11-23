#ifndef OUTSTANDINGLEAVEREPORT_H
#define OUTSTANDINGLEAVEREPORT_H

#include "Reportable.h"
#include "Leave.h"
#include <vector>
#include <iostream>


class OutstandingLeaveReport : public Reportable {
private:
    std::vector<Leave*> leaveRequests;

public:
    // Constructor
    OutstandingLeaveReport(const std::vector<Leave*>& requests) : leaveRequests(requests) {}

    // Generate outstanding leave report
    void generateReport() override {
        std::cout << "Outstanding Leave Report\n";
        for (const auto& leave : leaveRequests) {
            if (leave->getStatus() == "Pending") {
                std::cout << "Employee ID: " << leave->getEmployeeId()
                          << ", Leave Type: " << leave->getLeaveType()
                          << ", Reason: " << leave->getReason() << "\n";
            }
        }
    }
};


#endif // OUTSTANDINGLEAVEREPORT_H
