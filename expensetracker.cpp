#include "MyLibraries.h"
#include "expense.h"

using namespace std;

// Prototypes
void setBudget(double &budget);
void displayMenu();
void handleMenu(vector<Expense>* expensesDataBasePtr);
void addExpense(vector<Expense>* expensesDataBasePtr);
void viewExpenses(vector<Expense>* expensesDataBasePtr);
void viewTotalExpenses(vector<Expense>* expensesDataBasePtr);

// ---------------------------------------------

int main()
{
    double budget = 0.0;
    vector<Expense> expensesDataBase;
    vector<Expense>* expensesDataBasePtr = &expensesDataBase; 

    setBudget(budget);
    displayMenu();

    while (true)
    {
        handleMenu(expensesDataBasePtr);
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
    cout << "4. Exit\n";

    // cout << "5. View Budget Summary\n";              *TO BE ADDED*

    cout << setw(30) << setfill('-') << '-' << endl;
} 

void handleMenu(vector<Expense>* expensesDataBasePtr) 
{
    int userInput;

    while (true)
    {
        cout << "Enter your choice: ";
        cin >> userInput;
        cin.ignore();

        if (userInput > 4 || userInput < 1){cout << "Please select a valid option.\n";}
        else {break;} 
    }
    
    switch (userInput)
    {
    case 1:
        addExpense(expensesDataBasePtr);
        break;
    case 2:
        viewExpenses(expensesDataBasePtr);
        break;
    case 3:
        viewTotalExpenses(expensesDataBasePtr);
        break;
    case 4:
        exit(0);
    }
}

void addExpense(vector<Expense>* expensesDataBasePtr)
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
    } while (toupper(userInput) != 'N');
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
    cout << "Total of expenses: " << total << endl;
    cout << "Items recorded: " << expensesDataBasePtr->size() << endl;
}