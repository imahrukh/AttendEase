#ifndef UNPAIDLEAVE_H
#define UNPAIDLEAVE_H

#include "Leave.h"

class UnpaidLeave : public Leave {
public:
    std::string getLeaveType() const override;
    bool isApprovalRequired() const override;
    bool isDirectorApprovalRequired() const override; // Director approval required
};

#endif // UNPAIDLEAVE_H