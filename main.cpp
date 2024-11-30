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
int Leave::leaveIdCounter = 0;

Leave::Leave(int empId, const std::string& type, const std::string& start, const std::string& end, const std::string& reason)
    : employeeId(empId), leaveType(type), startDate(start), endDate(end), reason(reason), status("Pending") {
    leaveId = ++leaveIdCounter;
    try {
        if (startDate.size() >= 10 && endDate.size() >= 10) {
            duration = std::stoi(endDate.substr(8, 2)) - std::stoi(startDate.substr(8, 2)) + 1;
        } else {
            throw std::invalid_argument("Invalid date format");
        }
    } catch (const std::exception& e) {
        std::cerr << "Error calculating leave duration: " << e.what() << '\n';
        duration = 0; // Fallback duration
    }
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

Employee::Employee(int id, const std::string& n, const std::string& r) : employeeId(id), name(n), role(r) {}

    // Getters and Setters
int Employee::getEmployeeId() const { return employeeId; }
const std::string& Employee:: getName() const { return name; }
const std::string& Employee:: getRole() const { return role; }
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

void Employee::requestLeave(const std::string& leaveType, const std::string& startDate, const std::string& endDate, const std::string& reason) {
    int leaveDays = 0;
    try {
        // Validate date formats
        if (startDate.size() >= 10 && endDate.size() >= 10) {
            leaveDays = std::stoi(endDate.substr(8, 2)) - std::stoi(startDate.substr(8, 2)) + 1;
        } else {
            throw std::invalid_argument("Invalid date format");
        }
    } catch (const std::exception& e) {
        std::cerr << "Error calculating leave days: " << e.what() << "\n";
        return; // Exit function if date parsing fails
    }

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
    Director(int id, const std::string& n, const std::string& r ="Employee") : Employee(id, n, r) {}

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
    Supervisor(int id, const std::string& n, const std::string& r) : Employee(id, n,r) {}

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
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open employee data file for reading.\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        try {
            std::stringstream ss(line);
            int id;
            std::string name, role, temp;
            float totalHours = 0.0;
            int casualLeaves = 0, earnedLeaves = 0;

            std::cout << line << std::endl;

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

            std::shared_ptr<Employee> emp;
            if (role == "Supervisor") {
                emp = std::make_shared<Supervisor>(id, name, role);
            } else if (role == "Director") {
                emp = std::make_shared<Director>(id, name, role);
            } else {
                emp = std::make_shared<Employee>(id, name, role);
            }

            emp->setTotalHoursWorked(totalHours);
            emp->setCasualLeaveBalance(casualLeaves);
            emp->setEarnedLeaveBalance(earnedLeaves);

            employees.push_back(emp);
            //std::cout << "Successfully added Employee: " << id << ", Role: " << role << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error processing line: " << line << " - " << e.what() << '\n';
        }
    }

    file.close();
    //std::cout << "Completed reading employee data.\n";
}

void FileHandler::writeEmployeeData(const Employee& employee) {
    std::ofstream file(employeeFile, std::ios::app); // Open file in append mode
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open employee file for writing.\n";
        return;
    }

    try {
        file << employee.getEmployeeId() << "|"
             << employee.getName() << "|"
             << employee.getRole() << "|"
             << employee.getTotalHoursWorked() << "|"
             << employee.getCasualLeaveBalance() << "|"
             << employee.getEarnedLeaveBalance() << "\n";
        //std::cout << "Employee data written for ID " << employee.getEmployeeId() << ".\n";
    } catch (const std::exception& e) {
        std::cerr << "Error writing employee data: " << e.what() << "\n";
    }

    file.close();
}

void FileHandler::updateEmployeeData(const Employee& employee) {
    std::ifstream file(employeeFile);
    std::ofstream tempFile("temp_employees.txt");
    std::string line;
    bool recordUpdated = false;

    if (!file.is_open() || !tempFile.is_open()) {
        std::cerr << "Error: Unable to open employee file for updating.\n";
        return;
    }

    while (std::getline(file, line)) {
        try {
            std::stringstream ss(line);
            int id;
            std::string temp;

            // Parse Employee ID
            if (!std::getline(ss, temp, '|') || temp.empty()) throw std::invalid_argument("Invalid Employee ID");
            id = std::stoi(temp);

            // If IDs match, write updated data
            if (id == employee.getEmployeeId()) {
                tempFile << employee.getEmployeeId() << "|"
                         << employee.getName() << "|"
                         << employee.getRole() << "|"
                         << employee.getTotalHoursWorked() << "|"
                         << employee.getCasualLeaveBalance() << "|"
                         << employee.getEarnedLeaveBalance() << "\n";
                recordUpdated = true;
            } else {
                tempFile << line << "\n"; // Copy unchanged line
            }
        } catch (const std::exception& e) {
            std::cerr << "Error processing line: " << line << " - " << e.what() << "\n";
            tempFile << line << "\n"; // Preserve original line
        }
    }

    file.close();
    tempFile.close();

    if (recordUpdated) {
        if (remove(employeeFile.c_str()) != 0 || rename("temp_employees.txt", employeeFile.c_str()) != 0) {
            std::cerr << "Error: Unable to replace the employee file with updated data.\n";
        } else {
            std::cout << "Employee data updated for ID " << employee.getEmployeeId() << ".\n";
        }
    } else {
        std::cerr << "Employee ID " << employee.getEmployeeId() << " not found. No changes made.\n";
        remove("temp_employees.txt"); // Clean up
    }
}

void FileHandler::readAttendanceData(std::vector<AttendanceRecord>& attendanceRecords) {
    std::ifstream file(attendanceFile);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open attendance data file for reading.\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        try {
            std::stringstream ss(line);
            int empId;
            std::string date;
            float hoursWorked;

            std::string temp;

            // Parse Employee ID
            if (!std::getline(ss, temp, '|') || temp.empty()) 
                throw std::invalid_argument("Missing or invalid Employee ID");
            empId = std::stoi(temp);

            // Parse Date
            if (!std::getline(ss, date, '|') || date.empty()) 
                throw std::invalid_argument("Missing or invalid Date");

            // Parse Hours Worked
            if (!std::getline(ss, temp, '|') || temp.empty()) 
                throw std::invalid_argument("Missing or invalid Hours Worked");
            hoursWorked = std::stof(temp);

            // Check if record for this Employee ID already exists
            auto it = std::find_if(attendanceRecords.begin(), attendanceRecords.end(),
                                   [empId](const AttendanceRecord& record) {
                                       return record.getEmployeeId() == empId;
                                   });

            if (it != attendanceRecords.end()) {
                // Add attendance to existing record
                it->addAttendance(date, hoursWorked);
            } else {
                // Create a new record for the employee
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

void FileHandler::writeAttendanceData(const AttendanceRecord& record) {
    if (record.getRecords().empty()) {
        std::cerr << "No attendance records to write for Employee ID " << record.getEmployeeId() << ".\n";
        return;
    }

    std::ofstream file(attendanceFile, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open attendance file for writing.\n";
        return;
    }

    try {
        for (const auto& attendance : record.getRecords()) {
            file << record.getEmployeeId() << "|"
                 << attendance.getDate() << "|"
                 << attendance.getHoursWorked() << "\n";
        }
        //std::cout << "Attendance data written for Employee ID " << record.getEmployeeId() << ".\n";
    } catch (const std::exception& e) {
        std::cerr << "Error writing attendance data: " << e.what() << "\n";
    }

    file.close();
}

void FileHandler::readLeaveData(std::vector<std::shared_ptr<Leave>>& leaveRecords) {
    std::ifstream file(leaveFile);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open leave data file for reading.\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        try {
            std::stringstream ss(line);
            int id, empId;
            std::string type, startDate, endDate, reason, status, supervisorApproval, directorApproval, temp;

           std::cout << line << std::endl;

            if (!std::getline(ss, temp, '|') || temp.empty()) throw std::invalid_argument("Invalid Leave ID");
            id = std::stoi(temp);

            if (!std::getline(ss, temp, '|') || temp.empty()) throw std::invalid_argument("Invalid Employee ID");
            empId = std::stoi(temp);

            if (!std::getline(ss, type, '|') || type.empty()) throw std::invalid_argument("Invalid Leave Type");
            if (!std::getline(ss, startDate, '|') || startDate.empty()) throw std::invalid_argument("Invalid Start Date");
            if (!std::getline(ss, endDate, '|') || endDate.empty()) throw std::invalid_argument("Invalid End Date");
            if (!std::getline(ss, reason, '|') || reason.empty()) throw std::invalid_argument("Invalid Reason");
            if (!std::getline(ss, status, '|') || status.empty()) throw std::invalid_argument("Invalid Status");
            std::getline(ss, supervisorApproval, '|');
            std::getline(ss, directorApproval, '|') ;

            auto leave = LeaveFactory::createLeave(type, empId, startDate, endDate, reason);
            if (!leave) throw std::runtime_error("Failed to create Leave object");

            leave->setStatus(status);
            leave->setSupervisorApproval(supervisorApproval);
            leave->setDirectorApproval(directorApproval);

            leaveRecords.push_back(leave);
           // std::cout << "Successfully added Leave ID: " << id << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error processing line: " << line << " - " << e.what() << '\n';
        }
    }

    file.close();
   // std::cout << "Completed reading leave data.\n";
}

void FileHandler::updateLeaveStatus(int leaveId, const std::string& newStatus) {
    std::ifstream file(leaveFile);
    std::ofstream tempFile("temp_leaves.txt");
    std::string line;
    bool leaveUpdated = false;

    if (!file.is_open() || !tempFile.is_open()) {
        std::cerr << "Error: Unable to open leave file for updating.\n";
        return;
    }

    while (std::getline(file, line)) {
        try {
            std::stringstream ss(line);
            int id;
            std::string type, startDate, endDate, reason, status, supervisorApproval, directorApproval, temp;

            // Read Leave ID
            if (!std::getline(ss, temp, '|') || temp.empty()) throw std::invalid_argument("Invalid Leave ID");
            id = std::stoi(temp);

            // Read rest of the line
            std::getline(ss, type, '|');
            std::getline(ss, startDate, '|');
            std::getline(ss, endDate, '|');
            std::getline(ss, reason, '|');
            std::getline(ss, status, '|');
            std::getline(ss, supervisorApproval, '|');
            std::getline(ss, directorApproval, '|');

            // If Leave ID matches, update status
            if (id == leaveId) {
                status = newStatus;
                leaveUpdated = true;
            }

            // Write updated or original data to temp file
            tempFile << id << "|" << type << "|" << startDate << "|" << endDate << "|"
                     << reason << "|" << status << "|" << supervisorApproval << "|" << directorApproval << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Error processing line: " << line << " - " << e.what() << "\n";
            tempFile << line << "\n"; // Preserve original line
        }
    }

    file.close();
    tempFile.close();

    if (leaveUpdated) {
        if (remove(leaveFile.c_str()) != 0 || rename("temp_leaves.txt", leaveFile.c_str()) != 0) {
            std::cerr << "Error: Unable to replace the leave file with updated data.\n";
        } else {
            std::cout << "Leave status updated for Leave ID " << leaveId << ".\n";
        }
    } else {
        std::cerr << "Leave ID " << leaveId << " not found. No changes made.\n";
        remove("temp_leaves.txt"); // Clean up
    }
}

void FileHandler::writeLeaveData(const Leave& leave) {
    std::ofstream file(leaveFile, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open leave file for writing.\n";
        return;
    }

    try {
        file << leave.getLeaveId() << "|"
             << leave.getEmployeeId() << "|"
             << leave.getLeaveType() << "|"
             << leave.getStartDate() << "|"
             << leave.getEndDate() << "|"
             << leave.getReason() << "|"
             << leave.getStatus() << "|"
             << leave.getSupervisorApproval() << "|"
             << leave.getDirectorApproval() << "\n";
        //std::cout << "Leave data written for Leave ID " << leave.getLeaveId() << ".\n";
    } catch (const std::exception& e) {
        std::cerr << "Error writing leave data: " << e.what() << "\n";
    }

    file.close();
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
                if ((*loggedInEmployee)->getRole() == "Employee") {
                    displayEmployeeMenu(*loggedInEmployee);
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

            auto loggedInSupervisor = std::find_if(employees.begin(), employees.end(),
                                                   [empId](const std::shared_ptr<Employee>& emp) {
                                                       return emp->getEmployeeId() == empId && dynamic_cast<Supervisor*>(emp.get()) != nullptr;
                                                   });

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

            auto loggedInDirector = std::find_if(employees.begin(), employees.end(),
                                                 [empId](const std::shared_ptr<Employee>& emp) {
                                                     return emp->getEmployeeId() == empId && dynamic_cast<Director*>(emp.get()) != nullptr;
                                                 });

            if (loggedInDirector != employees.end()) {
                displayDirectorMenu(*dynamic_cast<Director*>(loggedInDirector->get()), leaveRequests);
            } else {
                std::cout << "Error: Director not found!" << std::endl;
            }
            break;
        }
        case 4: { // Exit
            std::cout << "Exiting system. Goodbye!" << std::endl;
            return 0;
        }
    }

    return 0;
}

