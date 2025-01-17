#include "MyLibraries.h"

class Expense {
    private:
        // Data variables
        string nameOfExpense;
        double cost;
        string categoryOfExpense;
    public:
        // Mutators (setters)
        void setExpenseName(string expenseName) 
        {
            nameOfExpense = expenseName;
        }

        void setExpenseCost(double expenseCost)
        {
            cost = expenseCost;
        }

        void setExpenseCategory(string expenseCategory) 
        {
            categoryOfExpense = expenseCategory;
        }

        // Accessors (getters)
        string getExpenseName() {return nameOfExpense;}

        double getExpenseCost() {return cost;}

        string getExpenseCategory() {return categoryOfExpense;}

        // Constructors
        Expense(string expenseName, string expenseCategory, double expenseCost)
        {
            setExpenseName(expenseName);
            setExpenseCost(expenseCost);
            setExpenseCategory(expenseCategory);
        }

        Expense()
        {
            setExpenseName("N/A");
            setExpenseCost(0);
            setExpenseCategory("N/A");
        }

        // Destructors
        ~Expense() {};

        // User-defined methods
        

        // WRITE METHODS THAT RELATE TO EXPENSE CLASS
};