# BasicArduinoDigitalThermometer
This is a simple digital thermometer using the LM35 sensor. For displaying the final rezult I use an 74HC595 shift register along with an SH5461AS 7-Segment display, but any common catode display will work, as long as you properly connect D1-D4 and mach the  outputs of the shift register like this: Q1-A ,Q2 - B, ... ,Q7 - DP.

Here is the notation for the 7-Segment display (credit to circuitbasics.com):
![alt text](https://www.circuitbasics.com/wp-content/uploads/2017/05/Arduino-7-Segment-Display-Tutorial-Segment-Layout-Diagram.png | width=100) 


Here is the diagram of the circuit, simplified with a simpler display pin layout. The real one is really unintuitive:
![alt text](https://github.com/TheWiseWolfy/BasicArduinoDigitalThermometer/blob/main/Diagram.png)
