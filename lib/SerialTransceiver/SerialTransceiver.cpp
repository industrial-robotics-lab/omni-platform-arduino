#include "SerialTransceiver.h"

SerialTransceiver::SerialTransceiver(float *desired, float *feedback) {
    desiredPtr = desired;
    feedbackPtr = feedback;
}

void SerialTransceiver::rx() {
    Serial.readBytesUntil('\n', buffer, 17);
    for (int i = 0; i < 4; i++) {
        n1.b[i] = buffer[i];
        n2.b[i] = buffer[i + 4];
        n3.b[i] = buffer[i + 8];
        n4.b[i] = buffer[i + 12];
    }
    desiredPtr[0] = n1.f;
    desiredPtr[1] = n2.f;
    desiredPtr[2] = n3.f;
    desiredPtr[3] = n4.f;
}

void SerialTransceiver::tx() {
    Serial.write((byte*)feedbackPtr, sizeof(float)*4);
    Serial.write('\n');
}

void SerialTransceiver::talk() {
    rx();
    tx();
}