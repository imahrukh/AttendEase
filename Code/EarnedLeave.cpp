#include "EarnedLeave.h"

string EarnedLeave::getLeaveType() const {
    return "Earned Leave";
}

bool EarnedLeave::isApprovalRequired() const {
    return true; // Supervisor approval needed
}

bool EarnedLeave::isDirectorApprovalRequired() const {
    return true; // Director approval needed
}