#include <stdio.h>
#include <stdint.h>

void bin(unsigned n)
{
    unsigned i;
    for (i = 1 << 31; i > 0; i = i / 2)
        (n & i) ? printf("1") : printf("0");
}

unsigned get_sign(float f)
{
	unsigned int* iptr = (unsigned int*)&f;
	return ((*iptr >> 31) & 1);
}

unsigned get_exponent(float f)
{
	unsigned int* iptr = (unsigned int*)&f;
	return ((*iptr >> 23) & 0xff);
}

unsigned get_mantissa(float f)
{
	unsigned int* iptr = (unsigned int*)&f;
	return (*iptr & 0x7FFFFF);
}

float get_float(unsigned sign, unsigned exponent, unsigned mantissa)
{
	unsigned float_rep = ((sign << 31) | (exponent << 23) | mantissa);

	return *(float*)&float_rep;
}

float add_float(float a, float b)
/**
 * Computes the addition of two 32-bit float
 *
 * @param a			First float
 * @param b			Second float
 * @return float	Addition result
 */
{
	uint32_t sign_a = get_sign(a);
	uint32_t exponent_a = get_exponent(a);
	uint32_t mantissa_a = get_mantissa(a);
	printf("A: %f\n", get_float(sign_a, exponent_a, mantissa_a));

	uint32_t sign_b = get_sign(b);
	uint32_t exponent_b = get_exponent(b);
	uint32_t mantissa_b = get_mantissa(b);
	printf("B: %f\n", get_float(sign_b, exponent_b, mantissa_b));

	uint32_t result_sign;
	uint32_t result_exponent;
	uint32_t result_mantissa;

	uint32_t different_sign = sign_a ^ sign_b;

	// Catch case NaN
	if (!(exponent_a ^ 0xFF) && mantissa_a) return a;
	if (!(exponent_b ^ 0xFF) && mantissa_b) return b;

	// Catch case Inf
	if (!(exponent_a ^ 0xFF) && !(exponent_b ^ 0xFF)) {
		// Both are Inf
		if (different_sign) // Inf - Inf = NaN
			return get_float(0, 0xFF, 1);
		else // Inf or -Inf
			return a;
	}
	else if (!(exponent_a ^ 0xFF)) return a;
	else if (!(exponent_b ^ 0xFF)) return b;

	// Case other
	uint32_t exponent_diff;
	if (different_sign) {
		exponent_diff = exponent_a + exponent_b;
	}
	else {
		// No need to account for constant BO
		// Beware of underflow
		if (exponent_a > exponent_b) exponent_diff = exponent_a - exponent_b;
		else exponent_diff = exponent_b - exponent_a;
	}

	uint32_t x_bigger_abs;
	if		(exponent_a > exponent_b)	x_bigger_abs = 1;
	else if (exponent_a < exponent_b)	x_bigger_abs = 0;
	else if (mantissa_a > mantissa_b)	x_bigger_abs = 1;
	else								x_bigger_abs = 0;

	if (!different_sign) {
		// Both numbers have the same sign (addition)
		result_sign = sign_a;

		if (x_bigger_abs) {
			result_mantissa = ((mantissa_a << 1) + (mantissa_b << 1)) >> exponent_diff;
			result_exponent = exponent_a;
		}
		else {
			result_mantissa = (mantissa_b << 1) + ((mantissa_a << 1) >> exponent_diff);
			result_exponent = exponent_b;
		}
	}
	else {
		// This is a subtraction
		if (x_bigger_abs) {
			result_sign = sign_a;
			result_exponent = exponent_a;

			// Subtract and round to 23 bit
			result_mantissa = (mantissa_a << 1) - ((mantissa_b << 1) >> exponent_diff);
		}
		else {
			result_sign = sign_b;
			result_exponent = exponent_b;

			result_mantissa = (mantissa_b << 1) - ((mantissa_a << 1) >> exponent_diff);
		}
	}

	if (result_mantissa << 31) result_mantissa = (result_mantissa >> 1) + 1;
	else result_mantissa = (result_mantissa >> 1);

	// Normalize
	uint32_t temp = result_mantissa << 9;
	for (uint32_t count = 0; count < 23; ++count) {
		if (!((temp << count) >> 31)) {
			result_mantissa <<= ++count;
			result_exponent -= count;
			break;
		}
	}

	float result = get_float(result_sign, result_exponent, result_mantissa);

	return result;
}

int main()
{
	float a = 1.5;
	float b = 1.75;

	printf("%f\n", add_float(a, b));
}
