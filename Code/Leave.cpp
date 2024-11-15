#include <memory>

using namepsace std;

// Abstract Base Class for Leaves
class Leave {
protected:
    string startDate;
    string endDate;
    string status; // Pending, Approved, Rejected
    string reason;

public:
    virtual void applyLeave() = 0;
    virtual ~Leave() = default;

    void displayStatus() {
        cout << "Leave from " << startDate << " to " << endDate
                  << " is " << status << ". Reason: " << reason << "\n";
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

    void applyLeave() override {
        std::cout << "Applying for Casual Leave from " << startDate << " to " << endDate << "\n";
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

    void applyLeave() override {
        cout << "Applying for Earned Leave from " << startDate << " to " << endDate << "\n";
    }
};

// Factory for Creating Leaves
class LeaveFactory {
public:
    static shared_ptr<Leave> createLeave(string type, string start, string end, string reason) {
        if (type == "Casual") return make_shared<CasualLeave>(start, end, reason);
        if (type == "Earned") return make_shared<EarnedLeave>(start, end, reason);
        return nullptr;
    }
};

// Strategy Pattern for Approval
class LeaveApprovalStrategy {
public:
    virtual void approveLeave(shared_ptr<Leave> leave) = 0;
};

class SupervisorApproval : public LeaveApprovalStrategy {
public:
    void approveLeave(shared_ptr<Leave> leave) override {
        std::cout << "Supervisor approves leave.\n";
        leave->displayStatus();
    }
};

class DirectorApproval : public LeaveApprovalStrategy {
public:
    void approveLeave(shared_ptr<Leave> leave) override {
        std::cout << "Director approves leave.\n";
        leave->displayStatus();
    }
};
