#pragma once
#include <string>
#include <iostream>

//A class representing complex numbers.
class Complex
{
private:
	float real;
	float imaginary;

public:
	//Constructor
	Complex(float = 0, float = 0, const std::string = " ");

	//Overloading necessary operators.
	Complex operator + (Complex);
	Complex operator - (Complex);
	Complex operator * (Complex);
	Complex operator / (int);
	bool operator == (Complex);
	friend std::ostream& operator << (std::ostream&, Complex);
};

