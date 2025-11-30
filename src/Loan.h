#ifndef LOANCALCULATOR_H_INCLUDED
#define LOANCALCULATOR_H_INCLUDED

#include <string>

class LoanCalculator
{
public:
  LoanCalculator();
  ~LoanCalculator() {}

  inline void setAmount(float A) { amount_ = A; amountSet_ = true; }
  inline float getAmount() const { return amount_; }

  inline void setInitialPayment(float initialA)  { initialPayment_ = initialA; }
  inline float getInitialPayment() const         { return initialPayment_; }

  void setInterest(float i) { interest_ = i; interestPeriodic_ = i/100.0/12.0; interestSet_ = true; }
  inline float getInterest() const         { return interest_; }
  inline float getPeriodicInterest() const { return interestPeriodic_; }

  void setPayment(float P)        { payment_ = P; paymentSet_ = true; }
  inline float getPayment() const { return payment_; }

  void setPeriodTotal(int N)        { periodTotal_ = N; periodTotalSet_ = true; }
  inline int getPeriodTotal() const { return periodTotal_; }

  void setPeriodElapsed(int n)         { periodElapsed_ = n; periodElapsedSet_ = true; }
  inline int getPeriodElapsed() const  { return periodElapsed_; }

  inline void setOpeningFee(float fee) { openingFee_ = fee; }
  inline float getOpeningFee() const   { return openingFee_; }

  inline void setOpeningPercent(float percent) { openingPercent_ = percent; }
  inline float getOpeningPercent() const       { return openingPercent_; }

  inline void reset() {
    amount_ = initialPayment_ = interest_ = interestPeriodic_ = payment_ = openingFee_ = openingPercent_ = 0.0;
    periodTotal_ = periodElapsed_ = 0;
    amountSet_ = interestSet_ = paymentSet_ = periodTotalSet_ = periodElapsedSet_ = false;
  }

  float calculateLoanBalance();
  float calculatePayment();
  float calculateNumberPayments();
  float calculateLoanAmount();
  float calculateInterestRate();
  float calculateEffectiveInterestRate();

  std::string toString();

private:
  float amount_;
  bool amountSet_;
  float initialPayment_;
  float interest_;
  float interestPeriodic_;
  bool interestSet_;
  float payment_;
  bool paymentSet_;
  int periodTotal_;
  bool periodTotalSet_;
  int periodElapsed_;
  bool periodElapsedSet_;
  float openingFee_;
  float openingPercent_;
};

#endif