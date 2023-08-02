#include <printf.h>

int flag(int first, int second)
{
	// one
	// -4 = w0
	// -8 = second
	int a = first >> 2;

	// two
	// -4 = a
	// -8 = second
	int b = a + 40;

	// three
	// -4 = b
	// -8 = second
	int c = b - 2;

	// four
	// -4 = c
	// -8 = second
	int d = c / 10;

	// five
	// -4 = d
	// -8 = second
	int e = second * d;

	// six
	// -4 = e
	// -8 = second
	int f = second * e;

	// seven
	// -4 = e
	// -8 = f
	int g = f << (e * f);

	// eight
	// -4 = g
	// -8 = f
	int h = g & f;

	// nine
	// -4 = g
	// -8 = f
	// -12 = h
	int i = (h ^ g) | f;

	// ten
	// -4 = g
	// -8 = f
	// -12 = i 
	double j = g;

	// eleven
	// -4 = g
	// -8 = f
	// -12 = i
	double k = f;

	// twelve
	double l = printf("%lf %lf", j, k);
	// sp+8 = return value

	// thirteen
	// -4 = g
	// -8 = f
	// -12 = i
	double m = i;

	// fourteen
	// -4 = g
	// -8 = f
	// -12 = i
	double n = i;

	// fifteen
	double o = printf("%lf %lf", m, n);
	// return value = d1
	
	// sixteen 
	int p = l * o;

	return p;
}

int main()
{
	// +48 = return:frame-pointer
	
	// sp+24 = b
	// sp+20 = 0
	// sp+12 = 42
	// sp+16 = 69
	// x29-4 = 0
	// x29-16 = a
	float a = flag(42, 69);
	float b = flag(69, 42);
	float c = a+b;

	// Format stored in an unknown place, assuming %f %f
	printf("%f %f", c, b);

	return 0;
}
