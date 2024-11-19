#ifndef DIRECTOR_H
#define DIRECTOR_H

#include "Employee.h"
#include "LeaveRequest.h"

class Director : public Employee {
public:
    Director(int id, const string& name);
    void approveLeave(LeaveRequest& request); // Implement approval logic for Director
    void rejectLeave(LeaveRequest& request);  // Implement rejection logic for Director
};

#endif // DIRECTOR_H