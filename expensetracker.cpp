#include "MyLibraries.h"
#include "expense.h"

using namespace std;

// Prototypes
void setBudget(double &budget);
void displayMenu();
void handleMenu(vector<Expense>* expensesDataBasePtr, double* budgetPtr);
void addExpense(vector<Expense>* expensesDataBasePtr, double* budgetPtr);
void viewExpenses(vector<Expense>* expensesDataBasePtr);
void viewTotalExpenses(vector<Expense>* expensesDataBasePtr);
void editExpense(vector<Expense>* expenseDataBasePtr); // *TODO* - Must update budget if                            expense cost is updated. Must add old expense cost back to budget.
void exportToFile(vector<Expense>* expenseDataBasePtr, double* budgetPtr);

// ---------------------------------------------

int main()
{
    double budget = 0.0;
    double* budgetPtr = &budget;
    vector<Expense> expensesDataBase;
    vector<Expense>* expensesDataBasePtr = &expensesDataBase;
    setBudget(budget);
    displayMenu();

    while (true)
    {
        handleMenu(expensesDataBasePtr, budgetPtr);
    }
    
    return 0;
}

void setBudget(double &budget)
{
    cout << "Enter your budget: $";
    cin >> budget;
    cout << "\n";
}

void displayMenu()
{
    cout << setw(29) << setfill('=') << '=' << endl;
    cout << right << setw(22)  << setfill(' ') << "EXPENSE TRACKER" << endl;
    cout << setw(29) << setfill('=') << '=' << endl;

    cout << "1. Add New Expense\n";
    cout << "2. View Expenses\n";
    cout << "3. View Total Expenses\n";
    cout << "4. Edit An Expense\n";
    cout << "5. Export to CSV\n";
    cout << "6. Exit\n";

    // cout << "View Budget Summary\n";              *TO BE ADDED*

    cout << setw(30) << setfill('-') << '-' << endl;
}

void handleMenu(vector<Expense>* expensesDataBasePtr, double* budgetPtr)
{
    int userInput;

    while (true)
    {
        cout << "\nEnter your choice: ";
        cin >> userInput;
        cin.ignore();

        if (userInput > 6 || userInput < 1){cout << "Please select a valid option.\n";}
        else {break;}
    }
    
    switch (userInput)
    {
    case 1:
        addExpense(expensesDataBasePtr, budgetPtr);
        break;
    case 2:
        viewExpenses(expensesDataBasePtr);
        break;
    case 3:
        viewTotalExpenses(expensesDataBasePtr);
        break;
    case 4:
        editExpense(expensesDataBasePtr);
        break;
    case 5:
        exportToFile(expensesDataBasePtr, budgetPtr);
        break;
    case 6:
        exit(0);
    }
}

void addExpense(vector<Expense>* expensesDataBasePtr, double* budgetPtr)
{
    string expenseName, expenseCategory;
    double expenseCost;
    char userInput;

    do
    {
        cout << "Enter description: ";
        getline(cin, expenseName);
        cout << "Enter category: ";
        getline(cin, expenseCategory);
        cout << "Enter amount: $";
        cin >> expenseCost;
        cout << "Would you like to enter another expense (Y / N): ";
        cin >> userInput;
        cin.ignore();
        expensesDataBasePtr->push_back(Expense(expenseName, expenseCategory, expenseCost));
        
        *budgetPtr = *budgetPtr - expenseCost;

    } while (toupper(userInput) != 'N');
    
    cout << "\nRemaining Budget: $" << *budgetPtr << endl;
}

void viewExpenses(vector<Expense>* expensesDataBasePtr)
{
    cout << "\n" << left << setw(10) << setfill('=') << '=' << " Expenses "
    << right << setw(10) << setfill('=') << '=' << endl;

    cout << left << setw(5) << setfill(' ')<< "No."
    << setw(20) << "Description"
    << setw(15) << "Category"
    << setw(5) << "Amount" << endl;

    for (int i = 0; i < expensesDataBasePtr->size(); i++)
    {
        cout << setw(5) << i + 1;
        cout << setw(20) << (*expensesDataBasePtr)[i].getExpenseName();
        cout << setw(15) << (*expensesDataBasePtr)[i].getExpenseCategory();
        cout << "$" << showpoint  << fixed << setprecision(2)
        << (*expensesDataBasePtr)[i].getExpenseCost() << endl;
    }
}

void viewTotalExpenses(vector<Expense>* expensesDataBasePtr)
{
    double total = 0.0;

    if (expensesDataBasePtr->empty())
    {
        cout << "No expense has been recorded yet." << endl;
        return;
    }
    
    for (int i = 0; i < expensesDataBasePtr->size(); i++)
    {
        total += (*expensesDataBasePtr)[i].getExpenseCost();
    }

    cout << "\n" << left << setw(7) << setfill('=') << '=' << " Total Expenses "
    << right << setw(7) << setfill('=') << '=' << endl;

    cout << showpoint  << fixed << setprecision(2);
    cout << "Total of expenses: $" << total << endl;
    cout << "Items recorded: " << expensesDataBasePtr->size() << endl;
}

void editExpense(vector<Expense>* expenseDataBasePtr)
{
    int expenseNumber = 0;
    string expenseName, expenseCategory;
    double expenseCost;
    
    viewExpenses(expenseDataBasePtr);
    
    cout << "\nExpense # to edit: ";
    cin >> expenseNumber;
    cin.ignore();
    
    cout << "Enter expense name: ";
    getline(cin, expenseName);
    cout << "Enter expense category: ";
    getline(cin, expenseCategory);
    cout << "Enter expense cost: ";
    cin >> expenseCost;
    
    (*expenseDataBasePtr)[expenseNumber - 1].setExpenseName(expenseName);
    (*expenseDataBasePtr)[expenseNumber - 1].setExpenseCategory(expenseCategory);
    (*expenseDataBasePtr)[expenseNumber - 1].setExpenseCost(expenseCost);

    cout << "\nExpense #" << expenseNumber << " updated.\n";
}

void exportToFile(vector<Expense>* expenseDataBasePtr, double* budgetPtr)
{
    ofstream expensesFile("/Users/fud/Documents/expenses.csv");
    
    expensesFile << "Budget" << ',' << *budgetPtr << endl;
    
    expensesFile << "Expense Name" << ',' << "Expense Category" << ',' << "Expense Cost" << endl;
    
    for (int i = 0; i < (*expenseDataBasePtr).size(); i++)
    {
        expensesFile << (*expenseDataBasePtr)[i].getExpenseName() << ','
        << (*expenseDataBasePtr)[i].getExpenseCategory() << ',' <<
        (*expenseDataBasePtr)[i].getExpenseCost() << endl;
    }
        
    cout << "\nExpense file created and exported.\n";
}
