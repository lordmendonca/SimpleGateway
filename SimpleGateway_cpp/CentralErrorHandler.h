/*
 * CentralErrorHandler.h
 *
 *  Created on: 14.12.2019
 *      Author: Fromm
 */

#ifndef CENTRALERRORHANDLER_H_
#define CENTRALERRORHANDLER_H_

#include <string>

#include "global.h"
#include "ErrorWriter.h"
#include "CentralErrorHandler_cfg.h"

class CentralErrorHandler
{
public:
	/** 
	 * \brief Type definition of a function pointer with string parameter.
	 */
	typedef void (*fct_out_t) (std::string errMsg);
	/** 
	 * \brief Type definition of a function pointer with no parameter.
	 */
	typedef void (*fct_terminate_t) ();
private:
	/**
	 *  \param An object of ErrorWriter.
	 */
	ErrorWriter& m_outFct;
	/**
	 *  \param A function pointer.
	 */
	fct_terminate_t m_terminateFct;
public:
	/**
	 * \brief Constructor, taking two configuration parameters identifying the functions which will be called in error case.
	 */
	CentralErrorHandler(ErrorWriter& errorFct, fct_terminate_t terminateFct = 0);
	/**
	 * \brief Report function.
	 * \details Enum values for the argument are defined in the configuration file.
	 */
	RC_t report(CEH_source_t err);
};

#endif /* CENTRALERRORHANDLER_H_ */
