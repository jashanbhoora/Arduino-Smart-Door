#include "door_monitor.h"

DoorMonitor::DoorMonitor(int reedSwitchPin, int overrideSwitchPin)
{
	_reedSwitchPin = reedSwitchPin;
	_overrideSwitchPin = overrideSwitchPin;
	
	//expects to start with the door already locked
	_doorLocked = true;
}

bool DoorMonitor::isDoorClosed()
{
	return digitalRead(_reedSwitchPin);
}

bool DoorMonitor::openOverride()
{
	return digitalRead(_overrideSwitchPin);
}

void DoorMonitor::setDoorLocked()
{
	_doorLocked = true;
}

void DoorMonitor::setDoorUnlocked()
{
	_doorLocked = false;
}

bool DoorMonitor::isDoorLocked()
{
	return _doorLocked;
}