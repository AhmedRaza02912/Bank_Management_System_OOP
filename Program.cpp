#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Transaction class
class Transaction {
public:
    string type;
    float amount;
    float updatedAmount;
    string userID;

    Transaction(const string& t, float amt, float updatedAmt, const string& id)
        : type(t), amount(amt), updatedAmount(updatedAmt), userID(id) {}
};

// Forward declaration for displayAllUsers
class User;
void displayAllUsers(const vector<User>& users);

// User class
class User {
private:
    string name;
    string ID;
    string password;
    float amount = 0;

public:
    float bank_charges = 0;
    vector<Transaction> transactions;

    User() {
        cout << "\n\nWelcome User.";
    }

    bool isIDUnique(const vector<User>& users, const string& ID) {
        for (const auto& user : users) {
            if (user.ID == ID) return false;
        }
        return true;
    }

    void setName(const string& newName) { name = newName; }
    void setID(const string& newID) { ID = newID; }
    void setPassword(const string& newPassword) { password = newPassword; }
    void setAmount(float newAmount) { amount = newAmount; }

    string getName() const { return name; }
    string getID() const { return ID; }
    string getPassword() const { return password; }
    float getAmount() const { return amount; }

    void input_details(const vector<User>& users) {
        string tempName, tempID, tempPassword;
        float initialAmount;
        char choice;

        cout << "\n\nEnter name: ";
        cin.ignore();
        getline(cin, tempName);
        setName(tempName);

        cout << "\n\nEnter ID: ";
        cin >> tempID;

        while (!isIDUnique(users, tempID)) {
            cout << "\nID is already in use. Please enter a different ID: ";
            cin >> tempID;
        }
        setID(tempID);

        cout << "\n\nEnter password: ";
        cin >> tempPassword;
        setPassword(tempPassword);

        cout << "\n\nDo you wish to store an initial amount (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            cout << "\n\nEnter initial amount: ";
            cin >> initialAmount;
            setAmount(initialAmount);
        } else {
            setAmount(0.00);
        }
    }

    void add_user(vector<User>& users) {
        system("cls");
        User newUser;
        newUser.input_details(users);
        newUser.save_user_to_file();
        newUser.update_user_in_file();
        users.push_back(newUser);
        cout << "\n\nAccount created successfully.";
        cout << "\n\nAs per policy, 0.33 will be reduced as bank charge.";
        cout << "\n\nPress any key to return to the main menu!";
        cin.ignore();
        cin.get();
    }

    void search_user(const vector<User>& users) {
        system("cls");
        string input_password, input_ID;
        cout << "\n\nEnter password: ";
        cin >> input_password;
        cout << "\n\nEnter ID: ";
        cin >> input_ID;

        bool found = false;
        for (const auto& user : users) {
            if (user.getPassword() == input_password && user.getID() == input_ID) {
                cout << "\n\nName: " << user.getName();
                cout << "\n\nID: " << user.getID();
                cout << "\n\nAmount currently: " << user.getAmount();
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "\n\nIncorrect password/ID or account doesn't exist!";
        }
        cout << "\n\nPress any key to return to the main menu!";
        cin.ignore();
        cin.get();
    }

    void deposit_money(vector<User>& users) {
        system("cls");
        string input_password, input_ID;
        cout << "\n\nEnter password: ";
        cin >> input_password;
        cout << "\n\nEnter ID: ";
        cin >> input_ID;
        bool found = false;

        for (auto& user : users) {
            if (user.getPassword() == input_password && user.getID() == input_ID) {
                float deposit_amount;
                cout << "\n\nEnter amount to deposit: ";
                cin >> deposit_amount;

                if (deposit_amount > 0) {
                    user.setAmount(user.getAmount() + deposit_amount - 0.333);
                    user.bank_charges += 0.333;

                    Transaction newTransaction("Deposit", deposit_amount, user.getAmount(), user.getID());
                    user.transactions.push_back(newTransaction);
                    user.save_transaction_to_file(newTransaction);
                    user.update_user_in_file();

                    cout << "\n\nDeposit successful! Current balance: " << user.getAmount();
                } else {
                    cout << "\n\nInvalid deposit amount!";
                }

                found = true;
                break;
            }
        }

        if (!found) {
            cout << "\n\nIncorrect password/ID or account doesn't exist!";
        }
        cout << "\n\nPress any key to return to the main menu!";
        cin.ignore();
        cin.get();
    }

    void withdraw_money(vector<User>& users) {
        system("cls");
        string input_password, input_ID;
        cout << "\n\nEnter password: ";
        cin >> input_password;
        cout << "\n\nEnter ID: ";
        cin >> input_ID;

        bool found = false;
        for (auto& user : users) {
            if (user.getPassword() == input_password && user.getID() == input_ID) {
                float withdraw_amount;
                cout << "\n\nEnter amount to withdraw: ";
                cin >> withdraw_amount;

                if (withdraw_amount > 0 && user.getAmount() >= (withdraw_amount + 0.333)) {
                    user.setAmount(user.getAmount() - withdraw_amount - 0.333);
                    user.bank_charges += 0.333;

                    Transaction newTransaction("Withdraw", withdraw_amount, user.getAmount(), user.getID());
                    user.transactions.push_back(newTransaction);
                    user.save_transaction_to_file(newTransaction);
                    user.update_user_in_file();

                    cout << "\n\nWithdrawal successful! Current balance: " << user.getAmount();
                } else {
                    cout << "\n\nInsufficient balance or invalid withdrawal amount!";
                }

                found = true;
                break;
            }
        }

        if (!found) {
            cout << "\n\nIncorrect password/ID or account doesn't exist!";
        }
        cout << "\n\nPress any key to return to the main menu!";
        cin.ignore();
        cin.get();
    }

    void save_user_to_file() {
        ofstream userFile("users.txt", ios::app);
        if (userFile.is_open()) {
            userFile << getName() << "," << getID() << "\n";
            userFile.close();
        }
    }

    void update_user_in_file() {
        ofstream userFile("amounts.txt", ios::app);
        if (userFile.is_open()) {
            userFile << getID() << "," << getAmount() << "\n";
            userFile.close();
        }
    }

    void save_transaction_to_file(const Transaction& transaction) {
        ofstream transFile("transactions.txt", ios::app);
        if (transFile.is_open()) {
            transFile << transaction.userID << "," << transaction.type << ","
                      << transaction.amount << "," << transaction.updatedAmount << "\n";
            transFile.close();
        }
    }

    friend void displayAllUsers(const vector<User>& users);
};

// Admin class
class Admin {
private:
    string adminPassword = "admin123";

public:
    void adjust_user_balance(vector<User>& users) {
        system("cls");
        string enteredPassword;
        cout << "\nEnter Admin Password: ";
        cin >> enteredPassword;

        if (enteredPassword != adminPassword) {
            cout << "\nIncorrect Admin Password! Access Denied.";
            return;
        }

        string userID;
        cout << "\nEnter User ID to adjust balance: ";
        cin >> userID;

        bool found = false;
        for (auto& user : users) {
            if (user.getID() == userID) {
                float adjustment;
                system("cls");
                cout << "\nEnter balance adjustment amount: ";
                cin >> adjustment;
                cout << "Add OR Remove money from the amount? (A/R): ";
                char ch;
                cin >> ch;
                if (ch == 'a' || ch == 'A') {
                    user.setAmount(user.getAmount() + adjustment);
                } else if (ch == 'r' || ch == 'R') {
                    user.setAmount(user.getAmount() - adjustment);
                }
                cout << "\nBalance adjusted successfully! New Balance: " << user.getAmount();
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "\nUser ID not found!";
        }
    }
};

// Friend function
void displayAllUsers(const vector<User>& users) {
    string password;
    system("cls");
    cout << "\nEnter admin password: ";
    cin >> password;
    if (password == "admin123") {
        cout << "\n\nALL REGISTERED USERS";
        for (const auto& user : users) {
            cout << "\nName: " << user.getName();
            cout << "\nID: " << user.getID();
        }
    } else {
        cout << "\nAccess Denied! Password Incorrect!";
    }
}

// Display heading
void heading() {
    char ch = 178;
    cout << "\n ";
    for (int i = 1; i <= 26; i++) cout << ch;
    cout << " BANK MANAGEMENT SYSTEM ";
    for (int i = 1; i <= 26; i++) cout << ch;
    cout << endl;
}

// Main Function
int main() {
    vector<User> users;
    User u;
    Admin ad;
    short int choice;

    do {
        system("cls");
        heading();

        cout << "\n\n1. Add Account";
        cout << "\n\n2. Search Account";
        cout << "\n\n3. Deposit Money";
        cout << "\n\n4. Withdraw Money";
        cout << "\n\n5. Adjust User Balance (Admin)";
        cout << "\n\n6. Show all accounts";
        cout << "\n\n7. Exit";
        cout << "\n\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: u.add_user(users); break;
            case 2: u.search_user(users); break;
            case 3: u.deposit_money(users); break;
            case 4: u.withdraw_money(users); break;
            case 5: ad.adjust_user_balance(users); cin.ignore(); cin.get(); break;
            case 6: displayAllUsers(users); cin.ignore(); cin.get(); break;
            case 7: cout << "\nProgram Ended."; break;
            default: cout << "\n\nInvalid choice!"; cin.ignore(); cin.get();
        }
    } while (choice != 7);

    return 0;
}

