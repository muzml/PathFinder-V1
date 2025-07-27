# PathFinder-V1

## 🌟 Overview

Pathfinder V1 is a TinyML-powered navigation assistant designed to empower visually impaired individuals to navigate their surroundings more confidently. This wearable/handheld device detects obstacles and recognizes objects in real-time, providing feedback through audio cues, vibration patterns, and buzzer signals.

Developed during a 24-hour TinyML Hackathon at TinkerSpace, hosted by TinkerHub.

## 🚀 Features

- Real-time obstacle detection using ultrasonic sensors
- TinyML-based object recognition using Edge Impulse
- Multi-modal feedback system:
  - Vibration patterns for directional guidance
  - Buzzer alerts for immediate obstacles
  - (Optional) Audio cues for object identification
- Compact, portable design suitable for handheld or wearable use
- Low power consumption for extended battery life

## 💡 Technology Stack

- **Hardware**:
  - XIAO ESP32S3 - Main processing unit
  - HC-SR04 Ultrasonic Sensors - For distance measurement
  - Vibration Motors - For haptic feedback
  - Buzzer - For audio alerts
  - Battery module - For portable power
  
- **Software**:
  - Arduino IDE - For programming the XIAO ESP32S3
  - Edge Impulse - For TinyML model training and deployment
  - C++ - Primary programming language

## 🛠️ Setup & Installation

### Hardware Setup

1. Connect the ultrasonic sensors to the XIAO ESP32S3:
   - VCC to 5V
   - GND to GND
   - TRIG to pin D2
   - ECHO to pin D3

2. Connect the vibration motor:
   - Positive to pin D5
   - Negative to GND

3. Connect the buzzer:
   - Positive to pin D6
   - Negative to GND

For detailed wiring diagram, see [hardware/schematic.md](hardware/schematic.md).

### Software Setup

1. Install Arduino IDE (version 1.8.x or later)
2. Add ESP32 board support to Arduino IDE
3. Install required libraries:
   - [Edge Impulse Arduino library](https://docs.edgeimpulse.com/docs/deployment/arduino-library)
   - NewPing library for ultrasonic sensors
4. Flash the main code to your XIAO ESP32S3

For detailed software instructions, see the [src/README.md](src/README.md).

## 🧠 Edge Impulse Model

The object recognition model was trained using Edge Impulse with a dataset of common indoor and outdoor objects. The model was optimized for TinyML deployment on the ESP32S3.

Steps to recreate the model:
1. Create an Edge Impulse account
2. Collect or import images of common objects
3. Train an image classification model
4. Deploy the model to Arduino format
5. Integrate the model with the main code

## 👀 Project Gallery

![Pathfinder V1 Prototype](docs/images/1735728053423.jpg)

Our prototype showcases the compact design of Pathfinder V1, utilizing the XIAO ESP32S3 as the main processing unit along with ultrasonic sensors for obstacle detection, and vibration motors and buzzer for providing feedback to the user.

## 🤝 Team VYSE

This project was built by:
- [Muzammil Latheef Seedi](https://github.com/muzml)
- [Jeevan Joseph](https://github.com/jeevanjoseph03)
- [Mizhab A S](https://github.com/mizhab-as)
- [Muhammed Irfan Nazar](https://github.com/Irfan-34)

## ⏱️ Project Timeline

- Hackathon Date: 24-hour TinyML Hackathon at TinkerSpace (TinkerHub 22nd December,2024)
- Repository Created: 2025-04-22 10:48:07 UTC

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgements

Special thanks to TinkerHub for organizing the TinyML Hackathon and providing the platform for this project.

