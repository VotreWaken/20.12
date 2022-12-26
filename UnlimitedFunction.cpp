#include <iostream>
#include <stdarg.h>

using namespace std;

// Function with unlimited number of parameters ( int )
void ShowInt(int count, ...)
{
	va_list arg_ptr;
	va_start(arg_ptr, count);
	while (count--)
	{
		cout << va_arg(arg_ptr, int) << " ";
	}
	va_end(arg_ptr);
	cout << endl;
}
// Function with unlimited number of parameters ( char )
void ShowChar(int count, ...)
{
	va_list arg_ptr;
	va_start(arg_ptr, count);
	while (count--)
	{
		cout << va_arg(arg_ptr, char) << " ";
	}
	va_end(arg_ptr);
	cout << endl;
}
// Function with unlimited number of parameters ( With end Sign )
void ShowEndSign(int count, ...)
{
	int* pCount = &count;

	while (*pCount)
	{
		cout << *(pCount++) << " ";
	}
	cout << endl;
}

int main()
{
	ShowChar(5, 'H', 'e', 'l', 'l', 'o');
	ShowInt(3, 1, 2, 5);
	ShowEndSign(1, 5, 2, 3, 1, 5, 0);
}