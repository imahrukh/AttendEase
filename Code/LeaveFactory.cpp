#include "LeaveFactory.h"

std::unique_ptr<Leave> LeaveFactory :: createLeave(const std::string& leaveType, int employeeId, const std::string& startDate, const std::string& endDate, const std::string& reason) {
    if (leaveType == "Casual") {
        return std::make_unique<CasualLeave>(employeeId, startDate, endDate, reason);
    } else if (leaveType == "Earned") {
        return std::make_unique<EarnedLeave>(employeeId, startDate, endDate, reason);
    } else if (leaveType == "Official") {
        return std::make_unique<OfficialLeave>(employeeId, startDate, endDate, reason);
    } else if (leaveType == "Unpaid") {
        return std::make_unique<UnpaidLeave>(employeeId, startDate, endDate, reason);
    } else {
        return nullptr;  // Invalid leave type
    }
}
