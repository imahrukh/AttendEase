#include <memory>
#include <iostream>
#include <string>

using namespace std;

// Abstract Base Class for Leaves
class Leave {
protected:
    string startDate;
    string endDate;
    string status; // Pending, Approved, Rejected
    string reason;

public:
    virtual void apply() = 0;
    virtual ~Leave() = default;

    void setStatus(string s) {
        status = s;
    }

    string getStatus() const {
        return status;
    }

    void displayLeaveDetails() const {
        cout << "Leave from " << startDate << " to " << endDate
                  << ", Status: " << status
                  << ", Reason: " << reason << "\n";
    }
};

class CasualLeave : public Leave {
public:
    CasualLeave(string start, string end, string r) {
        startDate = start;
        endDate = end;
        reason = r;
        status = "Pending";
    }

    void apply() override {
        cout << "Applying for Casual Leave.\n";
    }
};

class EarnedLeave : public Leave {
public:
    EarnedLeave(string start, string end, string r) {
        startDate = start;
        endDate = end;
        reason = r;
        status = "Pending";
    }

    void apply() override {
        cout << "Applying for Earned Leave.\n";
    }
};

class LeaveFactory {
public:
    static shared_ptr<Leave> createLeave(string type, std::string start, string end, string reason) {
        if (type == "Casual") return std::make_shared<CasualLeave>(start, end, reason);
        if (type == "Earned") return std::make_shared<EarnedLeave>(start, end, reason);
        return nullptr;
    }
};
