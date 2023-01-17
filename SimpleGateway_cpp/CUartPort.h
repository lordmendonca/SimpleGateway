/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CUARTPORT.H
* Author          :
* Description     :
*
*
****************************************************************************/

#ifndef CUARTPORT_H
#define CUARTPORT_H

#include "global.h"
#include "CPort.h"
#include "CRingBuffer.h"
#include "CUartPort_Config.h"

#include <set>

class CUartPort : public CPort {
public:
    /**
     *  \brief Enum : port_t   : UART ports.
     */
    enum port_t{
    	ASCLIN1,		/**< \brief ASCLIN Port 1, per default mapped to USB bridge. */
		ASCLIN2, 		/**< \brief ASCLIN Port 2, can be mapped to PIN P12(0),PIN P12(2). */
		ASCLIN3, 		/**< \brief ASCLIN Port 3, can be mapped to PIN P12(3),PIN P12(4). */
		ASCLIN4, 		/**< \brief ASCLIN Port 4, can be mapped to PIN P12(1),PIN P12(5). */
		ASCLIN5, 		/**< \brief ASCLIN Port 5, can be mapped to PIN P12(6). */
		NONE,			/**< \brief default value no valid port. */
    };
    /**
     *  \brief Enum : parity_t   : Parity type.
     */
    enum parity_t{
    	ODD, 			/**< \brief ODD parity, will detect single bit transmission errors. */
		EVEN, 			/**< \brief EVEN parity, will detect single bit transmission errors .*/
		NOPARITY,		/**< \brief NO parity check, only recommended for baudrates below 115200. */
    };
    /**
     * \brief Constructor - Will initialize the peripheral port and setup the RX and TX buffers.
     *
     *  Constructor - Will initialize the peripheral port and setup the RX and TX buffers.
     *  Please check the hardware limitations to ensure proper configuration parameters.
     *
     *  \param port_t port = NONE			: IN	The hardware port to be used.
     *  \param uint16_t baudrate = UART_DEFAULTBAUDRATE	: IN	The baudrate of the device. Check the hardware manual for valid values.
     *  \param uint8_t bits = UART_DEFAULTBITS				: IN	The number of data bits, typically 7 or 8.
     *  \param parity_t parity = NONE		: IN	Parity, ODD, EVEN or NONE.
     *  \param uint8_t stopbits = 1			: IN	Number of Stopbits, 1 or 2.
     *  \param uint16_t bufferSizeRx = UART_DEFAULTBUFFERSIZE : IN 	Size of the Receive Buffer.
     *  \param uint16_t bufferSizeTx = UART_DEFAULTBUFFERSIZE : IN Size of the Transmit Buffer.
     *  \param uint16_t packageSize = UART_DEFAULTPACKAGESIZE : IN Packaging capacity of the port.
     */
    CUartPort(port_t port = NONE,
             uint32_t baudrate = UART_DEFAULTBAUDRATE,
             uint8_t bits = UART_DEFAULTBITS,
             parity_t parity = NOPARITY,
             uint8_t stopbits = UART_DEFAULTSTOPBITS,
			 uint16_t bufferSizeRx = UART_DEFAULTBUFFERSIZE,
			 uint16_t bufferSizeTx = UART_DEFAULTBUFFERSIZE,
			 uint16_t packageSize = UART_DEFAULTPACKAGESIZE
			 );
    /**
     *  \brief Method that checks if the UART port to be accessed is already occupied or not.
	 * \details This is a static member function.
     *  \param [in] port The UART port that must be accessed, provided by CUartPort::port_t.
     *  \return Returns the state of the port to be accessed, provided by CPort::portState_t.
     */	
    static CPort::portState_t isPortAvailable(CUartPort::port_t port);
private:
	/**
	 *  \param A set of occupied UART ports.
	 * \details This is a static member attribute.	 
	 */
    static std::set<CUartPort::port_t> m_occupiedPorts;
	/**
	 *  \param The packaging capacity of a UART port.
	 */
    uint16_t m_uartPackageSize;
    /**
     * \brief Sends one Byte to the hardware.
     * \note The function is non-blocking. In case the hardware is occupied, an error code will be returned.
     *       Therefore the function preferably should be called through an ISR
     * \param [in] data	: Byte to be transmitted
     * \return RC_t:
     * 		 RC_SUCCESS - byte was transmitted,
     * 		 RC_PERIPHERALOCCUPIED - peripheral was occupied, no data was transmitted, must be re-send
     */
    RC_t writeByte_hw(uint8_t data);
    /**
     * \brief Receive one Byte from the hardware.
     * \note The function is non-blocking. In case the hardware is empty, an error code will be returned.
     *       Therefore the function preferably should be called through an ISR
     * \param [in] data	: Byte received
     * \return RC_t:
     * 		 RC_SUCCESS - byte was received,
     * 		 RC_NODATA - peripheral was empty, no data was received, must be re-queried
     */
    RC_t readByte_hw(uint8_t& data);
    /**
     * \brief Sends a packet of data to the hardware.
     *
     * \note The function is non-blocking. In case the hardware is occupied, an error code will be returned.
     *       Therefore the function preferably should be called through an ISR.
     * \param [in] dataBuf : The buffered packet to be transmitted.
     * \return RC_t:
     * 		 RC_SUCCESS - byte was transmitted,
     * 		 RC_PERIPHERALOCCUPIED - peripheral was occupied, no data was transmitted, must be re-send
     */
    RC_t writePackage_hw(CRingBuffer data);
    /**
     * \brief Receive a packet of data from the hardware
     *
     * \note The function is non-blocking. In case the hardware is empty, an error code will be returned.
     *       Therefore the function preferably should be called through an ISR
     * \param [in] dataBuf : Reference of the buffered packet to be received.
     * \return RC_t:
     * 		 RC_SUCCESS - byte was received,
     * 		 RC_NODATA - peripheral was empty, no data was received, must be re-queried
     */
    RC_t readPackage_hw(CRingBuffer& data);
    /**
     * \brief Getter method to fetch the data packaging capacity of a UART port.
     *
     * \return Returns the data packaging size of the UART port.
     */
    uint16_t getDriverPackageSize() const;
};

#endif /* CUARTPORT_H */
