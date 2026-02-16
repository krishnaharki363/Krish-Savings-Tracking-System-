#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

// ANSI Color Codes
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define MAGENTA "\033[35m"
#define RED     "\033[31m"

// Helper function to print header
void printMainHeader() {
    cout << CYAN << BOLD;
    cout << "\n╔════════════════════════════════════════════╗\n";
    cout << "║        💰 SAVINGS TRACKER SYSTEM 💰       ║\n";
    cout << "║       Track Your Goals, Build Wealth      ║\n";
    cout << "╚════════════════════════════════════════════╝\n";
    cout << RESET;
}

// Helper function for progress bar
void printProgressBar(double current, double goal) {
    if (goal <= 0) return;
    double percentage = (current / goal) * 100;
    int filled = static_cast<int>(percentage / 5);
    cout << GREEN;
    cout << "  [";
    for (int i = 0; i < 20; i++) {
        if (i < filled) cout << "█";
        else cout << "░";
    }
    cout << "] " << YELLOW << fixed << setprecision(1) << percentage << "%" << RESET << "\n";
}

class SavingsTracker {
private:
    string userName;
    double savingsGoal;
    double currentSavings;
    string goalDeadline; // optional
    vector<pair<string, double>> withdrawalHistory; // track withdrawals

public:
    // Default constructor
    SavingsTracker() {
        userName = "Unknown";
        savingsGoal = 0.0;
        currentSavings = 0.0;
        goalDeadline = "N/A";
    }

    // Parameterized constructor
    SavingsTracker(string name, double goal, string deadline = "N/A") {
        userName = name;
        savingsGoal = goal;
        currentSavings = 0.0;
        goalDeadline = deadline;
    }

    // Set savings goal
    void setGoal() {
        cout << "\n" << BLUE << BOLD;
        cout << "┌─────────────────────────────────────────┐\n";
        cout << "│       ⚙️  SET SAVINGS GOAL ⚙️          │\n";
        cout << "└─────────────────────────────────────────┘\n";
        cout << RESET;
        
        cout << CYAN << "Enter your name: " << RESET;
        cin.ignore();
        getline(cin, userName);
        
        cout << YELLOW << "Enter your savings goal amount (NPR): " << RESET;
        cin >> savingsGoal;
        cin.ignore();
        
        cout << MAGENTA << "Enter your goal deadline (optional): " << RESET;
        getline(cin, goalDeadline);
        
        currentSavings = 0.0;
        withdrawalHistory.clear();
        
        cout << GREEN << BOLD << "\n✓ Goal set successfully!\n" << RESET << "\n";
    }

    // Add savings
    void addSavings() {
        double amount;
        cout << "\n" << GREEN << BOLD;
        cout << "┌─────────────────────────────────────────┐\n";
        cout << "│       ➕ ADD SAVINGS ➕               │\n";
        cout << "└─────────────────────────────────────────┘\n";
        cout << RESET;
        
        cout << CYAN << "Enter amount to add (NPR): " << RESET;
        cin >> amount;
        
        if (amount > 0) {
            currentSavings += amount;
            cout << GREEN << BOLD << "✓ Amount added successfully!\n";
            cout << "Current savings: NPR " << fixed << setprecision(2) << currentSavings << RESET << "\n\n";
        } else {
            cout << RED << BOLD << "❌ Invalid amount. Must be positive.\n" << RESET << "\n";
        }
    }

    // Withdraw savings
    void withdrawSavings() {
        double amount;
        cout << "\n" << YELLOW << BOLD;
        cout << "┌─────────────────────────────────────────┐\n";
        cout << "│      🏦 WITHDRAW SAVINGS 🏦            │\n";
        cout << "└─────────────────────────────────────────┘\n";
        cout << RESET;
        
        cout << CYAN << "Enter amount to withdraw (NPR): " << RESET;
        cin >> amount;
        
        if (amount > 0 && amount <= currentSavings) {
            currentSavings -= amount;
            withdrawalHistory.push_back({"Withdrawal", amount});
            cout << GREEN << BOLD << "✓ Withdrawal successful!\n";
            cout << "Remaining savings: NPR " << fixed << setprecision(2) << currentSavings << RESET << "\n\n";
        } else if (amount > currentSavings) {
            cout << RED << BOLD << "❌ Error: Insufficient funds.\n";
            cout << "Current balance: NPR " << fixed << setprecision(2) << currentSavings << RESET << "\n\n";
        } else {
            cout << RED << BOLD << "❌ Invalid amount. Must be positive.\n" << RESET << "\n";
        }
    }

    // Show progress
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

    // Check if goal is achieved
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
    
    // Show all data
    void showAllData() {
        cout << "\n" << BLUE << BOLD;
        cout << "┌─────────────────────────────────────────┐\n";
        cout << "│       📁 ALL ACCOUNT DATA 📁           │\n";
        cout << "└─────────────────────────────────────────┘\n";
        cout << RESET;
        
        cout << CYAN << "User Name: " << BOLD << userName << RESET << "\n";
        cout << YELLOW << "Savings Goal: " << BOLD << "NPR " << fixed << setprecision(2) << savingsGoal << RESET << "\n";
        cout << GREEN << "Current Savings: " << BOLD << "NPR " << fixed << setprecision(2) << currentSavings << RESET << "\n";
        cout << MAGENTA << "Goal Deadline: " << BOLD << goalDeadline << RESET << "\n";
        
        if (withdrawalHistory.empty()) {
            cout << YELLOW << "\nNo withdrawal history.\n" << RESET << "\n";
        } else {
            cout << "\n" << CYAN << BOLD << "Withdrawal History:\n" << RESET;
            for (int i = 0; i < withdrawalHistory.size(); i++) {
                cout << "  " << (i + 1) << ". " << YELLOW << withdrawalHistory[i].first << ": " << RED 
                     << "NPR " << fixed << setprecision(2) << withdrawalHistory[i].second << RESET << "\n";
            }
            cout << "\n";
        }
    }
    
    // Withdrawal analysis
    void withdrawalAnalysis() {
        cout << "\n" << MAGENTA << BOLD;
        cout << "┌─────────────────────────────────────────┐\n";
        cout << "│    📊 WITHDRAWAL ANALYSIS 📊           │\n";
        cout << "└─────────────────────────────────────────┘\n";
        cout << RESET;
        
        if (withdrawalHistory.empty()) {
            cout << YELLOW << "No withdrawals made yet.\n" << RESET << "\n";
            return;
        }
        
        double totalWithdrawn = 0;
        for (auto& entry : withdrawalHistory) {
            totalWithdrawn += entry.second;
        }
        
        cout << CYAN << "Total withdrawals: " << BOLD << withdrawalHistory.size() << RESET << "\n";
        cout << YELLOW << "Total amount withdrawn: " << BOLD << "NPR " << fixed << setprecision(2) << totalWithdrawn << RESET << "\n";
        cout << GREEN << "Average withdrawal: " << BOLD << "NPR " << fixed << setprecision(2) << (totalWithdrawn / withdrawalHistory.size()) << RESET << "\n\n";
    }

    // Optional: Save data to file
    void saveData() {
        ofstream outFile("savings_data.txt");
        if (outFile.is_open()) {
            outFile << userName << "\n";
            outFile << savingsGoal << "\n";
            outFile << currentSavings << "\n";
            outFile << goalDeadline << "\n";
            // Save withdrawal history
            outFile << withdrawalHistory.size() << "\n";
            for (auto& entry : withdrawalHistory) {
                outFile << entry.first << "," << entry.second << "\n";
            }
            outFile.close();
            cout << GREEN << BOLD << "✓ Data saved successfully.\n" << RESET << "\n";
        } else {
            cout << RED << BOLD << "❌ Error saving data.\n" << RESET << "\n";
        }
    }

    // Optional: Load data from file
    void loadData() {
        ifstream inFile("savings_data.txt");
        if (inFile.is_open()) {
            getline(inFile, userName);
            inFile >> savingsGoal;
            inFile >> currentSavings;
            inFile.ignore();
            getline(inFile, goalDeadline);
            
            int historyCount;
            inFile >> historyCount;
            inFile.ignore();
            
            withdrawalHistory.clear();
            for (int i = 0; i < historyCount; i++) {
                string line;
                getline(inFile, line);
                int commaPos = line.find(',');
                string type = line.substr(0, commaPos);
                double amount = stod(line.substr(commaPos + 1));
                withdrawalHistory.push_back({type, amount});
            }
            
            inFile.close();
            cout << GREEN << BOLD << "✓ Data loaded successfully.\n" << RESET << "\n";
        } else {
            cout << YELLOW << "⚠️ No saved data found.\n" << RESET << "\n";
        }
    }
};

// Menu-driven system
void showMenu() {
    cout << "\n" << BOLD << YELLOW;
    cout << "╔════════════════════════════════════════════╗\n";
    cout << "║              MAIN MENU                    ║\n";
    cout << "╚════════════════════════════════════════════╝\n";
    cout << RESET;
    
    cout << CYAN << "  " << BOLD << "1" << RESET << CYAN << " - Set Savings Goal\n";
    cout << GREEN << "  " << BOLD << "2" << RESET << GREEN << " - Add Savings\n";
    cout << YELLOW << "  " << BOLD << "3" << RESET << YELLOW << " - Withdraw Savings\n";
    cout << BLUE << "  " << BOLD << "4" << RESET << BLUE << " - Show Savings Progress\n";
    cout << MAGENTA << "  " << BOLD << "5" << RESET << MAGENTA << " - Check Goal Status\n";
    cout << CYAN << "  " << BOLD << "6" << RESET << CYAN << " - Show All Data\n";
    cout << GREEN << "  " << BOLD << "7" << RESET << GREEN << " - Withdrawal Analysis\n";
    cout << YELLOW << "  " << BOLD << "8" << RESET << YELLOW << " - Save Data\n";
    cout << BLUE << "  " << BOLD << "9" << RESET << BLUE << " - Load Data\n";
    cout << RED << "  " << BOLD << "0" << RESET << RED << " - Exit\n";
    
    cout << "\n" << BOLD << CYAN << "Enter your choice (0-9): " << RESET;
}

int main() {
    SavingsTracker tracker;
    int choice;
    
    printMainHeader();

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            tracker.setGoal();
            break;
        case 2:
            tracker.addSavings();
            break;
        case 3:
            tracker.withdrawSavings();
            break;
        case 4:
            tracker.showProgress();
            break;
        case 5:
            tracker.checkGoalStatus();
            break;
        case 6:
            tracker.showAllData();
            break;
        case 7:
            tracker.withdrawalAnalysis();
            break;
        case 8:
            tracker.saveData();
            break;
        case 9:
            tracker.loadData();
            break;
        case 0:
            cout << "\n" << GREEN << BOLD;
            cout << "╔════════════════════════════════════════════╗\n";
            cout << "║  Thank you for using Savings Tracker!     ║\n";
            cout << "║     Keep saving, keep growing! 📈         ║\n";
            cout << "╚════════════════════════════════════════════╝\n";
            cout << RESET << "\n";
            break;
        default:
            cout << "\n" << RED << BOLD << "❌ Invalid choice. Please enter 0-9.\n" << RESET << "\n";
        }

    } while (choice != 0);

    return 0;
}
