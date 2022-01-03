# esp32_wifi
Controlling devices through a website using esp32. Esp32 accesses and updates the website's database.

Inspired by http://electronoobs.com/eng_arduino_tut101.php with a few modifications of my own.

<h2>Summary</h2>

In this project we are able to connect sensors to an ESP-32 and send the values to a database on the internet. Then we are able to enter that website and see the values from anywhere in the world with internet connection. Through that same website we are also able to control stuff connected to the ESP-32 such as turn on LEDs, Relays and more. The same stuff controllable through the website is also controlled by in-site switches, that updates the database if used. Which means, we have a two way switch to the same device, one physical and one online, and we are able to know the status of our device at anytime. 

In conclusion, we have a back and forth dual control over using the ESP-32 module. The code will send data to our database, receive the echo data.

<h2>Website Preview</h2>
<p>Below we can have a preview of how the website looks once published.</p>
<img width="1440" alt="Website Setup" src="https://user-images.githubusercontent.com/53828752/147973954-13736fb7-eee9-43ab-9c5e-527f9c36583b.png">

<h2>ESP-32 Setup</h2>
<p>The code for the ESP-32 was uploaded to the device using the Arduino IDE. Please refer to this tutorial(https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/) for more information on how to setup the Arduino IDE for the ESP-32.</p>

<p>For testing purposes the ESP-32 code only deals with the control of one led, however the website as viewed above and database is built to support other components, such as relays, step motors, and other sensors in general.</p>

<p>For testing a push button was used to control the built-in led on the esp-32 board. This led was controllable by the Boolean Control 1 button on the website amd by the push button. When the physical button is used it updates the database, so that when the website is refreshed we can see the actual state of the led. </p>

<img align="middle" width="500" alt="Esp-32 Setup" src="https://user-images.githubusercontent.com/53828752/147980441-cd97195e-d03a-460e-b9a9-925cd33975ef.png" >


<h2>Future Modifications</h2>
With the actual code we are able to control one led, however the website and database is setup in such a way that it supports more sensors and actuators. Therefore, the only modification necessary to add more controlled by the website is in the arduino code. 
