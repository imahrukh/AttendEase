#ifndef LEAVEFACTORY_H
#define LEAVEFACTORY_H

#include "Leave.h"
#include "CasualLeave.h"
#include "EarnedLeave.h"

class LeaveFactory {
public:
    static Leave* createLeave(const string& type);
};

#endif // LEAVEFACTORY_H