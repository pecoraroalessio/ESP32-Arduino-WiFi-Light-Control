# ESP32/Arduino Magic Home Surp Life WiFi Light Control

## Description

This standalone project offers a solution for controlling Magic Home, Surp Life LED lights' color and brightness wirelessly using an ESP32 microcontroller and a rotary encoder. The design is housed within a 3D printed case, making it a neat and practical device for home automation.

## Features

- Standalone operation with Magic Home, Surp Life WiFi LED lights
- Adjustable brightness and color (Red, Green, Blue, White)
- User-friendly interface with a rotary encoder
- Customizable, 3D printed case

## Hardware Required

- ESP32 Microcontroller
- Rotary Encoder
- Magic Home or Surp Life WiFi LED Light (Tested with Taipow LED ceiling light)
- 3D printed case (Files included in the repository: `Cover.stl` and `Body.stl`)

## Rotary Encoder to ESP32 Pin Mapping

| Rotary Encoder | ESP32 |
| -------------- | ----- |
| CLK            | GPIO22|
| DT             | GPIO23|
| SW             | GPIO21|
| + (VCC)        | 3V3   |
| GND            | GND   |

## Installation and Setup

1. Clone the repository to your local machine.
2. Upload the `.ino` file to your ESP32 microcontroller using Arduino IDE.
3. Adjust your network credentials (`ssid` and `password`) and server details (`serverIP` and `serverPort`) within the sketch.
4. Compile and upload the code to the ESP32.
5. Connect the rotary encoder and LED light as per the pin configuration above.

## Credits

This project was inspired and aided by the [flux_led](https://github.com/Danielhiversen/flux_led) project, which helped in figuring out the hex codes to use.

## License

This project is open source under the MIT license. See [LICENSE](LICENSE) file for more details.

## Demonstration

![Demonstration GIF](https://github.com/pecoraroalessio/ESP32-WiFi-Light-Control/blob/main/Output.gif)
