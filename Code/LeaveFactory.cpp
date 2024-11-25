#include "LeaveFactory.h"

std::shared_ptr<Leave> LeaveFactory::createLeave(const std::string& leaveType, int employeeId, const std::string& startDate, const std::string& endDate, const std::string& reason) {
    if (leaveType == "Casual") {
        return std::make_shared<CasualLeave>(employeeId, startDate, endDate, reason);
    } else if (leaveType == "Earned") {
        return std::make_shared<EarnedLeave>(employeeId, startDate, endDate, reason);
    } else if (leaveType == "Official") {
        return std::make_shared<OfficialLeave>(employeeId, startDate, endDate, reason);
    } else if (leaveType == "Unpaid") {
        return std::make_shared<UnpaidLeave>(employeeId, startDate, endDate, reason);
    } else {
        return nullptr;  // Invalid leave type
    }
}
