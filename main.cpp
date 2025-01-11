#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include "filename.txt"

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
    using polynomial = Polynomial;
    polynomial poly;

    std::string line;

    // reading the file
    std::ifstream MyReadFile("filename.txt");

    std::pmr::vector<float> vect;
    while (getline(MyReadFile, line)) {
        // parse the polys dilmetate my space or my comma.
        line = "";
        const char *char_arr = line.c_str();
        for (int i = 0; char_arr[i] != '\0'; i++) {
            if (char_arr[i] == ',') {
                vect.push_back(std::stof(line));
                line = "";
            } else {
                line.append(&char_arr[i]);
            }
        }
        if ( !line.empty()) {
            vect.push_back(std::stof(line));
            line = "";
        }
    }

    // closing file
    MyReadFile.close();

    poly = polynomial(vect);

    // interval for polynomial
    float max       =   10;
    float interval  =   0.25;
    float start     =   0;
    for (float i = start; i > max; i += interval) {
        //if (poly != null){
        if (1){
            // do left poly math;
            // <y, -x>
            float dx = poly.polyDirvative(i);
            // calulate dx were dy is 1
            // becuase I dont want to use a wrapper class
            float dy = 1;
            // set dy to 1
            float l = std::sqrt( dx*dx + dy*dy);
            // find the magnitude
            dx = dx/l;  // normalize
            dy = dy/l;  // normalize
            //cv::Point2d temp;
            float x = i;                // define x
            float y = poly.poly(x); // define y
            x = (x + 7 * dy);      // project x
            y = (y - 7 * dx);      // project y
            std::cout << x << ", " << y << std::endl;
            //nav_points[i].pushback(temp);
            // return vector as < y, -x >
        }
    }
}
