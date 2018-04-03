#include "ALU.h"

template <class T>
T ALU<T>::And(T a, T b) {
	return (a & b);
}

template <class T>
T ALU<T>::Compliment(T a) {
	T N;
	N.flip();
	return Add(1, XOr(a, N)); // Get 2's compliment of a value
}

// Performs a bit comparison between a and b.
// Doesn't treat last bit as a negative (unsigned bit comparison).
template <class T>
int ALU<T>::GreaterThan(T &a, T &b) {
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

template <class T>
T ALU<T>::XOr(T a, T b) {
	return (a ^ b);
}

template <typename T>
T ALU<T>::Add(T a, T b) {
	bool IsNeg = false;
	if (a[a.size() - 1])
		IsNeg = !IsNeg;
	if (b[b.size() - 1])
		IsNeg = !IsNeg;

	T temp = XOr(a, b);
	b = And(a, b) << 1;
	a = temp;
	// Algorithm performs add operation using a pattern discovered during testing.
	assert(a.size() == b.size());
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
	//cout << a << ", " << b << endl;
	return a;
}

template <class T>
T ALU<T>::Subtract(T a, T b) {
	return Add(a, Compliment(b)); // Use 2's compliment to invert b
}

template <class T>
T ALU<T>::Multiply(T a, T b) {
	if (a == 0 || b == 0)
		return 0;
	if (a == 1)
		return b;
	if (b == 1)
		return a;

	bool IsNeg = false;
	if (b[b.size() - 1]) { // b < 0
		IsNeg = !IsNeg;
		b = Compliment(b);
	}

	T sum = 0;
	T mult = 1;

	while (b != 0) {
		//std::cout << a << std::endl;

		//cout << "sum: " << sum << ", a: " << a << ", b: " << b << endl;
		if (b[0]) {
			sum = Add(sum, a);
		}
		//Add(a, a << 1);
		a = a << 1;
		b = b >> 1;
		//cout << a << endl;
		//cout << a << endl;
	}
	if (IsNeg)
		return Compliment(sum);
	return sum;
}

template <class T>
T ALU<T>::Divide(T a, T b) {
	// Special cases
	if (b == 0)
		throw std::logic_error("Can't divide by zero!");
	else if (b == 1)
		return a;

	bool IsNeg = false;
	if (b[b.size() - 1]) { // b > 0
		b = Compliment(b);
		IsNeg = !IsNeg;
	}
	if (a[a.size() - 1]) { // a > 0
		a = Compliment(a);
		IsNeg = !IsNeg;
	}

	T sum = 0;
	T mult = 1;
	while (GreaterThan(a, b) > 0) { // Unsigned int comparison: a > b
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

template <class T>
T ALU<T>::Exponent(T a, T b) {
	// Special cases
	if (b == 0)
		return 1;
	if (((b[b.size() - 1]) || a == 0) && !(a == 1 || a == Compliment(1))) // (b < 0 || a == 0) && a isn't 1 or -1
		return 0;
	if (a == -1 && b[b.size() - 1])
		b = Compliment(b);

	T sum = 1;
	T temp = a;
	while (!b[b.size() - 1] && b != 0) { // b > 0
		if (b[0])
			sum = Multiply(sum, a);
		temp = Multiply(a, a);
		b = b >> 1;
		a = temp;
	}
	return sum;
}

template <class T>
T ALU<T>::Modulus(T a, T b) {
	// Special cases
	if (b == 0)
		throw std::logic_error("Can't divide by zero!");

	bool IsNeg = false;
	if (b[b.size() - 1]) { // b < 0
		b = Compliment(b);
	}
	if (a[a.size() - 1]) { // a < 0
		IsNeg = true;
		a = Compliment(a);
	}

	T mult = 1;
	while (GreaterThan(a, b) > 0) {
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