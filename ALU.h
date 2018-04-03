// ALU.h
// Made by: Hayden Burker

#ifndef ALU_H
#define ALU_H

#include <bitset>
#include <cassert>
#include <climits>
#include <string>
#include <iostream>


template <typename T>
class ALU {

	//------Bit Operations------

	// Not accessed by CPU
	T And(T, T);

	T Compliment(T);

	int GreaterThan(T&, T&);

	T XOr(T, T);
public: 
	T Add(T, T);
	T Subtract(T, T);
	T Multiply(T, T);
	T Divide(T, T);
	T Exponent(T, T);
	T Modulus(T, T);

	
};

#endif // !ALU_H

// Simplified Version

/*
#pragma once

template <typename T>
class ALU {

	//------Bit Operations------

	// Not accessed by CPU

	T And(T a, T b) {
		return (a & b);
	}

	T Compliment(T &a) {
		return Add(1, XOr(a, -1)); // Get 2's compliment of a value
	}

	int GreaterThan(T a, T b) {
		assert(a.size() == b.size());
		T Result = 1;
		if (a[a.size() - 1]) {
			Result = Compliment(Result);
		}
		if (b[b.size() - 1]) {
			Result = Compliment(Result);
		}

		for (int i = a.size() - 2; i >= 0; i--) {
			//std::cout << a[i] << ", " << b[i] << "  ";
			if (a[i] > b[i])
				return Result.to_ulong();
			else if (a[i] < b[i])
				return Compliment(Result).to_ulong();
		}
		return 0;
	}

	T XOr(T a, T b) {
		return (a ^ b);
	}

public:

	T Add(T a, T b) {
		if (b == 0)
			return a;
		return Add(XOr(a, b), And(a, b) << 1);
		// XOr(a, b) is the sum so far
		// And(a, b) << 1 is the carry value
	}

	T Subtract(T a, T b) {
		return Add(a, Compliment(b)); // Use 2's compliment to invert b
	}

	T Multiply(T a, T b) {
		bool IsNeg = false;
		if (b[b.size() - 1] && b != 0) { // b > 0
			IsNeg = true;
			b = Compliment(b);
		}

		T sum = 0;
		while (!b[b.size() - 1] && b != 0) { // b < 0
			sum = Add(sum, a);
			b = Subtract(b, 1);
		}
		if (IsNeg)
			return Compliment(sum);
		return sum;
	}
	
	T Divide(T a, T b) {
		std::bitset<1> IsNeg = false;
		if (b[b.size() - 1] && b != 0) { // b > 0
			b = Compliment(b);
			IsNeg.flip();
		}
		if (a[a.size() - 1] && a != 0) { // a > 0
			a = Compliment(a);
			IsNeg.flip();
		}

		T sum = 0;
		while (GreaterThan(a, b) >= 0) {
			sum = Add(sum, 1);
			a = Subtract(a, b);
		}
		if (IsNeg.all())
			return Compliment(sum);
		return sum;
	}
	
	T Exponent(T a, T b) {
		if (b == 0)
			return 1;
		else if (b[b.size() - 1] && b != 0) // b < 0
			return 0;
		T sum = 1;
		while (!b[b.size() - 1] && b != 0) { // b > 0
			sum = Multiply(sum, a);
			b = Subtract(b, 1);
		}
		return sum;
	}
	
	T Modulus(T a, T b) {
		bool isNeg = false;
		if (GreaterThan(b, 0) < 0) { // b < 0
			b = Compliment(b);
		}
		if (GreaterThan(a, 0) < 0) { // a < 0
			isNeg = true;
			a = Compliment(a);
		}
		while (GreaterThan(a, b) >= 0) {
			a = Subtract(a, b);
		}
		if (isNeg)
			return Compliment(a);
		return a;
	}

};
*/