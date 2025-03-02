# floating-point-translator
A simple tool to demonstrate how computers store floating-point numbers (base on IEEE-754).

# Features
[Input]  A single floating-point number.
    - If multiple values or non-numeric input are provided, an error will be generated.
[Output] text printed to the screen.

# How it works
This C program runs in an infinite loop. It takes a single input value (X) from the user and performs the following steps:
1. Display how X is stored in RAM. (as a uint32_t in hexdecimal format)
2. Display the actual floating-point value read from RAM.
3. Measure the CPU clock time required to access this float.
4. Extract and display the sign bit from the IEEE-754 representation.
5. Extract and display the exponent bits from the IEEE-754 representation.
6. Extract and display the mantissa bits from the IEEE-754 representation.
7. Convert the IEEE-754 representation back to a floating-point number, which should be identical to the result in step 2.
8. Measure the CPU clock time required for the IEEE-754 to floating-point conversion. This should be significantly slower than the time measured in step 3.
