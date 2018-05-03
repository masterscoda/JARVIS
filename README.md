# JARVIS

Code and folders in this repo are part of a project to automate home aplliances

LightSwitch: 
	-Connect a power strip to an Wi-Fi enabled microcontroller. Lights would be plugged into the power strip and the ESP8266 Dev-Thing board by Sparkfun 
would act as a on/off power switch. To control the output of the ESP8266, it was decided to first create a web server and a web page on the ESP8266.
The web page consisted of a button that when clicked would act as an on/off switch. Using the ESP8266 local IP address, it could be accessed by any device connected to the same local area network.
Video here: https://www.youtube.com/watch?v=Xh9vkSxsGi0

	-allow the microcontroller to be controlled by voice. It was decided to use the free web-based service called IFTTT. Within IFTTT,
 an applet was created that when it received a voice command it would send a HTTP Post method to the ESP8266. To simplify the communication, it was decided to connect the ESP8266
 to a cloud web server called Thinger.io. IFTTT would send its HTTP Post method to Thinger.io and the ESP8266 would continuously wait for Thinger.io to send data to output power.
Video here: https://www.youtube.com/watch?v=yvxOQVtqoq8



GarageControl:
	-Take the voice command setup for the light switch and now use it to open and close a garage door. This stage was done to explore connecting to a ESP8266 to a different electronic device and to use other components like a relay switch.
Video here: https://www.youtube.com/watch?v=VOG3wxw6I2E and https://www.youtube.com/watch?v=QCdGcic5tZU


Jarvis.py:
	-Used for Google AIY project to set up Google Assistant on a Raspberry Pi 3