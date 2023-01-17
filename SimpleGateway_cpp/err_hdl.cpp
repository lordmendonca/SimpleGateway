/*
 * err_hdl.cpp
 *
 *  Created on: 06-Feb-2022
 *      Author: JASON
 */

#include "err_hdl.h"

ErrorWriter errConsole;
CentralErrorHandler cErrHdlr(errConsole,terminateError);

void terminateError()
{
	std::terminate();
}
void terminateWarning()
{
	std::cerr << "A bad configuration was encountered but allowed." << std::endl;
}
