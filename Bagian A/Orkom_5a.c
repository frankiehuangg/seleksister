#include <stdio.h>

int arraySum(int arr[], int length)
/**
 * Computes the sum of all array elements
 *
 * @param arr[]	  Array of integers
 * @param length  Array length
 */
{
	int i = 0;
	int sum = 0;

add_element:
	sum += arr[i];
	i++;
	if (i < length)
		goto add_element;
	else
		goto finish;

finish:
	return sum;
}

float floatArraySum(float arr[], int length)
/**
 * Computes the sum of all array elements
 *
 * @param arr[]	  Array of floats
 * @param length  Array length
 */
{
	int i = 0;
	float sum = 0;

add_element:
	sum += arr[i];
	i++;
	if (i < length)
		goto add_element;
	else
		goto finish;

finish:
	return sum;
}

int main()
{
	int intArr[10] = { 5, 3, 9, 11, 21, 84, 12, 1, 33, 17 };
	float floatArr[10] = { 5.3, 1.2, 9.4, -2.4, 0.3, 11.3, -0.4, 3.3, 12.4, -20.7 };

	printf("%d\n", intArraySum(intArr, 10));
	printf("%f\n", floatArraySum(floatArr, 10));
}
