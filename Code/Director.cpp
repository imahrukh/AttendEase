#include "Director.h"
#include <iostream>

void Director::applyLeave(std::shared_ptr<Leave> leave) {
    std::cout << "Director reviewing leave request for Employee ID: " << leave->getEmployeeId() << "\n";
    if (leave->getLeaveType() == "Earned" || leave->getLeaveType() == "Unpaid") {
        if (hasSufficientLeave(leave->getLeaveType(), 5)) {
            leave->setStatus("Approved");
            updateLeaveBalance(leave->getLeaveType(), 5);
        } else {
            leave->setStatus("Rejected");
        }
    } else {
        leave->setStatus("Rejected");
    }
}

void Director::displayLeaveDetails() {
    std::cout << "Director's leave approval details for Employee ID: " << getEmployeeId() << "\n";
}

void Director::notifyLeaveApproval(const std::string& status) {
    std::cout << "Director has " << status << " the leave request for Employee ID: " << getEmployeeId() << ".\n";
}

void Director::checkLeaveRequests(std::vector<std::shared_ptr<Leave>>& leaveRequests) {
    std::cout << "Director checking leave requests...\n";
    for (auto& leave : leaveRequests) {
        if (leave->getStatus() == "Pending") {
            applyLeave(leave);
        }
    }
}
