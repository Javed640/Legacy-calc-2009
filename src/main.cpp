#include <stdlib.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <cmath>
#include "LoanCalculator.h"

using namespace std;

// Simple command line parser implementation
class CmdLineOption {
public:
    virtual ~CmdLineOption() {}
    virtual bool parse(const string& value) = 0;
    virtual string getName() const = 0;
};

class CmdLineOptionFloat : public CmdLineOption {
    float value_;
    string name_;
public:
    CmdLineOptionFloat(const string& name, float defaultValue = 0.0f) 
        : value_(defaultValue), name_(name) {}
    bool parse(const string& value) override {
        try {
            value_ = stof(value);
            return true;
        } catch(...) {
            return false;
        }
    }
    string getName() const override { return name_; }
    float getValue() const { return value_; }
};

class CmdLineOptionInt : public CmdLineOption {
    int value_;
    string name_;
public:
    CmdLineOptionInt(const string& name, int defaultValue = 0) 
        : value_(defaultValue), name_(name) {}
    bool parse(const string& value) override {
        try {
            value_ = stoi(value);
            return true;
        } catch(...) {
            return false;
        }
    }
    string getName() const override { return name_; }
    int getValue() const { return value_; }
};

class CmdLineOptionFlag : public CmdLineOption {
    bool value_;
    string name_;
    int key_;
public:
    CmdLineOptionFlag(const string& name, const string& help, bool defaultValue, int key) 
        : value_(defaultValue), name_(name), key_(key) {}
    bool parse(const string& value) override {
        value_ = true;
        return true;
    }
    string getName() const override { return name_; }
    bool getValue() const { return value_; }
    int getValueKey() const { return key_; }
};

class CmdLineParser {
public:
    bool parseCmdLine(int argc, char** argv) {
        for(int i = 1; i < argc; i++) {
            string arg = argv[i];
            if(arg == "-h" || arg == "--help") {
                printUsage();
                return false;
            }
        }
        return true;
    }
    
    void printUsage() {
        cout << "Loan Calculator Usage:" << endl;
        cout << "Options:" << endl;
        cout << "  -a <amount>          Set the initial amount" << endl;
        cout << "  -ai <payment>        Set the initial payment" << endl;
        cout << "  -i <interest>        Set the yearly interest rate" << endl;
        cout << "  -p <payment>         Set the monthly payment" << endl;
        cout << "  -N <months>          Set the total loan period in months" << endl;
        cout << "  -n <months>          Set the elapsed period in months" << endl;
        cout << "  -of <fee>            Set opening fee" << endl;
        cout << "  -op <percent>        Set opening fee percentage" << endl;
        cout << "  -cp                  Calculate monthly payment" << endl;
        cout << "  -ca                  Calculate loan amount" << endl;
        cout << "  -ci                  Calculate interest rate" << endl;
        cout << "  -cn                  Calculate number of payments" << endl;
        cout << "  -cb                  Calculate loan balance" << endl;
        cout << "  -h, --help           Show this help message" << endl;
    }
    
    template<typename T>
    T* getCmdLineOption(const string& name) { 
        static T dummy(""); 
        return &dummy; 
    }
    
    CmdLineOption* getMutExclOption() { return nullptr; }
    void setMinNumberArgs(int) {}
    void setMainHelpText(const string&) {}
    void setMainHelpTextEnd(const string&) {}
    void addMutExclCmdLineOption(CmdLineOptionFlag*) {}
    void setMutExclUsageText(const string&) {}
    void addCmdLineOption(CmdLineOption*) {}
};

enum CALC_TYPE
{
  CALC_UNKNOWN=0,
  CALC_BALANCE=100,
  CALC_PAYMENT,
  CALC_NUMPAYMENTS,
  CALC_AMOUNT,
  CALC_INTEREST
};

void loadCmdLine(CmdLineParser &clp)
{
  // Empty in this simplified version
}

CALC_TYPE parseCommandLine(int argc, char **argv, CmdLineParser &clp, LoanCalculator &calculator)
{
  CALC_TYPE ct = CALC_UNKNOWN;
  
  // Simple command line parsing
  for(int i = 1; i < argc; i++) {
    string arg = argv[i];
    
    if(arg == "-cp") ct = CALC_PAYMENT;
    else if(arg == "-ca") ct = CALC_AMOUNT;
    else if(arg == "-ci") ct = CALC_INTEREST;
    else if(arg == "-cn") ct = CALC_NUMPAYMENTS;
    else if(arg == "-cb") ct = CALC_BALANCE;
    else if(arg == "-a" && i+1 < argc) calculator.setAmount(stof(argv[++i]));
    else if(arg == "-ai" && i+1 < argc) calculator.setInitialPayment(stof(argv[++i]));
    else if(arg == "-i" && i+1 < argc) calculator.setInterest(stof(argv[++i]));
    else if(arg == "-p" && i+1 < argc) calculator.setPayment(stof(argv[++i]));
    else if(arg == "-N" && i+1 < argc) calculator.setPeriodTotal(stoi(argv[++i]));
    else if(arg == "-n" && i+1 < argc) calculator.setPeriodElapsed(stoi(argv[++i]));
    else if(arg == "-of" && i+1 < argc) calculator.setOpeningFee(stof(argv[++i]));
    else if(arg == "-op" && i+1 < argc) calculator.setOpeningPercent(stof(argv[++i]));
    else if(arg == "-h" || arg == "--help") {
      clp.printUsage();
      return CALC_UNKNOWN;
    }
  }
  
  return ct;
}

void runInteractiveMode() {
    LoanCalculator calculator;
    cout << "Loan Calculator (Interactive Mode)" << endl;
    cout << "Enter values (press Enter for default 0):" << endl;
    
    string input;
    
    cout << "Loan Amount: "; 
    getline(cin, input);
    if(!input.empty()) calculator.setAmount(stof(input));
    
    cout << "Initial Payment: "; 
    getline(cin, input);
    if(!input.empty()) calculator.setInitialPayment(stof(input));
    
    cout << "Interest Rate (%): "; 
    getline(cin, input);
    if(!input.empty()) calculator.setInterest(stof(input));
    
    cout << "Monthly Payment: "; 
    getline(cin, input);
    if(!input.empty()) calculator.setPayment(stof(input));
    
    cout << "Loan Period (months): "; 
    getline(cin, input);
    if(!input.empty()) calculator.setPeriodTotal(stoi(input));
    
    cout << "Elapsed Period (months): "; 
    getline(cin, input);
    if(!input.empty()) calculator.setPeriodElapsed(stoi(input));
    
    cout << "Opening Fee: "; 
    getline(cin, input);
    if(!input.empty()) calculator.setOpeningFee(stof(input));
    
    cout << "Opening Fee %: "; 
    getline(cin, input);
    if(!input.empty()) calculator.setOpeningPercent(stof(input));
    
    cout << "\nSelect calculation type:" << endl;
    cout << "1. Monthly Payment" << endl;
    cout << "2. Loan Amount" << endl;
    cout << "3. Interest Rate" << endl;
    cout << "4. Number of Payments" << endl;
    cout << "5. Loan Balance" << endl;
    cout << "Choice: ";
    
    getline(cin, input);
    int choice = input.empty() ? 1 : stoi(input);
    
    CALC_TYPE ct = CALC_UNKNOWN;
    switch(choice) {
      case 1: ct = CALC_PAYMENT; break;
      case 2: ct = CALC_AMOUNT; break;
      case 3: ct = CALC_INTEREST; break;
      case 4: ct = CALC_NUMPAYMENTS; break;
      case 5: ct = CALC_BALANCE; break;
      default: ct = CALC_PAYMENT; break;
    }
    
    // Perform calculation
    try {
      cout << endl;
      if(ct == CALC_BALANCE) {
        cout << "Loan Balance = " << calculator.calculateLoanBalance() << endl;
      }
      else if(ct == CALC_PAYMENT) {
        float payment = calculator.calculatePayment();
        cout << "Monthly Payment    = " << payment << "\n"
             << "Total amt paid     = " << (payment * calculator.getPeriodTotal())
             << endl;
        if(calculator.getOpeningPercent() != 0.0 || calculator.getOpeningFee() != 0.0) {
          cout << "Interest with fees = "
               << calculator.calculateEffectiveInterestRate()
               << "%"
               << endl;
        }
      }
      else if(ct == CALC_NUMPAYMENTS) {
        cout << "Number of payments = " << calculator.calculateNumberPayments() << endl;
      }
      else if(ct == CALC_AMOUNT) {
        cout << "Initial Loan amount = " << calculator.calculateLoanAmount() << endl;
      }
      else if(ct == CALC_INTEREST) {
        cout << "Yearly Interest Rate = " << calculator.calculateInterestRate() << "%" << endl;
      }
      
      cout << calculator.toString() << endl;
    }
    catch(const exception &e) {
      cerr << "Error: " << e.what() << endl;
    }
}

int main(int argc, char **argv)
{
  LoanCalculator calculator;
  CmdLineParser clp;

  if(argc == 1) {
    // Interactive console mode
    runInteractiveMode();
    return 0;
  }

  // Command line mode
  CALC_TYPE ct = parseCommandLine(argc, argv, clp, calculator);

  try {
    cout << endl;
    if(ct == CALC_BALANCE) {
        cout << "Loan Balance = " << calculator.calculateLoanBalance() << endl;
    }
    else if(ct == CALC_PAYMENT) {
      float payment = calculator.calculatePayment();
      cout << "Monthly Payment    = " << payment << "\n"
           << "Total amt paid     = " << (payment * calculator.getPeriodTotal())
           << endl;
      if(calculator.getOpeningPercent() != 0.0 || calculator.getOpeningFee() != 0.0) {
        cout << "Interest with fees = "
             << calculator.calculateEffectiveInterestRate()
             << "%"
             << endl;
      }
    }
    else if(ct == CALC_NUMPAYMENTS) {
      cout << "Number of payments = " << calculator.calculateNumberPayments() << endl;
    }
    else if(ct == CALC_AMOUNT) {
      cout << "Initial Loan amount = " << calculator.calculateLoanAmount() << endl;
    }
    else if(ct == CALC_INTEREST) {
      cout << "Yearly Interest Rate = " << calculator.calculateInterestRate() << "%" << endl;
    }
    else if(ct == CALC_UNKNOWN) {
      return 1;
    }
    else {
      cerr << "Unrecognized calculation type" << endl;
      return 0;
    }

    cout << calculator.toString() << endl;
  }
  catch(const exception &e) {
    cerr << "Error: " << e.what() << endl;
  }

  cout << endl;
  return 0;
}