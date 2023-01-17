
/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CPORTFACTORY.CPP
* Author          :
* Description     :
*
*
****************************************************************************/

#include "CPortFactory.h"
#include "err_hdl.h"

CPort* CPortFactory::createCanPort(CCanPort::port_t port,
		uint32_t baudrate, uint16_t bufferSizeRx, uint16_t bufferSizeTx, uint16_t packageSize)
{
	return new CCanPort(port, baudrate,bufferSizeRx, bufferSizeTx, packageSize);
}

CPort* CPortFactory::createUartPort(CUartPort::port_t port,
		uint32_t baudrate, uint8_t bits, CUartPort::parity_t parity,
		uint8_t stopbits, uint16_t bufferSizeRx, uint16_t bufferSizeTx, uint16_t packageSize)
{
	return new CUartPort(port, baudrate, bits, parity,stopbits, bufferSizeRx, bufferSizeTx, packageSize);
}

CPort* CPortFactory::createPort(port_t port)
{
	switch (port)
	{
	case UART: return createUartPort();
	case CAN: return createCanPort();
	default:
		cErrHdlr.report(CEH_INVALIDPOINTER);
		break;
	}
	return 0;
}
