#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include "Employee.h"
#include "LeaveRequest.h"

class Supervisor : public Employee {
public:
    Supervisor(int id, const string& name);
    void approveLeave(LeaveRequest& request); // Implement approval logic for Supervisor
    void rejectLeave(LeaveRequest& request);  // Implement rejection logic for Supervisor
};

#endif // SUPERVISOR_H