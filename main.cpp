#include <iostream>
#include <string>
#include <iomanip> //Required for formatting
using namespace std;

//Employee class
class Employee {
private:
    string emp_id, name, position, emp_type;
    double basic_salary, hourly_wage, daily_wage;
    int working_hours, leave_days, overtime_hours;

public:
    Employee() : emp_id(""), name(""), position(""), emp_type(""),
                 basic_salary(0), hourly_wage(0), daily_wage(0),
                 working_hours(0), leave_days(0), overtime_hours(0) {}

    void setEmployeeDetails(string id, string n, string pos, string type,
                            double salary, int hours, int leave, int overtime)
     {  emp_id = id;
        name = n;
        position = pos;
        emp_type = type;
        basic_salary = salary;
        working_hours = hours;

        if (emp_type == "Part-time") {
            leave_days = 0;
            overtime_hours = 0;
        } else {
            leave_days = leave;
            overtime_hours = overtime;
        }

        hourly_wage = basic_salary / (30 * 8);
        daily_wage = basic_salary / 30;
    }
// Calculates the net salary of an employee based on their type and details.
    double calculateSalary() {
        if (emp_type == "Part-time") {
            return working_hours * hourly_wage;
        } else {
            double leave_bonus = 0;
            if (leave_days == 0) leave_bonus = 300;
            else if (leave_days == 1) leave_bonus = 200;
            else if (leave_days == 2) leave_bonus = 100;

            double overtime_pay = overtime_hours * hourly_wage * 2;
            double penalty = 0;
            if (leave_days > 4 && overtime_hours > 0) penalty = basic_salary * 0.01;

           const double income_tax = basic_salary * 0.02;
            const double social_security_tax = 10;

            return basic_salary + leave_bonus + overtime_pay - penalty - income_tax - social_security_tax;
        }
    }

    string getEmployeeType() { return emp_type; }
    double getNetSalary() { return calculateSalary(); }

    void displayInfo() {
        cout << left << setw(10) << emp_id
             << setw(20) << name
             << setw(15) << position
             << setw(12) << emp_type
             << setw(12) << fixed << setprecision(2) << basic_salary
             << setw(12) << fixed << setprecision(2) << hourly_wage
             << setw(12) << fixed << setprecision(2) << daily_wage
             << setw(12) << working_hours
             << setw(12) << leave_days
             << setw(12) << overtime_hours
             << setw(12) << fixed << setprecision(2) << calculateSalary()
             << endl;
    }
};

void quickSort(Employee employees[], int low, int high) {
    if (low < high) {
        double pivot = employees[high].getNetSalary();
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (employees[j].getNetSalary() <= pivot) {
                i++;
                swap(employees[i], employees[j]);
            }
        }
        swap(employees[i + 1], employees[high]);
        int partitionIndex = i + 1;

        quickSort(employees, low, partitionIndex - 1);
        quickSort(employees, partitionIndex + 1, high);
    }
}

void displayBasicSalaries() {
    cout << "\nType of Employee    Basic Salary\n";
    cout << "-------------------------------\n";
    cout << "1. Barista            $1920\n";
    cout << "2. Cashier            $1790\n";
    cout << "3. Kitchen Staff      $1850\n";
    cout << "4. Cleaner            $1400\n";
    cout << "5. Waiter/Waitress    $1700\n";
    cout << "6. Supervisor         $2400\n";
}

int main() {
    const int MAX_EMPLOYEES = 10;
    Employee employees[MAX_EMPLOYEES];
    int employee_count = 0;

    while (true) {
        cout << "\n--- Employee Payroll System ---\n";
        cout << "1. Add Employee\n";
        cout << "2. Display All Employees\n";
        cout << "3. Calculate Total Salary\n";
        cout << "4. Display Basic Salaries\n";
        cout << "5. Sort Employees by Net Salary\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            if (employee_count >= MAX_EMPLOYEES) {
                cout << "Cannot add more employees. Maximum limit reached.\n";
                continue;
            }
            string id, n, pos, type;
            double salary;
            int hours, leave = 0, overtime = 0;

            cout << "\nType of Employee    Basic Salary\n";
            cout << "-------------------------------\n";
            cout << "1. Barista            $1920\n";
            cout << "2. Cashier            $1790\n";
            cout << "3. Kitchen Staff      $1850\n";
            cout << "4. Cleaner            $1400\n";
            cout << "5. Waiter/Waitress    $1700\n";
            cout << "6. Supervisor         $2400\n";
            cout << "Enter the position number (1-6): ";
            int position_choice;
            cin >> position_choice;

            if (position_choice == 1) pos = "Barista";
            else if (position_choice == 2) pos = "Cashier";
            else if (position_choice == 3) pos = "Kitchen Staff";
            else if (position_choice == 4) pos = "Cleaner";
            else if (position_choice == 5) pos = "Waiter/Waitress";
            else if (position_choice == 6) pos = "Supervisor";
            else {
                cout << "Invalid position choice. Try again.\n";
                continue;
            }

            cout << "Enter Employee ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Employee Name: ";
            getline(cin, n);
            cout << "Enter Employee Type (Full-time/Part-time): ";
            getline(cin, type);
            cout << "Enter Basic Salary: ";
            cin >> salary;
            cout << "Enter Working Hours: ";
            cin >> hours;

            if (type == "Full-time") {
                cout << "Enter Leave Days(Only for Full-time): ";
                cin >> leave;
                cout << "Enter Overtime Hours(Only for Full-time): ";
                cin >> overtime;
            }

            employees[employee_count].setEmployeeDetails(id, n, pos, type, salary, hours, leave, overtime);
            employee_count++;
            cout << "Employee added successfully!\n";

        }
        else if (choice == 2) {
            cout << "\nEmployee Details:\n";
            cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(15) << "Position"
                 << setw(12) << "Type" << setw(12) << "Basic Sal" << setw(12) << "Hourly Wage"
                 << setw(12) << "Daily Wage" << setw(12) << "Wrk Hrs" << setw(12) << "Leave"
                 << setw(12) << "Overtime" << setw(12) << "Net Salary" << endl;
            for (int i = 0; i < employee_count; i++) {
                employees[i].displayInfo();
            }

        } else if (choice == 3) {
            double total_payment = 0, full_time_payment = 0, part_time_payment = 0;
            int full_time_count = 0, part_time_count = 0;

            cout << "\n--- Total Payment Details ---\n";
            cout << left << setw(10) << "ID"
                 << setw(20) << "Name"
                 << setw(15) << "Position"
                 << setw(12) << "Type"
                 <<setw(12)  << "Basic sal"
                 <<setw(12) <<"Hourly Wage"
                 << setw(12) << "Daily Wage"
                 << setw(12) << "Wrk Hrs"
                 << setw(12) << "Leave"
                 << setw(12) << "Overtime"
                 << setw(12) << "Net Salary" << endl;

            for (int i = 0; i < employee_count; i++) {
                employees[i].displayInfo();
                double net_salary = employees[i].calculateSalary();
                total_payment += net_salary;

                if (employees[i].getEmployeeType() == "Full-time") {
                    full_time_payment += net_salary;
                    full_time_count++;
                } else if (employees[i].getEmployeeType() == "Part-time") {
                    part_time_payment += net_salary;
                    part_time_count++;
                }
            }

            cout << "\n--- Summary ---\n";
            cout << "Total Monthly Payment: $" << fixed << setprecision(2) << total_payment << endl;
            cout << "Full-Time Payment: $" << fixed << setprecision(2) << full_time_payment << endl;
            cout << "Part-Time Payment: $" << fixed << setprecision(2) << part_time_payment << endl;
            cout << "Full-Time Employee Count: " << full_time_count << endl;
            cout << "Part-Time Employee Count: " << part_time_count << endl;
            cout << "Total Employee Count: " << full_time_count + part_time_count << endl;

        } else if (choice == 4) {
            displayBasicSalaries();

        } else if (choice == 5) {
            if (employee_count > 0) {
                quickSort(employees, 0, employee_count - 1);
                cout << "Employees sorted by net salary successfully.\n";
                cout << "\nSorted Employee Details:\n";
                cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(15) << "Position"
                     << setw(12) << "Type" << setw(12) << "Basic Sal" << setw(12) << "Hourly Wage"
                     << setw(12) << "Daily Wage" << setw(12) << "Wrk Hrs" << setw(12) << "Leave"
                     << setw(12) << "Overtime" << setw(12) << "Net Salary" << endl;
                for (int i = 0; i < employee_count; i++) {
                    employees[i].displayInfo();
                }
            } else {
                cout << "No employees to sort.\n";
            }

        } else if (choice == 6) {
            cout << "Exiting the program. Goodbye!\n";
            break;

        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
