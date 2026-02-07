#include <MAVLink.h>
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;
bool mavConnected = false;
unsigned long lastHeartbeatReceived = 0;
const unsigned long connectionTimeout = 3000; // 3 seconds timeout

void setup() {
  Serial.begin(57600);
  SerialBT.begin("ESP32_MAVLink_Check"); // Bluetooth device name
  lastHeartbeatReceived = millis(); // Initialize to current time
}

void loop() {
  // Send HEARTBEAT message to Serial once a second
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];

  mavlink_msg_heartbeat_pack(1, MAV_COMP_ID_AUTOPILOT1, &msg, MAV_TYPE_QUADROTOR, MAV_AUTOPILOT_GENERIC, MAV_MODE_FLAG_MANUAL_INPUT_ENABLED, 0, MAV_STATE_STANDBY);
  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);

  Serial.write(buf, len);
  
  // Check for incoming MAVLink messages to detect connection
  int bytesProcessed = 0;
  while (Serial.available() && bytesProcessed < 100) {
    uint8_t c = Serial.read();
    mavlink_message_t rxMsg;
    mavlink_status_t status;
    
    if (mavlink_parse_char(MAVLINK_COMM_0, c, &rxMsg, &status)) {
      // Received a valid MAVLink message
      lastHeartbeatReceived = millis();
      
      // If we just established connection, print to Bluetooth
      if (!mavConnected) {
        mavConnected = true;
        SerialBT.println("ok ack received");
      }
    }
    bytesProcessed++;
  }
  
  // Check if connection timed out
  if (mavConnected && ((millis() - lastHeartbeatReceived) > connectionTimeout)) {
    mavConnected = false;
  }
  
  delay(1000);
}
