#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <sstream>
// #include <bits/regex.h>
// #include "/home/alex/IdeaProjects/Derek Cant Clean Data/src/dereksDataCleaned.txt"
// #include "Data/Datav1.txt"
#include <vector>

int main() {
    class Polynomial {
    private:
        std::vector<float> vect;
    public:
        explicit Polynomial(const std::vector<float>& vect) : vect(vect) {
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

    };
    //using polynomial = Polynomial;
    // Polynomial poly;

    std::string line;
    int frame_num = 0;

    // reading the file
    //std::ifstream MyReadFile("/home/alex/IdeaProjects/Derek Cant Clean Data/src/dereksDataCleaned.txt");
    std::ifstream MyReadFile("/home/alex/CLionProjects/untitled/Data/Datav4.txt");
    // std::ifstream MyReadFile("C:/Users/Alex Boccaccio/CLionProjects/untitled/Data/Datav1.txt");

    if (!MyReadFile.is_open()) {
        //std::cerr << "Error: Could not open MyReadFile: " << strerror(errno);
        return 1;
    }

    std::ofstream MyWriteFile("/home/alex/CLionProjects/untitled/Data/outPut.txt");

    if (!MyWriteFile.is_open()) {
        std::cout << "Error: Could not open MyWriteFile: " << strerror(errno);
    }


    std::vector<std::string> stringer;
    while (!MyReadFile.eof()) {
        // store the current line of the file
        // in the "line" variable
        std::vector<float> vect;
        std::getline(MyReadFile, line);
        std::stringstream ss(line);
        std::string token;
        while (std::getline(ss, token, ' ')) {
            vect.push_back(atof(token.c_str()));
        }
        // poly = Polynomial(vect);
        // Check if the vector is populated
        if (vect.empty()) {
            std::cerr << "Error: Polynomial vector is empty after reading the file!" << std::endl;
            // return 1;
        }
        float sum = 0;
        for (int i = 0; i < vect.size(); i++) {
            sum += vect[i];
        }
        if ( sum == 0) {
            std::cerr << "Error: Polynomial sum is zero!" << std::endl;
        }

        // Set the polynomial object after the file is read
        auto* poly = new Polynomial(vect);

        // interval for polynomial
        float max = 540;
        float numberOfIntervals = 38;
        float start = 0;
        float interval = (max - start) / numberOfIntervals;
        bool outputPrinted = false;

        for (float i = start; i <= max; i += interval) {
            // if (poly != null){
            if (1) { // Always true condition can be removed
                // do left poly math;
                // <y, -x>
                float dy = poly->polyDerivative(i);
                // calculate dx where dy is 1
                // because I don't want to use a wrapper class
                float dx = 1;
                // set dy to 1
                float l = std::sqrt(dx * dx + dy * dy); // find the magnitude
                dx /= l;  // normalize
                dy /= l;  // normalize
                //cv::Point2d temp;
                float x = i;                // define x
                float y = poly->poly(x);     // define y
                x = (x + 7 * dy);           // project x
                y = (y - 7 * dx);           // project y
                //std::cout << x << ", " << y << std::endl;
                float lengthCheck = sqrt(pow(x - i, 2)  + pow(y - poly->poly(i), 2));
                if (lengthCheck < 7.5 && lengthCheck > 1 ) {
                    std::cout   << " valid " << x << ", " << y << "   length: "<< lengthCheck << std::endl; ;
                    // MyWriteFile << " valid " << x << ", " << y << "   length: "<< lengthCheck<< std::endl;
                    // MyWriteFile <<"(" << x << ", " << y <<")" <<std::endl;
                    MyWriteFile << x << " " << y <<std::endl;
                } else {
                    std::cout   << "invalid " << x << ", " << y << std::endl; ;
                    // MyWriteFile << "invalid " << x << ", " << y << std::endl;
                    MyWriteFile << x << " " << y << std::endl;
                }
                //std::cout << stringout << std::endl;
                //MyWriteFile << stringout << std::endl;
                // stringer.push_back(std::to_string(x) + ", " + std::to_string(y) +"\n");
                // outputPrinted = true;
            }
        }
        std::cout << "new polynomial: "  + std::to_string(frame_num)<< "\n";
        // MyWriteFile << "new polynomial: " + std::to_string(frame_num) << "\n";
        frame_num++;
        if (!outputPrinted) {
            // std::cerr << "No output was printed, possibly due to invalid polynomial data." << std::endl;
            // MyWriteFile << "No output was printed, possibly due to invalid polynomial data." << std::endl;

        }
        delete poly;
        //std::stringstream ss(line);
    }

    int i = 0;
    while ( i < stringer.size()) {
        // MyWriteFile << stringer[i] << "";
        i++;
    }

    MyWriteFile.close();

    // delete poly;
    /*while (std::getline(MyReadFile, line)) {
        // parse the polys, delimitate by spaces (not commas)

        // line = std::regex_replace(line, std::regex("^\\s+|\\s+$"), "");
        line.erase(0,1);
        line.erase(line.size() -1 );

        line = line.substr(1,line.length()-2);


        std::stringstream ss(line);
        std::string token;
        while (ss >> token) { // Use `>>` to read space-separated values
            try {
                //if (token[0] == '-') {
                //    token[0] = 0;
               //     vect.push_back(std::stof(token) * -1); // Convert string to float
                //} else {
                    vect.push_back(std::stof(token) * 1); // Convert string to float
                //}
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error: Invalid number format in line: " << line << std::endl;
            }
        }
    }

    // closing file
    MyReadFile.close();
*/
    /*
    // Check if the vector is populated
    if (vect.empty()) {
        std::cerr << "Error: Polynomial vector is empty after reading the file!" << std::endl;
        return 1;
    }
    float sum = 0;
    for (int i = 0; i < vect.size(); i++) {
        sum += vect[i];
    }
    if ( sum == 0) {
        std::cerr << "Error: Polynomial sum is zero!" << std::endl;
    }

    // Set the polynomial object after the file is read
    poly = Polynomial(vect);

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
    */

    return 0;
}
