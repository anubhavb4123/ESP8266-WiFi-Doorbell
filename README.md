# ESP8266-WiFi-Doorbell

# 🔔 ESP8266 WiFi-Based Doorbell System

A smart doorbell system using multiple ESP8266 boards communicating over Wi-Fi. When a button is pressed on the main controller, it notifies multiple receiver nodes to ring buzzers. If the main Wi-Fi is unavailable, the controller automatically switches to Access Point (AP) mode, and the receivers connect to it.

## 📦 Components Used
- 6 × ESP8266 (e.g., NodeMCU)
- 1 × Push Button
- 5 × Buzzers or small speakers
- Jumper wires, resistors, power supplies

## 🏗️ Architecture

- **Doorbell_Controller (ESP1)**: Listens for a button press and sends ring signals to other nodes.
- **Receiver_Nodes (ESP2–ESP6)**: Host a web server and ring buzzers when the ring signal is received.

## 🔧 Features
- Wi-Fi-based communication using HTTP
- Auto fallback to Access Point if no Wi-Fi available
- Can be extended with MQTT, Telegram, camera, or OTA
