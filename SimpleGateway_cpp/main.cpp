// Standard (system) header files
#include <iostream>
#include <stdlib.h>

using namespace std;

/* Project Header Files */
#include "CGateway.h"
#include "CPortFactory.h"

/* Main program. */
int main (void)
{

	cout << "CONFIGURE YOUR GATEWAY." << endl;
	CGateway simpleGateway;
	for(uint16_t noOfConnections = 1; noOfConnections <= ((PORT_ASCLINMAX + PORT_CANNMAX)/2); noOfConnections++)
	{
		cout << endl << "CONNECTION " << noOfConnections << endl;
		simpleGateway.transmitFromAToB();
	}
	cout << endl << "YOUR GATEWAY WAS SUCCESSFULLY CONFIGURED." << endl;

	return 0;
}
