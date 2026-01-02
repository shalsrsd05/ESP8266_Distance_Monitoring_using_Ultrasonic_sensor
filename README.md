# Ultrasonic Distance Monitoring System

ESP8266 | Ultrasonic Sensor | MQTT | Python | MySQL (XAMPP)

## Project Overview

This project implements a real-time ultrasonic distance monitoring system using an ESP8266 (NodeMCU) as the sender and a Python-based MQTT receiver for data storage. Distance values measured by an ultrasonic sensor are transmitted via MQTT and stored in a MySQL database using XAMPP, enabling reliable monitoring and analysis.

## System Architecture


Ultrasonic Sensor → ESP8266 (Sender) → MQTT Broker → Python Receiver → MySQL Database

## Hardware Requirements

* ESP8266 (NodeMCU)
* Ultrasonic Sensor (HC-SR04)
* Voltage Divider (1 kΩ and 2 kΩ resistors for ECHO pin)
* USB Cable
* Computer with XAMPP installed


## Software Requirements

* Arduino IDE
* Python 3.8 or higher
* XAMPP (Apache and MySQL)
* MQTT Broker: broker.emqx.io

## Arduino Sender Code

### Required Arduino Libraries

To compile and upload the ESP8266 sender code in Arduino IDE, install the following:

#### 1. ESP8266 Board Package

Required to program the ESP8266 microcontroller.

* Package Name: ESP8266 by ESP8266 Community
* Installation Path:
  Arduino IDE → Tools → Board → Boards Manager → Search "ESP8266" → Install

#### 2. Built-in Arduino Libraries

The ultrasonic sender code uses only core Arduino functions. No external library is required for ultrasonic distance measurement.

* Arduino.h (default)
* ESP8266WiFi.h (used only if Wi-Fi is enabled)

#### 3. Optional Library (Only for MQTT Communication)

Required only if the sender publishes distance data using MQTT.

* Library Name: PubSubClient
* Installation Path:
  Sketch → Include Library → Manage Libraries → Search "PubSubClient" → Install


## Python Receiver Code

### Python Dependencies

Install the following libraries before running the receiver code:


pip install paho-mqtt
pip install mysql-connector-python


Note: The json module is built into Python and does not require installation.

## Database Configuration

* Database Name: ultrasonic_monitoring
* Table Name: distance_data
* Fields:

  * distance_cm (FLOAT)
  * timestamp (DATETIME)

The database and table are automatically created when the receiver code is executed.


## How to Run the Project

### Step 1: Upload Sender Code

1. Open Arduino IDE
2. Select Board: ESP8266 NodeMCU
3. Select the correct COM Port
4. Upload the sender code

### Step 2: Start XAMPP

1. Open the XAMPP Control Panel
2. Start the MySQL service

### Step 3: Run Python Receiver

1. Open your Python IDE (VS Code, PyCharm, or IDLE)
2. Run the receiver script:

python receiver.py

## Output

* Ultrasonic distance values displayed in the Python terminal
* Data stored in the MySQL database
* System ready for visualization using PHP or Grafana

## Applications

* Smart dustbin monitoring
* Water level measurement
* Obstacle detection
* IoT-based monitoring systems

## Conclusion

This project demonstrates a complete IoT data pipeline using ESP8266, MQTT, and Python–MySQL integration. Powering the ultrasonic sensor through the VIN pin with proper voltage level protection ensures reliable operation, while MQTT enables efficient real-time data transmission.


## Author

SHALINI DEVI R

---

If you want, I can also prepare a lab-record version or an academic report version of this content.
