/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for Port Module.
 *
 * Author:  Abdullah Moustafa
 ******************************************************************************/
#ifndef PORT_CFG_H
#define PORT_CFG_H

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)


/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API                (STD_OFF)

/* Pre-compile option for presence of Port_SetPinDirection API*/
#define PORT_SET_PIN_DIRECTION_API                (STD_ON)

/* Number of the configured Dio Channels */
#define PORT_CONFIGURED_CHANNLES              (3U)


//Changeable configuration related to the upper layer RTE / Application

#define portConf_LED_CHANNEL_ID_INDEX 				    (uint8)0x00
#define portConf_LED_PORT_NUM			  				PORTC_ID
#define portConf_LED_CHANNEL_NUM			 			PORT_PIN5
#define portConf_LED_CHANNEL_CHANNEL_DIRECTION 			PORT_PIN_OUT
#define portConf_LED_CHANNEL_INPUT_PIN_MODE				initial_Low


#define portConf_BUTTON_CHANNEL_ID_INDEX 				(uint8)0x01
#define portConf_BUTTON_PORT_NUM		  				PORTD_ID
#define portoConf_BUTTON_CHANNEL_NUM		 			PORT_PIN2
#define portConf_BUTTON_CHANNEL_CHANNEL_DIRECTION 		PORT_PIN_IN
#define portConf_BUTTON_CHANNEL_INPUT_PIN_MODE			Enable_Pull_up





#endif
