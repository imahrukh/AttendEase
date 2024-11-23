#include "Director.h"
#include "Leave.h"

using namespace std;    
void Director::applyLeave(Leave* leave) {
    cout << "Director reviewing leave request for Employee ID: " << leave->getEmployeeId() << "\n";
    // Only approve Earned or Unpaid Leave
    if (leave->getLeaveType() == "Earned" || leave->getLeaveType() == "Unpaid") {
        int leaveDays = 5;  // Earned/Unpaid leave duration (can be customized)
        if (hasSufficientLeave(leave->getLeaveType(), leaveDays)) {
            leave->setStatus("Approved");
            updateLeaveBalance(leave->getLeaveType(), leaveDays);
        } else {
            leave->setStatus("Rejected");
        }
    } else {
        leave->setStatus("Rejected");  // Director cannot approve Casual leave
    }
}

void Director::displayLeaveDetails() {
    cout << "Director's leave approval details for Employee ID: " << employeeId << "\n";
}

void Director::notifyLeaveApproval(const string& status) {
    cout << "Director has " << status << " the leave request for Employee ID: " << employeeId << ".\n";
}

void Director::checkLeaveRequests(vector<Leave*>& leaveRequests) {
    cout << "Director checking leave requests...\n";
    for (auto& leave : leaveRequests) {
        if (leave->getStatus() == "Pending") {
            cout << "Leave Request for Employee ID: " << leave->getEmployeeId() << "\n";
            updateLeaveStatus(leave);  // Check leave request and update status
        }
    }
}

void Director::updateLeaveStatus(Leave* leave) {
    if (leave->getLeaveType() == "Earned" || leave->getLeaveType() == "Unpaid") {
        int leaveDays = 5;
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
