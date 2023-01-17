/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CPORTFACTORY.H
* Author          :
* Description     :
*
*
****************************************************************************/

#ifndef CPORTFACTORY_H
#define CPORTFACTORY_H

#include "CPort_Config.h"

class CPortFactory {
private:
    /**@link dependency*/
    /*# CUartPort lnkCUartPort; */
    /**@link dependency*/
    /*# CCanPort lnkCCanPort; */
public:
    /**
     *  \brief Enum : port_t   : Type of Ports.
     */
	enum port_t{
		UART,	/**< \brief UART Port. */
		CAN,	/**< \brief CAN Port. */
		NONE	/**< \brief default value no valid port. */
	};
    /**
     * \brief Method that creates a UART Port.
	 * \details This is a static member function.
     *  \param port_t port = NONE			: IN	The hardware port to be used.
     *  \param uint16_t baudrate = CAN_DEFAULTBAUDRATE	: IN	The baudrate of the device. Check the hardware manual for valid values.
     *  \param uint16_t bufferSizeRx = CAN_DEFAULTBUFFERSIZE : IN 	Size of the Receive Buffer.
     *  \param uint16_t bufferSizeTx = CAN_DEFAULTBUFFERSIZE : IN Size of the Transmit Buffer.
     *  \param uint16_t packageSize = CAN_DEFAULTPACKAGESIZE : IN Packaging capacity of the port.
     *  \return : Returns the pointer to the CPort that was created.
     */
	static CPort* createCanPort(
			CCanPort::port_t port = CCanPort::NONE,
			uint32_t baudrate = CAN_DEFAULTBAUDRATE,
			uint16_t bufferSizeRx = CAN_DEFAULTBUFFERSIZE,
			uint16_t bufferSizeTx = CAN_DEFAULTBUFFERSIZE,
			uint16_t packageSize = CAN_DEFAULTPACKAGESIZE);
    /**
     * \brief Method that creates a UART Port.
	 * \details This is a static member function.
     *  \param port_t port = NONE			: IN	The hardware port to be used.
     *  \param uint16_t baudrate = UART_DEFAULTBAUDRATE	: IN	The baudrate of the device. Check the hardware manual for valid values.
     *  \param uint8_t bits = UART_DEFAULTBITS				: IN	The number of data bits, typically 7 or 8.
     *  \param parity_t parity = NONE		: IN	Parity, ODD, EVEN or NONE.
     *  \param uint8_t stopbits = 1			: IN	Number of Stopbits, 1 or 2.
     *  \param uint16_t bufferSizeRx = UART_DEFAULTBUFFERSIZE : IN 	Size of the Receive Buffer.
     *  \param uint16_t bufferSizeTx = UART_DEFAULTBUFFERSIZE : IN Size of the Transmit Buffer.
     *  \param uint16_t packageSize = UART_DEFAULTPACKAGESIZE : IN Packaging capacity of the port.
     *  \return : Returns the pointer to the CPort that was created.
     */
    static CPort* createUartPort(
    		CUartPort::port_t port = CUartPort::NONE,
            uint32_t baudrate = UART_DEFAULTBAUDRATE,
            uint8_t bits = UART_DEFAULTBITS,
            CUartPort::parity_t parity = CUartPort::NOPARITY,
            uint8_t stopbits = UART_DEFAULTSTOPBITS,
			uint16_t bufferSizeRx = UART_DEFAULTBUFFERSIZE,
			uint16_t bufferSizeTx = UART_DEFAULTBUFFERSIZE,
			uint16_t packageSize = UART_DEFAULTPACKAGESIZE);

    /**
     * \brief Will create a port using the default configuration of the port (i.e. the default parameters set above).
	 * \details This is a static member function.
	 * \param [in] Type of the port to be created, as provided by CPortFactory::port_t.
     * \return : Returns the pointer to the CPort that was created.
     */
    static CPort* createPort(port_t port);
};
/********************
**  CLASS END
*********************/
#endif /* CPORTFACTORY_H */
