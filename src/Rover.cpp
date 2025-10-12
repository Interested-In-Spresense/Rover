#include "Rover.h"

extern Drv8835Class Drv8835;

// =========================================================
// DualDCMotorRover
// =========================================================
DualDCMotorRover::DualDCMotorRover(bool mode, uint8_t e0, uint8_t p0, uint8_t e1, uint8_t p1)
: _mode(mode), _e0(e0), _p0(p0), _e1(e1), _p1(p1), _speed(100) {}

void DualDCMotorRover::begin() {
    Drv8835.begin(_mode, _e0, _p0, _e1, _p1);
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
SteerDCMotorDriveRover::SteerDCMotorDriveRover(bool mode, uint8_t e0, uint8_t p0, uint8_t e1, uint8_t p1)
: _mode(mode), _e0(e0), _p0(p0), _e1(e1), _p1(p1), _speed(100) {}

void SteerDCMotorDriveRover::begin() {
    Drv8835.begin(_mode, _e0, _p0, _e1, _p1);
}

void SteerDCMotorDriveRover::setSpeed(int speed) {
    _speed = constrain(speed, 0, 100);
}

void SteerDCMotorDriveRover::front() {
    Drv8835.front(0, _speed);
}

void SteerDCMotorDriveRover::front(int speed) {
    Drv8835.front(0, speed);
}

void SteerDCMotorDriveRover::back() {
    Drv8835.back(0, _speed);
}

void SteerDCMotorDriveRover::back(int speed) {
    Drv8835.back(0, speed);
}

void SteerDCMotorDriveRover::right() {
    Drv8835.front(1, _speed);
}

void SteerDCMotorDriveRover::left() {
    Drv8835.back(1, _speed);
}

void SteerDCMotorDriveRover::stop() {
    Drv8835.stop(0);
    Drv8835.stop(1);
}

// =========================================================
// SteerServoDriveRover
// =========================================================
SteerServoDriveRover::SteerServoDriveRover(bool mode, uint8_t e0, uint8_t p0, uint8_t servoPin)
: _mode(mode), _e0(e0), _p0(p0), _servoPin(servoPin),
  _speed(100), _center(90), _range(30) {}

void SteerServoDriveRover::begin() {
    Drv8835.begin(_mode, _e0, _p0, 0, 0);  // ch1–¢Žg—p
    _servo.attach(_servoPin);
    _servo.write(_center);
}

void SteerServoDriveRover::setSpeed(int speed) {
    _speed = constrain(speed, 0, 100);
}

void SteerServoDriveRover::front() {
    Drv8835.front(0, _speed);
    _servo.write(_center);
}

void SteerServoDriveRover::front(int speed) {
    Drv8835.front(0, speed);
    _servo.write(_center);
}

void SteerServoDriveRover::back() {
    Drv8835.back(0, _speed);
}

void SteerServoDriveRover::back(int speed) {
    Drv8835.back(0, speed);
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

void SteerServoDriveRover::setSteerCenter(int center) {
    _center = constrain(center, 0, 180);
    _servo.write(_center);
}

void SteerServoDriveRover::setSteerRange(int range) {
    _range = constrain(range, 0, 90);
}
