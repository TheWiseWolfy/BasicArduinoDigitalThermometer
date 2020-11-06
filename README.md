# BasicArduinoDigitalThermometer
This is a simple digital thermometer using the LM35 sensor. For displaying the final rezult I use an 74HC595 shift register along with an SH5461AS 7-Segment display, but any common catode display will work, as long as you properly connect D1-D4 and mach the numbers of the shift register output like this: Q1-A ,Q2 - B, ... ,Q7 - DP.


Here is the diagram of the circuit, simplified with a simples display.
![alt text](https://github.com/TheWiseWolfy/BasicArduinoDigitalThermometer/blob/main/Diagram.png)
