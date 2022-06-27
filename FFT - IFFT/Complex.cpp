#include "Complex.h"
#include <cmath>

//Overloading the output stream operator
std::ostream& operator << (std::ostream& out, Complex c) {

	if (c.real != 0 && c.imaginary != 0) out << c.real << " + " << c.imaginary << 'i';
	else if (c.real == 0 && c.imaginary == 0) out << '0';
	else if (c.imaginary == 0) out << c.real;
	else out << c.imaginary << 'i';

	return out;

 }

//Constructor
 Complex::Complex(float r, float imaginary_or_theta, const std::string coordinateSystem) {

	 if (coordinateSystem == "polar") {                    //If polar coordinates are taken as input, tranform them into cartesian coordinates.
		 
		 real = r * cos(imaginary_or_theta);
		 imaginary = r * sin(imaginary_or_theta);
	 
	 }
	 else {

		 real = r;
		 imaginary = imaginary_or_theta;
	 
	 }

}


 //Overloading of arithmetic operators.

 Complex Complex::operator + (Complex c) {

	 return Complex(real + c.real, imaginary + c.imaginary);

}
 Complex Complex::operator - (Complex c) {

	 return Complex(real - c.real, imaginary - c.imaginary);

}
 Complex Complex::operator * (Complex c) {

	 return Complex(real * c.real - imaginary * c.imaginary, real * c.imaginary + imaginary * c.real);

}

 Complex Complex::operator/(int divisor)
 {
	 float newReal = real / (float)divisor;
	 float newImaginary = imaginary / (float)divisor;
	 newReal = newReal - (int)newReal > 0.001 ? newReal : (int)newReal;
	 newImaginary = newImaginary - (int)newImaginary > 0.001 ? newImaginary : (int)newImaginary;

	 return Complex(newReal, newImaginary);
 }


 //Overloading the == operator for more compact comparisons.
 bool Complex::operator==(Complex c)
 {
	 return (real == c.real && imaginary == c.imaginary);
 }
