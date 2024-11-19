#include "UnpaidLeave.h"

string UnpaidLeave::getLeaveType() const {
    return "Unpaid Leave";
}

bool UnpaidLeave::isApprovalRequired() const {
    return true; // Supervisor approval needed
}

bool UnpaidLeave::isDirectorApprovalRequired() const {
    return true; // Director approval needed
}