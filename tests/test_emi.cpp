#include "LoanCalculator.h"
#include <gtest/gtest.h>
#include <limits>

TEST(LoanCalculatorTest, NormalEMICalculation) {
    LoanCalculator loan(12000, 0.01, 12);
    double emi = loan.calculateEMI();
    EXPECT_TRUE(std::isfinite(emi));
    EXPECT_GT(emi, 0.0);
}

TEST(LoanCalculatorTest, InvalidInputHandling) {
    EXPECT_THROW(LoanCalculator(-5000, 0.05, 12), std::invalid_argument);
    EXPECT_THROW(LoanCalculator(5000, -0.05, 12), std::invalid_argument);
    EXPECT_THROW(LoanCalculator(5000, 0.05, 0), std::invalid_argument);
}

TEST(LoanCalculatorTest, LargeTenureCalculation) {
    LoanCalculator loan(1e6, 0.01, 600); // 50 years, high tenure
    double emi = loan.calculateEMI();
    double totalRepayment = emi * 600;
    EXPECT_TRUE(std::isfinite(emi));
    EXPECT_TRUE(std::isfinite(totalRepayment));
    EXPECT_GT(emi, 0.0);
    EXPECT_GT(totalRepayment, 0.0);
}
