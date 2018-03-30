// ALU.h
// Made by: Hayden Burker

#pragma once

template <typename T>
class ALU {

	//------Bit Operations------

	// Not accessed by CPU

	T And(T a, T b) {
		return (a & b);
	}

	T Compliment(T &a) {
		T N;
		N.flip();
		return Add(1, XOr(a, N)); // Get 2's compliment of a value
	}

	// Performs a bit comparison between a and b.
	// Doesn't treat last bit as a negative (unsigned bit comparison).
	int GreaterThan(T a, T b) {
		assert(a.size() == b.size());

		for (int i = a.size() - 1; i >= 0; i--) {
			//cout << a[i] << ", " << b[i] << "  ";
			if (a[i] > b[i])
				return 1;
			else if (a[i] < b[i]) {
				return -1;
			}
		}
		return 0;
	}

	T XOr(T a, T b) {
		return (a ^ b);
	}

public:

	T Add(T a, T b) {
		bool IsNeg = false;
		if (a[a.size() - 1] && a != 0)
			IsNeg = !IsNeg;
		if (b[b.size() - 1] && b != 0)
			IsNeg = !IsNeg;

		bool CanOverflow = false;
		if ((a[a.size() - 1] ^ a[a.size() - 2]) || b[b.size() - 1] ^ b[b.size() - 2])
			CanOverflow = true;

		T temp = XOr(a, b);
		b = And(a, b) << 1;
		a = temp;
		// Algorithm performs add operation in runtime using a pattern discovered during testing.
		for (int i = 0; i < b.size(); i++) {
			if (b[i]) {
				if (a[i]) {
					b[i] = 0;
					if (i != b.size() - 1)
						b[i + 1] = 1;
					a[i] = 0;
				}
				else {
					b[i] = 0;
					a[i] = 1;
				}
			}
		}
		if ((a[a.size() - 1] ^ IsNeg) && CanOverflow)
			throw runtime_error("Overflow Add");
		return a;
	}

	T Subtract(T a, T b) {
		return Add(a, Compliment(b)); // Use 2's compliment to invert b
	}

	T Multiply(T a, T b) {
		bool IsNeg = false;
		if (b[b.size() - 1] && b != 0) { // b < 0
			IsNeg = !IsNeg;
			b = Compliment(b);
		}
		if (a[a.size() - 1] && a != 0)
			IsNeg = !IsNeg;

		T sum = 0;
		T mult = 1;

		while (b != 0) {
			if (b[0]) {
				sum = Add(sum, a);
				if (sum[sum.size() - 1] && !IsNeg)
					throw runtime_error("Overflow");
			}
			a = a << 1;
			b = b >> 1;
		}

		//if (IsNeg)
			//return Compliment(sum);
		return sum;
	}
	
	T Divide(T a, T b) {
		if (b == 0)
			throw logic_error("Can't divide by zero!");

		bool IsNeg = false;
		if (b[b.size() - 1] && b != 0) { // b > 0
			b = Compliment(b);
			IsNeg = !IsNeg;
		}
		if (a[a.size() - 1] && a != 0) { // a > 0
			a = Compliment(a);
			IsNeg = !IsNeg;
		}

		T sum = 0;
		T mult = 1;
		while (GreaterThan(a, b) > 0) { // Unsigned int comparison: a > b
			if (b[b.size() - 1] && !IsNeg)
				throw runtime_error("Overflow");
			mult = mult << 1;
			b = b << 1;
		}

		while (mult != 0) {

			if (GreaterThan(a, b) >= 0) { // a >= b
				sum = Add(sum, mult);
				a = Subtract(a, b);
			}

			b = b >> 1;
			mult = mult >> 1;
			
		}

		if (IsNeg)
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
			if (b[0])
				sum = Multiply(sum, a);
			//cout << sum << endl;
			//cout << a << endl;
			a = Multiply(a, a);
			b = b >> 1;
		}
		return sum;
	}
	
	T Modulus(T a, T b) {
		if (b == 0)
			throw logic_error("Can't divide by zero!");

		bool IsNeg = false;
		if (b[b.size() - 1] && b != 0) { // b < 0
			b = Compliment(b);
		}
		if (a[a.size() - 1] && a != 0) { // a < 0
			IsNeg = true;
			a = Compliment(a);
		}

		T mult = 1;
		while (GreaterThan(a, b) > 0) {
			if (b[b.size() - 1] && !IsNeg)
				throw runtime_error("Overflow");
			mult = mult << 1;
			b = b << 1;
		}
		
		while (mult != 0) {
			if (GreaterThan(a, b) >= 0) {
				a = Subtract(a, b);
			}

			b = b >> 1;
			mult = mult >> 1;
		}

		if (IsNeg)
			return Compliment(a);
		return a;
	}

};


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