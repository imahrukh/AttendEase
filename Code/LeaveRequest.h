#ifndef LEAVEREQUEST_H
#define LEAVEREQUEST_H

#include "Leave.h"
#include <string>
#include <ctime>

class LeaveRequest {
public:
    LeaveRequest(int employeeId, Leave* leaveType, const std::tm& from, const std::tm& to, const std::string& reason);
    void approve(int approverId); // Approver ID can be either supervisor or director
    void reject();
    bool isPending() const;
    bool isApproved() const;

private:
    int employeeId;
    Leave* leaveType;
    std::tm from;
    std::tm to;
    std::string reason;
    bool approved;
    bool supervisorApproved; // Track if supervisor approved
    bool directorApproved; // Track if director approved
};

#endif // LEAVEREQUEST_H