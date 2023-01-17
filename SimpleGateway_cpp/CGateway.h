/*
 * CParser.h
 *
 *  Created on: 01.12.2019
 *      Author: Fromm
 */

#ifndef CPARSER_H_
#define CPARSER_H_

#include "global.h"
#include "CPort_Config.h"
#include "CPortFactory.h"

class CGateway
{
private:
	/**
	 * \brief A pointer to the Transmission port.
	 */
	CPort* m_portA;
	/**
	 * \brief A pointer to the Reception port.
	 */
	CPort* m_portB;
	/**
	 *  \brief A private helper function to select the transmission and recption ports of the gateway.
	 *  
     * \return RC_t:
     * 		 RC_SUCCESS - Ports were successfully configured. 
     * 		Specific error code in case of error 	
	 */
	RC_t SelectPortTypes();
	/**
	 *  \brief A private helper function to select the UART ports of the gateway.
	 *  
	 *  \param [in] A reference to a pointer of type CPort.
	 *  
     * \return RC_t:
     * 		 RC_SUCCESS - UART ports were successfully chosen. 
     * 		Specific error code in case of error
	 */
	RC_t SelectUartPorts(CPort*& port);
	/**
	 *  \brief A private helper function to select the CAN ports of the gateway.
	 *  
	 *  \param [in] A reference to a pointer of type CPort.
	 *  
     * \return RC_t:
     * 		 RC_SUCCESS - CAN ports were successfully chosen. 
     * 		Specific error code in case of error .
	 */
	RC_t SelectCanPorts(CPort*& port);
public:
	/**
	 * \brief Constructor taking explicit port objects.
	 */
	CGateway(CPort& portA, CPort& portB);
	/**
	 * Contsructor, using the default factory settings
	 */
	CGateway(CPortFactory::port_t portA,  CPortFactory::port_t portB);
	/**
	 * \brief Default Constructor to support dynamic port selection.
	 */
	CGateway();
	/**
	 *  \brief Method to transmit data from Transmission port (Port A) to Reception port (port B).
	 *  
     * \return RC_t:
     * 		 RC_SUCCESS - Transmisson successful.
     * 		Specific error code in case of error.
	 */
	RC_t transmitFromAToB();
	/**
	 *  \brief Destructor.
	 */
	virtual ~CGateway();
};

#endif /* CPARSER_H_ */
