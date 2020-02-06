/*
 * Port.c
 *
 *  Created on: Jan 31, 2020
 *      Author: Abdullah Moustafa
 */


#include "Port.h"
#include "Det.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
		|| (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
		|| (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif

#endif

//STATIC Port_ConfigType * State = NULL_PTR;
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;
STATIC Port_ConfigChannel *port_PortChannels = NULL_PTR;

STATIC Port_PortType get_portID(Port_PinType pin){
	Port_PortType port_id ;
	if ((pin >= PORT_A_START) && (pin <= PORT_A_FINISH))
	{
		port_id = PORTA_ID;
	}
	else if ((pin >= PORT_B_START) && (pin <= PORT_B_FINISH))
	{
		port_id = PORTB_ID;
	}
	else if ((pin >= PORT_C_START) && (pin <= PORT_C_FINISH))
	{
		port_id = PORTC_ID;
	}
	else if ((pin >= PORT_D_START) && (pin <= PORT_D_FINISH))
	{
		port_id = PORTD_ID;

	}
	else
	{

	}

	return port_id;
}

STATIC Port_PinType get_pinID(Port_PinType pin){
	Port_PinType pin_id ;
	pin_id = (Port_PortType) pin% PINS_PER_PORT ;
	return pin_id;
}

/************************************************************************************
 * Service Name: Port_Init
 * Service ID[hex]: 0x00
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in): ConfigPtr - Pointer to configuration set
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Initializes the Port Driver module.
 ************************************************************************************/
void Port_Init( const Port_ConfigType* ConfigPtr )
{
	Port_PortType *DDR_ptr;
	Port_PortType *port_ptr;

#if (PORT_DEV_ERROR_DETECT == STD_ON)

	/* Check if the Driver is initialized before using this function */
	if (PORT_E_UNINIT == Port_Status)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_INIT_SID, PORT_E_UNINIT);
	}
	else
	{
		/* No Action Required */
	}

	/* check if Port_Init service called with wrong parameter */
	if (PORT_E_PARAM_CONFIG == STD_ON)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,
				PORT_E_PARAM_CONFIG);
	}
	else
#endif
	{	/* Loop over the ports to set the DDR_ptr with the port address */
		port_PortChannels = ConfigPtr->port_channels;
		for (int itr = 0; itr < PORT_CONFIGURED_CHANNLES; itr++) {
			/*get port */
			switch (port_PortChannels[itr].port) {
			case PORTA_ID: DDR_ptr  = &DDRA_REG;
			port_ptr = &PORTA_REG;
			break;
			case PORTB_ID: DDR_ptr  = &DDRB_REG;
			port_ptr = &PORTB_REG;
			break;
			case PORTC_ID: DDR_ptr  = &DDRC_REG;
			port_ptr = &PORTC_REG;
			break;
			case PORTD_ID: DDR_ptr  = &DDRD_REG;
			port_ptr = &PORTD_REG;
			break;
			}

			if(PORT_PIN_IN==port_PortChannels[itr].direction)
			{
				CLEAR_BIT(*DDR_ptr,port_PortChannels[itr].pin_num);
				if (Disable_Pull_up == port_PortChannels[itr].pin_in_mode)
				{
					CLEAR_BIT(*port_ptr, port_PortChannels[itr].pin_num);

				}
				else if(Enable_Pull_up== port_PortChannels[itr].pin_in_mode)
				{
					SET_BIT(*port_ptr, port_PortChannels[itr].pin_num);
				}
				else
				{

				}

			}
			else if(PORT_PIN_OUT==port_PortChannels[itr].direction)
			{
				SET_BIT(*DDR_ptr,port_PortChannels[itr].pin_num);
				if (initial_Low==port_PortChannels[itr].pin_out_mode)
				{
					CLEAR_BIT(*port_ptr,port_PortChannels[itr].pin_num);

				}
				else if (initial_High==port_PortChannels[itr].pin_out_mode)
				{
					SET_BIT(*port_ptr,port_PortChannels[itr].pin_num);
				}
				else
				{

				}

			}
			else
			{

			}

		}
		Port_Status = PORT_INITIALIZED;
	}
}
/************************************************************************************
 * Service Name: Port_SetPinDirection
 * Service ID[hex]: 0x01
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Pin - type(Port Pin ID number)  &  Direction type(Port Pin Direction)
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Sets the port pin direction(INPUT/OUTPUT).
 ************************************************************************************/
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction )
{	Port_PortType *DDR_ptr;
Port_PortType local_port;
Port_PinType local_pin;


#if (PORT_DEV_ERROR_DETECT == STD_ON)
/* Check if the Driver is initialized before using this function */
if (PORT_E_UNINIT == Port_Status)
{
	Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
			PORT_SET_PIN_DIRECTION_SID, PORT_E_UNINIT);
}
else
{
	/* No Action Required */
}


/* Check if Incorrect Port Pin ID passed */
if (PORT_E_PARAM_PIN == STD_ON)
{
	Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
			PORT_SET_PIN_DIRECTION_SID, PORT_E_PARAM_INVALID_MODE);
}
else
{
	/* No Action Required */
}


/* Check if Port Pin not configured as changeable */
if (PORT_E_DIRECTION_UNCHANGEABLE == STD_ON)
{
	Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
			PORT_SET_PIN_DIRECTION_SID, PORT_E_PARAM_INVALID_MODE);
}
else

	/* No Action Required */



#endif

	/* In-case there are no errors */
{

	local_port = get_portID(Pin);
	local_pin = get_pinID(Pin);
	switch (local_port) {
	case PORTA_ID:DDR_ptr = &DDRA_REG;
	break;
	case PORTB_ID:DDR_ptr = &DDRB_REG;
	break;
	case PORTC_ID:DDR_ptr = &DDRC_REG;
	break;
	case PORTD_ID:DDR_ptr = &DDRD_REG;
	break;
	}

	if (PORT_PIN_OUT == Direction)			//Output direction
	{
		SET_BIT(*DDR_ptr, local_pin);

	}
	else if (PORT_PIN_IN == Direction)		//Input direction
	{
		CLEAR_BIT(*DDR_ptr, local_pin);

	}
	else
	{

	}
}

}
/************************************************************************************
 * Service Name: Port_SetPinDirection
 * Service ID[hex]: 0x04
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Pin type(Port Pin ID number) & Mode type(New Port Pin mode to be set on port pin)
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Sets the port pin mode (HIGH/LOW).
 ************************************************************************************/
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode )
{

	Port_PortType *Port_ptr;
	Port_PortType local_port;
	Port_PinType local_pin;


#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (PORT_E_UNINIT == Port_Status)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_MODE_SID, PORT_E_UNINIT);
	}
	else
	{
		/* No Action Required */
	}

	/* Check if Incorrect Port Pin ID passed */
	if (PORT_E_PARAM_PIN == Port_Status)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_MODE_SID, PORT_E_UNINIT);
	}
	else
	{
		/* No Action Required */
	}


	/* Check if Port Pin Mode passed not valid */
	if (PORT_E_PARAM_INVALID_MODE == STD_ON)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_MODE_SID, PORT_E_UNINIT);
	}
	else
	{
		/* No Action Required */
	}

	/* Port_SetPinMode service called when the mode is unchangeable */
	if (PORT_E_MODE_UNCHANGEABLE == STD_ON)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_MODE_SID, PORT_E_UNINIT);
	}
	else

		/* No Action Required */


#endif
		/* In-case there are no errors */
	{

		local_port = get_portID(Pin);
		local_pin = get_pinID(Pin);
		switch (local_port) {
		case PORTA_ID:	Port_ptr = &PORTA_REG;
		break;
		case PORTB_ID:	Port_ptr = &PORTB_REG;
		break;
		case PORTC_ID:	Port_ptr = &PORTC_REG;
		break;
		case PORTD_ID:	Port_ptr = &PORTD_REG;
		break;
		}

		if (initial_High == Mode)			//Set the input pin to HIGH mode
		{
			SET_BIT(*Port_ptr, local_pin);

		}
		else if (initial_Low == Mode)		//Set the input pin to LOW mode
		{
			CLEAR_BIT(*Port_ptr, local_pin);

		}
		else
		{

		}

	}

}

/************************************************************************************
 * Service Name: Port_GetVersionInfo
 * Service ID[hex]: 0x03
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): VersionInfo - Pointer to where to store the version information of this module.
 * Return value: None
 * Description: Returns the version information of this module.
 ************************************************************************************/
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if input pointer is not Null pointer */
	if(NULL_PTR == versioninfo)
	{
		/* Report to DET  */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
	}
	else
#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */
	{
		/* Copy the vendor Id */
		versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
		/* Copy the module Id */
		versioninfo->moduleID = (uint16)PORT_MODULE_ID;
		/* Copy Software Major Version */
		versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
	}
}
#endif
