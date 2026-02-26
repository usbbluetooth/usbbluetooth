#include "usbbluetooth_err.h"

const char * USBBLUETOOTH_CALL usbbluetooth_status_name(usbbluetooth_status_t status)
{
	switch (status)
	{
	case USBBLUETOOTH_STATUS_OK:
		return "USBBLUETOOTH_STATUS_OK";
	case USBBLUETOOTH_STATUS_ERR_UNK:
		return "USBBLUETOOTH_STATUS_ERR_UNK";
	case USBBLUETOOTH_STATUS_ERR_NOMEM:
		return "USBBLUETOOTH_STATUS_ERR_NOMEM";
	case USBBLUETOOTH_STATUS_WRONG_DRIVER:
		return "USBBLUETOOTH_STATUS_WRONG_DRIVER";
	default:
		return "**UNKNOWN**";
	}
}
