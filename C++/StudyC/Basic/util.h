#pragma once
#include <iostream>
#include <string>

using namespace std;

namespace util
{
	void func(string func,bool choice)
	{
		if (choice) cout << "\n\n<============" << func << "============>\n" << endl;
		else cout << "\n<============" << func << "============>\n\n" << endl;
	}
}