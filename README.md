# Cloud Home Security using Thingspeak cloud platform (with TimeControl and Matlab Analysis for Email Alert).


Controller: ESP32

Sensors used: Flame Sensor, IR sensor, Keypad Module, MQ-2 Gas sensor.


ESP32 Dev Module is used for collecting the data from the sensors and sending the collected data over wifi to the **ThingSpeak cloud platform**.

ThingSpeak allows for creating custom analysis snippets in it's own **matlab environment**, using this ability we made a custom email alert just to test the feature.


The alert is set to recurr every 5 minutes with the help of **TimeControl** feature in ThingSpeak and it sends an email whenever the smoke level is greater than the threshold limit that we give ourselves.


The code is entirely written in visual studio code's "PlatformIO" extension.

**2 ESP32's collect data from their respective sensors and send the data to the same channel to their respective setFields and then the above said analysis can be done :)**


![timecontrol](https://user-images.githubusercontent.com/62737084/232129602-9e35cd0e-b6c8-4c3b-9b15-a134a6fc1f24.png)
![analysis](https://user-images.githubusercontent.com/62737084/232129612-205f8040-62f2-4880-92c1-fedcdd36b33c.png)
