/*
 * CentralErrorHandler.cpp
 *
 *  Created on: 14.12.2019
 *      Author: Fromm
 */

#include "CentralErrorHandler.h"


/**\brief Array of strings, containing human readable representations of event sources */
const char * const CEH__source_strings[] = {
		CEH_CFG(CEH_CFG_ENUM_STR)
};


/**\brief Configuration storage */
const CEH_event_table_entry_t CEH_event_table[] = {
		CEH_CFG(CEH_CFG_ENTRY)
};

/**
 * Constructor, taking two configuration parameters identifying the functions which will be called in error case
 */
CentralErrorHandler::CentralErrorHandler(ErrorWriter& errorFct, fct_terminate_t terminateFct) : m_outFct(errorFct)
{
	m_terminateFct = terminateFct;
}

/**
 * Report function
 * Enum values for the argument are defined in the configuration file
 */
RC_t CentralErrorHandler::report(CEH_source_t err)
{
	//Translate enum into index
	uint16_t index = (uint16_t)err;

	//CHeck for valid function pointers
	if (0 == m_terminateFct)
	{
		return RC_ERROR;
	}

	std::string errorMessage = CEH__source_strings[index];

	if (true == CEH_event_table[index].report)
	{
		 m_outFct(errorMessage);
	}

	if (true == CEH_event_table[index].terminate)
	{
		m_terminateFct();
	}

	return RC_SUCCESS;
}
