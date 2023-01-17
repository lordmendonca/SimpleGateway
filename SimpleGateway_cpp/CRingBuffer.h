/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CRINGBUFFER.H
* Author          :
* Description     :
*
*
****************************************************************************/

#ifndef CRINGBUFFER_H
#define CRINGBUFFER_H

#include "global.h"
#include <string>

#include <ostream>

class CRingBuffer {
public:
    /**
     *  \brief Enum : bufferSize   : Default Configuration for the Ring Buffer.
     */
	enum bufferSize{
		DEFAULT = 20,	/**< \brief Default Buffer Size. VALUE = 20.*/
		MAXSIZE = 64,	/**< \brief Maximum Buffer Size. VALUE = 64.*/
		MINSIZE = 1		/**< \brief Minimum Buffer Size. VALUE = 1. */
	};
private:
	/**
	 *  \param A character pointer used to store bytes of data upto size 'm_size'.
	 */
	uint8_t* m_pBuffer;
	/**
	 *  \param The size of the Ring Buffer.
	 */
	uint16_t m_size;
	/**
	 *  \param The index to read the buffer that points to most recent position on the buffer.
	 */
	uint16_t m_readIdx;
	/**
	 *  \param The index to write the buffer that points to most recent position on the buffer.
	 */
	uint16_t m_writeIdx;
	/**
	 *  \param The incremental capacity indicator when the buffer is either written into or read from.
	 */
	uint16_t m_fillLevel;
public:
    /**
     *  \brief Paramterized Constructor.
     *  
     *  \param [in] size : The size of the buffer.
     *  \details Default size if provided by CRingBuffer::DEFAULT
     */
    CRingBuffer(uint16_t size = CRingBuffer::DEFAULT);
    /**
     *  \brief Copy Constructor
     *  
     *  \param [in] rop Right-hand-operator that takes a reference of the object of type CRingBuffer.
     *  \details Required for overloading insertion operator "<<".
     */
    CRingBuffer(const CRingBuffer& rop);
    /**
     *  \brief Destructor
     */
    ~CRingBuffer();
    /**
     *  \brief Method used to read the content from the buffer.
     *  
     *  \param [in] data : A reference where a byte of data that was read from buffer will be written into.
     *  \return 
     *  		RC_SUCCESS	- Reading from buffer was successful.
     *  		RC_BUFFERUNDERFLOW - The buffer was empty.
     *  
     */
    RC_t read(uint8_t& data);
    /**
     *  \brief Method used to write the content into the buffer.
     *  
     *  \param [in] data : A byte of data that has to be written into the buffer.
     *  \return 
     *  		RC_SUCCESS	- Reading from buffer was successful.
     *  		RC_BUFFEROVERFLOW - The buffer was overflown..
     *  
     */
    RC_t write(uint8_t data);
    /**
     *  \brief Method used to clear the buffer.
     *  
     *  \return RC_SUCCESS	- Reading from buffer was successful.
     */
    RC_t clear();
	/**
	*  \brief Function used to overload the insertion operator '<<'.
	*  \details This is a friend function to the class CRingBuffer.
	*  
	*  \param [in] out A reference of ostream object to insert data for printing on console.
	*  \param [in] rop The Right-hand-operator while overloading, of type CRingBuffer.
	*  \return A reference of the ostream object into which the data was inserted for printing on console.
	*/
    friend std::ostream& operator << (std::ostream& out, CRingBuffer rop);
};
/********************
**  CLASS END
*********************/
#endif /* CRINGBUFFER_H */
