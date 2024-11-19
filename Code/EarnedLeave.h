#ifndef EARNEDLEAVE_H
#define EARNEDLEAVE_H

#include "Leave.h"

class EarnedLeave : public Leave {
public:
    std::string getLeaveType() const override;
    bool isApprovalRequired() const override;
    bool isDirectorApprovalRequired() const override; // Director approval required
};

#endif // EARNEDLEAVE_H