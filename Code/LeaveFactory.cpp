#include "LeaveFactory.h"

Leave* LeaveFactory::createLeave(const string& type) {
    if (type == "Casual") {
        return new CasualLeave();
    } else if (type == "Earned") {
        return new EarnedLeave();
    }
    return nullptr;
}