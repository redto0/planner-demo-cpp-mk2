#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <cmath> // for pow

class Polynomial {
public:
    // Constructors
    Polynomial(const std::vector<float>& vect);  // Constructor with coefficients
    Polynomial() = default;  // Default constructor

    // Method to calculate the polynomial value at a given x
    float poly(float x) const;

    // Method to calculate the derivative of the polynomial at a given x
    float polyDerivative(float x) const;

private:
    std::vector<float> vect;  // Vector to store polynomial coefficients
};

#endif // POLYNOMIAL_H