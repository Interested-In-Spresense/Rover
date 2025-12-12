/*
 *  DualDCMotorRover & AI Camera Sample
 *
 *  Hardware:
 *    - Dual DC motors (left / right)
 *    - DRV8835 motor driver
 *
 *  Author: Interested-In-Spresense
 *  License: MIT
 */

#include <Camera.h>
#include <DNNRT.h>
#include <SDHCI.h>
#include "Rover.h"

SDClass SD;
DNNRT dnnrt;

#define OFFSET_X  (48)
#define OFFSET_Y  (6)
#define CLIP_WIDTH  (224)
#define CLIP_HEIGHT  (224)
#define DNN_WIDTH  (28)
#define DNN_HEIGHT  (28)

// RGBの画像を入力
DNNVariable input(DNN_WIDTH*DNN_HEIGHT*3);  

DualDCMotorRover rover;

static float cx, cy, area;

void CamCB(CamImage img)
{

  if (!img.isAvailable()) return;

  // 画像の切り出しと縮小
  CamImage small; 
  CamErr camErr = img.clipAndResizeImageByHW(small
            ,OFFSET_X ,OFFSET_Y 
            ,OFFSET_X+CLIP_WIDTH-1 ,OFFSET_Y+CLIP_HEIGHT-1 
            ,DNN_WIDTH ,DNN_HEIGHT);
  if (!small.isAvailable()) return;

  // 画像をYUVからRGB565に変換
  small.convertPixFormat(CAM_IMAGE_PIX_FMT_RGB565); 
  uint16_t* sbuf = (uint16_t*)small.getImgBuff();

  // RGBのピクセルをフレームに分割
  float* fbuf_r = input.data();
  float* fbuf_g = fbuf_r + DNN_WIDTH*DNN_HEIGHT;
  float* fbuf_b = fbuf_g + DNN_WIDTH*DNN_HEIGHT;
  for (int i = 0; i < DNN_WIDTH*DNN_HEIGHT; ++i) {
   fbuf_r[i] = (float)((sbuf[i] >> 11) & 0x1F)/31.0; // 0x1F = 31
   fbuf_g[i] = (float)((sbuf[i] >>  5) & 0x3F)/63.0; // 0x3F = 64
   fbuf_b[i] = (float)((sbuf[i])       & 0x1F)/31.0; // 0x1F = 31
  }
  
  // 推論を実行
  dnnrt.inputVariable(input, 0);
  dnnrt.forward();
  DNNVariable output = dnnrt.outputVariable(0); 
 
  // DNNRTの結果をLCDに出力するために画像化
  static uint16_t result_buf[DNN_WIDTH*DNN_HEIGHT];
  for (int i = 0; i < DNN_WIDTH * DNN_HEIGHT; ++i) {
    uint16_t value = output[i] * 0x3F; // 6bit
    if (value > 0x3F) value = 0x3F;
    result_buf[i] = (value << 5);  // Only Green
  }

  cx = cy = area = 0.0f;

  bool err = calculate_centroid_and_area(output, DNN_WIDTH, DNN_HEIGHT, &cx, &cy, &area);
  if (!err) {
    Serial.println("Detection error");
    return;
  }

  Serial.printf("Centroid: (%.2f, %.2f), Weighted Area: %.2f\n", cx, cy, area);

}

void setup()
{
  Serial.begin(115200);

  while (!SD.begin()) {Serial.println("Insert SD card");}
  // SDカードにある学習済モデルの読み込み
  File nnbfile = SD.open("segment.nnb");

  if(nnbfile == 0){ puts("NNB Open Error!"); exit(1); }
  // 学習済モデルでDNNRTを開始
  dnnrt.begin(nnbfile);

  Serial.println("Prepare camera");
//  CamErr err = theCamera.begin();
  CamErr err = theCamera.begin();
  assert(err == CAM_ERR_SUCCESS);

  /* Auto white balance configuration */
  err = theCamera.setAutoWhiteBalanceMode(CAM_WHITE_BALANCE_AUTO);
  assert(err == CAM_ERR_SUCCESS);

  /* Start video stream */
  err = theCamera.startStreaming(true, CamCB);
  assert(err == CAM_ERR_SUCCESS);

  rover.begin(true, 6, 12, 9, 13, 2);
  rover.setSpeed(80);

}

void loop()
{
  if (area >= 500.0f) {
    rover.back(50);
  } 
  else if (area >= 300.0f && area < 500.0f) {
    rover.stop();
  }
  else if (area >= 100.0f && area < 300.0f) {
    rover.front(100);
  } else {
    rover.stop();
  }

  if (area >= 100.0f){
    if (cx >= 18.0f) {
      rover.right();
    } else if (cx <= 10.0f) {
      rover.left();
    } else {
      rover.center();
    }
  }else{
    rover.center();
  }

  usleep(50*1000);

}
