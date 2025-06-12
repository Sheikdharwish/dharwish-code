#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <locale>
using namespace std;

class ATM {
private:
    string username;
    string password;
    double balance;

public:
    ATM() : balance(0.0) {}

    // Format amount in INR with ₹ symbol
    string formatINR(double amount) {
        stringstream ss;
        ss.imbue(locale(""));
        ss << "₹" << fixed << setprecision(2) << amount;
        return ss.str();
    }

    // Login by checking username and password
    bool login(string user, string pass) {
        ifstream file("accounts.txt");
        string u, p;
        double b;
        while (file >> u >> p >> b) {
            if (u == user && p == pass) {
                username = u;
                password = p;
                balance = b;
                return true;
            }
        }
        return false;
    }

    // Create a new account
    void signup(string user, string pass) {
        ofstream file("accounts.txt", ios::app);
        file << user << " " << pass << " 0.0" << endl;
        cout << "✅ Account created successfully!\n";
    }

    // Show current balance
    void showBalance() {
        cout << "💰 Your current balance is: " << formatINR(balance) << endl;
    }

    // Deposit money
    void deposit(double amount) {
        if (amount <= 0) {
            cout << "❌ Invalid deposit amount.\n";
            return;
        }
        balance += amount;
        updateAccount();
        cout << "✅ Deposited " << formatINR(amount) << " successfully.\n";
    }

    // Withdraw money
    void withdraw(double amount) {
        if (amount <= 0) {
            cout << "❌ Invalid withdrawal amount.\n";
            return;
        }
        if (amount > balance) {
            cout << "⚠️ Insufficient balance.\n";
        } else {
            balance -= amount;
            updateAccount();
            cout << "✅ Withdrawn " << formatINR(amount) << " successfully.\n";
        }
    }

    // Update account details in file
    void updateAccount() {
        ifstream file("accounts.txt");
        ofstream temp("temp.txt");
        string u, p;
        double b;

        while (file >> u >> p >> b) {
            if (u == username && p == password) {
                temp << u << " " << p << " " << balance << endl;
            } else {
                temp << u << " " << p << " " << b << endl;
            }
        }

        file.close();
        temp.close();

        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");
    }
};

int main() {
    ATM atm;
    int choice;
    string username, password;

    cout << "----- 🏧 Welcome to Indian ATM Management System 🏧 -----\n";
    cout << "1. Login\n2. Signup\nEnter your choice: ";
    cin >> choice;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (choice == 1) {
        if (atm.login(username, password)) {
            int op;
            do {
                cout << "\n--- ATM Menu ---\n";
                cout << "1. Check Balance\n2. Deposit\n3. Withdraw\n4. Exit\n";
                cout << "Choose an option: ";
                cin >> op;

                if (op == 1) {
                    atm.showBalance();
                } else if (op == 2) {
                    double amt;
                    cout << "Enter amount to deposit: ₹";
                    cin >> amt;
                    atm.deposit(amt);
                } else if (op == 3) {
                    double amt;
                    cout << "Enter amount to withdraw: ₹";
                    cin >> amt;
                    atm.withdraw(amt);
                } else if (op != 4) {
                    cout << "❌ Invalid option.\n";
                }
            } while (op != 4);
        } else {
            cout << "❌ Login failed. Incorrect username or password.\n";
        }
    } else if (choice == 2) {
        atm.signup(username, password);
    } else {
        cout << "❌ Invalid choice.\n";
    }

    cout << "\n🙏 Thank you for using Indian ATM System. Have a nice day!\n";
    return 0;
}
