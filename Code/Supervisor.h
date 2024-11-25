#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include "Employee.h"

class Supervisor : public Employee {
public:
    Supervisor(int id, const std::string& n) : Employee(id, n) {}

    void applyLeave(std::shared_ptr<Leave> leave) override;
    void displayLeaveDetails() override;
    void notifyLeaveApproval(const std::string& status) override;
    void checkLeaveRequests(std::vector<std::shared_ptr<Leave>>& leaveRequests) override;
};

#endif // SUPERVISOR_H
