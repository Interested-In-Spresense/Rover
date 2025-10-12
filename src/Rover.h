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
    virtual void begin() = 0;
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
    DualDCMotorRover(bool mode, uint8_t e0, uint8_t p0, uint8_t e1, uint8_t p1);

    void begin() override;
    void setSpeed(int speed) override;
    void front() override;
    void front(int speed) override;
    void back() override;
    void back(int speed) override;
    void right() override;
    void left() override;
    void stop() override;

private:
    bool _mode;
    uint8_t _e0, _p0, _e1, _p1;
    int _speed;
};

// =========================================================
// DCモーターステアリング駆動型ローバー (SteerDCMotorDriveRover)
// =========================================================
class SteerDCMotorDriveRover : public RoverBase {
public:
    SteerDCMotorDriveRover(bool mode, uint8_t e0, uint8_t p0, uint8_t e1, uint8_t p1);

    void begin() override;
    void setSpeed(int speed) override;
    void front() override;
    void front(int speed) override;
    void back() override;
    void back(int speed) override;
    void right() override;
    void left() override;
    void stop() override;

private:
    bool _mode;
    uint8_t _e0, _p0, _e1, _p1;
    int _speed;
};

// =========================================================
// サーボステアリング駆動型ローバー (SteerServoDriveRover)
// =========================================================
class SteerServoDriveRover : public RoverBase {
public:
    SteerServoDriveRover(bool mode, uint8_t e0, uint8_t p0, uint8_t servoPin);

    void begin() override;
    void setSpeed(int speed) override;
    void front() override;
    void front(int speed) override;
    void back() override;
    void back(int speed) override;
    void right() override;
    void left() override;
    void stop() override;

    // ステアリング設定
    void setSteerCenter(int center);
    void setSteerRange(int range);

private:
    bool _mode;
    uint8_t _e0, _p0;
    uint8_t _servoPin;
    Servo _servo;
    int _speed;
    int _center;
    int _range;
};
