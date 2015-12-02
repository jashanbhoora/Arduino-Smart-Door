#ifndef DOORMONITOR_H
#define DOORMONITOR_H

#include "Arduino.h"

class DoorMonitor
{
	private:
		bool _doorLocked;
		int _reedSwitchPin, _overrideSwitchPin;
	
	public:
		DoorMonitor(int reedSwitchPin, int overrideSwitchPin);
		bool isDoorClosed();
		bool openOverride();
		
		void setDoorLocked();
		void setDoorUnlocked();
		bool isDoorLocked();
};

#endif