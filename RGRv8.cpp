#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>

class Logger {
    std::string logFile;
    int shift;
public:
    Logger(std::string file, int shift) : logFile(file), shift(shift) {}
    void log(std::string message) {
        std::ofstream file(logFile, std::ios_base::app);
        file << encrypt(message) << std::endl;
        file.close();
    }

    std::string encrypt(std::string message) {
        for (char& c : message) {
            if (c >= 'a' && c <= 'z') {
                c = 'a' + (c - 'a' + shift) % 26;
            }
            else if (c >= 'A' && c <= 'Z') {
                c = 'A' + (c - 'A' + shift) % 26;
            }
        }
        return message;
    }
};

class Complex {
    double real;
    double imag;
public:
    Complex(double real = 0.0, double imag = 0.0) : real(real), imag(imag) {}
    void setReal(double real) { this->real = real; }
    void setImag(double imag) { this->imag = imag; }
    double getReal() const { return real; }
    double getImag() const { return imag; }
    double calculateModulus(const Complex& c) {
        double realSum = real + c.real;
        double imagSum = imag + c.imag;
        return std::sqrt(realSum * realSum + imagSum * imagSum);
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
};

std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << c.real;
    if (c.imag >= 0)
        os << "+";
    os << c.imag << "i";
    return os;
}

int main() {
    Logger logger("log.txt", 3);
    Complex c1(1, 3);
    Complex c2(-1, 2);
    Complex c3(3, 4);
    Complex c4(-2, -1);

    logger.log("Complex numbers: " + std::to_string(c1.getReal()) + " " + std::to_string(c1.getImag()) + ", " +
        std::to_string(c2.getReal()) + " " + std::to_string(c2.getImag()));

    std::cout << "Complex number c1: " << c1 << "\n";
    std::cout << "Complex number c2: " << c2 << "\n";

    double modulus1 = c1.calculateModulus(c2);
    std::cout << "Modulus of sum (c1 + c2): " << modulus1 << "\n";

    std::ostringstream ss1;
    ss1 << modulus1;
    std::string modulus1_str = ss1.str();

    logger.log("Modulus of sum (c1 + c2): " + modulus1_str);

    std::cout << "Complex number c3: " << c3 << "\n";
    std::cout << "Complex number c4: " << c4 << "\n";

    double modulus2 = c3.calculateModulus(c4);
    std::cout << "Modulus of sum (c3 + c4): " << modulus2 << "\n";

    std::ostringstream ss2;
    ss2 << modulus2;
    std::string modulus2_str = ss2.str();

    logger.log("Modulus of sum (c3 + c4): " + modulus2_str);

    return 0;
}

