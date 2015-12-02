#include <door_monitor.h>
#include <motor_controller.h>
#include <FPS_GT511C3.h>
#include <SoftwareSerial.h>

BipolarMotor mainLock = BipolarMotor(5,3,2,4,6,10,200,true);

//takes pin arguments for reed switch and internal switch
DoorMonitor door = DoorMonitor(10,11);

                            //8 - arduino rx, 9 - fps tx (black cable)
FPS_GT511C3 fps = FPS_GT511C3(8,9);

void setup()
{  
  //open serial port and start fps communication
  Serial.begin(9600);
  delay(100);
  fps.Open();
  fps.SetLED(false);
  delay(200);
  fps.SetLED(true);
  delay(200);
  fps.SetLED(false);
  
  //want door to be closed and unlocked to start with, so check for this
  while(!door.isDoorClosed())
  {
    Serial.print ("Initializer delay loop, door closed pin: ");
    Serial.println(door.isDoorClosed());
    delay(200);
  }
  
  LockDoor();
  //fps.SetLED(true);
}

void loop()
{
  //Serial.println("main loop start");
  
  //first, check for unconditional open
  
  //Serial.print("Override status: ");
  //Serial.println(door.openOverride());
  //Serial.print("door closed status: ");
  //Serial.println(door.isDoorClosed());
  //if(door.openOverride() && door.isDoorLocked() && door.isDoorClosed())
  if(door.openOverride() && door.isDoorLocked())
  {
    accessRoutine();
  }

  //next, check if a finger is present. If it is process and unlock if valid
  //Serial.print("finger status: ");
  //Serial.println(fps.IsPressFinger());
  //Serial.print("locked status: ");
  //Serial.println(door.isDoorLocked());
  //Serial.print("closed status: ");
  //Serial.println(door.isDoorClosed());
  
  //apparently, the actual sensor needs the led on to scan
  fps.SetLED(true);
  delay(100);
  //if(fps.IsPressFinger() && door.isDoorLocked() && door.isDoorClosed())
  if(fps.IsPressFinger() && door.isDoorLocked())
  {
    fps.CaptureFinger(false);
    int id = fps.Identify1_N();
    if(id < 200)
    {
      //short blink sequence as visual feedback for accepted
      fps.SetLED(false);
      delay(50);
      fps.SetLED(true);
      delay(50);
      fps.SetLED(false);
      delay(50);
      fps.SetLED(true);
      delay(50);
      
      accessRoutine();
      
      //fps.SetLED(false);
    }
    else
    {
      //long LED blink to indicate failure
      for (int i = 0; i < 5; i++)
      {
        fps.SetLED(false);
        delay(700);
        fps.SetLED(true);
        delay(700);
      }
      
      
    }
  }
  fps.SetLED(false);
  
  delay(300);
  
  
  //todo: add an error check for when the door is physically open, but the software state is locked, indicating a manual unlock
    
}

void accessRoutine()
{
    UnlockDoor();
  
restartWait:
    while(!door.isDoorClosed())
    {
      delay(3000);
    }
    delay(3000);
    if(!door.isDoorClosed())
    {
      //todo: remove the quick-fix goto!
      //an attempt to catch the case of the door closing, but then instantly being opened again for any reason while still unlocked
      goto restartWait;
    }
    
    LockDoor();
}

void LockDoor()
{
  mainLock.rotateMotor(150);
  door.setDoorLocked();
}

void UnlockDoor()
{
  mainLock.rotateMotor(-150);
  door.setDoorUnlocked();
}
