/*
  motor_controller.cpp - Library for controlling a stepper motor using an L293D on an Arduino.
  Created by Jashan Bhoora, March 2, 2014.
*/

#include "motor_controller.h"

BipolarMotor::BipolarMotor(int pin1, int pin2, int pin3, int pin4, int enablePin, int delayTime, float stepsPerRev, bool dualPhase = false)
{
	_pin1 = pin1;
	_pin2 = pin2;
	_pin3 = pin3;
	_pin4 = pin4;
	
	_delayTime = delayTime;
	_enablePin = enablePin;
	
	_anglePerStep = 360/stepsPerRev;
	
	pinMode(_pin1, OUTPUT);
	pinMode(_pin2, OUTPUT);
	pinMode(_pin3, OUTPUT);
	pinMode(_pin4, OUTPUT);
	
	//Serial.println("Initialized Motor");
}

void BipolarMotor::_enableMotor()
{
	digitalWrite(_enablePin, HIGH);
}

void BipolarMotor::_disableMotor()
{
	digitalWrite(_enablePin, LOW);
}

void BipolarMotor::_clearPinControl()
{
	digitalWrite(_pin1, LOW);
	digitalWrite(_pin2, LOW);
	digitalWrite(_pin3, LOW);
	digitalWrite(_pin4, LOW);
	//Serial.println("Control Cleared");
}

void BipolarMotor::_getCurrentPinStates()
{
	_pinState1 = digitalRead(_pin1);
	_pinState2 = digitalRead(_pin2);
	_pinState3 = digitalRead(_pin3);
	_pinState4 = digitalRead(_pin4);
	//Serial.println("Read pin states");
}

void BipolarMotor::_printPinStates()
{
	//_getCurrentPinStates();
	Serial.print("Pin 1: ");
	Serial.println(_pinState1);
	Serial.print("Pin 2: ");
	Serial.println(_pinState2);
	Serial.print("Pin 3: ");
	Serial.println(_pinState3);
	Serial.print("Pin 4: ");
	Serial.println(_pinState4);
}

void BipolarMotor::_stepClockwise()
{
	//Serial.println("");
	_getCurrentPinStates();
	//_printPinStates();
	if(_pinState4 || (!_pinState1 && !_pinState2 && !_pinState3 && !_pinState4))
	{
		digitalWrite(_pin2, LOW);
		digitalWrite(_pin3, LOW);
		digitalWrite(_pin4, LOW);
		digitalWrite(_pin1, HIGH);
	}
	
	else if(_pinState1)
	{
		digitalWrite(_pin1, LOW);
		digitalWrite(_pin3, LOW);
		digitalWrite(_pin4, LOW);
		digitalWrite(_pin2, HIGH);
	}
	
	else if(_pinState2)
	{
		digitalWrite(_pin1, LOW);
		digitalWrite(_pin2, LOW);
		digitalWrite(_pin4, LOW);
		digitalWrite(_pin3, HIGH);
	}
	
	else if(_pinState3)
	{
		digitalWrite(_pin1, LOW);
		digitalWrite(_pin2, LOW);
		digitalWrite(_pin3, LOW);
		digitalWrite(_pin4, HIGH);
	}
	//Serial.println("Stepped CW");
	//_getCurrentPinStates();
	//_printPinStates();
	//Serial.println("");
}

void BipolarMotor::_stepAntiClockwise()
{
	//Serial.println("");
	_getCurrentPinStates();
	//_printPinStates();
	
	if(_pinState4 || (!_pinState1 && !_pinState2 && !_pinState3 && !_pinState4))
	{
		digitalWrite(_pin1, LOW);
		digitalWrite(_pin2, LOW);
		digitalWrite(_pin4, LOW);
		digitalWrite(_pin3, HIGH);
	}
	
	else if(_pinState1)
	{
		digitalWrite(_pin1, LOW);
		digitalWrite(_pin2, LOW);
		digitalWrite(_pin3, LOW);
		digitalWrite(_pin4, HIGH);
	}
	
	else if(_pinState2)
	{
		digitalWrite(_pin2, LOW);
		digitalWrite(_pin3, LOW);
		digitalWrite(_pin4, LOW);
		digitalWrite(_pin1, HIGH);
	}
	
	else if(_pinState3)
	{
		digitalWrite(_pin1, LOW);
		digitalWrite(_pin3, LOW);
		digitalWrite(_pin4, LOW);
		digitalWrite(_pin2, HIGH);
	}
	//Serial.println("Stepped CCW");
	//_getCurrentPinStates();
	//_printPinStates();
	//Serial.println("");
}

void BipolarMotor::_stepClockwiseDualPhase()
{
	_getCurrentPinStates();
	
	if((_pinState4 && _pinState1) || (!_pinState1 && !_pinState2 && !_pinState3 && !_pinState4))
	{
		digitalWrite(_pin3, LOW);
		digitalWrite(_pin4, LOW);
		digitalWrite(_pin1, HIGH);
		digitalWrite(_pin2, HIGH);
	}
	
	else if(_pinState1 && _pinState2)
	{
		digitalWrite(_pin1, LOW);
		digitalWrite(_pin4, LOW);
		digitalWrite(_pin2, HIGH);
		digitalWrite(_pin3, HIGH);
	}
	
	else if(_pinState2 && _pinState3)
	{
		digitalWrite(_pin1, LOW);
		digitalWrite(_pin2, LOW);
		digitalWrite(_pin3, HIGH);
		digitalWrite(_pin4, HIGH);
	}
	
	else if(_pinState3 && _pinState4)
	{
		digitalWrite(_pin3, LOW);
		digitalWrite(_pin2, LOW);
		digitalWrite(_pin1, HIGH);
		digitalWrite(_pin4, HIGH);
	}
	
	//Serial.println("Stepped CW DP");
	//_getCurrentPinStates();
	//_printPinStates();
	//Serial.println("");
}

void BipolarMotor::_stepAntiClockwiseDualPhase()
{
	_getCurrentPinStates();
	
	if((_pinState4 && _pinState1) || (!_pinState1 && !_pinState2 && !_pinState3 && !_pinState4))
	{
		digitalWrite(_pin3, LOW);
		digitalWrite(_pin4, LOW);
		digitalWrite(_pin1, HIGH);
		digitalWrite(_pin2, HIGH);
	}
	
	else if(_pinState1 && _pinState2)
	{
		digitalWrite(_pin1, LOW);
		digitalWrite(_pin4, LOW);
		digitalWrite(_pin2, HIGH);
		digitalWrite(_pin3, HIGH);
	}
	
	else if(_pinState2 && _pinState3)
	{
		digitalWrite(_pin1, LOW);
		digitalWrite(_pin2, LOW);
		digitalWrite(_pin3, HIGH);
		digitalWrite(_pin4, HIGH);
	}
	
	else if(_pinState3 && _pinState4)
	{
		digitalWrite(_pin3, LOW);
		digitalWrite(_pin2, LOW);
		digitalWrite(_pin1, HIGH);
		digitalWrite(_pin4, HIGH);
	}
	//Serial.println("Stepped CCW DP");
	//_getCurrentPinStates();
	//_printPinStates();
	//Serial.println("");
}

void BipolarMotor::rotateMotor(int angle)
{
	//Serial.println("Rotate start");
	_enableMotor();
	float _angleTurned = 0.0;
	if(angle < 0)
	{
		while(_angleTurned <= -angle)
		{
			if(_dualPhase)
			{
				_stepAntiClockwiseDualPhase();
			}
			else
			{
				_stepAntiClockwise();
			}
			_angleTurned += _anglePerStep;
			delay(_delayTime);
		}
	}
	else
	{
		while(_angleTurned <= angle)
		{
			if(_dualPhase)
			{
				_stepClockwiseDualPhase();
			}
			else
			{
				_stepClockwise();
			}
			_angleTurned += _anglePerStep;
			delay(_delayTime);
		}
	}
	_clearPinControl();
	_disableMotor();
	//Serial.println("Rotate end");
}


