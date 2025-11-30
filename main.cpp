#include <iostream>
#include "LoanCalculator.h"

int main() {
    LoanCalculator loan(1000, 0.01, 12);
    std::cout << "EMI: " << loan.calculateEMI() << std::endl;
    return 0;
}
