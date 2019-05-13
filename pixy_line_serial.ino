#include <Pixy2.h>
#define X_CENTER         (pixy.frameWidth/2)
#define DEBUG 0
Pixy2 pixy;

void setup()
{
  Serial.begin(115200);
  pixy.init();
  pixy.setLamp(1, 1);
  pixy.changeProg("line");
}


void loop()
{
  int8_t res;
  float x, y, theta;
  signed char deg, error;

  // Get latest data from Pixy, including main vector, new intersections and new barcodes.
  res = pixy.line.getMainFeatures();

  // If error or nothing detected, stop motors
  if (res <= 0)
  {
    Serial.write(100);//header
    Serial.write(0);//中心からのずれ
    Serial.write(0);//ベクトルの傾き
  }

  // We found the vector...
  if (res & LINE_VECTOR)
  {
    error = (int32_t)pixy.line.vectors->m_x0 - (int32_t)X_CENTER;
    x = pixy.line.vectors->m_y0 - pixy.line.vectors->m_y1;
    y = pixy.line.vectors->m_x0 - pixy.line.vectors->m_x1;
    theta = atan2(y, x);
    deg = theta * 180 / PI;
    Serial.write(100);//ヘッダー
    Serial.write(error);//中心からのずれ
    Serial.write(deg);//ベクトルの傾き
    if (DEBUG) {
      Serial.print(deg);
      Serial.print(" ");
      Serial.println(error);
    }
    
  }
}
