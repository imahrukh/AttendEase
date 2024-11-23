#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include "Employee.h"

// Supervisor class inherited from Employee
class Supervisor : public Employee {
public:
    Supervisor(int id, const std::string& n) : Employee(id, n) {}

    // Override methods
    void applyLeave(Leave* leave) override;
    void displayLeaveDetails() override;
    void notifyLeaveApproval(const std::string& status) override;
    void checkLeaveRequests(std::vector<Leave*>& leaveRequests) override;
    void updateLeaveStatus(Leave* leave);
};

#endif // SUPERVISOR_H
