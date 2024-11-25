#include "Supervisor.h"
#include <iostream>

void Supervisor::applyLeave(std::shared_ptr<Leave> leave) {
    std::cout << "Supervisor reviewing leave request for Employee ID: " << leave->getEmployeeId() << "\n";
    if (leave->getLeaveType() == "Casual" && hasSufficientLeave("Casual", 2)) {
        leave->setStatus("Approved");
        updateLeaveBalance("Casual", 2);
    } else {
        leave->setStatus("Rejected");
    }
}

void Supervisor::displayLeaveDetails() {
    std::cout << "Supervisor's leave approval details for Employee ID: " << getEmployeeId() << "\n";
}

void Supervisor::notifyLeaveApproval(const std::string& status) {
    std::cout << "Supervisor has " << status << " the leave request for Employee ID: " << getEmployeeId() << ".\n";
}

void Supervisor::checkLeaveRequests(std::vector<std::shared_ptr<Leave>>& leaveRequests) {
    std::cout << "Supervisor checking leave requests...\n";
    for (auto& leave : leaveRequests) {
        if (leave->getStatus() == "Pending") {
            applyLeave(leave);
        }
    }
}
