# ESP32 MAVLink Bluetooth Check

This Arduino sketch for ESP32 implements MAVLink communication with Bluetooth Serial acknowledgment.

## Features

- **MAVLink Heartbeat Transmission**: Sends MAVLink HEARTBEAT messages via Serial at 1-second intervals
- **Connection Detection**: Monitors incoming Serial data for MAVLink messages to detect when MAVLink is connected
- **Bluetooth Acknowledgment**: Prints "ok ack received" to Bluetooth Serial when MAVLink connection is established
- **Connection Timeout**: Automatically detects disconnection after 3 seconds of no received messages

## Hardware Requirements

- ESP32 development board
- MAVLink-compatible autopilot or ground control station connected via Serial

## Dependencies

- MAVLink library (https://github.com/mavlink/c_library_v2)
- BluetoothSerial library (included with ESP32 Arduino core)

## How It Works

1. The ESP32 sends HEARTBEAT messages on the Serial port at 57600 baud
2. It listens for incoming MAVLink messages on the same Serial port
3. When a valid MAVLink message is received, it considers MAVLink as "connected"
4. Upon first detection of connection, it sends "ok ack received" to the Bluetooth Serial
5. If no messages are received for 3 seconds, the connection is considered lost

## Usage

1. Upload the sketch to your ESP32
2. Connect to the ESP32 via Bluetooth with the device name "ESP32_MAVLink_Check"
3. Connect a MAVLink-compatible device to the Serial port
4. When the MAVLink device responds, you'll see "ok ack received" in the Bluetooth terminal

## Configuration

- **Baud Rate**: 57600 (line 10)
- **Bluetooth Device Name**: "ESP32_MAVLink_Check" (line 11)
- **Connection Timeout**: 3000ms (line 7)
