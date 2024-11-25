#ifndef DIRECTOR_H
#define DIRECTOR_H

#include "Employee.h"
#include <string>
#include <vector>

// Director class inherited from Employee
class Director : public Employee {
public:
    Director(int id, const std::string& n) : Employee(id, n) {}

    // Override methods
    void applyLeave(Leave* leave) override;
    void displayLeaveDetails() override;
    void notifyLeaveApproval(const std::string& status) override;
    void checkLeaveRequests(std::vector<Leave*>& leaveRequests) override;
    void updateLeaveStatus(Leave* leave);
};

#endif // DIRECTOR_H
