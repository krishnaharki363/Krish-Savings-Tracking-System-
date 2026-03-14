#include <iostream> // for cin and cout
#include <fstream>  // for file handling
#include <string>  // for string data 
#include <iomanip> // for formatting like setprecision 
#include <vector> // to store transcation history 
#include <ctime> // to get data and time 


using namespace std;

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define MAGENTA "\033[35m"
#define RED     "\033[31m"

struct Transaction {  //structure stores one transcation and i
    string type;
    double amount;
    string timestamp;
};

void printMainHeader() {
    cout << CYAN << BOLD;
    cout << "\n╔════════════════════════════════════════════╗\n";
    cout << "║        💰 SAVINGS TRACKER SYSTEM 💰       ║\n";
    cout << "║       Track Your Goals, Build Wealth      ║\n";
    cout << "╚════════════════════════════════════════════╝\n";
    cout << RESET;
}
// // Calculate how many blocks of the progress bar should be filled
// The progress bar has 20 blocks, and 100% / 20 = 5% per block
// So we divide the percentage by 5 to know how many blocks to fill
// static_cast<int> converts the result into an integer (whole number)
void printProgressBar(double current, double goal) {
    if (goal <= 0) return;
    double percentage = (current / goal) * 100;
    int filled = static_cast<int>(percentage / 5);
    cout << GREEN;
    cout << "  ["; //start of the test bar in gree color
    for (int i = 0; i < 20; i++) {
        if (i < filled) cout << "█";
        else cout << "░";
    }
    cout << "] " << YELLOW << fixed << setprecision(1) << percentage << "%" << RESET << "\n";
}

string getCurrentTimestamp() {
    time_t now = time(0); //it gets the cuurent time from the system clock
    struct tm* timeinfo = localtime(&now); //localtime() converts the seconds into human-readable time components based on your system's local timezone.
    char buffer[80]; //This creates a temporary storage space to hold the formatted time string.
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    return string(buffer);
}

class SavingsTracker {
private:
    string userName;
    double savingsGoal;
    double currentSavings;
    string goalDeadline;
    vector<Transaction> transactionHistory;

public:
    SavingsTracker() {
        userName = "Unknown";
        savingsGoal = 0.0;
        currentSavings = 0.0;
        goalDeadline = "N/A";
    }

    SavingsTracker(string name, double goal, string deadline = "N/A") {
        userName = name;
        savingsGoal = goal;
        currentSavings = 0.0;
        goalDeadline = deadline;
    }

    string getUserName() const {
        return userName;
    }

    void setGoal() {
        cout << "\n" << BLUE << BOLD;
        cout << "┌─────────────────────────────────────────┐\n";
        cout << "│       ⚙️  SET SAVINGS GOAL ⚙️          │\n";
        cout << "└─────────────────────────────────────────┘\n";
        cout << RESET;
        cout << YELLOW << "Enter your savings goal amount (NPR): " << RESET;
        cin >> savingsGoal;
        cin.ignore();
        cout << MAGENTA << "Enter your goal deadline (optional): " << RESET;
        getline(cin, goalDeadline);
        cout << GREEN << BOLD << "\n✓ Goal set successfully!\n" << RESET << "\n";
    }

    void deposit() {
        double amount;
        cout << "\n" << GREEN << BOLD;
        cout << "┌─────────────────────────────────────────┐\n";
        cout << "│       💵 DEPOSIT MONEY 💵              │\n";
        cout << "└─────────────────────────────────────────┘\n";
        cout << RESET;
        cout << CYAN << "Enter amount to deposit (NPR): " << RESET;
        cin >> amount;
        if (amount > 0) {
            currentSavings += amount;
            transactionHistory.push_back({"Deposit", amount, getCurrentTimestamp()});
            cout << GREEN << BOLD << "✓ Deposit successful!\n";
            cout << "Current balance: NPR " << fixed << setprecision(2) << currentSavings << RESET << "\n\n";
        } else {
            cout << RED << BOLD << "❌ Invalid amount. Must be positive.\n" << RESET << "\n";
        }
    }

    void withdraw() {
        double amount;
        cout << "\n" << YELLOW << BOLD;
        cout << "┌─────────────────────────────────────────┐\n";
        cout << "│      🏦 WITHDRAW MONEY 🏦             │\n";
        cout << "└─────────────────────────────────────────┘\n";
        cout << RESET;
        cout << CYAN << "Enter amount to withdraw (NPR): " << RESET;
        cin >> amount;
        if (amount > 0 && amount <= currentSavings) {
            currentSavings -= amount;
            transactionHistory.push_back({"Withdrawal", amount, getCurrentTimestamp()});
            cout << GREEN << BOLD << "✓ Withdrawal successful!\n";
            cout << "Remaining balance: NPR " << fixed << setprecision(2) << currentSavings << RESET << "\n\n";
        } else if (amount > currentSavings) {
            cout << RED << BOLD << "❌ Error: Insufficient funds.\n";
            cout << "Current balance: NPR " << fixed << setprecision(2) << currentSavings << RESET << "\n\n";
        } else {
            cout << RED << BOLD << "❌ Invalid amount. Must be positive.\n" << RESET << "\n";
        }
    }

    void checkBalance() {
        cout << "\n" << BLUE << BOLD;
        cout << "┌─────────────────────────────────────────┐\n";
        cout << "│       💳 ACCOUNT BALANCE 💳            │\n";
        cout << "└─────────────────────────────────────────┘\n";
        cout << RESET;
        cout << CYAN << "Current balance: " << BOLD << "NPR " << fixed << setprecision(2) << currentSavings << RESET << "\n\n";
    }

    void showProgress() {
        cout << "\n" << BLUE << BOLD;
        cout << "┌─────────────────────────────────────────┐\n";
        cout << "│       📊 SAVINGS PROGRESS REPORT 📊     │\n";
        cout << "└─────────────────────────────────────────┘\n";
        cout << RESET;
        cout << CYAN << "  User: " << BOLD << userName << RESET << "\n";
        cout << YELLOW << "  Goal: " << BOLD << "NPR " << fixed << setprecision(2) << savingsGoal << RESET << "\n";
        cout << GREEN << "  Saved: " << BOLD << "NPR " << fixed << setprecision(2) << currentSavings << RESET << "\n";
        cout << "\n" << MAGENTA << "  Progress:\n" << RESET;
        printProgressBar(currentSavings, savingsGoal);
        if (savingsGoal > 0) {
            if (currentSavings >= savingsGoal) {
                cout << "\n" << GREEN << BOLD;
                cout << "  ✓ ★ GOAL ACHIEVED! CONGRATULATIONS! ★\n";
                cout << "  You have successfully reached your savings goal!\n";
                cout << RESET;
            } else {
                double remaining = savingsGoal - currentSavings;
                cout << "\n" << CYAN << "  Remaining: " << BOLD << RED << "NPR " << fixed << setprecision(2) << remaining << RESET << "\n";
            }
        }
        if (goalDeadline != "N/A") {
            cout << YELLOW << "  Deadline: " << BOLD << goalDeadline << RESET << "\n";
        }
        cout << "\n";
    }

    void showTransactionHistory() {
        cout << "\n" << MAGENTA << BOLD;
        cout << "┌─────────────────────────────────────────┐\n";
        cout << "│      📋 TRANSACTION HISTORY 📋         │\n";
        cout << "└─────────────────────────────────────────┘\n";
        cout << RESET;
        if (transactionHistory.empty()) {
            cout << YELLOW << "No transactions yet.\n" << RESET << "\n";
            return;
        }
        cout << CYAN << BOLD << left << setw(15) << "Type" << setw(15) << "Amount (NPR)" << "Date & Time" << RESET << "\n";
        cout << string(50, '-') << "\n";
        for (const auto& trans : transactionHistory) {
            if (trans.type == "Deposit") {
                cout << GREEN;
            } else {
                cout << YELLOW;
            }
            cout << left << setw(15) << trans.type << setw(15) << fixed << setprecision(2) << trans.amount << trans.timestamp << RESET << "\n";
        }
        cout << "\n";
    }

    void checkGoalStatus() {
        cout << "\n" << MAGENTA << BOLD;
        cout << "┌─────────────────────────────────────────┐\n";
        cout << "│         📋 GOAL STATUS 📋             │\n";
        cout << "└─────────────────────────────────────────┘\n";
        cout << RESET;
        if (savingsGoal <= 0) {
            cout << YELLOW << "Please set a savings goal first.\n" << RESET << "\n";
            return;
        }
        cout << CYAN << "Name: " << BOLD << userName << RESET << "\n";
        if (currentSavings >= savingsGoal) {
            cout << GREEN << BOLD;
            cout << "Status: ✓ GOAL ACHIEVED!\n";
            cout << "Saved: NPR " << fixed << setprecision(2) << currentSavings << "\n";
            cout << "Goal: NPR " << fixed << setprecision(2) << savingsGoal << RESET << "\n\n";
        } else {
            double remaining = savingsGoal - currentSavings;
            cout << YELLOW << "Status: IN PROGRESS\n" << RESET;
            cout << CYAN << "Saved: " << BOLD << "NPR " << fixed << setprecision(2) << currentSavings << RESET << "\n";
            cout << YELLOW << "Goal: " << BOLD << "NPR " << fixed << setprecision(2) << savingsGoal << RESET << "\n";
            cout << RED << "Still need: " << BOLD << "NPR " << fixed << setprecision(2) << remaining << RESET << "\n\n";
        }
    }

    void showAllData() {
        cout << "\n" << BLUE << BOLD;
        cout << "┌─────────────────────────────────────────┐\n";
        cout << "│       📁 ALL ACCOUNT DATA 📁           │\n";
        cout << "└─────────────────────────────────────────┘\n";
        cout << RESET;
        cout << CYAN << "User Name: " << BOLD << userName << RESET << "\n";
        cout << YELLOW << "Savings Goal: " << BOLD << "NPR " << fixed << setprecision(2) << savingsGoal << RESET << "\n";
        cout << GREEN << "Current Balance: " << BOLD << "NPR " << fixed << setprecision(2) << currentSavings << RESET << "\n";
        cout << MAGENTA << "Goal Deadline: " << BOLD << goalDeadline << RESET << "\n";
        showTransactionHistory();
    }

    void saveData() {
        ofstream outFile("users/" + userName + "_account.txt");
        if (outFile.is_open()) {
            outFile << userName << "\n";
            outFile << fixed << setprecision(2) << savingsGoal << "\n";
            outFile << fixed << setprecision(2) << currentSavings << "\n";
            outFile << goalDeadline << "\n";
            outFile << transactionHistory.size() << "\n";
            for (const auto& trans : transactionHistory) {
                outFile << trans.type << "|" << fixed << setprecision(2) << trans.amount << "|" << trans.timestamp << "\n";
            }
            outFile.close();
            cout << GREEN << BOLD << "✓ Data saved successfully.\n" << RESET << "\n";
        } else {
            cout << RED << BOLD << "❌ Error saving data.\n" << RESET << "\n";
        }
    }

    void loadData() {
        ifstream inFile("users/" + userName + "_account.txt");
        if (inFile.is_open()) {
            string storedName;
            getline(inFile, storedName);
            userName = storedName;
            inFile >> savingsGoal;
            inFile >> currentSavings;
            inFile.ignore();
            getline(inFile, goalDeadline);
            int transCount;
            inFile >> transCount;
            inFile.ignore();
            transactionHistory.clear();
            for (int i = 0; i < transCount; i++) {
                string line;
                getline(inFile, line);
                int pos1 = line.find('|');
                int pos2 = line.find('|', pos1 + 1);
                string type = line.substr(0, pos1);
                double amount = stod(line.substr(pos1 + 1, pos2 - pos1 - 1));
                string timestamp = line.substr(pos2 + 1);
                transactionHistory.push_back({type, amount, timestamp});
            }
            inFile.close();
        }
    }
};

class User {
private:
    string username;
    string password;

public:
    User(string u, string p) : username(u), password(p) {}

    string getUsername() const {
        return username;
    }

    string getPassword() const {
        return password;
    }

    void saveCredentials() {
        ofstream userFile("users/users_list.txt", ios::app);
        if (userFile.is_open()) {
            userFile << username << "|" << password << "\n";
            userFile.close();
        }
    }

    static bool userExists(string u) {
        ifstream userFile("users/users_list.txt");
        if (userFile.is_open()) {
            string line;
            while (getline(userFile, line)) {
                int pos = line.find('|');
                string storedUsername = line.substr(0, pos);
                if (storedUsername == u) {
                    userFile.close();
                    return true;
                }
            }
            userFile.close();
        }
        return false;
    }

    static bool verifyCredentials(string u, string p) {
        ifstream userFile("users/users_list.txt");
        if (userFile.is_open()) {
            string line;
            while (getline(userFile, line)) {
                int pos = line.find('|');
                string storedUsername = line.substr(0, pos);
                string storedPassword = line.substr(pos + 1);
                if (storedUsername == u && storedPassword == p) {
                    userFile.close();
                    return true;
                }
            }
            userFile.close();
        }
        return false;
    }
};

void registerUser() {
    cout << "\n" << GREEN << BOLD;
    cout << "┌─────────────────────────────────────────┐\n";
    cout << "│          📝 USER REGISTRATION 📝       │\n";
    cout << "└─────────────────────────────────────────┘\n";
    cout << RESET;

    string username, password;
    cout << CYAN << "Enter username: " << RESET;
    cin >> username;

    if (User::userExists(username)) {
        cout << RED << BOLD << "❌ Username already exists!\n" << RESET << "\n";
        return;
    }

    cout << CYAN << "Enter password: " << RESET;
    cin >> password;

    if (password.length() < 3) {
        cout << RED << BOLD << "❌ Password must be at least 3 characters!\n" << RESET << "\n";
        return;
    }

    User newUser(username, password);
    newUser.saveCredentials();
    cout << GREEN << BOLD << "✓ Account created successfully!\n" << RESET << "\n";
}

SavingsTracker* loginUser() {
    cout << "\n" << BLUE << BOLD;
    cout << "┌─────────────────────────────────────────┐\n";
    cout << "║          🔐 USER LOGIN 🔐             ║\n";
    cout << "└─────────────────────────────────────────┘\n";
    cout << RESET;

    string username, password;
    cout << CYAN << "Enter username: " << RESET;
    cin >> username;

    cout << CYAN << "Enter password: " << RESET;
    cin >> password;

    if (!User::verifyCredentials(username, password)) {
        cout << RED << BOLD << "❌ Invalid credentials!\n" << RESET << "\n";
        return nullptr;
    }

    cout << GREEN << BOLD << "✓ Login successful!\n" << RESET << "\n";

    SavingsTracker* tracker = new SavingsTracker(username, 0.0);
    tracker->loadData();
    return tracker;
}

void showMenu() {
    cout << "\n" << BOLD << YELLOW;
    cout << "╔════════════════════════════════════════════╗\n";
    cout << "║              ACCOUNT MENU                 ║\n";
    cout << "╚════════════════════════════════════════════╝\n";
    cout << RESET;

    cout << CYAN << "  " << BOLD << "1" << RESET << CYAN << " - Set Savings Goal\n";
    cout << GREEN << "  " << BOLD << "2" << RESET << GREEN << " - Deposit Money\n";
    cout << YELLOW << "  " << BOLD << "3" << RESET << YELLOW << " - Withdraw Money\n";
    cout << BLUE << "  " << BOLD << "4" << RESET << BLUE << " - Check Balance\n";
    cout << MAGENTA << "  " << BOLD << "5" << RESET << MAGENTA << " - Show Progress\n";
    cout << CYAN << "  " << BOLD << "6" << RESET << CYAN << " - View Transaction History\n";
    cout << GREEN << "  " << BOLD << "7" << RESET << GREEN << " - Check Goal Status\n";
    cout << YELLOW << "  " << BOLD << "8" << RESET << YELLOW << " - Show All Data\n";
    cout << BLUE << "  " << BOLD << "9" << RESET << BLUE << " - Save Data\n";
    cout << RED << "  " << BOLD << "0" << RESET << RED << " - Logout\n";

    cout << "\n" << BOLD << CYAN << "Enter your choice (0-9): " << RESET;
}

void showMainMenu() {
    cout << "\n" << BOLD << YELLOW;
    cout << "╔════════════════════════════════════════════╗\n";
    cout << "║             MAIN MENU                     ║\n";
    cout << "╚════════════════════════════════════════════╝\n";
    cout << RESET;

    cout << GREEN << "  " << BOLD << "1" << RESET << GREEN << " - Login\n";
    cout << CYAN << "  " << BOLD << "2" << RESET << CYAN << " - Register\n";
    cout << RED << "  " << BOLD << "0" << RESET << RED << " - Exit\n";

    cout << "\n" << BOLD << CYAN << "Enter your choice: " << RESET;
}

int main() {
    printMainHeader();
    int mainChoice;
    SavingsTracker* currentUser = nullptr;

    do {
        showMainMenu();
        cin >> mainChoice;

        if (mainChoice == 1) {
            currentUser = loginUser();
            if (currentUser != nullptr) {
                int choice;
                do {
                    showMenu();
                    cin >> choice;

                    switch (choice) {
                    case 1:
                        currentUser->setGoal();
                        break;
                    case 2:
                        currentUser->deposit();
                        break;
                    case 3:
                        currentUser->withdraw();
                        break;
                    case 4:
                        currentUser->checkBalance();
                        break;
                    case 5:
                        currentUser->showProgress();
                        break;
                    case 6:
                        currentUser->showTransactionHistory();
                        break;
                    case 7:
                        currentUser->checkGoalStatus();
                        break;
                    case 8:
                        currentUser->showAllData();
                        break;
                    case 9:
                        currentUser->saveData();
                        break;
                    case 0:
                        currentUser->saveData();
                        cout << "\n" << CYAN << BOLD;
                        cout << "╔════════════════════════════════════════════╗\n";
                        cout << "║         Thank you for using the app!      ║\n";
                        cout << "║            Logout successful! 👋          ║\n";
                        cout << "╚════════════════════════════════════════════╝\n";
                        cout << RESET << "\n";
                        break;
                    default:
                        cout << "\n" << RED << BOLD << "❌ Invalid choice. Please enter 0-9.\n" << RESET << "\n";
                    }
                } while (choice != 0);

                delete currentUser;
                currentUser = nullptr;
            }
        } else if (mainChoice == 2) {
            registerUser();
        } else if (mainChoice == 0) {
            cout << "\n" << GREEN << BOLD;
            cout << "╔════════════════════════════════════════════╗\n";
            cout << "║  Thank you for using Savings Tracker!     ║\n";
            cout << "║     Keep saving, keep growing! 📈         ║\n";
            cout << "╚════════════════════════════════════════════╝\n";
            cout << RESET << "\n";
        } else {
            cout << "\n" << RED << BOLD << "❌ Invalid choice. Please try again.\n" << RESET << "\n";
        }
    } while (mainChoice != 0);

    return 0;
}

