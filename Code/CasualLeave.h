#ifndef CASUALLEAVE_H
#define CASUALLEAVE_H

#include "Leave.h"

class CasualLeave : public Leave {
public:
    std::string getLeaveType() const override;
    bool isApprovalRequired() const override;
    bool isDirectorApprovalRequired() const override; // Not needed for Casual Leave
};

#endif // CASUALLEAVE_H