/*
 * CParser.cpp
 *
 *  Created on: 01.12.2019
 *      Author: Fromm
 */

#include <iostream>
#include "CGateway.h"

#include <string>
#include <map>
#include "CPort.h"
#include "err_hdl.h"
using namespace std;

CGateway::CGateway(CPort &portA, CPort &portB)
{
	try
	{
		m_portA = &portA;
		m_portB = &portB;
		/* Handle null pointer error. */
		if(nullptr == m_portA || nullptr == m_portB)
			throw RC_ERROR;
	}
	catch(RC_t& err)
	{
		cErrHdlr.report(CEH_INVALIDPOINTER);
	}
}

CGateway::CGateway(CPortFactory::port_t portA, CPortFactory::port_t portB)
{
	try
	{
		m_portA = CPortFactory::createPort(portA);
		m_portB = CPortFactory::createPort(portB);
		/* Handle null pointer error. */
		if(nullptr == m_portA || nullptr == m_portB)
			throw RC_ERROR;
	}
	catch(RC_t& err)
	{
		cErrHdlr.report(CEH_INVALIDPOINTER);
	}
}

CGateway::CGateway()
{
	m_portA = nullptr;
	m_portB = nullptr;
}

CGateway::~CGateway()
{
	m_portA = 0;
	m_portB = 0;
}


RC_t CGateway::SelectPortTypes()
{
	uint16_t selectportA ;
	uint16_t selectportB;

	bool isSelectionValid = false;

	static uint16_t countUartPort = 0;
	static uint16_t countCanPort = 0;

	do
	{
		try
		{
			cout << "Select Port A : [1] UART | [2] CAN : ";
			cin >> selectportA;
			cout << "Select Port B : [1] UART | [2] CAN : ";
			cin >> selectportB;
			isSelectionValid = (selectportA == 1 || selectportA == 2) && (selectportB == 1 || selectportB == 2);
			/* Handle invalid input. */
			if(false == isSelectionValid)
				throw RC_WRONGPARAM;
		}
		catch(RC_t& err)
		{
			cerr << "Invalid Selection. Select the correct ports." << endl;
		}
	}while(!isSelectionValid);

	if(selectportA == 1) countUartPort++;
	else countCanPort++;

	if(selectportB == 1) countUartPort++;
	else countCanPort++;

	try
	{
		/* Handle exceeding maximum number of allowed ports in the gateway. */
		if(countUartPort > PORT_ASCLINMAX)
			throw RC_EXCEEDEDASCLINPORTS;
		if(countCanPort > PORT_CANNMAX)
			throw RC_EXCEEDEDCANPORTS;
	}
	catch(RC_t& err)
	{
		if(err == RC_EXCEEDEDASCLINPORTS)
			cErrHdlr.report(CEH_MAXASCLINPORTSREACHED);
		else if(err == RC_EXCEEDEDCANPORTS)
			cErrHdlr.report(CEH_MAXCANPORTSREACHED);

	}
	/* Processing the selected port information. */
	switch((selectportA * 10 + selectportB))
	{
		case 12:
			cout << endl << "[ UART to CAN ]" << endl;
			SelectUartPorts(m_portA);
			SelectCanPorts(m_portB);
			break;
		case 21:
			cout << endl <<  "[ CAN to UART ]" << endl;
			SelectCanPorts(m_portA);
			SelectUartPorts(m_portB);
			break;
		case 11:
			cout << endl << "[ UART to UART ]" << endl;
			SelectUartPorts(m_portA);
			SelectUartPorts(m_portB);
			break;
		case 22:
			cout << endl << "[ CAN to CAN ]" << endl;
			SelectCanPorts(m_portA);
			SelectCanPorts(m_portB);
			break;
		default:
			/* Error handled beforehand. */
			break;
	}

	return RC_SUCCESS;
}

RC_t CGateway::SelectUartPorts(CPort*& port)
{
	uint16_t select;
	bool isSelectionValid = false;
	do
	{
		try
		{
			cout << "Select UART Port : [1] ASCLIN1 | [2] ASCLIN2 | [3] ASCLIN3 | [4] ASCLIN4 | [5] ASCLIN5 : ";
			cin  >> select;
			/* Handling first if the port is occupied and then assigning that port. */
			switch(select)
			{
				case 1 :
					if(CPort::NOTAVAILABLE == CUartPort::isPortAvailable(CUartPort::ASCLIN1))
							throw CppErrorHandler("PORT ALREADY OCCUPIED", "ASCLIN1");
					port = CPortFactory::createUartPort(CUartPort::ASCLIN1, UART_DEFAULTBAUDRATE, UART_DEFAULTBITS, CUartPort::NOPARITY,
							UART_DEFAULTSTOPBITS, UART_DEFAULTBUFFERSIZE, UART_DEFAULTBUFFERSIZE, UART_DEFAULTPACKAGESIZE);
					break;
				case 2 :
					if(CPort::NOTAVAILABLE == CUartPort::isPortAvailable(CUartPort::ASCLIN2))
						throw CppErrorHandler(" PORT ALREADY OCCUPIED", "ASCLIN2");
					port = CPortFactory::createUartPort(CUartPort::ASCLIN2, UART_DEFAULTBAUDRATE, UART_DEFAULTBITS, CUartPort::NOPARITY,
							UART_DEFAULTSTOPBITS, UART_DEFAULTBUFFERSIZE, UART_DEFAULTBUFFERSIZE, UART_DEFAULTPACKAGESIZE);
					break;
				case 3 :
					if(CPort::NOTAVAILABLE == CUartPort::isPortAvailable(CUartPort::ASCLIN3))
							throw CppErrorHandler(" PORT ALREADY OCCUPIED", "ASCLIN3");
					port = CPortFactory::createUartPort(CUartPort::ASCLIN3, UART_DEFAULTBAUDRATE, UART_DEFAULTBITS, CUartPort::NOPARITY,
							UART_DEFAULTSTOPBITS, UART_DEFAULTBUFFERSIZE, UART_DEFAULTBUFFERSIZE, UART_DEFAULTPACKAGESIZE);
					break;
				case 4 :
					if(CPort::NOTAVAILABLE == CUartPort::isPortAvailable(CUartPort::ASCLIN4))
							throw CppErrorHandler(" PORT ALREADY OCCUPIED", "ASCLIN4");
					port = CPortFactory::createUartPort(CUartPort::ASCLIN4, UART_DEFAULTBAUDRATE, UART_DEFAULTBITS, CUartPort::NOPARITY,
							UART_DEFAULTSTOPBITS, UART_DEFAULTBUFFERSIZE, UART_DEFAULTBUFFERSIZE, UART_DEFAULTPACKAGESIZE);
					break;
				case 5 :
					if(CPort::NOTAVAILABLE == CUartPort::isPortAvailable(CUartPort::ASCLIN5))
							throw CppErrorHandler(" PORT ALREADY OCCUPIED", "ASCLIN5");
					port = CPortFactory::createUartPort(CUartPort::ASCLIN5, UART_DEFAULTBAUDRATE, UART_DEFAULTBITS, CUartPort::NOPARITY,
							UART_DEFAULTSTOPBITS, UART_DEFAULTBUFFERSIZE, UART_DEFAULTBUFFERSIZE, UART_DEFAULTPACKAGESIZE);
					break;
				default :
					throw isSelectionValid; /* Handling invalid input. */
			}
			/* Handling null pointer assignment. */
			if(nullptr == port)
				throw RC_ERROR;
			isSelectionValid = true;
			break;
		}
		/* Catching when port is occupied. */
		catch(CppErrorHandler& err)
		{
			err.report();
		}
		/* Catching when invalid input. */
		catch(RC_t& err)
		{
			cErrHdlr.report(CEH_INVALIDPOINTER);
		}
		/* Catching when null pointer assignment. */
		catch(bool& err)
		{
			cerr << "Invalid Selection. Select the correct port number." << endl;
		}
	}while(!isSelectionValid);

	return RC_SUCCESS;
}
RC_t CGateway::SelectCanPorts(CPort*& port)
{
	uint16_t select;
	bool isSelectionValid = false;
	do
	{
		try
		{
			cout << "Select CAN Port : [1] CAN1 | [2] CAN2 : ";
			cin  >> select;
			/* Handling first if the port is occupied and then assigning that port. */
			switch(select)
			{
			case 1 :
				if(CPort::NOTAVAILABLE == CCanPort::isPortAvailable(CCanPort::CAN1))
						throw CppErrorHandler(" PORT ALREADY OCCUPIED", "CAN1");
				port = CPortFactory::createCanPort(CCanPort::CAN1, CAN_DEFAULTBAUDRATE, CAN_DEFAULTBUFFERSIZE, CAN_DEFAULTBUFFERSIZE, CAN_DEFAULTPACKAGESIZE);
				break;
			case 2 :
				if(CPort::NOTAVAILABLE == CCanPort::isPortAvailable(CCanPort::CAN2))
						throw CppErrorHandler(" PORT ALREADY OCCUPIED", "CAN2");
				port = CPortFactory::createCanPort(CCanPort::CAN2, CAN_DEFAULTBAUDRATE, CAN_DEFAULTBUFFERSIZE, CAN_DEFAULTBUFFERSIZE, CAN_DEFAULTPACKAGESIZE);
				break;
			default:
				throw isSelectionValid;
			}
			/* Handling null pointer assignment. */
			if(nullptr == port)
				throw RC_ERROR;
			break;
		}
		/* Catching when port is occupied. */
		catch(CppErrorHandler& err)
		{
			err.report();
		}
		/* Catching when invalid input. */
		catch(RC_t& err)
		{
			cErrHdlr.report(CEH_INVALIDPOINTER);
		}
		/* Catching when null pointer assignment. */
		catch(bool& err)
		{
			cerr << "Invalid Selection. Select the correct port number." << endl;
		}
	}while(!isSelectionValid);
	return RC_SUCCESS;
}

RC_t CGateway::transmitFromAToB()
{
	/* Select the communication ports. */
	SelectPortTypes();

	/* Simulate reception of data. */
	m_portA->portRx_isr();

	/* Transmit from Port A to Port B. */
	string data;

	/* Read the data. */
	m_portA->readByteStream(data);

	/* Some Operation on data is done. */

	/* Write the data. */
	m_portB->writeByteStream(data);

	return RC_SUCCESS;
}
