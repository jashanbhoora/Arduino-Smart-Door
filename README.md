# Arduino Smart Door
The code and wiring behind the Arduino Smart Door

Blog post: http://www.jashanbhoora.co.uk/blog/thales-project-arduino

Video: https://www.youtube.com/watch?v=8-D_LgbKshE

This repository contains all the files that were written for the Arduino Smart Door created for the Thales Arduino Challenge 2014.
In addition to the files here, the existing Arduino library for the FPS_GT511C3 fingerprint sensor is also required.

The Smart Door code consists of 4 components:

<h5>Arduino Sketch</h5>
<p>Highest level logic.</p>

<h5>The FPS_GT511C3 Library</h5>
<p>To interface with the fingerprint sensor: https://github.com/sparkfun/Fingerprint_Scanner-TTL</p>

<h5>motor_controller</h5>
<p>Maintains the state of the stepper motor in code. This was written in a couple of days, and it is highly likely that there are existing libraries that are better written, and do this in a better way.</p>

<h5>door_monitor</h5>
<p>A simple wrapper for a few operations to check the physical status of the door.</p>

# Parts
<p>Aside from the code, the follow components were also used</p>
<ul>
    <li>Power Supply for the motor</li>
    <li>Bipolar Stepper motor (4 wires)</li>
    <li>Arduino Uno</li>
    <li>Fingerprint Sensor</li>
    <li>Push Button</li>
    <li>SPST switch</li>
    <li>L293D Motor Driver</li>
    <li>Reed Switch and magnet</li>
    <li>Lots of wire</li>
</ul>

# Usage
<p>Not much in the way of instructions...<p>
<ol>
    <li>Install the libraries into your local Arduino libraries folder</li>
    <li>Connect components to the Arduino according to the circuit diagram</li>
    <li>Cross fingers and test</li>
</ol>

<p>Most of the pins were chosen arbitrarily, so changing them should not be a problem. The numbers in the diagram do not refer to the pins on the Arduino, so you'll need to look at the Arduino project to find those.</p>
<p>Send me a question if I've missed something!</p>
