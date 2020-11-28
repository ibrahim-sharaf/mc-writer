/*
** Modem Command Writer, a utility to write AT Commands to Modems.
** Author: Ibrahim Sharaf
*/


#include <iostream>
#include <communicator.h>
#include <wincolors.h>

using namespace std;

int main(int argc, char const *argv[])
{
	if(argc > 1) {

		if(strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "-version") == 0) {
			cout<<"version 1.0"<<endl;
			return 0;
		}

		else if(strcmp(argv[1], "-about") == 0 )
		{
			cout<<"Modem Commmand Writer is a utility to write AT commands to modems"<<endl;
			return 0;
		}

		else if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "-help") == 0)
		{
			cout<<"Write modemwriter without arguments to start the command shell"<<endl;
			return 0;
		}

		else 
		{
			cout<<"Command not supported"<<endl;
		}
	}

	cout<<"\nStarting ...\n"<<endl;

	Communicator serial;

	if(serial.state == 0) {

		cout<<"Unable to communicate with port"<<endl;
		cout<<"Make sure you that you have a Modem plugged in your Machine"<<endl;
		cout<<"Closing ..."<<endl;
		return 1;
	}

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, GREAN);

	cout<<"\n *******   Welecome to Modem Command Writer    ******,\n";
	   cout<<"    *** to exit programme type x or ctrl+c  ***\n"<<endl;
	   cout<<"          ****************************** "<<endl;

	string sCommand;

	do
	{
		SetConsoleTextAttribute(hConsole, 5);
		cout<< ">> ";
		SetConsoleTextAttribute(hConsole, WHITE);
		
		cin>>sCommand;

		Charify cCommand(sCommand);

		if(sCommand == "x") {
			cout<<"Closing..."<<endl;
			serial.close();
			break;
		}

		if(!serial.writeSerial(cCommand.chr)) {
			cout<<"Can't write to port"<<endl;
			serial.close();
			return 1;
		}

		SetConsoleTextAttribute(hConsole, LIGHTBLUE);

		if(!serial.readSerial()) {
			cout<<"Can't read from port"<<endl;
			serial.close();
			return 1;
		} 

		cout<<serial.res<<endl;

	} while (1);

	CloseHandle(hConsole);
	serial.close();

	return 0;
}