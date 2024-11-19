#ifndef OFFICIALLEAVE_H
#define OFFICIALLEAVE_H

#include "Leave.h"

class OfficialLeave : public Leave {
public:
    string getLeaveType() const override;
    bool isApprovalRequired() const override;
    bool isDirectorApprovalRequired() const override; // Not needed for Official Leave
};

#endif // OFFICIALLEAVE_H