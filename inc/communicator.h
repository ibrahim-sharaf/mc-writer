#ifndef _COMUNICATER
#define _COMUNICATER

#include <windows.h>
#include "charify.h"

#define MAXSIZE 100

using namespace std;

class Communicator
{
	private:

		void openPort(int port);

		void open(char *port);

		int findPort(void);

		bool isValid(void);

	public:

		HANDLE hCom;

		int state;

		char res[MAXSIZE];

		Communicator(void);

		bool writeSerial(char command[]);

		bool readSerial(void);

		void close(void);

};

#endif