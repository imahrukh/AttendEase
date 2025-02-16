#include "helper.h"
#include <algorithm>
#include <cstdlib> 

// Constructor for Attendance class to initialize date and hours worked
Attendance::Attendance(const std::string& date, float hours) : date(date), hoursWorked(hours) {}

// Getter to retrieve the date of attendance
const std::string& Attendance::getDate() const { return date; }

// Getter to retrieve the number of hours worked on the specific date
float Attendance::getHoursWorked() const { return hoursWorked; }

// Display attendance details in a readable format
void Attendance::displayAttendance() const {
    std::cout << "Date: " << date << ", Hours Worked: " << hoursWorked << " hours\n";
}

// Constructor for AttendanceRecord to initialize employee ID
AttendanceRecord::AttendanceRecord(int empId) : employeeId(empId) {}

// Add a new attendance record for a specific date and hours worked
void AttendanceRecord::addAttendance(const std::string& date, float hoursWorked) {
    records.emplace_back(date, hoursWorked); // Add a new Attendance object to the records vector
}

// Calculate the total hours worked by summing up all attendance records
float AttendanceRecord::getTotalHoursWorked() const {
    float total = 0;
    for (const auto& record : records) {
        total += record.getHoursWorked(); // Accumulate hours worked
    }
    return total;
}

// Calculate attendance percentage based on total hours worked and expected hours
float AttendanceRecord::calculateAttendancePercentage(float totalExpectedHours) const {
    return (getTotalHoursWorked() / totalExpectedHours) * 100; // Calculate percentage
}

// Display all attendance records for the employee
void AttendanceRecord::displayAllAttendance() const {
    std::cout << "Attendance Records for Employee ID: " << employeeId << "\n";
    for (const auto& record : records) {
        record.displayAttendance(); // Display each attendance record
    }
}

// Getter to retrieve all attendance records
const std::vector<Attendance>& AttendanceRecord::getRecords() const {
    return records;
}

// Getter to retrieve the employee ID associated with this attendance record
int AttendanceRecord::getEmployeeId() const {
    return employeeId;
}

// Initialize static leave ID counter
int Leave::leaveIdCounter = 0;

Leave::Leave(int empId, const std::string& type, const std::string& start, const std::string& end, const std::string& reason)
    : employeeId(empId), leaveType(type), startDate(start), endDate(end), reason(reason), status("Pending") {
    leaveId = ++leaveIdCounter; // Assign a unique ID to the leave
    try {
        // Calculate leave duration in days if valid dates are provided
        if (startDate.size() >= 10 && endDate.size() >= 10) {
            duration = std::stoi(endDate.substr(8, 2)) - std::stoi(startDate.substr(8, 2)) + 1;
        } else {
            throw std::invalid_argument("Invalid date format");
        }
    } catch (const std::exception& e) {
        std::cerr << "Error calculating leave duration: " << e.what() << '\n';
        duration = 0; // Default duration in case of an error
    }

    // Set initial approval status based on leave type
    if (leaveType == "Casual") {
        supervisorApproval = "N/A";
        directorApproval = "N/A";
        status = "Approved";
    } else if (leaveType == "Earned" || leaveType == "Unpaid") {
        supervisorApproval = "Pending";
        directorApproval = "Pending";
    } else if (leaveType == "Official") {
        supervisorApproval = "N/A";
        directorApproval = "N/A";
        status = "Approved";
    }
}

// Getters for Leave class attributes
int Leave::getLeaveId() const { return leaveId; }
int Leave::getEmployeeId() const { return employeeId; }
const std::string& Leave::getLeaveType() const { return leaveType; }
const std::string& Leave::getStatus() const { return status; }
const std::string& Leave::getStartDate() const { return startDate; }
const std::string& Leave::getEndDate() const { return endDate; }
const std::string& Leave::getReason() const { return reason; }
int Leave::getDuration() const { return duration; }
const std::string& Leave::getSupervisorApproval() const { return supervisorApproval; }
const std::string& Leave::getDirectorApproval() const { return directorApproval; }

// Setters for updating Leave class attributes
void Leave::setStatus(const std::string& newStatus) { status = newStatus; }
void Leave::setSupervisorApproval(const std::string& approval) { supervisorApproval = approval; }
void Leave::setDirectorApproval(const std::string& approval) { directorApproval = approval; }

// Display a summary of the leave
void Leave::displayLeaveSummary() {
    std::cout << "Leave ID: " << leaveId << ", Type: " << leaveType << ", Status: " << status
              << ", Duration: " << duration << " days, Reason: " << reason
              << ", Supervisor Approval: " << supervisorApproval
              << ", Director Approval: " << directorApproval << "\n";
}

// Abstract base class for attendance reporting
class AttendanceReportable {
public:
    virtual void generateAttendanceReport(float requiredPercentage) = 0; // Pure virtual function for reporting
    virtual ~AttendanceReportable() = default; // Virtual destructor for cleanup
};

// Class for generating attendance and leave reports
class AttendanceReport : public AttendanceReportable {
private:
    std::vector<AttendanceRecord> records; // List of attendance records
    std::vector<Leave*> leaveRequests;     // List of leave requests

public:
    // Add an attendance record to the reporting system
    void addEmployeeAttendance(const AttendanceRecord& record) {
        records.push_back(record);
    }

    // Add leave requests to the reporting system
    void addLeaveRequest(Leave* leave) {
        leaveRequests.push_back(leave);
    }

    // Generate attendance report for employees below the required attendance threshold
    void generateAttendanceReport(float requiredPercentage) override {
        const int totalExpectedHours = 40 * 4; // Assuming 40 hours/week for 4 weeks
        std::cout << "Low Attendance Report (Threshold: " << requiredPercentage << "%)\n";
        for (const auto& record : records) {
            float totalHours = record.getTotalHoursWorked();
            float percentage = (totalHours / totalExpectedHours) * 100;

            if (percentage < requiredPercentage) {
                std::cout << "Employee ID: " << record.getEmployeeId()
                          << ", Total Hours: " << totalHours << " (" << percentage << "%)\n";
            }
        }
    }

    // Generate report for unapproved or pending leave requests
    void generateUnapprovedLeaveReport() {
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

// CasualLeave class inherits from Leave class
class CasualLeave : public Leave {
public:
    // Constructor initializes CasualLeave with employee ID, start date, end date, and reason
    CasualLeave(int empId, const std::string& start, const std::string& end, const std::string& reason)  
        : Leave(empId, "Casual", start, end, reason) {}

    // Override the applyLeave method to define logic for applying casual leave
    void applyLeave() override {
        std::cout << "Applying for Casual Leave\n";
        // Logic for applying casual leave goes here (not implemented)
    }

    // Override the displayLeaveDetails method to show leave details
    void displayLeaveDetails() override {
        std::cout << "Casual Leave Details: " << "Employee ID: " << getEmployeeId() 
                  << ", Start: " << getStartDate() << ", End: " << getEndDate() 
                  << ", Reason: " << getReason() << "\n";
    }
};

// EarnedLeave class inherits from Leave class
class EarnedLeave : public Leave {
public:
    // Constructor initializes EarnedLeave with employee ID, start date, end date, and reason
    EarnedLeave(int empId, const std::string& start, const std::string& end, const std::string& reason)
        : Leave(empId, "Earned", start, end, reason) {}

    // Override the applyLeave method to define logic for applying earned leave
    void applyLeave() override {
        std::cout << "Applying for Earned Leave\n";
        // Logic for applying earned leave goes here (not implemented)
    }

    // Override the displayLeaveDetails method to show leave details
    void displayLeaveDetails() override {
        std::cout << "Earned Leave Details: " << "Employee ID: " << getEmployeeId() 
                  << ", Start: " << getStartDate() << ", End: " << getEndDate() 
                  << ", Reason: " << getReason() << "\n";
    }
};

// OfficialLeave class inherits from Leave class
class OfficialLeave : public Leave {
public:
    // Constructor initializes OfficialLeave with employee ID, start date, end date, and reason
    OfficialLeave(int empId, const std::string& start, const std::string& end, const std::string& reason)
        : Leave(empId, "Official", start, end, reason) {}

    // Override the applyLeave method to define logic for applying official leave
    void applyLeave() override {
        std::cout << "Applying for Official Leave\n";
        // Logic for applying official leave goes here (not implemented)
    }

    // Override the displayLeaveDetails method to show leave details
    void displayLeaveDetails() override {
        std::cout << "Official Leave Details: " << "Employee ID: " << getEmployeeId() 
                  << ", Start: " << getStartDate() << ", End: " << getEndDate() 
                  << ", Reason: " << getReason() << "\n";
    }
};

// UnpaidLeave class inherits from Leave class
class UnpaidLeave : public Leave {
public:
    // Constructor initializes UnpaidLeave with employee ID, start date, end date, and reason
    UnpaidLeave(int empId, const std::string& start, const std::string& end, const std::string& reason)
        : Leave(empId, "Unpaid", start, end, reason) {}

    // Override the applyLeave method to define logic for applying unpaid leave
    void applyLeave() override {
        std::cout << "Applying for Unpaid Leave\n";
        // Logic for applying unpaid leave goes here (not implemented)
    }

    // Override the displayLeaveDetails method to show leave details
    void displayLeaveDetails() override {
        std::cout << "Unpaid Leave Details: " << "Employee ID: " << getEmployeeId() 
                  << ", Start: " << getStartDate() << ", End: " << getEndDate() 
                  << ", Reason: " << getReason() << "\n";
    }
};

// Factory class for creating different leave types dynamically based on the leave type passed
class LeaveFactory {
public:
    // Static method to create a leave object of the specified type and return as shared pointer
    static std::shared_ptr<Leave> createLeave(const std::string& leaveType, int employeeId, const std::string& startDate, const std::string& endDate, const std::string& reason) {
        if (leaveType == "Casual") {
            return std::make_shared<CasualLeave>(employeeId, startDate, endDate, reason); // Create CasualLeave object
        } else if (leaveType == "Earned") {
            return std::make_shared<EarnedLeave>(employeeId, startDate, endDate, reason); // Create EarnedLeave object
        } else if (leaveType == "Official") {
            return std::make_shared<OfficialLeave>(employeeId, startDate, endDate, reason); // Create OfficialLeave object
        } else if (leaveType == "Unpaid") {
            return std::make_shared<UnpaidLeave>(employeeId, startDate, endDate, reason); // Create UnpaidLeave object
        } else {
            return nullptr;  // If leave type is not recognized, return null
        }
    }
};

// Reportable interface for generating reports
class Reportable {
public:
    // Pure virtual function to be implemented by derived classes for generating reports
    virtual void generateReport() = 0;  
    virtual ~Reportable() = default;   // Virtual destructor to allow proper cleanup of derived objects
};

// Constructor for Employee class initializes basic employee data
Employee::Employee(int id, const std::string& n, const std::string& r) : employeeId(id), name(n), role(r) {}

// Getter methods to retrieve employee's information
int Employee::getEmployeeId() const { return employeeId; }
const std::string& Employee::getName() const { return name; }
const std::string& Employee::getRole() const { return role; }
float Employee::getTotalHoursWorked() const { return totalHoursWorked; }
int Employee::getCasualLeaveBalance() const { return casualLeaveBalance; }
int Employee::getEarnedLeaveBalance() const { return earnedLeaveBalance; }

// Setter methods to update employee's data
void Employee::setTotalHoursWorked(float hours) { totalHoursWorked = hours; }
void Employee::setCasualLeaveBalance(int balance) { casualLeaveBalance = balance; }
void Employee::setEarnedLeaveBalance(int balance) { earnedLeaveBalance = balance; }

// Method to check if the employee has sufficient leave balance for the requested type and number of days
bool Employee::hasSufficientLeave(const std::string& leaveType, int days) {
    if (leaveType == "Casual" && casualLeaveBalance >= days) {
        return true; // Sufficient casual leave
    } else if (leaveType == "Earned" && earnedLeaveBalance >= days) {
        return true; // Sufficient earned leave
    }
    return false; // Insufficient leave
}

// Method to update the leave balance once leave is approved
void Employee::updateLeaveBalance(const std::string& leaveType, int days) {
    if (leaveType == "Casual") {
        casualLeaveBalance -= days; // Deduct days from casual leave balance
    } else if (leaveType == "Earned") {
        earnedLeaveBalance -= days; // Deduct days from earned leave balance
    }
}

// Method to check the status of a specific leave by its ID
void Employee::checkLeaveStatus(int leaveId) {
    std::ifstream file("Leaves.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open leave data file for reading.\n";
        return;
    }

    std::string line;
    bool leaveFound = false;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        int id, empId;
        std::string type, startDate, endDate, reason, status, supervisorApproval, directorApproval, temp;

        try {
            // Parse Leave ID from the line
            if (!std::getline(ss, temp, '|') || temp.empty()) continue;
            id = std::stoi(temp);

            // Parse Employee ID from the line
            if (!std::getline(ss, temp, '|') || temp.empty()) continue;
            empId = std::stoi(temp);

            // Parse other details from the line
            if (!std::getline(ss, type, '|') || type.empty()) throw std::invalid_argument("Invalid Leave Type");
            if (!std::getline(ss, startDate, '|') || startDate.empty()) throw std::invalid_argument("Invalid Start Date");
            if (!std::getline(ss, endDate, '|') || endDate.empty()) throw std::invalid_argument("Invalid End Date");
            if (!std::getline(ss, reason, '|') || reason.empty()) throw std::invalid_argument("Invalid Reason");
            if (!std::getline(ss, status, '|') || status.empty()) throw std::invalid_argument("Invalid Status");
            std::getline(ss, supervisorApproval, '|');
            std::getline(ss, directorApproval, '|');

            // Check if the Leave ID and Employee ID match
            if (id == leaveId && empId == employeeId) {
                std::cout << "Leave Status for Employee " << getName() << " (Leave ID: " << leaveId << "): "
                          << status << "\n";
                std::cout << "Supervisor Approval: " << supervisorApproval << "\n";
                std::cout << "Director Approval: " << directorApproval << "\n";
                leaveFound = true;
                break;
            }
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error processing line: " << line << " - " << e.what() << '\n';
        } catch (const std::out_of_range& e) {
            std::cerr << "Error processing line: " << line << " - " << e.what() << '\n';
        }
    }

    if (!leaveFound) {
        std::cout << "Leave not found for Employee " << getName() << " (Leave ID: " << leaveId << ").\n";
    }

    file.close();
}

// Method to generate a leave report for the employee
void Employee::generateLeaveReport() {
    std::ifstream file("Leaves.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open leave data file for reading.\n";
        return;
    }

    std::string line;
    bool leaveFound = false;
    std::cout << "Leave Report for Employee: " << name << "\n";
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        int id, empId;
        std::string type, startDate, endDate, reason, status, supervisorApproval, directorApproval, temp;

        try {
            // Parse Leave ID from the line
            if (!std::getline(ss, temp, '|') || temp.empty()) continue;
            id = std::stoi(temp);

            // Parse Employee ID from the line
            if (!std::getline(ss, temp, '|') || temp.empty()) continue;
            empId = std::stoi(temp);

            // Check if the Employee ID matches
            if (empId != employeeId) continue;

            // Parse other details from the line
            if (!std::getline(ss, type, '|') || type.empty()) throw std::invalid_argument("Invalid Leave Type");
            if (!std::getline(ss, startDate, '|') || startDate.empty()) throw std::invalid_argument("Invalid Start Date");
            if (!std::getline(ss, endDate, '|') || endDate.empty()) throw std::invalid_argument("Invalid End Date");
            if (!std::getline(ss, reason, '|') || reason.empty()) throw std::invalid_argument("Invalid Reason");
            if (!std::getline(ss, status, '|') || status.empty()) throw std::invalid_argument("Invalid Status");
            std::getline(ss, supervisorApproval, '|');
            std::getline(ss, directorApproval, '|');

            // Display leave details
            std::cout << "Leave ID: " << id
                      << ", Type: " << type
                      << ", Start Date: " << startDate
                      << ", End Date: " << endDate
                      << ", Reason: " << reason
                      << ", Status: " << status
                      << ", Supervisor Approval: " << supervisorApproval
                      << ", Director Approval: " << directorApproval << "\n";
            leaveFound = true;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error processing line: " << line << " - " << e.what() << '\n';
        } catch (const std::out_of_range& e) {
            std::cerr << "Error processing line: " << line << " - " << e.what() << '\n';
        }
    }

    if (!leaveFound) {
        std::cout << "No leave records found for Employee " << name << ".\n";
    }

    file.close();
}

void Employee::generateAttendanceReport() {
    // Clear existing attendance records
    attendanceRecords.clear();

    // Read attendance data from file
    FileHandler::readAttendanceData(attendanceRecords);

    // Display employee's basic info
    std::cout << "Attendance Report for Employee: " << name << "\n";
    std::cout << "Employee ID: " << employeeId << "\n";
    std::cout << "Role: " << role << "\n";
    std::cout << "Total Hours Worked: " << totalHoursWorked << "\n";
    std::cout << "Casual Leave Balance: " << casualLeaveBalance << "\n";
    std::cout << "Earned Leave Balance: " << earnedLeaveBalance << "\n";
    std::cout << "Attendance Records:\n";

    // Display attendance records for the employee
    for (const auto& record : attendanceRecords) {
        if (record.getEmployeeId() == employeeId) {
            record.displayAllAttendance();
        }
    }
}

// Method to request leave by employee after validating sufficient leave balance
void Employee::requestLeave(const std::string& leaveType, const std::string& startDate, const std::string& endDate, const std::string& reason) {
    int leaveDays = 0;
    try {
        // Validate date formats and calculate leave days
        if (startDate.size() >= 10 && endDate.size() >= 10) {
            leaveDays = std::stoi(endDate.substr(8, 2)) - std::stoi(startDate.substr(8, 2)) + 1;
        } else {
            throw std::invalid_argument("Invalid date format");
        }
    } catch (const std::exception& e) {
        std::cerr << "Error calculating leave days: " << e.what() << "\n";
        return; // Exit function if date parsing fails
    }

    // Validate leave request based on leave type
    if (leaveType == "Casual") {
        if (leaveDays > 4) {
            std::cout << "Casual leave cannot be more than 4 days. Request denied.\n";
            return;
        }
        if (casualLeaveBalance < leaveDays) {
            std::cout << "Insufficient casual leave balance. Request denied.\n";
            return;
        }
    } else if (leaveType == "Earned") {
        if (earnedLeaveBalance < leaveDays) {
            std::cout << "Insufficient earned leave balance. Request denied.\n";
            return;
        }
    } else if (leaveType == "Official") {
        leaveDays = 1; // Full credit (8 hours) is awarded
    } else if (leaveType == "Unpaid") {
        // No balance check for unpaid leave
    } else  {
        std::cout << "Invalid leave type provided. Request denied.\n";
        return;
    }

    // Create a new leave object using the factory and add it to the leave history
    std::shared_ptr<Leave> newLeave = LeaveFactory::createLeave(leaveType, employeeId, startDate, endDate, reason);

    if (newLeave) {
        leaveHistory.push_back(newLeave);  // Add to leave history

        // Save the leave to the file using FileHandler
        try {
            FileHandler::writeLeaveData(*newLeave);
            std::cout << leaveType << " leave request submitted successfully.\n";
        } catch (const std::exception& e) {
            std::cerr << "Error saving leave data: " << e.what() << "\n";
        }
    } else {
        std::cout << "Invalid leave type provided.\n";
    }
}

// Method to add an attendance record for an employee
void Employee::addAttendanceRecord(const AttendanceRecord& record){
    // Add the attendance record to the employee's list of attendance records
    attendanceRecords.push_back(record);
    // Update the total hours worked by adding the hours from the newly added record
    totalHoursWorked += record.getTotalHoursWorked();
}

// Getter method to retrieve attendance records
const std::vector<AttendanceRecord>& Employee::getAttendanceRecords() const {
    return attendanceRecords;
}

// Placeholder for applying leave (no implementation here)
void Employee::applyLeave(std::shared_ptr<Leave> leave) {}

// Placeholder for displaying leave details (no implementation here)
void Employee::displayLeaveDetails() {}

// Method to notify the employee about the leave approval status (currently empty implementation)
void Employee::notifyLeaveApproval(const std::string& status) {}

// Method for the employee to check their leave requests (empty implementation)
void Employee::checkLeaveRequests(std::vector<std::shared_ptr<Leave>>& leaveRequests) {}

// Director class inherits from Employee and overrides some methods
class Director : public Employee {
public:
    // Constructor to initialize Director, calling base Employee constructor
    Director(int id, const std::string& n, const std::string& r = "Employee") : Employee(id, n, r) {}

    // Override applyLeave method for Director's logic of leave approval
    void applyLeave(std::shared_ptr<Leave> leave) override {
        std::cout << "Director reviewing leave request for Employee ID: " << leave->getEmployeeId() << "\n";
        // Check for Earned or Unpaid leave type
        if (leave->getLeaveType() == "Earned" || leave->getLeaveType() == "Unpaid") {
            // If the director has sufficient leave balance, approve the leave
            if (hasSufficientLeave(leave->getLeaveType(), 5)) {
                leave->setStatus("Approved");
                updateLeaveBalance(leave->getLeaveType(), 5); // Deduct the leave days
            } else {
                leave->setStatus("Rejected");  // Reject if insufficient leave balance
            }
        } else {
            leave->setStatus("Rejected"); // Reject if the leave type is not Earned or Unpaid
        }
    }

    // Override displayLeaveDetails to show the director's leave approval details
    void displayLeaveDetails() override {
        std::cout << "Director's leave approval details for Employee ID: " << getEmployeeId() << "\n";
    }

    // Override notifyLeaveApproval to display leave approval status for director
    void notifyLeaveApproval(const std::string& status) override {
        std::cout << "Director has " << status << " the leave request for Employee ID: " << getEmployeeId() << ".\n";
    }

    // Override checkLeaveRequests to allow the director to review and approve/reject pending leave requests
    void checkLeaveRequests(const std::vector<std::shared_ptr<Leave>>& leaveRequests) {
            std::cout << "Pending Leave Requests:\n";
            bool foundPending = false;
            for (const auto& leave : leaveRequests) {
                if (leave->getStatus() == "Pending") {
                    std::cout << "Leave ID: " << leave->getLeaveId()
                              << ", Employee ID: " << leave->getEmployeeId()
                              << ", Type: " << leave->getLeaveType()
                              << ", Start Date: " << leave->getStartDate()
                              << ", End Date: " << leave->getEndDate()
                              << ", Reason: " << leave->getReason()
                              << ", Supervisor Approval: " << leave->getSupervisorApproval()
                              << ", Director Approval: " << leave->getDirectorApproval() << "\n";
                    foundPending = true;
                }
            }   
            if (!foundPending) {
                std::cout << "No pending leave requests found.\n";
            }
        }
    };

// Supervisor class inherits from Employee and overrides some methods
class Supervisor : public Employee {
public:
    // Constructor to initialize Supervisor, calling base Employee constructor
    Supervisor(int id, const std::string& n, const std::string& r) : Employee(id, n, r) {}

    // Override applyLeave method for Supervisor's logic of leave approval
    void applyLeave(std::shared_ptr<Leave> leave) override {
        std::cout << "Supervisor reviewing leave request for Employee ID: " << leave->getEmployeeId() << "\n";
        // Only approve Casual leave if the employee has enough balance
        if (leave->getLeaveType() == "Casual" && hasSufficientLeave("Casual", 2)) {
            leave->setStatus("Approved");
            updateLeaveBalance("Casual", 2); // Deduct the casual leave days
        } else {
            leave->setStatus("Rejected"); // Reject if conditions are not met
        }
    }

    // Override displayLeaveDetails to show the supervisor's leave approval details
    void displayLeaveDetails() override {
        std::cout << "Supervisor's leave approval details for Employee ID: " << getEmployeeId() << "\n";
    }

    // Override notifyLeaveApproval to display leave approval status for supervisor
    void notifyLeaveApproval(const std::string& status) override {
        std::cout << "Supervisor has " << status << " the leave request for Employee ID: " << getEmployeeId() << ".\n";
    }

    // Override checkLeaveRequests to allow the supervisor to review and approve/reject pending leave requests
    void checkLeaveRequests(const std::vector<std::shared_ptr<Leave>>& leaveRequests) {
        std::cout << "Pending Leave Requests:\n";
        bool foundPending = false;
        for (const auto& leave : leaveRequests) {
            if (leave->getStatus() == "Pending") {
                std::cout << "Leave ID: " << leave->getLeaveId()
                          << ", Employee ID: " << leave->getEmployeeId()
                          << ", Type: " << leave->getLeaveType()
                        << ", Start Date: " << leave->getStartDate()
                          << ", End Date: " << leave->getEndDate()
                          << ", Reason: " << leave->getReason()
                          << ", Supervisor Approval: " << leave->getSupervisorApproval()
                          << ", Director Approval: " << leave->getDirectorApproval() << "\n";
                foundPending = true;
            }
        }
        if (!foundPending) {
            std::cout << "No pending leave requests found.\n";
        }
    }
};

// Method to read employee data from file and populate the employee vector
void FileHandler::readEmployeeData(std::vector<std::shared_ptr<Employee>>& employees) {
    std::ifstream file(employeeFile);  // Open the employee data file
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open employee data file for reading.\n";
        return;  // Exit if file cannot be opened
    }

    std::string line;
    while (std::getline(file, line)) {  // Read each line from the file
        try {
            std::stringstream ss(line);  // Use stringstream for line parsing
            int id;
            std::string name, role, temp;
            float totalHours = 0.0;
            int casualLeaves = 0, earnedLeaves = 0;

            // Parse and validate the fields from the line
            if (!std::getline(ss, temp, '|') || temp.empty()) throw std::invalid_argument("Invalid Employee ID");
            id = std::stoi(temp);

            if (!std::getline(ss, name, '|') || name.empty()) throw std::invalid_argument("Invalid Name");
            if (!std::getline(ss, role, '|') || role.empty()) throw std::invalid_argument("Invalid Role");

            if (!std::getline(ss, temp, '|') || temp.empty()) throw std::invalid_argument("Invalid Total Hours");
            totalHours = std::stof(temp);

            if (!std::getline(ss, temp, '|') || temp.empty()) throw std::invalid_argument("Invalid Casual Leaves");
            casualLeaves = std::stoi(temp);

            if (!std::getline(ss, temp, '|') || temp.empty()) throw std::invalid_argument("Invalid Earned Leaves");
            earnedLeaves = std::stoi(temp);

            // Create the employee object based on role (Supervisor, Director, or Employee)
            std::shared_ptr<Employee> emp;
            if (role == "Supervisor") {
                emp = std::make_shared<Supervisor>(id, name, role);
            } else if (role == "Director") {
                emp = std::make_shared<Director>(id, name, role);
            } else {
                emp = std::make_shared<Employee>(id, name, role);
            }

            // Set additional employee attributes and add them to the list
            emp->setTotalHoursWorked(totalHours);
            emp->setCasualLeaveBalance(casualLeaves);
            emp->setEarnedLeaveBalance(earnedLeaves);

            employees.push_back(emp);
        } catch (const std::exception& e) {
            std::cerr << "Error processing line: " << line << " - " << e.what() << '\n';
        }
    }

    file.close();  // Close the file after reading
}

// Method to write employee data to the file
void FileHandler::writeEmployeeData(const Employee& employee) {
    // Open the employee data file in append mode to add new data
    std::ofstream file(employeeFile, std::ios::app); 
    if (!file.is_open()) {  // Check if the file was opened successfully
        std::cerr << "Error: Unable to open employee file for writing.\n";
        return;  // Exit if the file cannot be opened
    }

    try {
        // Write employee details into the file, separated by '|'
        file << employee.getEmployeeId() << "|"
             << employee.getName() << "|"
             << employee.getRole() << "|"
             << employee.getTotalHoursWorked() << "|"
             << employee.getCasualLeaveBalance() << "|"
             << employee.getEarnedLeaveBalance() << "\n";
    } catch (const std::exception& e) {  // Catch any exceptions during the write process
        std::cerr << "Error writing employee data: " << e.what() << "\n";
    }

    file.close();  // Close the file after writing
}

// Method to update employee data in the file
void FileHandler::updateEmployeeData(const Employee& employee) {
    // Open the employee file for reading and a temporary file for writing updated data
    std::ifstream file(employeeFile);
    std::ofstream tempFile("temp_employees.txt");
    std::string line;
    bool recordUpdated = false;

    if (!file.is_open() || !tempFile.is_open()) {  // Check if both files are opened
        std::cerr << "Error: Unable to open employee file for updating.\n";
        return;  // Exit if the files cannot be opened
    }

    // Read the original file line by line
    while (std::getline(file, line)) {
        try {
            std::stringstream ss(line);
            int id;
            std::string temp;

            // Parse Employee ID from the line
            if (!std::getline(ss, temp, '|') || temp.empty()) throw std::invalid_argument("Invalid Employee ID");
            id = std::stoi(temp);

            // If the Employee ID matches, update the record
            if (id == employee.getEmployeeId()) {
                tempFile << employee.getEmployeeId() << "|"
                         << employee.getName() << "|"
                         << employee.getRole() << "|"
                         << employee.getTotalHoursWorked() << "|"
                         << employee.getCasualLeaveBalance() << "|"
                         << employee.getEarnedLeaveBalance() << "\n";
                recordUpdated = true;
            } else {
                // Copy unchanged line to the temporary file
                tempFile << line << "\n";
            }
        } catch (const std::exception& e) {  // Catch exceptions while processing the line
            std::cerr << "Error processing line: " << line << " - " << e.what() << "\n";
            tempFile << line << "\n";  // Preserve the original line in case of error
        }
    }

    file.close();
    tempFile.close();

    // If a record was updated, replace the original file with the temporary one
    if (recordUpdated) {
        if (remove(employeeFile.c_str()) != 0 || rename("temp_employees.txt", employeeFile.c_str()) != 0) {
            std::cerr << "Error: Unable to replace the employee file with updated data.\n";
        } else {
            std::cout << "Employee data updated for ID " << employee.getEmployeeId() << ".\n";
        }
    } else {
        std::cerr << "Employee ID " << employee.getEmployeeId() << " not found. No changes made.\n";
        remove("temp_employees.txt"); // Clean up temporary file if no record was updated
    }
}

// Method to read attendance data from the file and store it in attendanceRecords vector
void FileHandler::readAttendanceData(std::vector<AttendanceRecord>& attendanceRecords) {
    // Open the attendance data file for reading
    std::ifstream file(attendanceFile);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open attendance data file for reading.\n";
        return;  // Exit if the file cannot be opened
    }

    std::string line;
    while (std::getline(file, line)) {  // Read the file line by line
        try {
            std::stringstream ss(line);
            int empId;
            std::string date;
            float hoursWorked;

            std::string temp;

            // Parse Employee ID from the line
            if (!std::getline(ss, temp, '|') || temp.empty()) 
                throw std::invalid_argument("Missing or invalid Employee ID");
            empId = std::stoi(temp);

            // Parse Date from the line
            if (!std::getline(ss, date, '|') || date.empty()) 
                throw std::invalid_argument("Missing or invalid Date");

            // Parse Hours Worked from the line
            if (!std::getline(ss, temp, '|') || temp.empty()) 
                throw std::invalid_argument("Missing or invalid Hours Worked");
            hoursWorked = std::stof(temp);

            // Check if an attendance record already exists for this employee
            auto it = std::find_if(attendanceRecords.begin(), attendanceRecords.end(),
                                   [empId](const AttendanceRecord& record) {
                                       return record.getEmployeeId() == empId;
                                   });

            // If found, add the new attendance to the existing record
            if (it != attendanceRecords.end()) {
                it->addAttendance(date, hoursWorked);
            } else {
                // If not found, create a new record and add to the vector
                AttendanceRecord newRecord(empId);
                newRecord.addAttendance(date, hoursWorked);
                attendanceRecords.push_back(newRecord);
            }
        } catch (const std::exception& e) {
            std::cerr << "Error processing line: " << line << " - " << e.what() << '\n';
        }
    }

    file.close();
    std::cout << "Attendance data loaded successfully.\n";
}

// Method to write attendance data to the file
void FileHandler::writeAttendanceData(const AttendanceRecord& record) {
    // If no attendance records exist for the employee, print a warning and return
    if (record.getRecords().empty()) {
        std::cerr << "No attendance records to write for Employee ID " << record.getEmployeeId() << ".\n";
        return;
    }

    // Open the attendance file in append mode
    std::ofstream file(attendanceFile, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open attendance file for writing.\n";
        return;  // Exit if the file cannot be opened
    }

    try {
        // Write each attendance record to the file
        for (const auto& attendance : record.getRecords()) {
            file << record.getEmployeeId() << "|"
                 << attendance.getDate() << "|"
                 << attendance.getHoursWorked() << "\n";
        }
    } catch (const std::exception& e) {  // Catch any exceptions during writing
        std::cerr << "Error writing attendance data: " << e.what() << "\n";
    }

    file.close();
}

// Method to read leave data from the file and store it in the leaveRecords vector
void FileHandler::readLeaveData(std::vector<std::shared_ptr<Leave>>& leaveRecords) {
    // Open the leave data file for reading
    std::ifstream file(leaveFile);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open leave data file for reading.\n";
        return;  // Exit if the file cannot be opened
    }

    std::string line;
    while (std::getline(file, line)) {  // Read the file line by line
        try {
            std::stringstream ss(line);
            int id, empId;
            std::string type, startDate, endDate, reason, status, supervisorApproval, directorApproval, temp;

            // Parse Leave ID from the line
            if (!std::getline(ss, temp, '|') || temp.empty()) throw std::invalid_argument("Invalid Leave ID");
            id = std::stoi(temp);

            // Parse Employee ID from the line
            if (!std::getline(ss, temp, '|') || temp.empty()) throw std::invalid_argument("Invalid Employee ID");
            empId = std::stoi(temp);

            // Parse other details from the line
            if (!std::getline(ss, type, '|') || type.empty()) throw std::invalid_argument("Invalid Leave Type");
            if (!std::getline(ss, startDate, '|') || startDate.empty()) throw std::invalid_argument("Invalid Start Date");
            if (!std::getline(ss, endDate, '|') || endDate.empty()) throw std::invalid_argument("Invalid End Date");
            if (!std::getline(ss, reason, '|') || reason.empty()) throw std::invalid_argument("Invalid Reason");
            if (!std::getline(ss, status, '|') || status.empty()) throw std::invalid_argument("Invalid Status");
            std::getline(ss, supervisorApproval, '|');
            std::getline(ss, directorApproval, '|');

            // Create the appropriate leave object using the LeaveFactory
            auto leave = LeaveFactory::createLeave(type, empId, startDate, endDate, reason);
            if (!leave) throw std::runtime_error("Failed to create Leave object");

            // Set the leave object attributes and add to the leaveRecords vector
            leave->setStatus(status);
            leave->setSupervisorApproval(supervisorApproval);
            leave->setDirectorApproval(directorApproval);

            leaveRecords.push_back(leave);
        } catch (const std::exception& e) {
            std::cerr << "Error processing line: " << line << " - " << e.what() << '\n';
        }
    }

    file.close();
}
// Method to update the status of a leave request in the leave data file
void FileHandler::updateLeaveStatus(int leaveId, const std::string& newStatus) {
    // Open the leave data file for reading and a temporary file for writing updated data
    std::ifstream file(leaveFile);
    std::ofstream tempFile("temp_leaves.txt");
    std::string line;
    bool leaveUpdated = false;  // Flag to track if a leave request is updated

    // Check if both files are opened successfully
    if (!file.is_open() || !tempFile.is_open()) {
        std::cerr << "Error: Unable to open leave file for updating.\n";
        return;  // Exit if files cannot be opened
    }

    // Read the leave data file line by line
    while (std::getline(file, line)) {
        try {
            std::stringstream ss(line);
            int id;
            std::string type, startDate, endDate, reason, status, supervisorApproval, directorApproval, temp;

            // Parse the Leave ID from the line and handle invalid data
            if (!std::getline(ss, temp, '|') || temp.empty()) throw std::invalid_argument("Invalid Leave ID");
            id = std::stoi(temp);

            // Parse other details like leave type, dates, reason, etc.
            std::getline(ss, type, '|');
            std::getline(ss, startDate, '|');
            std::getline(ss, endDate, '|');
            std::getline(ss, reason, '|');
            std::getline(ss, status, '|');
            std::getline(ss, supervisorApproval, '|');
            std::getline(ss, directorApproval, '|');

            // If the Leave ID matches the given leaveId, update the status
            if (id == leaveId) {
                status = newStatus;
                leaveUpdated = true;  // Mark that the leave was updated
            }

            // Write the updated or unchanged line to the temporary file
            tempFile << id << "|" << type << "|" << startDate << "|" << endDate << "|"
                     << reason << "|" << status << "|" << supervisorApproval << "|" << directorApproval << "\n";
        } catch (const std::exception& e) {  // Catch any exceptions and log errors
            std::cerr << "Error processing line: " << line << " - " << e.what() << "\n";
            tempFile << line << "\n";  // Preserve the original line in case of error
        }
    }

    file.close();
    tempFile.close();

    // If a leave was updated, replace the original file with the temporary one
    if (leaveUpdated) {
        if (remove(leaveFile.c_str()) != 0 || rename("temp_leaves.txt", leaveFile.c_str()) != 0) {
            std::cerr << "Error: Unable to replace the leave file with updated data.\n";
        } else {
            std::cout << "Leave status updated for Leave ID " << leaveId << ".\n";
        }
    } else {
        // If leave ID was not found, notify and clean up the temporary file
        std::cerr << "Leave ID " << leaveId << " not found. No changes made.\n";
        remove("temp_leaves.txt"); // Clean up temporary file
    }
}

// Method to update leave data in the file
void FileHandler:: updateLeaveData(const Leave& leave) {
    // Open the leave data file for reading and a temporary file for writing updated data
    std::ifstream file("Leaves.txt");
    std::ofstream tempFile("temp_leaves.txt");
    std::string line;
    bool leaveUpdated = false;

    if (!file.is_open() || !tempFile.is_open()) {
        std::cerr << "Error: Unable to open leave file for updating.\n";
        return;
    }

    // Read the original file line by line
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        int id;
        std::string temp;

        // Parse Leave ID from the line
        if (!std::getline(ss, temp, '|') || temp.empty()) continue;
        id = std::stoi(temp);

     // If the Leave ID matches, update the record
        if (id == leave.getLeaveId()) {
            tempFile << leave.getLeaveId() << "|"
                     << leave.getEmployeeId() << "|"
                     << leave.getLeaveType() << "|"
                     << leave.getStartDate() << "|"
                     << leave.getEndDate() << "|"
                     << leave.getReason() << "|"
                     << leave.getStatus() << "|"
                     << leave.getSupervisorApproval() << "|"
                     << leave.getDirectorApproval() << "\n";
            leaveUpdated = true;
        } else {
            // Copy unchanged line to the temporary file
            tempFile << line << "\n";
        }
    }

    file.close();
    tempFile.close();

    // If a leave was updated, replace the original file with the temporary one
    if (leaveUpdated) {
//method to write leave data to the file
if (remove("Leaves.txt") != 0 || rename("temp_leaves.txt", "Leaves.txt") != 0) {
            std::cerr << "Error: Unable to replace the leave file with updated data.\n";
        } else {
            std::cout << "Leave data updated for Leave ID " << leave.getLeaveId() << ".\n";
        }
    } else {
        std::cerr << "Leave ID " << leave.getLeaveId() << " not found. No changes made.\n";
        remove("temp_leaves.txt"); // Clean up temporary file if no record was updated
    }
}

void FileHandler::writeLeaveData(const Leave& leave) {
    // Open the leave file in append mode to add new leave data
    std::ofstream file("Leaves.txt", std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open leave file for writing.\n";
        return;  // Exit if file cannot be opened
    }

    try {
        // Write leave details to the file in the specified format
        file << leave.getLeaveId() << "|"
             << leave.getEmployeeId() << "|"
             << leave.getLeaveType() << "|"
             << leave.getStartDate() << "|"
             << leave.getEndDate() << "|"
             << leave.getReason() << "|"
             << leave.getStatus() << "|"
             << leave.getSupervisorApproval() << "|"
             << leave.getDirectorApproval() << "\n";  // Ensure newline character is added
        std::cout << "Leave data written to file successfully.\n";  // Debugging statement
    } catch (const std::exception& e) {
        std::cerr << "Error writing leave data: " << e.what() << "\n";
    }

    file.close();  // Close the file after writing
}
class ReportManager {
private:
    std::vector<std::unique_ptr<Reportable>> reports;  // A container to store various report objects

public:
    // Method to add a report dynamically to the list of reports
    void addReport(std::unique_ptr<Reportable> newReport) {
        reports.push_back(std::move(newReport));  // Move the report into the vector (ownership transferred)
    }

    // Method to generate all selected reports in the 'reports' list
    void generateReports() {
        if (!reports.empty()) {
            for (auto& report : reports) {  // Loop through all the reports
                report->generateReport();  // Call the generateReport method of each report
            }
        } else {
            std::cout << "No report type selected.\n";  // If no reports are added, notify the user
        }
    }
};

class LeaveReport : public Reportable {
private:
    std::vector<Leave*> leaveRequests;  // For unapproved leave requests
    std::vector<Leave*> leaveHistory;  // For employee leave details report

public:
    // Constructor to initialize leave requests and leave history (defaults to empty)
    LeaveReport(const std::vector<Leave*>& requests = {}, const std::vector<Leave*>& history = {})
        : leaveRequests(requests), leaveHistory(history) {}

    // Add leave request for unapproved leave reporting
    void addLeaveRequest(Leave* leave) {
        leaveRequests.push_back(leave);
    }

    // Add leave history for employee leave details reporting
    void addLeaveHistory(Leave* leave) {
        leaveHistory.push_back(leave);
    }

    // Generate report for unapproved leaves
    void generateUnapprovedLeaveReport() {
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

    // Generate leave details report
    void generateEmployeeLeaveDetailsReport() {
        std::cout << "Leave Details Report\n";
        for (const auto& leave : leaveHistory) {
            leave->displayLeaveSummary();  // Display details of each leave
        }
    }

    // Interface implementation for Reportable (generated by ReportManager)
    void generateReport() override {
        std::cout << "Leave Report: This is a combined report class. Call specific report methods as needed.\n";
    }
};

class OutstandingLeaveReport : public Reportable {
private:
    std::vector<Leave*> leaveRequests;  // Store leave requests for pending leaves

public:
    // Constructor to initialize with leave requests
    OutstandingLeaveReport(const std::vector<Leave*>& requests) : leaveRequests(requests) {}

    // Generate the outstanding leave report (pending leaves)
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

class HoursReport : public Reportable {
private:
    std::vector<AttendanceRecord> attendanceRecords;  // Store attendance records for employees
    float requiredPercentage;  // The attendance percentage threshold for the report

public:
    // Constructor to initialize with attendance records and required percentage
    HoursReport(const std::vector<AttendanceRecord>& records, float percentage)
        : attendanceRecords(records), requiredPercentage(percentage) {}

    // Generate the hours report for employees who have worked less than the required percentage
    void generateReport() override {
        const int totalExpectedHours = 40 * 4;  // 40 hours/week * 4 weeks
        std::cout << "Hours Report (Threshold: " << requiredPercentage << "%)\n";
        for (const auto& record : attendanceRecords) {
            float totalHours = record.getTotalHoursWorked();
            float percentage = (totalHours / totalExpectedHours) * 100;

            // Display report for employees whose attendance percentage is below the threshold
            if (percentage < requiredPercentage) {
                std::cout << "Employee ID: " << record.getRecords().front().getHoursWorked()
                          << ", Total Hours: " << totalHours << " (" << percentage << "%)\n";
            }
        }
    }
};

// Utility function to validate user input for choosing options
int getValidatedChoice(int min, int max) {
    int choice;
    while (true) {
        std::cin >> choice;  // Read user input
        if (std::cin.fail() || choice < min || choice > max) {  // Check for invalid input
            std::cin.clear();          // Clear input stream
            std::cin.ignore(1000, '\n'); // Ignore invalid input
            std::cout << "Invalid choice. Please try again: ";
        } else {
            return choice;  // Return valid choice
        }
    }
}

// Function to display a report with low attendance than the threshold
void showLowAttendanceReport(const std::vector<std::shared_ptr<Employee>>& employees) {
    const int thresholdHours = 40; // Set the threshold hours for low attendance
    std::cout << "Low Attendance Report (Threshold: " << thresholdHours << " hours)\n";

    for (const auto& employee : employees) {
        float totalHours = employee->getTotalHoursWorked();
        
        if (totalHours < thresholdHours) {
            std::cout << "Employee ID: " << employee->getEmployeeId() << "\n";
            std::cout << "Name: " << employee->getName() << "\n";
            std::cout << "Role: " << employee->getRole() << "\n";
            std::cout << "Total Hours Worked: " << totalHours << "\n";
            std::cout << "Attendance Records:\n";
            const auto& records = employee->getAttendanceRecords();
            
            for (const auto& record : records) {
                record.displayAllAttendance();
            }
            std::cout << "-----------------------------------\n";
        }
    }
}

// Function to display the outstanding leave report
void showOutstandingLeaveReport(const std::vector<std::shared_ptr<Leave>>& leaveRequests) {
    std::vector<Leave*> rawLeaveRequests;
    for (const auto& leave : leaveRequests) {
        rawLeaveRequests.push_back(leave.get());
    }
    OutstandingLeaveReport report(rawLeaveRequests);
    report.generateReport();
}

// Function to display the attendance details for a given employee
void showEmployeeAttendanceDetails(const std::vector<std::shared_ptr<Employee>>& employees) {
    int empId;
    std::cout << "Enter Employee ID: ";
    std::cin >> empId;

    auto employee = std::find_if(employees.begin(), employees.end(),
                                 [empId](const std::shared_ptr<Employee>& emp) {
                                     return emp->getEmployeeId() == empId;
                                 });

    if (employee != employees.end()) {
        (*employee)->generateAttendanceReport();
    } else {
        std::cout << "Error: Employee ID " << empId << " not found.\n";
    }
}

// Function to show leave details for a specific employee
void showEmployeeLeaveDetails(const std::vector<std::shared_ptr<Employee>>& employees) {
    int empId;
    std::cout << "Enter Employee ID: ";
    std::cin >> empId;

    auto employee = std::find_if(employees.begin(), employees.end(),
                                 [empId](const std::shared_ptr<Employee>& emp) {
                                     return emp->getEmployeeId() == empId;
                                 });

    if (employee != employees.end()) {
        (*employee)->generateLeaveReport();
    } else {
        std::cout << "Error: Employee ID " << empId << " not found.\n";
    }
}

// Function to display the reports menu
void generateReportsMenu(const std::vector<std::shared_ptr<Employee>>& employees, const std::vector<std::shared_ptr<Leave>>& leaveRequests) {
    int option;
    do {
        std::cout << "\n--- Reports Menu ---" << std::endl;
        std::cout << "1. Show employees with attendance less than a given percentage\n";
        std::cout << "2. Show employees with outstanding leaves\n";
        std::cout << "3. Show attendance details for a given employee\n";
        std::cout << "4. Show leave details for a given employee\n";
        std::cout << "5. Exit\nEnter your choice: ";

        option = getValidatedChoice(1, 5);

        switch (option) {
            case 1:
                showLowAttendanceReport(employees);
                break;
            case 2:
                showOutstandingLeaveReport(leaveRequests);
                break;
            case 3:
                showEmployeeAttendanceDetails(employees);
                break;
            case 4:
                showEmployeeLeaveDetails(employees);
                break;
            case 5:
                std::cout << "Exiting Reports Menu..." << std::endl;
                break;
        }
    } while (option != 5);
}

// Function to mark attendance for an employee
void markAttendance(std::vector<std::shared_ptr<Employee>>& employees) {
    int empId;
    std::string date;
    float hours;

    std::cout << "Enter Employee ID: ";
    std::cin >> empId;
    std::cout << "Enter Date (YYYY-MM-DD): ";
    std::cin >> date;
    std::cout << "Enter Hours Worked: ";
    std::cin >> hours;

    // Find the employee by ID
    auto employee = std::find_if(employees.begin(), employees.end(),
                                 [empId](const std::shared_ptr<Employee>& emp) {
                                     return emp->getEmployeeId() == empId;
                                 });

    if (employee != employees.end()) {
        AttendanceRecord record(empId);
        record.addAttendance(date, hours);
        (*employee)->addAttendanceRecord(record);

        // Save the attendance to the file using FileHandler
        try {
            FileHandler::writeAttendanceData(record);
            std::cout << "Attendance marked successfully.\n";
        } catch (const std::exception& e) {
            std::cerr << "Error saving attendance data: " << e.what() << "\n";
        }
    } else {
        std::cout << "Error: Employee ID " << empId << " not found.\n";
    }
}

// Function to display Employee Menu
void displayEmployeeMenu(const std::shared_ptr<Employee>& employee) {
    int option;
    do {
        // Display the Employee Menu options
        std::cout << "\n--- Employee Menu ---" << std::endl;
        std::cout << "1. View Attendance Details\n2. Request Leave\n3. View Leave Status\n4. View Leave Report\n5. Exit\nEnter your choice: ";
        
        // Get a validated choice from the user (ensures input is between 1 and 5)
        option = getValidatedChoice(1, 5);

        switch (option) {
            case 1:
                // Generate and display the attendance report
                employee->generateAttendanceReport();
                break;
            case 2: {
                // Collect leave request details from the employee
                std::string leaveType, startDate, endDate, reason;
                std::cout << "Enter Leave Type (Casual/Earned/Official/Unpaid): ";
                std::cin >> leaveType;
                std::cout << "Enter Start Date (YYYY-MM-DD): ";
                std::cin >> startDate;
                std::cout << "Enter End Date (YYYY-MM-DD): ";
                std::cin >> endDate;
                std::cout << "Enter Reason for Leave: ";
                std::cin.ignore(); // To clear the newline character from input buffer
                std::getline(std::cin, reason);

                // Request the leave
                employee->requestLeave(leaveType, startDate, endDate, reason);
                break;
            }
            case 3: {
                // Check the status of a leave by its ID
                int leaveId;
                std::cout << "Enter Leave ID to check status: ";
                std::cin >> leaveId;
                employee->checkLeaveStatus(leaveId);
                break;
            }
            case 4:
                // Generate and display the leave report
                employee->generateLeaveReport();
                break;
            case 5:
                // Exit the Employee Menu
                std::cout << "Exiting Employee Menu..." << std::endl;
                break;
        }
    } while (option != 5); // Continue showing the menu until option 5 (Exit) is selected
}

// Function to display Supervisor Menu

void displaySupervisorMenu(Supervisor& supervisor, std::vector<std::shared_ptr<Leave>>& leaveRequests) {
    int option;
    do {
        // Display Supervisor Menu options
        std::cout << "\n--- Supervisor Menu ---" << std::endl;
        std::cout << "1. View Pending Leave Requests\n2. Approve/Reject Leave\n3. Exit\nEnter your choice: ";
        
        // Get a validated choice from the user (ensures input is between 1 and 3)
        option = getValidatedChoice(1, 3);

        switch (option) {
            case 1:
                // Supervisor checks pending leave requests
                supervisor.checkLeaveRequests(leaveRequests);
                break;
            case 2: {
                // Supervisor approves or rejects leave requests
                int leaveId;
                std::string decision;
                std::cout << "Enter Leave ID to Approve/Reject: ";
                std::cin >> leaveId;
                std::cout << "Enter Decision (Approve/Reject): ";
                std::cin >> decision;

                // Update the leave status based on supervisor's decision
                for (auto& leave : leaveRequests) {
                    if (leave->getLeaveId() == leaveId) {
                        if (decision == "Approve") {
                            leave->setSupervisorApproval("Yes");
                            leave->setStatus("Approved");
                        } else if (decision == "Reject") {
                            leave->setSupervisorApproval("R");
                            leave->setStatus("Rejected");
                        }
                        supervisor.notifyLeaveApproval(decision); // Notify the supervisor's decision
                        FileHandler::updateLeaveData(*leave); // Update the leave data in the file
                        break;
                    }
                }
                break;
            }
            case 3:
                // Exit Supervisor Menu
                std::cout << "Exiting Supervisor Menu..." << std::endl;
                break;
        }
    } while (option != 3); // Continue showing the menu until option 3 (Exit) is selected
}

// Function to display Director Menu
void displayDirectorMenu(Director& director, std::vector<std::shared_ptr<Leave>>& leaveRequests) {
    int option;
    do {
        // Display Director Menu options
        std::cout << "\n--- Director Menu ---" << std::endl;
        std::cout << "1. View Pending Leave Requests\n2. Approve/Reject Leave\n3. Exit\nEnter your choice: ";
        
        // Get a validated choice from the user (ensures input is between 1 and 3)
        option = getValidatedChoice(1, 3);

        switch (option) {
            case 1:
                // Director checks pending leave requests
                director.checkLeaveRequests(leaveRequests);
                break;
            case 2: {
                // Director approves or rejects leave requests
                int leaveId;
                std::string decision;
                std::cout << "Enter Leave ID to Approve/Reject: ";
                std::cin >> leaveId;
                std::cout << "Enter Decision (Approve/Reject): ";
                std::cin >> decision;

                // Update the leave status based on director's decision
                for (auto& leave : leaveRequests) {
                    if (leave->getLeaveId() == leaveId) {
                        if (decision == "Approve") {
                            leave->setDirectorApproval("Yes");
                            if (leave->getSupervisorApproval() == "Yes") {
                                leave->setStatus("Approved");
                            }
                        } else if (decision == "Reject") {
                            leave->setDirectorApproval("R");
                            leave->setStatus("Rejected");
                        }
                        director.notifyLeaveApproval(decision); // Notify the director's decision
                        FileHandler::updateLeaveData(*leave); // Update the leave data in the file
                        break;
                    }
                }
                break;
            }
            case 3:
                // Exit Director Menu
                std::cout << "Exiting Director Menu..." << std::endl;
                break;
        }
    } while (option != 3); // Continue showing the menu until option 3 (Exit) is selected
}

// Main Function
int main() {
    // Load employee and leave data using FileHandler
    std::vector<std::shared_ptr<Employee>> employees;
    std::vector<std::shared_ptr<Leave>> leaveRequests;

    try {
        // Reading employee and leave data from files
        FileHandler::readEmployeeData(employees);
        FileHandler::readLeaveData(leaveRequests);
    } catch (const std::exception& ex) {
        std::cerr << "Error loading data: " << ex.what() << std::endl;
        return 1; // Exit if critical error occurs while loading data
    }
    std::system("cls"); // Clear the console screen
    // Welcome message and role selection menu
    std::cout << "Welcome to Attendance and Leave Management System!" << std::endl;
    std::cout << "Select your role:\n1. Employee\n2. Supervisor\n3. Director\n4. Mark Attendance\n5. Generate Reports\n6. Exit\nEnter your choice: ";
    
    // Get role choice from the user
    int choice = getValidatedChoice(1, 6);

    switch (choice) {
        case 1: { // Employee Role
            int empId;
            std::cout << "Enter your Employee ID: ";
            std::cin >> empId;

            // Find the employee by ID
            auto loggedInEmployee = std::find_if(employees.begin(), employees.end(),
                                                 [empId](const std::shared_ptr<Employee>& emp) {
                                                     return emp->getEmployeeId() == empId;
                                                 });

            // Display menu for the employee if found, otherwise show an error
            if (loggedInEmployee != employees.end()) {
                if ((*loggedInEmployee)->getRole() == "Employee") {
                    displayEmployeeMenu(*loggedInEmployee); // Show employee-specific menu
                }
                else {
                    std::cout << "Error: Invalid role for Employee ID " << empId << std::endl;
                }
            } else {
                std::cout << "Error: Employee not found!" << std::endl;
            }
            break;
        }
        case 2: { // Supervisor Role
            int empId;
            std::cout << "Enter your Employee ID: ";
            std::cin >> empId;

            // Find the supervisor by ID
            auto loggedInSupervisor = std::find_if(employees.begin(), employees.end(),
                                                   [empId](const std::shared_ptr<Employee>& emp) {
                                                       return emp->getEmployeeId() == empId && dynamic_cast<Supervisor*>(emp.get()) != nullptr;
                                                   });

            // Display menu for the supervisor if found, otherwise show an error
            if (loggedInSupervisor != employees.end()) {
                displaySupervisorMenu(*dynamic_cast<Supervisor*>(loggedInSupervisor->get()), leaveRequests);
            } else {
                std::cout << "Error: Supervisor not found!" << std::endl;
            }
            break;
        }
        case 3: { // Director Role
            int empId;
            std::cout << "Enter your Employee ID: ";
            std::cin >> empId;

            // Find the director by ID
            auto loggedInDirector = std::find_if(employees.begin(), employees.end(),
                                                 [empId](const std::shared_ptr<Employee>& emp) {
                                                     return emp->getEmployeeId() == empId && dynamic_cast<Director*>(emp.get()) != nullptr;
                                                 });

            // Display menu for the director if found, otherwise show an error
            if (loggedInDirector != employees.end()) {
                displayDirectorMenu(*dynamic_cast<Director*>(loggedInDirector->get()), leaveRequests);
            } else {
                std::cout << "Error: Director not found!" << std::endl;
            }
            break;
        }
        case 4: { // mark attendance
            markAttendance(employees);
            break;
        }
        case 5: { // generate reports
            generateReportsMenu(employees, leaveRequests);
            break;
        }
        case 6: { // Exit
            std::cout << "Exiting system. Goodbye!" << std::endl;
            return 0; // Exit the program
        }
    }

    return 0; // Main function ends successfully
}
