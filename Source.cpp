// Spike solution of ALU
// Made by: Hayden Burker

#include <bitset>
#include <cassert>
#include <climits>
#include <string>
#include <iostream>

#include "ALU.cpp" // Include .cpp files instead of .h files when using templates

using namespace std;

int main() {

	// CPU performs operations in ALU and returns value to a register
	// ex: register[c] = alu.Add(register[a], register[b]).to_ullong();
	const int SIZE = sizeof (int) * CHAR_BIT;
	ALU<bitset<SIZE>> alu;
	string input1;
	string input2;
	//cout << "hi" << endl;
	int num1 = 0;
	int num2 = 0;
	int result = 0;
	while (input1 != "end") {

		try {
			cin >> input1;
			num1 = stoi(input1);
			cin >> input2;
			num2 = stoi(input2);

			int result;

			//cout << "num1: " << num1 << endl;
			//cout << "num2: " << num2 << endl;
			//cout << "And: " << (num1 & num2) << endl;
			//cout << "Xor: " << (num1 ^ num2) << endl;
			result = alu.Add(num1, num2).to_ullong();
			cout << "Add: " << result << endl;
			result = alu.Subtract(num1, num2).to_ullong();
			cout << "Subtract: " << result << endl;
			result = alu.Multiply(num1, num2).to_ullong();
			cout << "Multiply: " << result << endl;

			try {
				result = alu.Divide(num1, num2).to_ullong();
				cout << "Divide: " << result << endl;
			}
			catch (exception &e) {
				cout << e.what() << endl;
			}

			result = alu.Exponent(num1, num2).to_ullong();
			cout << "Exponent: " << result << endl;

			try {
				result = alu.Modulus(num1, num2).to_ullong();
				cout << "Modulus: " << result << endl;
			}
			catch (exception &e) {
				cout << e.what() << endl;
			}
			


		}
		catch (exception &e) {
			cout << e.what() << endl;
		}
	}
}