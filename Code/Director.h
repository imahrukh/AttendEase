#ifndef DIRECTOR_H
#define DIRECTOR_H

#include "Employee.h"

class Director : public Employee {
public:
    Director(int id, const std::string& n) : Employee(id, n) {}

    void applyLeave(std::shared_ptr<Leave> leave) override;
    void displayLeaveDetails() override;
    void notifyLeaveApproval(const std::string& status) override;
    void checkLeaveRequests(std::vector<std::shared_ptr<Leave>>& leaveRequests) override;
};

#endif // DIRECTOR_H
