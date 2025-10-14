/*
 *  Rover.cpp - Simple rover control library using DRV8835 motor driver
 *  Author: Interested-In-Spresense
 *  License: MIT
 */

#include "Rover.h"

// =========================================================
// DualDCMotorRover
// =========================================================

DualDCMotorRover::DualDCMotorRover() : _speed(100) {}

void DualDCMotorRover::begin(bool mode, uint8_t e0, uint8_t p0, uint8_t e1, uint8_t p1) {
    Drv8835.begin(mode, e0, p0, e1, p1);
}

void DualDCMotorRover::begin(bool mode, uint8_t e0, uint8_t p0, uint8_t e1, uint8_t p1, uint8_t modePin) {
    Drv8835.begin(mode, e0, p0, e1, p1, modePin);
}

void DualDCMotorRover::setSpeed(int speed) {
    _speed = constrain(speed, 0, 100);
}

void DualDCMotorRover::front() {
    front(_speed);
}

void DualDCMotorRover::front(int speed) {
    Drv8835.front(0, speed);
    Drv8835.front(1, speed);
}

void DualDCMotorRover::back() {
    back(_speed);
}

void DualDCMotorRover::back(int speed) {
    Drv8835.back(0, speed);
    Drv8835.back(1, speed);
}

void DualDCMotorRover::right() {
    Drv8835.front(0, _speed);
    Drv8835.back(1, _speed);
}

void DualDCMotorRover::left() {
    Drv8835.back(0, _speed);
    Drv8835.front(1, _speed);
}

void DualDCMotorRover::stop() {
    Drv8835.stop(0);
    Drv8835.stop(1);
}

// =========================================================
// SteerDCMotorDriveRover
// =========================================================

SteerDCMotorDriveRover::SteerDCMotorDriveRover() : _speed(100) {}

void SteerDCMotorDriveRover::begin(bool mode, uint8_t e0, uint8_t p0, uint8_t e1, uint8_t p1) {
    Drv8835.begin(mode, e0, p0, e1, p1);
}

void SteerDCMotorDriveRover::begin(bool mode, uint8_t e0, uint8_t p0, uint8_t e1, uint8_t p1, uint8_t modePin) {
    Drv8835.begin(mode, e0, p0, e1, p1, modePin);
}

void SteerDCMotorDriveRover::setSpeed(int speed) {
    _speed = constrain(speed, 0, 100);
}

void SteerDCMotorDriveRover::front() {
    Drv8835.front(0, _speed);  // drive
    Drv8835.stop(1);           // steer neutral
}

void SteerDCMotorDriveRover::front(int speed) {
    setSpeed(speed);
    front();
}

void SteerDCMotorDriveRover::back() {
    Drv8835.back(0, _speed);
    Drv8835.stop(1);
}

void SteerDCMotorDriveRover::back(int speed) {
    setSpeed(speed);
    back();
}

void SteerDCMotorDriveRover::right() {
    Drv8835.front(1, _speed);  // steering right
}

void SteerDCMotorDriveRover::left() {
    Drv8835.back(1, _speed);   // steering left
}

void SteerDCMotorDriveRover::stop() {
    Drv8835.stop(0);
    Drv8835.stop(1);
}

// =========================================================
// SteerServoDriveRover
// =========================================================

SteerServoDriveRover::SteerServoDriveRover()
    : _speed(100), _center(90), _range(30), _servoPin(255) {}

void SteerServoDriveRover::begin(bool mode, uint8_t e0, uint8_t p0, uint8_t servoPin) {
    Drv8835.begin(mode, e0, p0, 0, 0); // Use ch0.
    _servoPin = servoPin;
    _servo.attach(_servoPin);
    _servo.write(_center);
}

void SteerServoDriveRover::begin(bool mode, uint8_t e0, uint8_t p0, uint8_t modePin, uint8_t servoPin) {
    Drv8835.begin(mode, e0, p0, 0, 0, modePin);
    _servoPin = servoPin;
    _servo.attach(_servoPin);
    _servo.write(_center);
}

void SteerServoDriveRover::setSpeed(int speed) {
    _speed = constrain(speed, 0, 100);
}

void SteerServoDriveRover::setSteerCenter(int center) {
    _center = constrain(center, 0, 180);
}

void SteerServoDriveRover::setSteerRange(int range) {
    _range = constrain(range, 0, 90);
}

void SteerServoDriveRover::front() {
    Drv8835.front(0, _speed);
    _servo.write(_center);
}

void SteerServoDriveRover::front(int speed) {
    setSpeed(speed);
    front();
}

void SteerServoDriveRover::back() {
    Drv8835.back(0, _speed);
    _servo.write(_center);
}

void SteerServoDriveRover::back(int speed) {
    setSpeed(speed);
    back();
}

void SteerServoDriveRover::right() {
    _servo.write(_center + _range);
}

void SteerServoDriveRover::left() {
    _servo.write(_center - _range);
}

void SteerServoDriveRover::stop() {
    Drv8835.stop(0);
    _servo.write(_center);
}
