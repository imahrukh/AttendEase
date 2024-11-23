#ifndef UNPAIDLEAVE_H
#define UNPAIDLEAVE_H

#include "Leave.h"

class UnpaidLeave : public Leave {
public:
    UnpaidLeave(int empId, const std::string& start, const std::string& end, const std::string& reason);

    void applyLeave() override;
    void displayLeaveDetails() override; 
};

#endif // UNPAIDLEAVE_H
