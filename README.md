
# Ultrasonic Distance Monitoring using ESP8266, MQTT, and MySQL

This project implements a complete IoT-based distance monitoring system using an Ultrasonic sensor (HC-SR04) and ESP8266. The measured distance data is published to an MQTT broker and received by a Python application, which stores the data in a MySQL database for logging and analysis.


## 1. Project Overview

The system consists of two main components:

1. Sender Unit (ESP8266 + Ultrasonic Sensor)  
   - Measures distance using ultrasonic waves  
   - Connects to WiFi  
   - Publishes distance data to an MQTT broker in JSON format  

2. Receiver Unit (Python + MQTT + MySQL)  
   - Subscribes to MQTT topic  
   - Displays real-time distance values  
   - Stores readings in a MySQL database  

This project is suitable for IoT learning, smart monitoring systems, and academic mini or major projects.


## 2. Hardware Requirements

- ESP8266 NodeMCU
- Ultrasonic Sensor (HC-SR04)
- USB Cable
- Jumper Wires
- PC or Laptop with Internet Access


## 3. Software Requirements

- Arduino IDE
- Python 3.8 or higher
- MySQL Server (XAMPP / WAMP / Standalone)
- Internet connection


## 4. Circuit Connections

| Ultrasonic Pin | ESP8266 Pin |
|---------------|-------------|
| VCC | VIN (5V) |
| TRIG | D5 (GPIO14) |
| ECHO | D6 (GPIO12) |
| GND | GND |

Important Note:  
- HC-SR04 Echo pin outputs 5V. Use a voltage divider (1kΩ and 2kΩ) or logic level shifter to step down Echo to 3.3V for ESP8266 safety.



## 5. Sender Side (ESP8266) Setup

### 5.1 ESP8266 Board Installation

1. Open Arduino IDE  
2. Go to File → Preferences  
3. Add the following URL in Additional Board Manager URLs:

```

[https://arduino.esp8266.com/stable/package_esp8266com_index.json](https://arduino.esp8266.com/stable/package_esp8266com_index.json)



4. Go to Tools → Board → Boards Manager  
5. Install "ESP8266 by ESP8266 Community"


### 5.2 Required Arduino Libraries

Install the following libraries using Arduino Library Manager:

- ESP8266WiFi (installed automatically with ESP8266 board)
- PubSubClient (by Nick O'Leary)



### 5.3 WiFi Configuration

Update WiFi credentials in the sender code:

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
````



### 5.4 MQTT Configuration (Sender)

```cpp
const char* mqtt_broker = "broker.emqx.io";
const int mqtt_port = 1883;
const char* mqtt_topic = "esp8266/ultrasonic";
```


### 5.5 Uploading Sender Code

1. Open the ultrasonic sender `.ino` file in Arduino IDE
2. Select Board: NodeMCU 1.0 (ESP-12E Module)
3. Select correct COM Port
4. Set baud rate to 115200
5. Upload the code
6. Open Serial Monitor to verify WiFi and MQTT connection



### 5.6 MQTT Data Format

The ESP8266 publishes distance data in JSON format:

```json
{
  "distance_cm": 24.8
}
```



## 6. Receiver Side (Python + MQTT + MySQL) Setup

### 6.1 Python Dependencies

Install required Python libraries:

```bash
pip install paho-mqtt mysql-connector-python
```

Verify installation:

```bash
python -c "import paho.mqtt, mysql.connector"
```


### 6.2 MySQL Configuration

Ensure MySQL Server is running. Default configuration:

```python
MYSQL_HOST = "localhost"
MYSQL_USER = "root"
MYSQL_PASSWORD = ""
MYSQL_DATABASE = "ultrasonic_monitoring"
MYSQL_TABLE = "distance_data"
```

Modify these values if your MySQL credentials differ.



### 6.3 Database Initialization

The receiver program automatically:

* Creates the database `ultrasonic_monitoring` if it does not exist
* Creates the table `distance_data` on first run

No manual SQL commands are required.



### 6.4 MQTT Configuration (Receiver)

```python
MQTT_BROKER = "broker.emqx.io"
MQTT_PORT = 1883
MQTT_TOPIC = "esp8266/ultrasonic"
```

Ensure the topic matches the ESP8266 sender configuration.



### 6.5 Running the Receiver Program

Navigate to the project directory and run:


python receiver.py

Expected output:

```
Connected to MQTT Broker
Distance: 24.8 cm
```


## 7. Database Schema

Database Name: `ultrasonic_monitoring`
Table Name: `distance_data`

| Column      | Type                              |
| ----------- | --------------------------------- |
| id          | INT (Primary Key, Auto Increment) |
| distance_cm | FLOAT                             |
| timestamp   | DATETIME                          |



## 8. Project Files

| File Name                          | Description                             |
| ---------------------------------- | --------------------------------------- |
| ultrasonic_sender_code.ino         | ESP8266 MQTT ultrasonic sender          |
| ultrasonic_receiver_python_code.py | Python MQTT receiver with MySQL storage |



## 9. Common Issues and Troubleshooting

| Issue                   | Solution                       |
| ----------------------- | ------------------------------ |
| No distance readings    | Check TRIG and ECHO wiring     |
| ESP8266 resets          | Use proper power supply        |
| Incorrect distance      | Ensure Echo pin level shifting |
| MQTT not receiving data | Verify topic and internet      |
| MySQL access denied     | Verify credentials             |



## 10. Applications

* Smart Dustbin Monitoring
* Water Level Monitoring
* Obstacle Detection Systems
* Smart Parking Systems
* Industrial Level Measurement


## 11. Future Enhancements

* Threshold-based alerts
* Grafana dashboard visualization
* Web dashboard using Flask
* Cloud database integration
* Mobile notifications



## 12. Author

SHALINI DEVI R
GitHub: [https://github.com/shalsrsd05](https://github.com/shalsrsd05)



## 13. License

This project is intended for educational and academic use.

