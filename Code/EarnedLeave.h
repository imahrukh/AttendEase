#ifndef EARNEDLEAVE_H
#define EARNEDLEAVE_H

#include "Leave.h"

class EarnedLeave : public Leave {
public:
    EarnedLeave(int empId, const std::string& start, const std::string& end, const std::string& reason);

    void applyLeave() override;

    void displayLeaveDetails() override;
};
#endif // EARNEDLEAVE_H
