#include "Supervisor.h"

Supervisor::Supervisor(int id, const std::string& name) : Employee(id, name) {}

void Supervisor::approveLeave(LeaveRequest& request) {
    // Logic for supervisor approval
    request.approve(id);
}

void Supervisor::rejectLeave(LeaveRequest& request) {
    request.reject();
}