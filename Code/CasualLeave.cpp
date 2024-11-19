#include "CasualLeave.h"

std::string CasualLeave::getLeaveType() const {
    return "Casual Leave";
}

bool CasualLeave::isApprovalRequired() const {
    return false;
}

bool CasualLeave::isDirectorApprovalRequired() const {
    return false; // No director approval needed
}