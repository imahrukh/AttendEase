#ifndef LEAVE_H
#define LEAVE_H

#include<iostream>
#include <string>
#include <ctime>

using namespace std;

class Leave {
public:
    virtual ~Leave() {}
    virtual string getLeaveType() const = 0;
    virtual bool isApprovalRequired() const = 0;
    virtual bool isDirectorApprovalRequired() const = 0;
};

#endif // LEAVE_H