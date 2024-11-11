#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>

class Polynomial {
    public:
    // TODO what does std::pmr::vec mean compared to std::vec ???
    Polynomial(std::pmr::vector<float>& vect) {
        this->vect = vect;
    }
    Polynomial() = default;
    // store the vector
    private:
        std::pmr::vector<float> vect;
    public:
    // returns the y value at a given X.
    float poly(float x) {
        float result = 0;
        for( int i = 0; i < vect.size(); i++ ) {
            int power = vect.size() - i;
            // TODO this pow function might be wrong
            result += vect[i] * pow(x, power); // a[n] * x ^ n
        }
        return result;
    }
    float polyDirvative(float x) {
        float result = 0;
        for( int i = 0; i < vect.size() -1; i++ ) {
            int power = vect.size() - i - 1;
            // todo finish?
            result += vect[i] * i * pow(x, power); // a[n] * n * x ^ (n - 1)
        }
    }
};

int main() {
    std::ifstream input("input.txt");
    if (input.is_open()) {
        std::pmr::vector<float> vect;
    }
    // globals for storing the arrays
    int startValue 0.01;
    // the value to incrememt by
    float delilator = 0.01;
    // the value to stop at lol
    int maxDistance = 10; // todo in meters??
    float current = startValue;
    // should be polynomial( Start );
    auto polynomialer = new Polynomial();
    if(!input) {
        // TODO read files
        // input using while(){}
    }
    while ( maxDistance > current) {
        // TODO run through the polynomial with the polynomial

        current += delilator;
        // todo pass off P(current) to hybird puresuit node;
    }
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
