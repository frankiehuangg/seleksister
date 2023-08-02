#include <stdio.h>

int flag(int first, int second)
{
	int a = ((first >> 2) + 38) / 10;

	int b = second * a;
	int c = second * b;

	int d = c << (b * c);
	int e = ((d & c) ^ d) | c;

	int f = printf("%d %d\n", d, c);

	int g = printf("%d %d\n", e, e);

	return f*g;
}

int main()
{
	float a = flag(42, 69);
	float b = flag(69, 42);
	a += b;

	printf("%f %f\n", a, b);

	return 0;
}
