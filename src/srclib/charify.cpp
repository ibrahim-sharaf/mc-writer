#include <iostream>
#include "charify.h"

using namespace std;

Charify::Charify(string str)
{
	int _size = str.length();
	chr  = new char[_size + 1];

	if(chr == NULL){
		exit(0);
	}

	chr = strcpy(chr, str.c_str());
	size = _size;
}


Charify::Charify(const Charify& that)
{
	chr = new char[that.size + 1];
	if (chr == NULL)
		exit(0);
	strcpy(chr, that.chr);
	size = that.size;
}

Charify::~Charify()
{
	delete[] chr;
}

Charify&
Charify::operator=(const Charify& that)
{
	char *local_chr = new char[that.size + 1];

	if (local_chr == NULL)
		exit(0);

	strcpy(local_chr, that.chr);
	delete[] chr;
	chr = local_chr;
	size = that.size;
	return *this;
}

int
Charify::numofdigits(unsigned int num)
{
	if(num == 0)
		return 1;
	return (int) log10(num) + 1;
}

void
Charify::numCat(int num)
{

	int _size = this->numofdigits(num);
	char cNum[_size + 1];
	if(cNum == NULL) {

		exit(1);
	}
	sprintf(cNum, "%d", num);
	strcat(this->chr, cNum);
	this->size += _size;
}