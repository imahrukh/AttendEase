#include "LeaveRequest.h"

// Constructor to initialize a leave request
LeaveRequest::LeaveRequest(int empId, Leave* leave, const std::tm& start, const std::tm& end, const std::string& reason)
    : employeeId(empId), leaveType(leave), from(start), to(end), reason(reason), approved(false), supervisorApproved(false), directorApproved(false) {}

// Approve the leave request based on the approver's ID
void LeaveRequest::approve(int approverId) {
    // Check if supervisor approval is required
    if (leaveType->isApprovalRequired()) {
        if (!supervisorApproved) {
            supervisorApproved = true; // Supervisor approves first
            cout << "Leave request approved by Supervisor for Employee ID: " << employeeId << std::endl;
        } 
        // Check if director approval is required
        else if (leaveType->isDirectorApprovalRequired() && !directorApproved) {
            directorApproved = true; // Director approves next
            cout << "Leave request approved by Director for Employee ID: " << employeeId << std::endl;
        }
    }

    // If both approvals are required and obtained, mark the request as fully approved
    if (supervisorApproved && (!leaveType->isDirectorApprovalRequired() || directorApproved)) {
        approved = true; // Leave is fully approved
        cout << "Leave request fully approved for Employee ID: " << employeeId << std::endl;
    }
}

// Reject the leave request
void LeaveRequest::reject() {
    approved = false; // Reject the leave request
    cout << "Leave request rejected for Employee ID: " << employeeId << std::endl;
}

// Check if the leave request is pending
bool LeaveRequest::isPending() const {
    return !approved; // If not approved, it's pending
}

// Check if the leave request is approved
bool LeaveRequest::isApproved() const {
    return approved; // Return approval status
}