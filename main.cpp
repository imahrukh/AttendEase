#include <string>
#include <iostream>
#include<vector>
#include<memory>




class Attendance {
private:
    std::string date;  // Format: YYYY-MM-DD
    float hoursWorked;

public:
    // Constructor
    Attendance(const std::string& date, float hours) : date(date), hoursWorked(hours) {}

    // Getters
    const std::string& getDate() const { return date; }
    float getHoursWorked() const { return hoursWorked; }

    // Display attendance details
    void displayAttendance() const {
        std::cout << "Date: " << date << ", Hours Worked: " << hoursWorked << " hours\n";
    }
};


class AttendanceRecord {
private:
    int employeeId;
    std::vector<Attendance> records;  // Store attendance entries

public:
    // Constructor
    AttendanceRecord(int empId): employeeId(empId) {}

    // Add an attendance record
    void addAttendance(const std::string& date, float hoursWorked){
        records.emplace_back(date, hoursWorked);
    }

    // Get total hours worked
    float getTotalHoursWorked() const {
        float total = 0;
        for (const auto& record : records) {
            total += record.getHoursWorked();
        }
        return total;
    }

    // Calculate attendance percentage
    float calculateAttendancePercentage(float totalExpectedHours) const{
        return (getTotalHoursWorked() / totalExpectedHours) * 100;
    }

    // Display all attendance records
    void displayAllAttendance() const{
        std::cout << "Attendance Records for Employee ID: " << employeeId << "\n";
        for (const auto& record : records) {
            record.displayAttendance();
        }
    }

    // Getter for the attendance records
    const std::vector<Attendance>& getRecords() const{
        return records;
    }

    // Getter for employee ID
    int getEmployeeId() const{
        return employeeId;
    }
};

class Leave {
protected:
    static int leaveIdCounter;
    int leaveId;
    int employeeId;
    std::string leaveType;
    std::string status;  // Pending, Approved, Rejected
    std::string startDate;
    std::string endDate;
    std::string reason;
    int duration;
    std::string supervisorApproval;  // Yes/No
    std::string directorApproval;    // Yes/No or N/A

public:
    Leave(int empId, const std::string& type, const std::string& start, const std::string& end, const std::string& reason)
        : employeeId(empId), leaveType(type), startDate(start), endDate(end), reason(reason), status("Pending"),
          supervisorApproval("N/A"), directorApproval("N/A") {
        leaveId = ++leaveIdCounter;
        duration = std::stoi(endDate.substr(8, 2)) - std::stoi(startDate.substr(8, 2)) + 1;
    }

    // Getters
    int getLeaveId() const { return leaveId; }
    int getEmployeeId() const { return employeeId; }
    const std::string& getLeaveType() const { return leaveType; }
    const std::string& getStatus() const { return status; }
    const std::string& getStartDate() const { return startDate; }
    const std::string& getEndDate() const { return endDate; }
    const std::string& getReason() const { return reason; }
    int getDuration() const { return duration; }
    const std::string& getSupervisorApproval() const { return supervisorApproval; }
    const std::string& getDirectorApproval() const { return directorApproval; }

    // Setters
    void setStatus(const std::string& newStatus) { status = newStatus; }
    void setSupervisorApproval(const std::string& approval) { supervisorApproval = approval; }
    void setDirectorApproval(const std::string& approval) { directorApproval = approval; }

    // Virtual methods
    virtual void applyLeave() = 0;
    virtual void displayLeaveDetails() = 0;

    void displayLeaveSummary() {
        std::cout << "Leave ID: " << leaveId << ", Type: " << leaveType << ", Status: " << status
                  << ", Duration: " << duration << " days, Reason: " << reason
                  << ", Supervisor Approval: " << supervisorApproval
                  << ", Director Approval: " << directorApproval << "\n";
    }
};
int Leave::leaveIdCounter = 0;

// Abstract base class for attendance reporting
class AttendanceReportable {
public:
    virtual void generateAttendanceReport(float requiredPercentage) = 0;  // Pure virtual function
    virtual ~AttendanceReportable() = default;  // Virtual destructor for proper cleanup
};

class AttendanceReport : public AttendanceReportable {
private:
    std::vector<AttendanceRecord> records;  // List of attendance records
    std::vector<Leave*> leaveRequests;      // List of leave requests

public:
    // Add an attendance record to the report system
    void addEmployeeAttendance(const AttendanceRecord& record){
        records.push_back(record);
    }

    // Add leave requests to the report system
    void addLeaveRequest(Leave* leave){
        leaveRequests.push_back(leave);
    }
    // Generate attendance report for employees with less than required percentage
    void generateAttendanceReport(float requiredPercentage) override{
        const int totalExpectedHours = 40 * 4;  // Assuming 40 hours/week * 4 weeks
        std::cout << "Low Attendance Report (Threshold: " << requiredPercentage << "%)\n";
        for (const auto& record : records) {
            float totalHours = record.getTotalHoursWorked();
            float percentage = (totalHours / totalExpectedHours) * 100;

            if (percentage < requiredPercentage) {
                std::cout << "Employee ID: " << record.getRecords().front().getHoursWorked()
                          << ", Total Hours: " << totalHours << " (" << percentage << "%)\n";
            }
        }
    }
    // Generate leave report for employees with unapproved/unfiled leaves
    void generateUnapprovedLeaveReport(){
        std::cout << "Unapproved Leave Report\n";
        for (const auto& leave : leaveRequests) {
            if (leave->getStatus() == "Pending" || leave->getStatus().empty()) {
                std::cout << "Employee ID: " << leave->getEmployeeId()
                          << ", Leave Type: " << leave->getLeaveType()
                          << ", Status: " << leave->getStatus()
                          << ", Reason: " << leave->getReason() << "\n";
            }
        }
    }
};

class CasualLeave : public Leave {
public:
    CasualLeave(int empId, const std::string& start, const std::string& end, const std::string& reason)  : Leave(empId, "Casual", start, end, reason) {}


    void applyLeave() override{
        std::cout << "Applying for Casual Leave\n";
        // Logic for applying casual leave
    }

    void displayLeaveDetails() override {
        std::cout << "Casual Leave Details: " << "Employee ID: " << getEmployeeId() 
                  << ", Start: " << getStartDate() << ", End: " << getEndDate() 
                  << ", Reason: " << getReason() << "\n";
    }
};

class EarnedLeave : public Leave {
public:
    EarnedLeave(int empId, const std::string& start, const std::string& end, const std::string& reason): Leave(empId, "Earned", start, end, reason) {}

    void applyLeave() override {
        std::cout << "Applying for Earned Leave\n";
        // Logic for applying earned leave
}

    void displayLeaveDetails() override{
        std::cout << "Earned Leave Details: " << "Employee ID: " << getEmployeeId() 
             << ", Start: " << getStartDate() << ", End: " << getEndDate() 
             << ", Reason: " << getReason() << "\n";
    }

};

class OfficialLeave : public Leave {
public:
    OfficialLeave(int empId, const std::string& start, const std::string& end, const std::string& reason): Leave(empId, "Official", start, end, reason) {}

    void applyLeave() override{
    std::cout << "Applying for Official Leave\n";
    // Logic for applying official leave
    }

    void displayLeaveDetails() override{
    std::cout << "Official Leave Details: " << "Employee ID: " << getEmployeeId() 
         << ", Start: " << getStartDate() << ", End: " << getEndDate() 
         << ", Reason: " << getReason() << "\n";
    }
};

class UnpaidLeave : public Leave {
public:
    UnpaidLeave(int empId, const std::string& start, const std::string& end, const std::string& reason): Leave(empId, "Unpaid", start, end, reason) {}

    void applyLeave() override{
        std::cout << "Applying for Unpaid Leave\n";
        // Logic for applying unpaid leave
    }
    void displayLeaveDetails() override{
        std::cout << "Unpaid Leave Details: " << "Employee ID: " << getEmployeeId() 
                  << ", Start: " << getStartDate() << ", End: " << getEndDate() 
                  << ", Reason: " << getReason() << "\n";
    }

};

class LeaveFactory {
public:
    // Static method to create leave objects dynamically and return shared pointers
    static std::shared_ptr<Leave> createLeave(const std::string& leaveType, int employeeId, const std::string& startDate, const std::string& endDate, const std::string& reason){
        if (leaveType == "Casual") {
            return std::make_shared<CasualLeave>(employeeId, startDate, endDate, reason);
        } else if (leaveType == "Earned") {
            return std::make_shared<EarnedLeave>(employeeId, startDate, endDate, reason);
        } else if (leaveType == "Official") {
            return std::make_shared<OfficialLeave>(employeeId, startDate, endDate, reason);
        } else if (leaveType == "Unpaid") {
            return std::make_shared<UnpaidLeave>(employeeId, startDate, endDate, reason);
        } else {
            return nullptr;  // Invalid leave type
        }
    }
};

class Reportable {
public:
    virtual void generateReport() = 0;  // Pure virtual function for generating a report
    virtual ~Reportable() = default;   // Virtual destructor for proper cleanup
};





















class OutstandingLeaveReport : public Reportable {
private:
    std::vector<Leave*> leaveRequests;

public:
    // Constructor
    OutstandingLeaveReport(const std::vector<Leave*>& requests) : leaveRequests(requests) {}

    // Generate outstanding leave report
    void generateReport() override {
        std::cout << "Outstanding Leave Report\n";
        for (const auto& leave : leaveRequests) {
            if (leave->getStatus() == "Pending") {
                std::cout << "Employee ID: " << leave->getEmployeeId()
                          << ", Leave Type: " << leave->getLeaveType()
                          << ", Reason: " << leave->getReason() << "\n";
            }
        }
    }
};
