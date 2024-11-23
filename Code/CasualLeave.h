#ifndef CASUALLEAVE_H
#define CASUALLEAVE_H

#include "Leave.h"

using namespace std;    

class CasualLeave : public Leave {
public:
    CasualLeave(int empId, const string& start, const string& end, const string& reason);

    void applyLeave() override;

    void displayLeaveDetails() override ;
};

#endif // CASUALLEAVE_H