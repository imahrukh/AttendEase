#include "helper.h"
#include <algorithm>

  // Constructor
Attendance::Attendance(const std::string& date, float hours) : date(date), hoursWorked(hours) {}
    // Getters
const std::string& Attendance:: getDate() const { return date; }
float Attendance:: getHoursWorked() const { return hoursWorked; }

    // Display attendance details
void Attendance:: displayAttendance() const {
    std::cout << "Date: " << date << ", Hours Worked: " << hoursWorked << " hours\n";
}



    // Constructor
AttendanceRecord::AttendanceRecord(int empId): employeeId(empId) {}

    // Add an attendance record
void AttendanceRecord::addAttendance(const std::string& date, float hoursWorked){
    records.emplace_back(date, hoursWorked);
    }

    // Get total hours worked
float AttendanceRecord::getTotalHoursWorked() const {
    float total = 0;
    for (const auto& record : records) {
        total += record.getHoursWorked();
    }
    return total;
}

    // Calculate attendance percentage
float AttendanceRecord::calculateAttendancePercentage(float totalExpectedHours) const{
    return (getTotalHoursWorked() / totalExpectedHours) * 100;
}

    // Display all attendance records
void AttendanceRecord::displayAllAttendance() const{
    std::cout << "Attendance Records for Employee ID: " << employeeId << "\n";
    for (const auto& record : records) {
        record.displayAttendance();
    }
}

    // Getter for the attendance records
const std::vector<Attendance>& AttendanceRecord:: getRecords() const{
    return records;
}

    // Getter for employee ID
int AttendanceRecord::getEmployeeId() const{
    return employeeId;
}

//Constructor
Leave::Leave(int empId, const std::string& type, const std::string& start, const std::string& end, const std::string& reason)
    : employeeId(empId), leaveType(type), startDate(start), endDate(end), reason(reason), status("Pending"),
      supervisorApproval("N/A"), directorApproval("N/A") {
    leaveId = ++leaveIdCounter;
    duration = std::stoi(endDate.substr(8, 2)) - std::stoi(startDate.substr(8, 2)) + 1;
}

    // Getters
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

    // Setters
void Leave:: setStatus(const std::string& newStatus) { status = newStatus; }
void Leave::setSupervisorApproval(const std::string& approval) { supervisorApproval = approval; }
void Leave::setDirectorApproval(const std::string& approval) { directorApproval = approval; }
    
        // Display leave summary
void Leave:: displayLeaveSummary() {
    std::cout << "Leave ID: " << leaveId << ", Type: " << leaveType << ", Status: " << status
              << ", Duration: " << duration << " days, Reason: " << reason
              << ", Supervisor Approval: " << supervisorApproval
              << ", Director Approval: " << directorApproval << "\n";
}

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

Employee::Employee(int id, const std::string& n) : employeeId(id), name(n) {}

    // Getters and Setters
int Employee::getEmployeeId() const { return employeeId; }
const std::string& Employee:: getName() const { return name; }
float Employee::getTotalHoursWorked() const { return totalHoursWorked; }
int Employee::getCasualLeaveBalance() const { return casualLeaveBalance; }
int Employee::getEarnedLeaveBalance() const { return earnedLeaveBalance; }

void Employee::setTotalHoursWorked(float hours) { totalHoursWorked = hours; }
void Employee::setCasualLeaveBalance(int balance) { casualLeaveBalance = balance; }
void Employee::setEarnedLeaveBalance(int balance) { earnedLeaveBalance = balance; }


    // Method to check leave balance
bool Employee::hasSufficientLeave(const std::string& leaveType, int days) {
    if (leaveType == "Casual" && casualLeaveBalance >= days) {
        return true;
    } else if (leaveType == "Earned" && earnedLeaveBalance >= days) {
        return true;
    }
    return false;
}
    
    // Method to update leave balance (used after approval)
void Employee::updateLeaveBalance(const std::string& leaveType, int days){
    if (leaveType == "Casual") {
        casualLeaveBalance -= days;
    } else if (leaveType == "Earned") {
        earnedLeaveBalance -= days;
    }
}


    // Method to check leave status
void Employee::checkLeaveStatus(int leaveId){
    // Loop through leave history and check for the leave ID
    for (auto& leave : leaveHistory) {
        if (leave->getLeaveId() == leaveId) {
            std::cout << "Leave Status for Employee " << getName() << " (Leave ID: " << leaveId << "): "
                      << leave->getStatus() << "\n";
            return;
        }
    }
    std::cout << "Leave not found for Employee " << getName() << " (Leave ID: " << leaveId << ").\n";
}

    // Method to generate leave report
void Employee::generateLeaveReport() {
    std::cout << "Leave Report for Employee: " << name << "\n";
    for (const auto& leave : leaveHistory) {
        std::cout << "Leave Type: " << leave->getLeaveType() 
                  << ", Status: " << leave->getStatus()
                  << ", Duration: " << leave->getDuration() << " days\n";
    }
}

    // Method to generate attendance report
void Employee::generateAttendanceReport(){
    std::cout << "Attendance Report for Employee: " << name << "\n";
    for (const auto& record : attendanceRecords) {
        //std::cout << "Date: " << record.getDate() << ", Hours Worked: " << record.getHoursWorked() << "\n";
    }
}

void Employee::requestLeave(const std::string& leaveType, const std::string& startDate, const std::string& endDate, const std::string& reason){
    int leaveDays = std::stoi(endDate.substr(8, 2)) - std::stoi(startDate.substr(8, 2)) + 1;

        // Check leave balance
    if (!hasSufficientLeave(leaveType, leaveDays)) {
        std::cout << "Insufficient leave balance for " << leaveType << ". Request denied.\n";
        return;
    }

        // Create leave using LeaveFactory
    std::shared_ptr<Leave> newLeave = LeaveFactory::createLeave(leaveType, employeeId, startDate, endDate, reason);

    if (newLeave) {
        leaveHistory.push_back(newLeave);  // Add to leave history

        // Save the leave to the file using FileHandler
        FileHandler::writeLeaveData(*newLeave);
        std::cout << leaveType << " leave request submitted successfully.\n";
    } else {
    std::cout << "Invalid leave type provided.\n";
    }
}

    // Method to add attendance record
void Employee::addAttendanceRecord(const AttendanceRecord& record){
    attendanceRecords.push_back(record);
    totalHoursWorked += record.getTotalHoursWorked();
}
void Employee::applyLeave(std::shared_ptr<Leave> leave) {}
void Employee::displayLeaveDetails(){}

void Employee:: notifyLeaveApproval(const std::string& status){}
void Employee::checkLeaveRequests(std::vector<std::shared_ptr<Leave>>& leaveRequests){}
class Director : public Employee {
public:
    Director(int id, const std::string& n) : Employee(id, n) {}

    void applyLeave(std::shared_ptr<Leave> leave) override {
        std::cout << "Director reviewing leave request for Employee ID: " << leave->getEmployeeId() << "\n";
        if (leave->getLeaveType() == "Earned" || leave->getLeaveType() == "Unpaid") {
            if (hasSufficientLeave(leave->getLeaveType(), 5)) {
                leave->setStatus("Approved");
                updateLeaveBalance(leave->getLeaveType(), 5);
            } else {
                leave->setStatus("Rejected");
            }
        } else {
            leave->setStatus("Rejected");
        }
    }

    void displayLeaveDetails() override {
        std::cout << "Director's leave approval details for Employee ID: " << getEmployeeId() << "\n";
    }

    void notifyLeaveApproval(const std::string& status) override{
        std::cout << "Director has " << status << " the leave request for Employee ID: " << getEmployeeId() << ".\n";
    }

    void checkLeaveRequests(std::vector<std::shared_ptr<Leave>>& leaveRequests) override{
        std::cout << "Director checking leave requests...\n";
        for (auto& leave : leaveRequests) {
            if (leave->getStatus() == "Pending") {
                applyLeave(leave);
            }
        }
    }
};

class Supervisor : public Employee {
public:
    Supervisor(int id, const std::string& n) : Employee(id, n) {}

    void applyLeave(std::shared_ptr<Leave> leave) override {
        std::cout << "Supervisor reviewing leave request for Employee ID: " << leave->getEmployeeId() << "\n";
        if (leave->getLeaveType() == "Casual" && hasSufficientLeave("Casual", 2)) {
            leave->setStatus("Approved");
            updateLeaveBalance("Casual", 2);
        } else {
            leave->setStatus("Rejected");
        }
    }

    void displayLeaveDetails() override{
        std::cout << "Supervisor's leave approval details for Employee ID: " << getEmployeeId() << "\n";
    }

    void notifyLeaveApproval(const std::string& status) override{
        std::cout << "Supervisor has " << status << " the leave request for Employee ID: " << getEmployeeId() << ".\n";
    }

    void checkLeaveRequests(std::vector<std::shared_ptr<Leave>>& leaveRequests) override {
        std::cout << "Supervisor checking leave requests...\n";
        for (auto& leave : leaveRequests) {
            if (leave->getStatus() == "Pending") {
                applyLeave(leave);
            }
        }
    }
};


void FileHandler::readEmployeeData(std::vector<std::shared_ptr<Employee>>& employees) {
    std::ifstream file(employeeFile);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            int id;
            std::string name, role;
            float totalHours;
            int casualLeaves, earnedLeaves;
            
            std::string temp;
            std::getline(ss, temp, '|'); id = std::stoi(temp);
            std::getline(ss, name, '|');
            std::getline(ss, temp, '|'); totalHours = std::stof(temp);
            std::getline(ss, temp, '|'); casualLeaves = std::stoi(temp);
            std::getline(ss, temp, '|'); earnedLeaves = std::stoi(temp);
            std::getline(ss, role, '|');

            std::shared_ptr<Employee> emp;
            if (role == "Supervisor") {
                emp = std::make_shared<Supervisor>(id, name);
            } else if (role == "Director") {
                emp = std::make_shared<Director>(id, name);
            } else {
                emp = std::make_shared<Employee>(id, name);  // default Employee class
            }

            emp->setTotalHoursWorked(totalHours);
            emp->setCasualLeaveBalance(casualLeaves);
            emp->setEarnedLeaveBalance(earnedLeaves);
            employees.push_back(emp);
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to open employee data file for reading.\n";
    }
}

void FileHandler::writeEmployeeData(const Employee& employee) {
    std::ofstream file(employeeFile, std::ios::app); // Open the file in append mode
    if (file.is_open()) {
        // Write the employee data in the specified format
        file << employee.getEmployeeId() << "|" 
             << employee.getName() << "|"
             << employee.getTotalHoursWorked() << "|"
             << employee.getCasualLeaveBalance() << "|"
             << employee.getEarnedLeaveBalance() << "\n";
        file.close();
        std::cout << "Employee data written successfully.\n";
    } else {
        std::cerr << "Error: Unable to open the employee file for writing.\n";
    }
}

void FileHandler::readAttendanceData(std::vector<AttendanceRecord>& attendanceRecords, int employeeId) {
    std::ifstream file(attendanceFile);
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            std::stringstream ss(line);
            int empId;
            std::string date;
            float hoursWorked;

            std::string temp;
            getline(ss, temp, '|'); empId = std::stoi(temp);  // Get Employee ID
            if (empId == employeeId) {  // Check if the employee ID matches
                getline(ss, date, '|');
                getline(ss, temp, '|'); hoursWorked = std::stof(temp);

                // Find the corresponding AttendanceRecord for the employeeId
                bool employeeFound = false;
                for (auto& record : attendanceRecords) {
                    if (record.getEmployeeId() == employeeId) {
                        record.addAttendance(date, hoursWorked);  // Add attendance record
                        employeeFound = true;
                        break;
                    }
                }

                // If employee not found, create a new record for the employee
                if (!employeeFound) {
                    AttendanceRecord newRecord(employeeId);
                    newRecord.addAttendance(date, hoursWorked);
                    attendanceRecords.push_back(newRecord);
                }
            }
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to open attendance data file for reading.\n";
    }
}

void FileHandler::writeAttendanceData(const AttendanceRecord& record) {
    std::ofstream file(attendanceFile, std::ios::app);
    if (file.is_open()) {
        for (const auto& attendance : record.getRecords()) {
            file << record.getEmployeeId() << "|" << attendance.getDate() << "|" << attendance.getHoursWorked() << "\n";
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to open attendance file for writing.\n";
    }
}

void FileHandler::readLeaveData(std::vector<std::shared_ptr<Leave>>& leaveRecords) {
    std::ifstream file(leaveFile);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            int id;
            int empId;
            std::string type, startDate, endDate, reason, status, supervisorApproval, directorApproval;

            // Declare 'temp' to temporarily store each field
            std::string temp;

            // Read the data for each field
            std::getline(ss, temp, '|'); id = std::stoi(temp);  // Read ID and convert to integer
            std::getline(ss, temp, '|'); empId = std::stoi(temp);  // Read employee ID and convert to integer
            std::getline(ss, type, '|');  // Read leave type
            std::getline(ss, startDate, '|');  // Read start date
            std::getline(ss, endDate, '|');  // Read end date
            std::getline(ss, reason, '|');  // Read reason
            std::getline(ss, status, '|');  // Read status
            std::getline(ss, supervisorApproval, '|');  // Read supervisor approval status
            std::getline(ss, directorApproval, '|');  // Read director approval status

                // Create the appropriate leave object using the LeaveFactory
            std::shared_ptr<Leave> leave = LeaveFactory::createLeave(type, empId, startDate, endDate, reason);
            leave->setStatus(status);  // Set the status
            leave->setSupervisorApproval(supervisorApproval);  // Set supervisor approval
            leave->setDirectorApproval(directorApproval);  // Set director approval

            leaveRecords.push_back(leave);  // Add the leave object to the records vector
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to open leave data file for reading.\n";
    }
}

void FileHandler::writeLeaveData(const Leave& leave) {
    std::ofstream file(leaveFile, std::ios::app);
    if (file.is_open()) {
        file << leave.getEmployeeId() << "|" << leave.getLeaveType() << "|"
             << leave.getStartDate() << "|" << leave.getEndDate() << "|"
             << leave.getReason() << "|" << leave.getStatus() << "\n";
        file.close();
    } else {
        std::cerr << "Error: Unable to open leave file for writing.\n";
    }
}

void FileHandler::updateLeaveStatus(int leaveId, const std::string& newStatus) {
    std::ifstream file(leaveFile);
    std::ofstream tempFile("temp.txt");
    std::string line;

    if (file.is_open() && tempFile.is_open()) {
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            int id;
            std::string type, startDate, endDate, reason, status, supervisorApproval, directorApproval;

            std::string temp;
            std::getline(ss, temp, '|'); id = std::stoi(temp);  // Read ID and convert to integer
            std::getline(ss, type, '|');  // Read leave type
            std::getline(ss, startDate, '|');  // Read start date
            std::getline(ss, endDate, '|');  // Read end date
            std::getline(ss, reason, '|');  // Read reason
            std::getline(ss, status, '|');  // Read status
            std::getline(ss, supervisorApproval, '|');  // Read supervisor approval
            std::getline(ss, directorApproval, '|');  // Read director approval

                // Update the status if the leave matches the provided leaveId
            if (id == leaveId) {
                status = newStatus;  // Update the status
            }

                // Write the updated data back to the temporary file
            tempFile << id << "|" << type << "|" << startDate << "|" << endDate << "|" << reason << "|" 
                     << status << "|" << supervisorApproval << "|" << directorApproval << "\n";
        }
        file.close();
        tempFile.close();

            // Rename the temporary file to replace the old file
        remove(leaveFile.c_str());
        rename("temp.txt", leaveFile.c_str());
    } else {
        std::cerr << "Error: Unable to open leave data file for updating.\n";
    }
}

void FileHandler::updateAttendanceData(int employeeId, const AttendanceRecord& record) {
    std::ifstream file(attendanceFile);
    std::ofstream tempFile("temp.txt");
    std::string line;

    if (file.is_open() && tempFile.is_open()) {
        while (getline(file, line)) {
            std::stringstream ss(line);
            int empId;
            std::string date;
            float hoursWorked;

            std::string temp;
            getline(ss, temp, '|'); empId = std::stoi(temp);
            getline(ss, date, '|');
            getline(ss, temp, '|'); hoursWorked = std::stof(temp);

                // If the employee ID matches and we are updating their attendance, modify the record
            if (empId == employeeId) {
                for (const auto& attendance : record.getRecords()) {
                    if (attendance.getDate() == date) {
                        hoursWorked = attendance.getHoursWorked();  // Update the hours worked
                    }
                }
            }

            // Write the updated or unchanged attendance record to the temp file
            tempFile << empId << "|" << date << "|" << hoursWorked << "\n";
        }
        file.close();
        tempFile.close();

            // Replace the original file with the updated file
        remove(attendanceFile.c_str());
        rename("temp.txt", attendanceFile.c_str());
    } else {
        std::cerr << "Error: Unable to open attendance data file for reading or writing.\n";
    }
}

class ReportManager {
private:
    std::vector<std::unique_ptr<Reportable>> reports;  // To store multiple report types

public:
    // Set the report type dynamically (this is now flexible for multiple reports)
    void addReport(std::unique_ptr<Reportable> newReport) {
        reports.push_back(std::move(newReport));
    }

    // Generate all selected reports
    void generateReports() {
        if (!reports.empty()) {
            for (auto& report : reports) {
                report->generateReport();
            }
        } else {
            std::cout << "No report type selected.\n";
        }
    }
};

class LeaveReport : public Reportable {
private:
    std::vector<Leave*> leaveRequests;  // For unapproved leave report
    std::vector<Leave*> leaveHistory;  // For employee leave details report

public:
    // Constructor
    LeaveReport(const std::vector<Leave*>& requests = {}, const std::vector<Leave*>& history = {})
        : leaveRequests(requests), leaveHistory(history) {}

    // Add leave request for unapproved leave reporting
    void addLeaveRequest(Leave* leave) {
        leaveRequests.push_back(leave);
    }

    // Add leave history for employee leave details
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
            leave->displayLeaveSummary();
        }
    }

    // Interface implementation for Reportable
    void generateReport() override {
        std::cout << "Leave Report: This is a combined report class. Call specific report methods as needed.\n";
    }
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

class HoursReport : public Reportable {
private:
    std::vector<AttendanceRecord> attendanceRecords;
    float requiredPercentage;

public:
    // Constructor
    HoursReport(const std::vector<AttendanceRecord>& records, float percentage)
        : attendanceRecords(records), requiredPercentage(percentage) {}

    // Generate report for employees with low hours
    void generateReport() override {
        const int totalExpectedHours = 40 * 4;  // 40 hours/week * 4 weeks
        std::cout << "Hours Report (Threshold: " << requiredPercentage << "%)\n";
        for (const auto& record : attendanceRecords) {
            float totalHours = record.getTotalHoursWorked();
            float percentage = (totalHours / totalExpectedHours) * 100;

            if (percentage < requiredPercentage) {
                std::cout << "Employee ID: " << record.getRecords().front().getHoursWorked()
                          << ", Total Hours: " << totalHours << " (" << percentage << "%)\n";
            }
        }
    }
};

// Utility function for input validation
int getValidatedChoice(int min, int max) {
    int choice;
    while (true) {
        std::cin >> choice;
        if (std::cin.fail() || choice < min || choice > max) {
            std::cin.clear();          // Clear input stream
            std::cin.ignore(1000, '\n'); // Ignore invalid input
            std::cout << "Invalid choice. Please try again: ";
        } else {
            return choice;
        }
    }
}

// Function to display Employee Menu
void displayEmployeeMenu(const std::shared_ptr<Employee>& employee) {
    int option;
    do {
        std::cout << "\n--- Employee Menu ---" << std::endl;
        std::cout << "1. View Attendance Details\n2. Request Leave\n3. View Leave Status\n4. View Leave Report\n5. Exit\nEnter your choice: ";
        option = getValidatedChoice(1, 5);

        switch (option) {
            case 1:
                employee->generateAttendanceReport();
                break;
            case 2: {
                std::string leaveType, startDate, endDate, reason;
                std::cout << "Enter Leave Type (Casual/Earned/Official/Unpaid): ";
                std::cin >> leaveType;
                std::cout << "Enter Start Date (YYYY-MM-DD): ";
                std::cin >> startDate;
                std::cout << "Enter End Date (YYYY-MM-DD): ";
                std::cin >> endDate;
                std::cout << "Enter Reason for Leave: ";
                std::cin.ignore();
                std::getline(std::cin, reason);
                employee->requestLeave(leaveType, startDate, endDate, reason);
                break;
            }
            case 3: {
                int leaveId;
                std::cout << "Enter Leave ID to check status: ";
                std::cin >> leaveId;
                employee->checkLeaveStatus(leaveId);
                break;
            }
            case 4:
                employee->generateLeaveReport();
                break;
            case 5:
                std::cout << "Exiting Employee Menu..." << std::endl;
                break;
        }
    } while (option != 5);
}

// Function to display Supervisor Menu
void displaySupervisorMenu(Supervisor& supervisor, std::vector<std::shared_ptr<Leave>>& leaveRequests) {
    int option;
    do {
        std::cout << "\n--- Supervisor Menu ---" << std::endl;
        std::cout << "1. View Pending Leave Requests\n2. Approve/Reject Leave\n3. Exit\nEnter your choice: ";
        option = getValidatedChoice(1, 3);

        switch (option) {
            case 1:
                supervisor.checkLeaveRequests(leaveRequests);
                break;
            case 2: {
                int leaveId;
                std::string decision;
                std::cout << "Enter Leave ID to Approve/Reject: ";
                std::cin >> leaveId;
                std::cout << "Enter Decision (Approve/Reject): ";
                std::cin >> decision;

                for (auto& leave : leaveRequests) {
                    if (leave->getLeaveId() == leaveId) {
                        leave->setStatus(decision);
                        supervisor.notifyLeaveApproval(decision);
                        break;
                    }
                }
                break;
            }
            case 3:
                std::cout << "Exiting Supervisor Menu..." << std::endl;
                break;
        }
    } while (option != 3);
}

// Function to display Director Menu
void displayDirectorMenu(Director& director, std::vector<std::shared_ptr<Leave>>& leaveRequests) {
    int option;
    do {
        std::cout << "\n--- Director Menu ---" << std::endl;
        std::cout << "1. View Pending Leave Requests\n2. Approve/Reject Leave\n3. Exit\nEnter your choice: ";
        option = getValidatedChoice(1, 3);

        switch (option) {
            case 1:
                director.checkLeaveRequests(leaveRequests);
                break;
            case 2: {
                int leaveId;
                std::string decision;
                std::cout << "Enter Leave ID to Approve/Reject: ";
                std::cin >> leaveId;
                std::cout << "Enter Decision (Approve/Reject): ";
                std::cin >> decision;

                for (auto& leave : leaveRequests) {
                    if (leave->getLeaveId() == leaveId) {
                        leave->setStatus(decision);
                        director.notifyLeaveApproval(decision);
                        break;
                    }
                }
                break;
            }
            case 3:
                std::cout << "Exiting Director Menu..." << std::endl;
                break;
        }
    } while (option != 3);
}

// Main Function
int main() {
    // Load data using FileHandler
    std::vector<std::shared_ptr<Employee>> employees;
    std::vector<std::shared_ptr<Leave>> leaveRequests;

    try {
        FileHandler::readEmployeeData(employees);
        FileHandler::readLeaveData(leaveRequests);
    } catch (const std::exception& ex) {
        std::cerr << "Error loading data: " << ex.what() << std::endl;
        return 1; // Exit on critical error
    }

    // Role-based system
    std::cout << "Welcome to Attendance and Leave Management System!" << std::endl;
    std::cout << "Select your role:\n1. Employee\n2. Supervisor\n3. Director\n4. Exit\nEnter your choice: ";
    int choice = getValidatedChoice(1, 4);

    switch (choice) {
        case 1: { // Employee Role
            int empId;
            std::cout << "Enter your Employee ID: ";
            std::cin >> empId;

            // Find the employee
            auto loggedInEmployee = std::find_if(employees.begin(), employees.end(),
                                                 [empId](const std::shared_ptr<Employee>& emp) {
                                                     return emp->getEmployeeId() == empId;
                                                 });

            if (loggedInEmployee != employees.end()) {
                displayEmployeeMenu(*loggedInEmployee);
            } else {
                std::cout << "Error: Employee not found!" << std::endl;
            }
            break;
        }
        case 2: { // Supervisor Role
            Supervisor supervisor(999, "Supervisor");
            displaySupervisorMenu(supervisor, leaveRequests);
            break;
        }
        case 3: { // Director Role
            Director director(888, "Director");
            displayDirectorMenu(director, leaveRequests);
            break;
        }
        case 4: { // Exit
            std::cout << "Exiting system. Goodbye!" << std::endl;
            return 0;
        }
    }

    return 0;
}

