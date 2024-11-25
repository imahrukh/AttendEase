#ifndef LEAVEFACTORY_H
#define LEAVEFACTORY_H

#include <string>
#include <memory>  // For smart pointers
#include "CasualLeave.h"
#include "EarnedLeave.h"
#include "Leave.h"
#include "OfficialLeave.h"
#include "UnpaidLeave.h"

class LeaveFactory {
public:
    // Static method to create leave objects dynamically and return shared pointers
    static std::shared_ptr<Leave> createLeave(const std::string& leaveType, int employeeId, const std::string& startDate, const std::string& endDate, const std::string& reason);
};

#endif // LEAVEFACTORY_H
