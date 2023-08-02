#include <stdio.h>

int maxElement(int arr[], int length)
/**
 * Returns the max element of an array
 *
 * @param arr[]	  Array of floats
 * @param length  Array length
 */
{
	int i = 1;
	int max = arr[0];

check:
	if (arr[i] > max)
		max = arr[i];
	i++;

	if (i < length)
		goto check;
	else
		goto finish;

finish:
	return max;
}

int minElement(int arr[], int length)
/**
 * Returns the min element of an array
 *
 * @param arr[]	  Array of floats
 * @param length  Array length
 */
{
	int i = 1;
	int min = arr[0];

check:
	if (arr[i] < min)
		min = arr[i];
	i++;
	
	if (i < length)
		goto check;
	else
		goto finish;

finish:
	return min;
}

int main()
{
	int intArr[10] = { 5, 3, 9, 11, 21, 84, 12, 1, -33, 17 };
	float floatArr[10] = { 5.3, 1.2, 9.4, -2.4, 0.3, 11.3, -0.4, 3.3, 12.4, -20.7 };

	printf("%d\n", maxElement(intArr, 10));
	printf("%d\n", minElement(intArr, 10));
}
