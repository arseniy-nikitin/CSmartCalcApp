# SmartCalc v1.0

SmartCalc is a versatile calculator application developed in C and C++ using the C11 standard. It provides both a command-line interface and a graphical user interface (GUI) based on the QT framework for the frontend and pure C for the backend.

## Features

- Supports keyboard input.
- The X value changes when the button is pressed for a certain period of time.
- Full line clearing occurs when the button is pressed for a certain period of time.
- Unary signs and nested degrees must be delimited by parentheses.

### Basic Calculator

- Perform arithmetic operations: addition, subtraction, multiplication, division, exponentiation, and modulo.
- Handle parentheses in infix expressions for complex calculations.
- Support mathematical functions: cos(x), sin(x), tan(x), acos(x), asin(x), atan(x), sqrt(x), ln(x), and log(x).
- Input numbers as integers or floating-point values.
- Calculate expressions after complete input and pressing '='.

### Graphical User Interface (GUI)

- Build and evaluate arbitrary arithmetic expressions in infix notation with variable substitution.
- Calculate expressions with x as a variable.
- Plot functions based on infix expressions with adaptive grid and scale display.
- Restrict the domain and range of plotted functions from -1000000 to 1000000.

### Additional Calculators

#### 1. Credit Calculator

- Calculate monthly payments, overpayment, and total payment for a loan.
- Input: total loan amount, loan term, interest rate, loan type (annuity or differentiated).

#### 2. Deposit Calculator

- Calculate interest, tax amount, and final deposit amount for savings.
- Input: initial deposit amount, deposit term, interest rate, tax rate, amount of replenishments, amount of withdrawals, frequency of replenishments, frequency of withdrawals, payout or capitalization frequency, deposit type (with or without capitalization).

## Prerequisites

- C11 compatible compiler (gcc recommended)
- QT framework for GUI components
- Check library for unit testing

## Installation and Usage

1. Clone the repository:
   ```
   git clone <repository-url>
   cd CSmartCalcApp/src
   ```

2. Build and run the application using Makefile:
   ```
   make
   ```

3. Run the application:
   ```
   make run
   ```

## Build Targets

- `make all`: Build the CLI and GUI versions of SmartCalc.
- `make install`: Install the application in a specified directory.
- `make uninstall`: Remove the installed application.
- `make run`: Run application.
- `make clean`: Clean build artifacts.

## Developer Notes

- Follow Google Style Guide for coding standards.
- Unit test modules using the Check library for accurate functionality.
- Ensure a minimum of 7 decimal places for floating-point accuracy.

## Contributors

- [arseniy-nikitin]
