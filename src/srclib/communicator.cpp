#include "communicator.h"
#include <iostream>

using namespace std;

Communicator::Communicator(void) {

	this->hCom  = NULL;
	this->state = 0;

	int port = this->findPort();
	
	if(port != -1) {
		this->state = 1;
	}
}

int Communicator::findPort(void) {

	for(int i = 0; i < 30; i++) {

		this->openPort(i);

		if(this->hCom != INVALID_HANDLE_VALUE){

			for(int i = 0; i <= 4; i++)
			{
				if(this->isValid())
					return i;
			}
		}
	}

	return -1;
}

void Communicator::openPort(int port) {

	if(port < 10) {
		
		Charify portName("COM");
		portName.numCat(port);
		
		this->open(portName.chr);
	} else {
		Charify portName("\\\\.\\COM");
		portName.numCat(port);

		this->open(portName.chr);
	}
}

void Communicator::open(char * port) {
	this->hCom = CreateFile(port, GENERIC_READ | GENERIC_WRITE, 0, 
		NULL, OPEN_EXISTING, 0, NULL);

	if (this->hCom != INVALID_HANDLE_VALUE)
	{
		COMMTIMEOUTS CommTimeOuts;
 		CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF;
 		CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
 		CommTimeOuts.ReadTotalTimeoutConstant = 500;
 		CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
 		CommTimeOuts.WriteTotalTimeoutConstant = 500;
 		SetCommTimeouts(hCom, &CommTimeOuts);
	}
}


bool Communicator::isValid(void) {
	/* Test for AT commands */
	char command[] = "AT";

	if(this->writeSerial(command)) {

		DWORD readBytes = 0;
		char toRead[100] = "";

		if(!ReadFile(this->hCom, toRead, sizeof(toRead), &readBytes, NULL)) {
			return FALSE;
		}

		char res[] = "OK";

		if (strstr(toRead, res) != NULL) {
			return TRUE;
		}
	}

	return FALSE;
}

bool Communicator::writeSerial(char *command) {

	DWORD writtenBytes = 0;
    strcat(command, "\r");

	unsigned int i;
	for (i = 0; i < strlen(command); i++) {
		if (!WriteFile(this->hCom, &command[i], 1, &writtenBytes, NULL)) {
			return false;
		}
	}

	return true;
}

bool Communicator::readSerial(void) {
	
	DWORD readBytes = 0;
	
	if(!ReadFile(this->hCom, this->res, MAXSIZE , &readBytes, NULL))
		return false;

	this->res[readBytes] = '\0'; 

	return true;
}

void Communicator::close(void) {

	CloseHandle(this->hCom);
}