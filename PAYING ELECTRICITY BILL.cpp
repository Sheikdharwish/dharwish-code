#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

class ElectricityBill {
private:
    string customerName;
    int customerID;
    int units;
    float amount;

public:
    void input() {
        cout << "Enter Customer ID: ";
        cin >> customerID;
        cin.ignore();  // clear input buffer
        cout << "Enter Customer Name: ";
        getline(cin, customerName);
        cout << "Enter Units Consumed: ";
        cin >> units;
        calculateBill();
    }

    void calculateBill() {
        if (units <= 100) {
            amount = units * 1.20;
        } else if (units <= 300) {
            amount = 100 * 1.20 + (units - 100) * 2.00;
        } else {
            amount = 100 * 1.20 + 200 * 2.00 + (units - 300) * 3.00;
        }
    }

    void display() const {
        cout << "\n--- Electricity Bill ---\n";
        cout << "Customer ID   : " << customerID << endl;
        cout << "Customer Name : " << customerName << endl;
        cout << "Units Used    : " << units << endl;
        cout << fixed << setprecision(2);
        cout << "Bill Amount   : ₹" << amount << "\n";
    }

    void saveToFile() const {
        ofstream file("bills.txt", ios::app);
        file << customerID << "," << customerName << "," << units << "," << amount << endl;
        file.close();
    }

    static void displayAllBills() {
        ifstream file("bills.txt");
        string line;
        cout << "\n--- All Customer Bills ---\n";
        cout << left << setw(15) << "Customer ID"
             << setw(20) << "Name"
             << setw(15) << "Units"
             << "Amount (₹)\n";
        cout << "------------------------------------------------------\n";

        while (getline(file, line)) {
            stringstream ss(line);
            string id, name, unitStr, amtStr;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, unitStr, ',');
            getline(ss, amtStr, ',');

            cout << left << setw(15) << id
                 << setw(20) << name
                 << setw(15) << unitStr
                 << amtStr << "\n";
        }

        file.close();
    }
};

int main() {
    ElectricityBill bill;
    int choice;

    do {
        cout << "\n===== Electricity Bill System =====\n";
        cout << "1. Generate New Bill\n";
        cout << "2. Display All Bills\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bill.input();
                bill.display();
                bill.saveToFile();
                break;
            case 2:
                ElectricityBill::displayAllBills();
                break;
            case 3:
                cout << "Exiting the system. Thank you!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 3);

    return 0;
}
