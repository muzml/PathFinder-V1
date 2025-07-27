# Pathfinder V1 Hardware Schematic

## Components Connection Diagram

```
                                   +----------------+
                                   |                |
                                   |   XIAO ESP32S3 |
                                   |                |
                                   +--------+-------+
                                            |
                     +------------+---------+-----------+
                     |            |         |           |
            +--------+--+  +------+-----+  |  +--------+--+
            |           |  |            |  |  |           |
            | Ultrasonic|  | Vibration  |  |  |  Buzzer   |
            |  Sensor   |  |   Motor    |  |  |           |
            |           |  |            |  |  |           |
            +-----------+  +------------+  |  +-----------+
                                           |
                                      +----+-----+
                                      |          |
                                      | Battery  |
                                      |          |
                                      +----------+
```

## Detailed Connections

### XIAO ESP32S3 Connections:
- D2: Connected to Ultrasonic Sensor TRIG pin
- D3: Connected to Ultrasonic Sensor ECHO pin
- D5: Connected to Vibration Motor (+)
- D6: Connected to Buzzer (+)
- 5V: Connected to Ultrasonic Sensor VCC
- GND: Connected to all GND connections

### Ultrasonic Sensor (HC-SR04):
- VCC: Connected to XIAO ESP32S3 5V
- GND: Connected to XIAO ESP32S3 GND
- TRIG: Connected to XIAO ESP32S3 D2
- ECHO: Connected to XIAO ESP32S3 D3

### Vibration Motor:
- Positive (+): Connected to XIAO ESP32S3 D5
- Negative (-): Connected to XIAO ESP32S3 GND

### Buzzer:
- Positive (+): Connected to XIAO ESP32S3 D6
- Negative (-): Connected to XIAO ESP32S3 GND

### Power Supply:
- 3.7V LiPo Battery connected to XIAO ESP32S3 battery connector
- Optional: Battery protection circuit
