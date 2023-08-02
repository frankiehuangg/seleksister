#include <stdio.h>
#include <stdint.h>

int add_int32(int a, int b)
/**
 * Computes the addition of two 32-bit integer
 *
 * @param a		First integer
 * @param b		Second integer
 * @return int	Addition result
 */
{
    int sum = a ^ b;
    int carry = (a & b) << 1;

    if (carry == 0)
        return sum;

    return add_int32(sum, carry);
}

int main()
{
	int a = 27;
	int b = -31;

	printf("%d\n", add_int32(a, b));	
}
