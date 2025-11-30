#include <iostream>
#include <math.h>
#include <stdexcept>
#include <sstream>
#include <string>
#include <math.h>

#include "LoanCalculator.h"

using namespace std;

LoanCalculator::LoanCalculator() :
  amountSet_(false),
  initialPayment_(0.0),
  interestSet_(false),
  paymentSet_(false),
  periodTotalSet_(false),
  periodElapsedSet_(false),
  openingFee_(0.0),
  openingPercent_(0.0)
{
}

float LoanCalculator::calculateLoanBalance()
{
  if(!amountSet_ || !interestSet_ || !periodElapsedSet_ || !paymentSet_)
  {
    throw invalid_argument("Must set loan amount, interest, and elapsed period for this calculation" );
  }

  return (amount_*pow((1+interestPeriodic_), periodElapsed_)) -
         (payment_/interestPeriodic_)*(pow((1+interestPeriodic_), periodElapsed_)-1);
}

float LoanCalculator::calculatePayment()
{
  if(!amountSet_ || !interestSet_ || !periodTotalSet_)
  {
    throw invalid_argument("Must set loan amount, interest, and total period for this calculation" );
  }

  float totalAmount = amount_ - initialPayment_;
  totalAmount = totalAmount + openingFee_ + (totalAmount * (openingPercent_/100.0));

  return (interestPeriodic_*totalAmount) /
         (1 - pow((1+interestPeriodic_), (-1*periodTotal_)));
}

float LoanCalculator::calculateNumberPayments()
{
  if(!amountSet_ || !interestSet_ || !paymentSet_)
  {
    throw invalid_argument("Must set loan amount, interest, and payment for this calculation" );
  }

  return (-1.0*log10(1.0-(interestPeriodic_*amount_/payment_))) /
         log10(1.0 + interestPeriodic_);
}

float LoanCalculator::calculateLoanAmount()
{
  if(!paymentSet_ || !interestSet_ || !periodTotalSet_)
  {
    throw invalid_argument("Must set payment, interest, and total period for this calculation" );
  }

  return (payment_/interestPeriodic_) *
         (1 - pow((1+interestPeriodic_), (-1*periodTotal_)));
}

float LoanCalculator::calculateInterestRate()
{
  if(!amountSet_ || !paymentSet_ || !periodTotalSet_)
  {
    throw invalid_argument("Must set amount, payment, and total period for this calculation" );
  }

  float q = log10(1.0 + 1.0/periodTotal_) / log10(2.0);
  float monthlyInterest = pow((pow((1.0 + payment_/amount_), 1.0/q) -1.0), q) -1.0;

  return monthlyInterest*12*100;
}

float LoanCalculator::calculateEffectiveInterestRate()
{
  if(!amountSet_ || !periodTotalSet_)
  {
    throw invalid_argument("Must set amount and total period for this calculation" );
  }

  float payment = calculatePayment();
  float totalAmount = amount_ - initialPayment_;

  float q = log10(1.0 + 1.0/periodTotal_) / log10(2.0);
  float monthlyInterest = pow((pow((1.0 + payment/totalAmount), 1.0/q) -1.0), q) -1.0;

  return monthlyInterest*12*100;
}

std::string Loan::toString() const { 
    if (!fieldsSet) { 
        return "Loan fields are not properly set"; 
    } 
     
    std::stringstream ss; 
    ss << std::fixed << std::setprecision(2); 
    ss << "Principal: $" << principal << "\n" 
       << "Annual Interest Rate: " << annualInterestRate << "%\n" 
       << "Tenure: " << tenureMonths << " months\n" 
       << "Monthly Fee: $" << monthlyFee << "\n" 
       << "Upfront Fee: $" << upfrontFee << "\n" 
       << "Monthly Payment: $" << calculateEMI() << "\n" 
       << "Total Payment: $" << getTotalPayment() << "\n" 
       << "Total Interest: $" << getTotalInterest(); 
     
    return ss.str(); 
} 