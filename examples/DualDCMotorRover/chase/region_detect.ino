/*
 * region_detect.ino - Centroid and Area calculation for semantic segmentation output.
 *
 *  Author: Interested-In-Spresense
 *  License: MIT
 */

const float threshold = 0.5;

/**
 * @brief 認識エリアの重心 (X, Y座標) を float で計算する
 * @param output  セマンティックセグメンテーションの認識結果 (DNNVariable)
 * @param w       認識結果の横幅
 * @param h       認識結果の縦幅
 * @param s_cx    重心X座標(float) を格納するポインタ
 * @param s_cy    重心Y座標(float) を格納するポインタ
 * @param s_area  面積(ピクセル数:int) を格納するポインタ
 * @return bool   成功=true
 */
bool calculate_centroid_and_area(DNNVariable &output, 
  int w, int h, float* s_cx, float* s_cy, float* s_area) {

  if (&output == NULL || w <= 0 || h <= 0) {
    *s_cx = 0.0f;
    *s_cy = 0.0f;
    *s_area = 0.0f;
    return false;
  }

  float total_weighted_x = 0.0f;
  float total_weighted_y = 0.0f;
  float weighted_area = 0.0f;

  for (int y = 0; y < h; ++y) {
    for (int x = 0; x < w; ++x) {

      float prob = output[y * w + x];
      if (prob > threshold) {

        total_weighted_x += (float)x * prob;
        total_weighted_y += (float)y * prob;

        // 重み付き面積として確率を加算
        weighted_area += prob;
      }
    }
  }

  if (weighted_area > 0.0f) {
    *s_cx = total_weighted_x / weighted_area;
    *s_cy = total_weighted_y / weighted_area;
    *s_area = weighted_area;   // 面積は float で格納
  } else {
    *s_cx = 0.0f;
    *s_cy = 0.0f;
    *s_area = 0.0f;
  }

  return true;
}
