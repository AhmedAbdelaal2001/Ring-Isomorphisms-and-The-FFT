#define _USE_MATH_DEFINES
#include <math.h>
#include "Complex.h"
#include <vector>
#include <algorithm>

using namespace std;

//Reads input from the user.
void getUserInput(vector<Complex>* coefficientsVector, int n, string inputType);

//Prints the coefficients of a polynomial.
void printPolynomial(vector<Complex>* coefficientsVector, string outputObject);

//Prints the values of p(xk), where p(x) is the polynomial as xk is the kth root of unity.
void printSamples(vector<Complex>* samplesVector, string outputObject);

//Prints the components of a vector.
void printVector(vector<Complex>* outputVector, string outputObject);

//Applies the Fast-Fourier-Transform on a vector. In this context, the function converts the polynomial from the coefficients 
//represntation to the samples representation.
vector<Complex>* FFT(vector<Complex>* coefficientsVector, int firstRootIndicator);

//Applies the Inverse Fast-Fourier-Transform on a vector. In this context, the function converts the polynomial from the samples 
//representation to the coefficients representation.
vector<Complex>* IFFT(vector<Complex>* samplesVector);

//Applies the FFT and IFFT to multiply 2 polynomials in O(nlogn) time.
vector<Complex>* multiplyPolynomials(vector<Complex>* polynomial1, vector<Complex>* polynomial2);

//Computes the convolution of two vectors by reversing the second vector, the treating both vectors as coefficient representations
//of polynomials, then multiplying them using the previous function.
vector<Complex>* convolution(vector<Complex>* vector1, vector<Complex>* vector2);

int main() {

	int choice, n, m;

	cout << "\n1. Convert a polynomial from the coefficient representation to the sample representation." << endl;
	cout << "2. Multiply two polynomials." << endl;
	cout << "3. Compute the convolution of two vectors." << endl;
	cout << "\nEnter the number of the action you wish to execute: " << endl;
	cin >> choice;

	switch (choice) {

	case 1:
	{
		cout << "\nEnter the degree of the polynomial: ";
		cin >> n;
		vector <Complex>* coefficientsVector = new vector<Complex>(pow(2, ceil(log(n + 1) / log(2))));
		cout << "\nEnter the coefficients of the polynomial: " << endl;
		getUserInput(coefficientsVector, n + 1, "polynomial");
		vector<Complex>* samples = FFT(coefficientsVector, 1);
		printSamples(samples, "Sample Representation");

		delete coefficientsVector;
		delete samples;

		break;
	}
	case 2:
	{
		cout << "\nEnter the degree of the first polynomial: ";
		cin >> n;
		cout << "Enter the degree of the second polynomial: ";
		cin >> m;

		vector <Complex>* coefficientsVector1 = new vector<Complex>(pow(2, ceil(log(n + m + 1) / log(2))));
		vector <Complex>* coefficientsVector2 = new vector<Complex>(pow(2, ceil(log(n + m + 1) / log(2))));

		cout << "\nEnter the coefficients of the first polynomial: " << endl;
		getUserInput(coefficientsVector1, n + 1, "polynomial");
		cout << "\nEnter the coefficients of the second polynomial:" << endl;
		getUserInput(coefficientsVector2, m + 1, "polynomial");

		vector<Complex>* productCoefficients = multiplyPolynomials(coefficientsVector1, coefficientsVector2);
		printPolynomial(productCoefficients, "Product Coefficients");

		delete coefficientsVector1;
		delete coefficientsVector2;
		delete productCoefficients;

		break;
	}
	case 3:
	{
		cout << "\nEnter the dimension of the first vector: ";
		cin >> n;
		cout << "Enter the dimension of the second vector: ";
		cin >> m;

		vector <Complex>* vector1 = new vector<Complex>(pow(2, ceil(log(n + m) / log(2))));
		vector <Complex>* vector2 = new vector<Complex>(pow(2, ceil(log(n + m) / log(2))));

		cout << "\nEnter the elements of the first vector: " << endl;
		getUserInput(vector1, n, "vector");
		cout << "\nEnter the elements of the second vector:" << endl;
		getUserInput(vector2, m, "vector");

		vector<Complex>* convolutionResult = convolution(vector1, vector2);
		printVector(convolutionResult, "Convolution Result");

		delete vector1;
		delete vector2;
		delete convolutionResult;

		break;
	}
	default:
		cout << "Unrecognized Input." << endl;

	}


	return 0;
}

void getUserInput(vector<Complex>* coefficientsVector, int n, string inputType) {

	float input;

	if (inputType == "polynomial")
		for (int i = 0; i < n; i++) {

			if (i == 0) cout << "Constant Term: ";
			else cout << "Degree " << i << " Term Coefficient: ";
			cin >> input;
			Complex inputNum(input);
			coefficientsVector->at(i) = inputNum;

		}
	else if (inputType == "vector")
		for (int i = 0; i < n; i++) {

			cout << "Element " << i + 1 << " = ";
			cin >> input;
			Complex inputNum(input);
			coefficientsVector->at(i) = inputNum;

		}
}

void printPolynomial(vector<Complex>* coefficientsVector, string outputObject) {

	cout << "\n------------------------------------------------------------------------------------------------------------\n";
	cout << "Printing " << outputObject << ':' << endl;
	for (int i = 0; i < coefficientsVector->size(); i++) {

		if (i == 0) cout << "Constant Term = ";
		else cout << "Degree " << i <<" Term's Coefficient = ";
		cout << coefficientsVector->at(i) << endl;

	}

}

void printSamples(vector<Complex>* samplesVector, string outputObject) {

	cout << "\n------------------------------------------------------------------------------------------------------------\n";
	cout << "Printing " << outputObject << ':' << endl;
	for (int i = 0; i < samplesVector->size(); i++) {

		cout << "Polynomial output at root of unity " << i + 1 << " = ";
		cout << samplesVector->at(i) << endl;

	}

}

void printVector(vector<Complex>* outputVector, string outputObject) {

	cout << "\n------------------------------------------------------------------------------------------------------------\n";
	cout << "Printing " << outputObject << ":" << endl;
	cout << "[";
	for (int i = 0; i < outputVector->size(); i++) {

		cout << outputVector->at(i);
		if (i != outputVector->size() - 1) cout << ", ";

	}
	cout << "]" << endl;

}

vector<Complex>* FFT(vector<Complex>* coefficientsVector, int firstRootIndicator) {

	if (coefficientsVector->size() == 1) return coefficientsVector;
	
	Complex w(1, 2 * M_PI * firstRootIndicator / (float)coefficientsVector->size(), "polar");
	Complex temp_w(1, 0);

	vector<Complex>* evenVector = new vector<Complex>;
	vector<Complex>* oddVector = new vector<Complex>;

	for (int i = 0; i < coefficientsVector->size(); i++) {
		
		if (i % 2 == 0) evenVector->push_back(coefficientsVector->at(i));
		else oddVector->push_back(coefficientsVector->at(i));
			
	}

	vector<Complex>* evenSamples = FFT(evenVector, firstRootIndicator);
	vector<Complex>* oddSamples = FFT(oddVector, firstRootIndicator);
	vector<Complex>* samples = new vector<Complex>(coefficientsVector->size());

	for (int i = 0; i < coefficientsVector->size() / 2; i++) {

		samples->at(i) = evenSamples->at(i) + temp_w * oddSamples->at(i);
		samples->at(i + samples->size() / 2) = evenSamples->at(i) - temp_w * oddSamples->at(i);
		temp_w = temp_w * w;

	}

	delete evenVector;
	delete oddVector;

	return samples;

}

vector<Complex>* IFFT(vector<Complex>* samplesVector) {

	vector<Complex>* coefficientsVector = FFT(samplesVector, -1);
	
	for (int i = 0; i < coefficientsVector->size(); i++)
		coefficientsVector->at(i) = coefficientsVector->at(i) / coefficientsVector->size();

	return coefficientsVector;

}

vector<Complex>* multiplyPolynomials(vector<Complex>* polynomial1, vector<Complex>* polynomial2) {

	vector<Complex>* fft1 = FFT(polynomial1, 1);
	vector<Complex>* fft2 = FFT(polynomial2, 1);

	vector<Complex>* productSamples = new vector<Complex>(fft1->size());

	for (int i = 0; i < productSamples->size(); i++)
		productSamples->at(i) = fft1->at(i) * fft2->at(i);

	vector<Complex>* productCoefficients = IFFT(productSamples);

	delete fft1;
	delete fft2;
	delete productSamples;

	return productCoefficients;
}

vector<Complex>* convolution(vector<Complex>* vector1, vector<Complex>* vector2) {

	Complex zero(0, 0);
	vector<Complex>::iterator it = vector2->end();
	it--;

	for (; it != vector2->begin(); it--) {
		
		if (!(*it == zero)) break;
	
	}

	if (*it == 0) return nullptr;

	reverse(vector2->begin(), ++it);
	return multiplyPolynomials(vector1, vector2);

}