Connor Wentzell
Fingerprint Scanner peripheral chip.



Project compiles, and code is functioning, LCD Performs as should. Code Prints "place Finger"
on line 1, but does not seem to be reading anything from the FP Scanner. More research on how to interface
using Atmega hardware is needed.

LCD library used in previous labs was utilized in scanner_test,c file. And performed as expected. 
My code was an attempt to transmit a communication packet called "handshake" to the scanner. All 
command packets are defined in the user manual that can be found on adafruit. 

Ultimately I was unable to get this device working properly. I went with a hardware approach and was never 
able to confirm successful communication between the driver and the scanner. Given more time I would probably 
take a software appraoch, which was what was used in the Arduino sketch. Fot those of you interested in using 
this device there is a working Arduino library and sketch downloadable from adafruit. 
