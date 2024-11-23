#include "Supervisor.h"
#include "Leave.h"

using namespece std;

void Supervisor::applyLeave(Leave* leave) {
    cout << "Supervisor reviewing leave request for Employee ID: " << leave->getEmployeeId() << "\n";
    // Only approve Casual Leave
    if (leave->getLeaveType() == "Casual") {
        int leaveDays = 2;  // Casual leave duration (can be customized)
        if (hasSufficientLeave(leave->getLeaveType(), leaveDays)) {
            leave->setStatus("Approved");
            updateLeaveBalance(leave->getLeaveType(), leaveDays);
        } else {
            leave->setStatus("Rejected");
        }
    } else {
        leave->setStatus("Rejected");  // Supervisor cannot approve other leave types
    }
}

void Supervisor::displayLeaveDetails() {
    cout << "Supervisor's leave approval details for Employee ID: " << employeeId << "\n";
}

void Supervisor::notifyLeaveApproval(const string& status) {
    cout << "Supervisor has " << status << " the leave request for Employee ID: " << employeeId << ".\n";
}

void Supervisor::checkLeaveRequests(vector<Leave*>& leaveRequests) {
    cout << "Supervisor checking leave requests...\n";
    for (auto& leave : leaveRequests) {
        if (leave->getStatus() == "Pending") {
            cout << "Leave Request for Employee ID: " << leave->getEmployeeId() << "\n";
            updateLeaveStatus(leave);  // Check leave request and update status
        }
    }
}

void Supervisor::updateLeaveStatus(Leave* leave) {
    if (leave->getLeaveType() == "Casual") {
        int leaveDays = 2;
        if (hasSufficientLeave(leave->getLeaveType(), leaveDays)) {
            leave->setStatus("Approved");
            updateLeaveBalance(leave->getLeaveType(), leaveDays);
        } else {
            leave->setStatus("Rejected");
        }
    } else {
        leave->setStatus("Rejected");
    }
    notifyLeaveApproval(leave->getStatus());
}
