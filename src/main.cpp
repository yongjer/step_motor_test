/*
#include <AccelStepper.h>  // 引入 AccelStepper 函式庫，用於控制步進馬達

// 定義引腳連接
const int cwPin = 2;  // 定義順時針旋轉的引腳
const int ccwPin = 3; // 定義逆時針旋轉的引腳

// 定義馬達介面類型
#define MOTOR_INTERFACE_TYPE 2  // 設定步進馬達的介面類型

// 創建一個新的 AccelStepper 類別實例
AccelStepper stepper = AccelStepper(MOTOR_INTERFACE_TYPE, cwPin, ccwPin);  // 使用指定引腳初始化步進馬達

// 定義循環持續時間（以毫秒為單位）
const unsigned long RUN_DURATION = 10000;  // 10 秒運行時間
const unsigned long PAUSE_DURATION = 2000; // 2 秒暫停時間

// 定義馬達速度
const int MOTOR_SPEED = 500000;  // 運行時的速度（每秒步進數）
const int STOP_SPEED = 0;        // 停止時的速度

// 用於追蹤循環狀態的變數
unsigned long previousMillis = 0; // 記錄上一次時間
int cycleState = 0;  // 記錄當前的循環狀態

void setup() {
  // 設定最大速度和加速度
  stepper.setMaxSpeed(1000000);  // 設定馬達的最大速度
  stepper.setAcceleration(500000);  // 設定馬達的加速度
  
  // 初始化串列通訊
  Serial.begin(9600);  // 開始串列通訊，波特率設為9600
}

void loop() {
  unsigned long currentMillis = millis();  // 獲取當前的時間（毫秒）

  // 根據循環狀態來運行馬達
  switch(cycleState) {
    case 0:  // 順時針運行10秒
      stepper.setSpeed(MOTOR_SPEED);  // 設定馬達順時針運行速度
      if (currentMillis - previousMillis >= RUN_DURATION) {  // 如果運行時間已達10秒
        cycleState = 1;  // 切換到狀態1
        previousMillis = currentMillis;  // 更新時間記錄
        Serial.println("Stopping after CW");  // 輸出訊息至串列監視器
      }
      break;

    case 1:  // 順時針後停止2秒
      stepper.setSpeed(STOP_SPEED);  // 設定馬達停止速度
      if (currentMillis - previousMillis >= PAUSE_DURATION) {  // 如果暫停時間已達2秒
        cycleState = 2;  // 切換到狀態2
        previousMillis = currentMillis;  // 更新時間記錄
        Serial.println("Starting CCW");  // 輸出訊息至串列監視器
      }
      break;

    case 2:  // 逆時針運行10秒
      stepper.setSpeed(-MOTOR_SPEED);  // 設定馬達逆時針運行速度
      if (currentMillis - previousMillis >= RUN_DURATION) {  // 如果運行時間已達10秒
        cycleState = 3;  // 切換到狀態3
        previousMillis = currentMillis;  // 更新時間記錄
        Serial.println("Stopping after CCW");  // 輸出訊息至串列監視器
      }
      break;

    case 3:  // 逆時針後停止2秒
      stepper.setSpeed(STOP_SPEED);  // 設定馬達停止速度
      if (currentMillis - previousMillis >= PAUSE_DURATION) {  // 如果暫停時間已達2秒
        cycleState = 0;  // 切換到狀態0，重新開始循環
        previousMillis = currentMillis;  // 更新時間記錄
        Serial.println("Starting CW");  // 輸出訊息至串列監視器
      }
      break;
  }

  stepper.runSpeed();  // 按照設定的速度運行馬達
}
*/
#include <Arduino.h>
#include <AccelStepper.h>

// Define pin connections
const int pin1 = 10;
const int pin2 = 11;
const int pin3 = 12;
const int pin4 = 13;

// Define the AccelStepper interface type; 4 wire motor in half step mode:
#define MotorInterfaceType 8

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper library with 28BYJ-48 stepper motor
AccelStepper stepper = AccelStepper(MotorInterfaceType, pin1, pin3, pin2, pin4);

void setup() {
  // Set the maximum speed and acceleration:
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(500);
  
  // Set the initial target position:
  stepper.moveTo(2048); // This is approximately one full rotation for 28BYJ-48
}

void loop() {
  // If at the end of travel go to the other end
  if (stepper.distanceToGo() == 0) {
    stepper.moveTo(-stepper.currentPosition());
  }
  
  // Move the motor one step
  stepper.run();
}
