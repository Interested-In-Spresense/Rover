/*
 *  Rover.h - Simple rover control library using DRV8835 motor driver
 *  Author: Interested-In-Spresense
 *  License: MIT
 */

#pragma once
#include <Arduino.h>
#include "Drv8835.h"
#include <Servo.h>

// =========================================================
// Base class
// =========================================================
class RoverBase {
public:
    virtual void begin(bool mode, uint8_t e0, uint8_t p0, uint8_t e1, uint8_t p1) = 0;
    virtual void begin(bool mode, uint8_t e0, uint8_t p0, uint8_t e1, uint8_t p1, uint8_t modePin) = 0;
    virtual void front() = 0;
    virtual void front(int speed) = 0;
    virtual void back() = 0;
    virtual void back(int speed) = 0;
    virtual void right() = 0;
    virtual void left() = 0;
    virtual void stop() = 0;
    virtual void setSpeed(int speed) = 0;
};

// =========================================================
// 差動駆動型ローバー (DualDCMotorRover)
// =========================================================
class DualDCMotorRover : public RoverBase {
public:
    DualDCMotorRover();

    void begin(bool mode, uint8_t e0, uint8_t p0, uint8_t e1, uint8_t p1) override;
    void begin(bool mode, uint8_t e0, uint8_t p0, uint8_t e1, uint8_t p1, uint8_t modePin) override;

    void setSpeed(int speed) override;
    void front() override;
    void front(int speed) override;
    void back() override;
    void back(int speed) override;
    void right() override;
    void left() override;
    void stop() override;

private:
    Drv8835Class _drv;
    int _speed;
};

// =========================================================
// DCモーターステアリング駆動型ローバー (SteerDCMotorDriveRover)
// =========================================================
class SteerDCMotorDriveRover : public RoverBase {
public:
    SteerDCMotorDriveRover();

    void begin(bool mode, uint8_t e0, uint8_t p0, uint8_t e1, uint8_t p1) override;
    void begin(bool mode, uint8_t e0, uint8_t p0, uint8_t e1, uint8_t p1, uint8_t modePin) override;

    void setSpeed(int speed) override;
    void front() override;
    void front(int speed) override;
    void back() override;
    void back(int speed) override;
    void right() override;
    void left() override;
    void stop() override;

private:
    Drv8835Class _drv;
    int _speed;
};

// =========================================================
// サーボステアリング駆動型ローバー (SteerServoDriveRover)
// =========================================================
class SteerServoDriveRover : public RoverBase {
public:
    SteerServoDriveRover();

    void begin(bool mode, uint8_t e0, uint8_t p0, uint8_t servoPin);
    void begin(bool mode, uint8_t e0, uint8_t p0, uint8_t modePin, uint8_t servoPin);

    void setSpeed(int speed) override;
    void setSteerCenter(int center);
    void setSteerRange(int range);
    void front() override;
    void front(int speed) override;
    void back() override;
    void back(int speed) override;
    void right() override;
    void left() override;
    void stop() override;

private:
    Drv8835Class _drv;
    Servo _servo;
    int _speed;
    int _center;
    int _range;
    uint8_t _servoPin;
};
