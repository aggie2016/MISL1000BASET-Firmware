#ifndef MISLHAL_H
#define MISLHAL_H

#include <stdbool.h>
#include <stdint.h>
#include <inc/hw_memmap.h>
#include <driverlib/gpio.h>
#include <driverlib/rom.h>
#include <driverlib/ssi.h>
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"


namespace MISL
{
	class MISLHAL
	{
	public:
		MISLHAL();
		~MISLHAL();
	};
}

#endif