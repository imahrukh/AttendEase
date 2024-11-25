#ifndef LEAVEFACTORY_H
#define LEAVEFACTORY_H

#include <string>
#include <memory>
#include "CasualLeave.h"
#include "EarnedLeave.h"
#include "OfficialLeave.h"
#include "UnpaidLeave.h"

class LeaveFactory {
public:
    static std::shared_ptr<Leave> createLeave(const std::string& leaveType, int employeeId, const std::string& startDate,
                                              const std::string& endDate, const std::string& reason);
};

#endif // LEAVEFACTORY_H
