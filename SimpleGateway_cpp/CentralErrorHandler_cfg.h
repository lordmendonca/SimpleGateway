/*
 * CentraErrorHandler_cfg.h
 *
 *  Created on: 14.12.2019
 *      Author: Fromm
 */

#ifndef CENTRAERRORHANDLER_CFG_H_
#define CENTRAERRORHANDLER_CFG_H_

/*=======================[ Symbols ]===============================================================*/

/** \brief macro to create the enumeration values */
#define CEH_CFG_ENUM(name, report, terminate) 		CEH_##name,

/** \brief Stringification of enumeration values */
#define CEH_CFG_ENUM_STR(name, report, terminate) 		#name,

/** \brief Makro to define an config entry */
#define CEH_CFG_ENTRY(name, report, terminate)			{CEH_##name, report, terminate},

/*=======================[ Types ]=================================================================*/

/*=======================[ Event configuration ]=================================================================*/

//===================	Event Name					REPORT			TERMINATE   ==========================//
#define CEH_CFG(DEF)\
		DEF(			EMPTY,						false,			false)		/**< \brief  NOP, do not remove */													\
		DEF(			BUFFEREMPTY,				true,			false)		/**< \brief  Buffer was empty, error e.g. in case of read operation */				\
		DEF(			BUFFEROVERRUN,				true,			false)		/**< \brief  Buffer was full, error e.g. in case of write operation */				\
		DEF(			INVALIDPOINTER,				true,			true)		/**< \brief  Invalid Pointer */														\
		DEF(			MAXASCLINPORTSREACHED,			true,			true)		/**< \brief  Reached maximum allowed ASCLIN ports. */														\
		DEF(			MAXCANPORTSREACHED,			true,			true)		/**< \brief  Reached maximum allowed CAN ports. */														\



/*=======================[ Event configuration END, no modifications after this line ]=================================================================*/

/**
 * \brief event source enumeration
 */
typedef enum{
	CEH_CFG(CEH_CFG_ENUM)
	CEH_SOURCE_MAX									/**< \brief Number of events configured in the CEH */
} CEH_source_t;

/**
 * \brief event configuration entry type
 */
typedef struct{
	CEH_source_t	source;							/**< \brief Source of the error event */
	bool			report;							/**< \brief if set, actuators will be stopped */
	bool		 	terminate;						/**< \brief if set, a debug instruction will be inserted */
}CEH_event_table_entry_t;

#endif /* CENTRAERRORHANDLER_CFG_H_ */
