/*
 * err_hdl.h
 *
 *  Created on: 05-Feb-2022
 *      Author: JASON
 */

#ifndef ERR_HDL_H_
#define ERR_HDL_H_
/**
 *  \brief Includes of Error Handler Classes.
 */
#include "ErrorWriter.h"
#include "CentralErrorHandler.h"
#include "CppErrorHandler.h"
/**
 *  \brief An extern definition of object of class ErrorWriter for handling errors globallly.
 */
extern ErrorWriter errConsole;
/**
 *  \brief An extern definition of object of class CentralErrorHandler for handling errors globallly.
 */
extern CentralErrorHandler cErrHdlr;
/**
 *  \brief Method that gives a hard termination when an error occurs.
 *  \details A function pointer to this function is utilized in CentralErrorHandler. 
 */
extern void terminateError();
/**
 *  \brief Method that throws a warning but allows the execution of program to continue when an error occurs.
 *  \details A function pointer to this function is utilized in CentralErrorHandler. 
 */
extern void terminateWarning();

#endif /* ERR_HDL_H_ */
