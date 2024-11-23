#ifndef OFFICIALLEAVE_H
#define OFFICIALLEAVE_H

#include "Leave.h"

class OfficialLeave : public Leave {
public:
    OfficialLeave(int empId, const std::string& start, const std::string& end, const std::string& reason);

    void applyLeave() override;

    void displayLeaveDetails() override; 
};

#endif // OFFICIALLEAVE_H