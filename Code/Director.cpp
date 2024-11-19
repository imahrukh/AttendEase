#include "Director.h"

Director::Director(int id, const std::string& name) : Employee(id, name) {}

void Director::approveLeave(LeaveRequest& request) {
    // Logic for director approval
    request.approve(id);
}

void Director::rejectLeave(LeaveRequest& request) {
    request.reject();
}