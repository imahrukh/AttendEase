#include "OfficialLeave.h"

string OfficialLeave::getLeaveType() const {
    return "Official Leave";
}

bool OfficialLeave::isApprovalRequired() const {
    return false; // No supervisor approval needed
}

bool OfficialLeave::isDirectorApprovalRequired() const {
    return false; // No director approval needed
}