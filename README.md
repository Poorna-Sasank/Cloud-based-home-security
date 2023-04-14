#Cloud Home Security using Thingspeak cloud platform (with TimeControl and Matlab Analysis for Email Alert).
#Controller: ESP32
#Sensors used: Flame Sensor, IR sensor, Keypad Module, MQ-2 Gas sensor
#ESP32 Dev Module is used for collecting the data from the sensors and sending the collected data over wifi to the ThingSpeak cloud platform 
#ThingSpeak allows for creating custom analysis snippets in it's own matlab environment, using this ability we made a custom email alert just to test the feature.
#The alert is set to recurr every 5 minutes with the help of TimeControl feature in ThingSpeak and it sends an email whenever the smoke level is greater than the threshold limit that we give ourselves.
