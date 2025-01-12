#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include "Data/Datav1.001"
#include "Polynomial.h"

class Polynomial {
public:
    Polynomial(const std::vector<float>& vect) {
        this->vect = vect;
    }
    Polynomial() = default;

    // returns the y value at a given X.
    float poly(float x) {
        float result = 0;
        for (int i = 0; i < vect.size(); i++) {
            int power = vect.size() - i - 1;
            result += vect[i] * pow(x, power); // a[n] * x ^ n
        }
        return result;
    }

    float polyDerivative(float x) {
        float result = 0;
        for (int i = 0; i < vect.size() - 1; i++) {
            int power = vect.size() - i - 1;
            result += vect[i] * power * pow(x, power - 1); // a[n] * n * x ^ (n - 1)
        }
        return result;
    }

private:
    std::vector<float> vect;
};

int main() {
    //using polynomial = Polynomial;
    polynomial poly;

    std::string line;

    // reading the file
    std::ifstream MyReadFile("Data/Datav1.001");

    if (!MyReadFile.is_open()) {
        std::cerr << "Error: Could not open file!" << std::endl;
        return 1;
    }

    std::vector<float> vect;
    while (std::getline(MyReadFile, line)) {
        // parse the polys, delimitate by spaces (not commas)

        line.erase(line.find_first_of('['));
        line.erase(line.find_last_of(']') );

        std::stringstream ss(line);
        std::string token;
        while (ss >> token) { // Use `>>` to read space-separated values
            try {
                vect.push_back(std::stof(token)); // Convert string to float
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error: Invalid number format in line: " << line << std::endl;
            }
        }
    }

    // closing file
    MyReadFile.close();

    // Check if the vector is populated
    if (vect.empty()) {
        std::cerr << "Error: Polynomial vector is empty after reading the file!" << std::endl;
        return 1;
    }

    // Set the polynomial object after the file is read
    poly = polynomial(vect);

    // interval for polynomial
    float max = 10;
    float interval = 0.25;
    float start = 0;
    bool outputPrinted = false;

    for (float i = start; i <= max; i += interval) {
        // if (poly != null){
        if (1) { // Always true condition can be removed
            // do left poly math;
            // <y, -x>
            float dx = poly.polyDerivative(i);
            // calculate dx where dy is 1
            // because I don't want to use a wrapper class
            float dy = 1;
            // set dy to 1
            float l = std::sqrt(dx * dx + dy * dy); // find the magnitude
            dx /= l;  // normalize
            dy /= l;  // normalize
            //cv::Point2d temp;
            float x = i;                // define x
            float y = poly.poly(x);     // define y
            x = (x + 7 * dy);           // project x
            y = (y - 7 * dx);           // project y
            std::cout << x << ", " << y << std::endl;
            outputPrinted = true;
        }
    }

    if (!outputPrinted) {
        std::cerr << "No output was printed, possibly due to invalid polynomial data." << std::endl;
    }

    return 0;
}
