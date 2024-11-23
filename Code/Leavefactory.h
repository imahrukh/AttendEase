#ifndef LEAVEFACTORY_H
#define LEAVEFACTORY_H

#include "CasualLeave.h"
#include "EarnedLeave.h"
#include "OfficialLeave.h"
#include "UnpaidLeave.h"

using namespace std;    

class LeaveFactory {
    public:
        static Leave* createLeave(const string& leaveType, int employeeId, const string& startDate, const string& endDate, const string& reason) {
            if (leaveType == "Casual") {
                return new CasualLeave(employeeId, startDate, endDate, reason);
            } else if (leaveType == "Earned") {
                return new EarnedLeave(employeeId, startDate, endDate, reason);
            } else if (leaveType == "Official") {
                return new OfficialLeave(employeeId, startDate, endDate, reason);
            } else if (leaveType == "Unpaid") {
                return new UnpaidLeave(employeeId, startDate, endDate, reason);
            } else {
                return nullptr;  // Invalid leave type
            }
        }
};


#endif // LEAVEFACTORY_H
