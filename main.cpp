#include <string>
#include <iostream>
#include<vector>
#include<memory>
#include<fstream>
#include <sstream>

class FileHandler;

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


class Employee {
protected:
    int employeeId;
    std::string name;
    float totalHoursWorked = 0;
    int casualLeaveBalance = 15;
    int earnedLeaveBalance = 21;
    std::vector<std::shared_ptr<Leave>> leaveHistory; // Store employee leave records using shared_ptr
    std::vector<AttendanceRecord> attendanceRecords; // Store employee attendance records

public:
    Employee(int id, const std::string& n) : employeeId(id), name(n) {}

    // Getters and Setters
    int getEmployeeId() const { return employeeId; }
    const std::string& getName() const { return name; }
    float getTotalHoursWorked() const { return totalHoursWorked; }
    int getCasualLeaveBalance() const { return casualLeaveBalance; }
    int getEarnedLeaveBalance() const { return earnedLeaveBalance; }

    void setTotalHoursWorked(float hours) { totalHoursWorked = hours; }
    void setCasualLeaveBalance(int balance) { casualLeaveBalance = balance; }
    void setEarnedLeaveBalance(int balance) { earnedLeaveBalance = balance; }

    // Methods to apply for leave and display leave details
    virtual void applyLeave(std::shared_ptr<Leave> leave) ;
    virtual void displayLeaveDetails();

    // Method to check leave balance
    bool hasSufficientLeave(const std::string& leaveType, int days) {
        if (leaveType == "Casual" && casualLeaveBalance >= days) {
            return true;
        } else if (leaveType == "Earned" && earnedLeaveBalance >= days) {
            return true;
        }
        return false;
    }
    
    // Method to update leave balance (used after approval)
    void updateLeaveBalance(const std::string& leaveType, int days){
        if (leaveType == "Casual") {
            casualLeaveBalance -= days;
        } else if (leaveType == "Earned") {
            earnedLeaveBalance -= days;
        }
    }


    // Virtual method to notify employee (Observer Pattern)
    virtual void notifyLeaveApproval(const std::string& status);

    // Virtual method to check leave requests (Supervisor/Director responsibility)
    virtual void checkLeaveRequests(std::vector<std::shared_ptr<Leave>>& leaveRequests);

    // Method to check leave status
    void checkLeaveStatus(int leaveId){
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
    void generateLeaveReport() {
        std::cout << "Leave Report for Employee: " << name << "\n";
        for (const auto& leave : leaveHistory) {
            std::cout << "Leave Type: " << leave->getLeaveType() 
                      << ", Status: " << leave->getStatus()
                      << ", Duration: " << leave->getDuration() << " days\n";
        }
    }

    // Method to generate attendance report
    void generateAttendanceReport(){
        std::cout << "Attendance Report for Employee: " << name << "\n";
        for (const auto& record : attendanceRecords) {
            //std::cout << "Date: " << record.getDate() << ", Hours Worked: " << record.getHoursWorked() << "\n";
        }
    }

    void requestLeave(const std::string& leaveType, const std::string& startDate, const std::string& endDate, const std::string& reason){
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
    void addAttendanceRecord(const AttendanceRecord& record){
        attendanceRecords.push_back(record);
        totalHoursWorked += record.getTotalHoursWorked();
    }
};

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


// Class to handle file reading and writing
class FileHandler {
public:
    static void readEmployeeData(std::vector<std::shared_ptr<Employee>>& employees) {
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

    static void FileHandler::writeEmployeeData(const Employee& employee) {
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

    static void readAttendanceData(std::vector<AttendanceRecord>& attendanceRecords, int employeeId) {
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

    static void writeAttendanceData(const AttendanceRecord& record) {
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

    static void readLeaveData(std::vector<std::shared_ptr<Leave>>& leaveRecords) {
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

    static void writeLeaveData(const Leave& leave) {
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

    static void updateLeaveStatus(int leaveId, const std::string& newStatus) {
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

    static void updateAttendanceData(int employeeId, const AttendanceRecord& record) {
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

private:
    static const std::string employeeFile;
    static const std::string attendanceFile;
    static const std::string leaveFile;
};

const std::string FileHandler::employeeFile = "Employees.txt";
const std::string FileHandler::attendanceFile = "Attendance.txt";
const std::string FileHandler::leaveFile = "Leaves.txt";

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

// Function prototypes
void displayEmployeeMenu(std::shared_ptr<Employee> employee);
void displaySupervisorMenu(Supervisor& supervisor, std::vector<std::shared_ptr<Leave>>& leaveRequests);
void displayDirectorMenu(Director& director, std::vector<std::shared_ptr<Leave>>& leaveRequests);

// Main Function
int main() {
    // Load data using FileHandler
    std::vector<std::shared_ptr<Employee>> employees;
    std::vector<std::shared_ptr<Leave>> leaveRequests;
    FileHandler::readEmployeeData(employees);
    FileHandler::readLeaveData(leaveRequests);

    // Role-based system
    std::cout << "Welcome to Attendance and Leave Management System!" << std::endl;
    std::cout << "Select your role:\n1. Employee\n2. Supervisor\n3. Director\nEnter your choice: ";
    int choice;
    std::cin >> choice;

    if (choice == 1) {
        // Employee Role
        int empId;
        std::cout << "Enter your Employee ID: ";
        std::cin >> empId;

        // Find the employee
        std::shared_ptr<Employee> loggedInEmployee = nullptr;
        for (auto& emp : employees) {
            if (emp->getEmployeeId() == empId) {
                loggedInEmployee = emp;
                break;
            }
        }

        if (loggedInEmployee) {
            displayEmployeeMenu(loggedInEmployee);
        } else {
            std::cout << "Error: Employee not found!" << std::endl;
        }
    } else if (choice == 2) {
        // Supervisor Role
        Supervisor supervisor(999, "Supervisor");  // Temporary supervisor object
        displaySupervisorMenu(supervisor, leaveRequests);
    } else if (choice == 3) {
        // Director Role
        Director director(888, "Director");  // Temporary director object
        displayDirectorMenu(director, leaveRequests);
    } else {
        std::cout << "Invalid choice. Exiting system." << std::endl;
    }

    return 0;
}

// Function to display Employee Menu
void displayEmployeeMenu(std::shared_ptr<Employee> employee) {
    int option;
    do {
        std::cout << "\n--- Employee Menu ---" <<std:: endl;
        std::cout << "1. View Attendance Details\n2. Request Leave\n3. View Leave Status\n4. View Leave Report\n5. Exit\nEnter your choice: ";
        std::cin >> option;

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
            std::cout << "Exiting Employee Menu..." <<std:: endl;
            break;
        default:
            std::cout << "Invalid option. Try again!" << std::endl;
        }
    } while (option != 5);
}

// Function to display Supervisor Menu
void displaySupervisorMenu(Supervisor& supervisor, std::vector<std::shared_ptr<Leave>>& leaveRequests) {
    int option;
    do {
        std::cout << "\n--- Supervisor Menu ---" << std::endl;
        std::cout << "1. View Pending Leave Requests\n2. Approve/Reject Leave\n3. Exit\nEnter your choice: ";
        std::cin >> option;

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
        default:
            std::cout << "Invalid option. Try again!" << std::endl;
        }
    } while (option != 3);
}

// Function to display Director Menu
void displayDirectorMenu(Director& director, std::vector<std::shared_ptr<Leave>>& leaveRequests) {
    int option;
    do {
        std::cout << "\n--- Director Menu ---" << std::endl;
        std::cout << "1. View Pending Leave Requests\n2. Approve/Reject Leave\n3. Exit\nEnter your choice: ";
        std::cin >> option;

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
        default:
            std::cout << "Invalid option. Try again!" << std::endl;
        }
    } while (option != 3);
}
