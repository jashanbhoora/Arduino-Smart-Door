#ifndef BIPOLARMOTOR_H
#define BIPOLARMOTOR_H

#include "Arduino.h"

class BipolarMotor
{
	private:
		short int _pin1, _pin2, _pin3, _pin4, _enablePin, _delayTime;
		float _anglePerStep;
		bool _dualPhase;
		bool _pinState1, _pinState2, _pinState3, _pinState4;
		
		void _clearPinControl();
		void _getCurrentPinStates();
		void _stepClockwise();
		void _stepAntiClockwise();
		void _stepClockwiseDualPhase();
		void _stepAntiClockwiseDualPhase();
		
		void _printPinStates();
		void _enableMotor();
		void _disableMotor();
	
	
	public:
		BipolarMotor(int pin1, int pin2, int pin3, int pin4, int enablePin, int delayTime, float stepsPerRev, bool dualPhase);
		void rotateMotor(int angle);
};

#endif