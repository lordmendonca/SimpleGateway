/*
 * global.h
 *
 *  Created on: 18.10.2019
 *      Author: Fromm
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_
/**
 *  \brief type defintions of basic data types.
 */
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
typedef signed int sint32_t;
typedef signed short sint16_t;
typedef signed char sint8_t;
/**
 *  \brief Enum RC_t : Type of Return Code.
 *  \details Enumerated type for readibilty of the return from a fucntion.
 */
enum RC_t{
	RC_SUCCESS,				/**< \brief A succesful return. */
	RC_ERROR,				/**< \brief An unsuccesful return due to some error. */
	RC_WRONGPARAM,			/**< \brief An unsuccesful return due to some wrong parameters provided/passed. */
	RC_BUFFEROVERFLOW,		/**< \brief An unsuccesful return due to buffer overrun. */
	RC_BUFFERUNDERFLOW,		/**< \brief An unsuccesful return due to buffer empty. */
	RC_PERIPHERALOCCUPIED,	/**< \brief An unsuccesful return due to peripheral being engaged. */
	RC_NODATA,				/**< \brief An unsuccesful return due to no further data. */
	RC_EXCEEDEDASCLINPORTS,	/**< \brief An unsuccesful return due to exceeding maximum number of allowed UART ports. */
	RC_EXCEEDEDCANPORTS		/**< \brief An unsuccesful return due to exceeding maximum number of allowed CAN ports. */
};

#endif /* GLOBAL_H_ */
