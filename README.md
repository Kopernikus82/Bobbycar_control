### What can the Bobbycar control can do for you?

With the ESP 32 control unit, you can equip your Bobbycar with lights. In addition to the normal headlights, you can then use a headlight flasher, left and right indicators, hazard warning lights and a blue light. Great fun, not just for children!
You can find a videos from the mockup here:

https://nothnagel.org/wp-content/uploads/2020/03/BBC_v1.mp4

https://nothnagel.org/wp-content/uploads/2020/03/Blinker_Links.mp4

https://nothnagel.org/wp-content/uploads/2020/03/Warnblinklicht.mp4

https://nothnagel.org/wp-content/uploads/2020/03/Rainbow.mp4

https://nothnagel.org/wp-content/uploads/2020/03/Lichthupe.mp4

https://nothnagel.org/wp-content/uploads/2020/03/Blaulicht.mp4


### What do you need ?
- ESP32
- 2 Neopixel RGB (Back)
- 2 Neopixel RGBW (Front)
- 4 Momentary switch buttons
- 1 Switch (Button)
- Some Resistors
- Some Wires
- 5V, as an example from an powerbank
- Maybe some connectors

### Who to install in your Bobbycar?

1.Flash the ESP via Arduino with the code
2.Connect the LED´s to the ESP32 (see Fritzing)
3.Connect 4 momentary push butttons to ESP (see Fritzing)
4.Install a wire for 5V at the ESP
5.Install the Switch between ESP and 5V source
6.Have fun!

![Bobbycar - control - Fritzing](https://github.com/Kopernikus82/Bobbycar_control/blob/main/BCC_Fritzing.png)
![Bobbycar - control - Main Unit](https://github.com/Kopernikus82/Bobbycar_control/blob/main/BCC_main_unit.jpg) 
![Bobbycar - control - Single LED](https://github.com/Kopernikus82/Bobbycar_control/blob/main/BCC_single_led.jpg)

The biggest fiddling starts when you try to fit everything into the Bobbycar. To make this a bit easier, I installed a connector between the LED and ESP (JSP), something small that you can just about get for little money from your friendly electronics dealer. I did the same with the switches. Then just install everything and you're done.


### NOTE ON THE SKETCH

I've taught myself how to program so far and I'm pretty sure that there's a lot of room for improvement. It was just the first thing I did with Arduino and an ESP! Suggestions and improvements are very welcome!
