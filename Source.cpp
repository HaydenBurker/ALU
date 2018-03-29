// Spike solution of ALU
// Made by: Hayden Burker

#include <bitset>
#include <cassert>
#include <string>
#include <iostream>

#include "ALU.h"

using namespace std;

int main() {

	// CPU performs operations in ALU and returns value to a register
	// ex: register[c] = process.Add(register[a], register[b]).to_ullong();
	const int SIZE = sizeof (int) * 8;
	ALU<bitset<SIZE>> process;
	string input1;
	string input2;
	int num1 = 0;
	int num2 = 0;
	int result = 0;
	while (input1 != "end") {

		try {
			cin >> input1;
			num1 = stoi(input1);
			cin >> input2;
			num2 = stoi(input2);
			cout << num1 / num2 << endl;

			int result;

			//cout << "num1: " << num1 << endl;
			//cout << "num2: " << num2 << endl;
			//cout << "And: " << (num1 & num2) << endl;
			//cout << "Xor: " << (num1 ^ num2) << endl;
			result = process.Add(num1, num2).to_ullong();
			cout << "Add: " << result << endl;
			result = process.Subtract(num1, num2).to_ullong();
			cout << "Subtract: " << result << endl;
			result = process.Multiply(num1, num2).to_ullong();
			cout << "Multiply: " << result << endl;
			result = process.Divide(num1, num2).to_ullong();
			cout << "Divide: " << result << endl;
			result = process.Exponent(num1, num2).to_ullong();
			cout << "Exponent: " << result << endl;
			result = process.Modulus(num1, num2).to_ullong();
			cout << "Modulus: " << result << endl;
			


		}
		catch (exception &e) {
			cout << e.what() << endl;
		}
	}
}