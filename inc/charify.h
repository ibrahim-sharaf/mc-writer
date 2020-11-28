#ifndef _CHARIFY
#define _CHARIFY

#include <stdlib.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <math.h>

using namespace std;

class Charify
{
	private:
		int numofdigits(unsigned int num);
	public:
		Charify(string str);
		Charify(const Charify& that);
		Charify& operator=(const Charify& that);
		~Charify();
		char *chr;
		int size;
		void numCat(int num);
};

#endif