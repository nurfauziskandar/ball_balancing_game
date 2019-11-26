#include <MD_MAX72xx.h>
//#include <SPI.h>

// Turn on debug statements to the serial output
#define  DEBUG  1

#if  DEBUG
#define PRINT(s, x) { Serial.print(F(s)); Serial.print(x); }
#define PRINTS(x) Serial.print(F(x))
#define PRINTD(x) Serial.println(x, DEC)

#else
#define PRINT(s, x)
#define PRINTS(x)
#define PRINTD(x)

#endif

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES  11

#define CLK_PIN   13  // or SCK
#define DATA_PIN  11  // or MOSI
#define CS_PIN    10  // or SS

#define DELAYTIME    1000

// SPI hardware interface
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

char data;

void setup()
{
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, 2);
  Serial.begin(115200);
}

void(*resetdong)(void) = 0;

void loop()
{
  uint8_t arrow[COL_SIZE] =
  {
    0b00010000,
    0b00111000,
    0b01111100,
    0b11111110,
    0b00111000,
    0b00111000,
    0b01111100,
    0b00000000
  };

  MD_MAX72XX::transformType_t  t[] =
  {
    MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL,
    MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL,
    MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL,
    MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL,
    MD_MAX72XX::TFLR,
    MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR,
    MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR,
    MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR,
    MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR,
    MD_MAX72XX::TRC,
    MD_MAX72XX::TSD, MD_MAX72XX::TSD, MD_MAX72XX::TSD, MD_MAX72XX::TSD,
    MD_MAX72XX::TSD, MD_MAX72XX::TSD, MD_MAX72XX::TSD, MD_MAX72XX::TSD,
    MD_MAX72XX::TFUD,
    MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU,
    MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU, MD_MAX72XX::TSU,
    MD_MAX72XX::TINV,
    MD_MAX72XX::TRC, MD_MAX72XX::TRC, MD_MAX72XX::TRC, MD_MAX72XX::TRC,
    MD_MAX72XX::TINV
  };

  //mx.clear();
  if (Serial.available() > 0)
  {
    data = Serial.read();
    if (data == 'w')
    {
      mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
      mx.setBuffer(((0 + 1)*COL_SIZE) - 1, COL_SIZE, arrow); //1
      mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

      mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
      mx.setBuffer(((1 + 1)*COL_SIZE) - 1, COL_SIZE, arrow); //2
      mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

      mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
      mx.setBuffer(((2 + 1)*COL_SIZE) - 1, COL_SIZE, arrow); //3
      mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
    }
    if (data == 'l')
    {
      mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
      mx.setBuffer(((3 + 1)*COL_SIZE) - 1, COL_SIZE, arrow); //4
      mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

      mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
      mx.setBuffer(((4 + 1)*COL_SIZE) - 1, COL_SIZE, arrow); //5
      mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
    }
    if (data == 'q')
    {
      mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
      mx.setBuffer(((5 + 1)*COL_SIZE) - 1, COL_SIZE, arrow); //6
      mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

      mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
      mx.setBuffer(((6 + 1)*COL_SIZE) - 1, COL_SIZE, arrow); //7
      mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
    }
    if (data == 'a')
    {
      mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
      mx.setBuffer(((7 + 1)*COL_SIZE) - 1, COL_SIZE, arrow); //8
      mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

      mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
      mx.setBuffer(((8 + 1)*COL_SIZE) - 1, COL_SIZE, arrow); //9
      mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

      mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
      mx.setBuffer(((9 + 1)*COL_SIZE) - 1, COL_SIZE, arrow); //10
      mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
    }
    if (data == 'A')
    {
      mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
      mx.setBuffer(((10 + 1)*COL_SIZE) - 1, COL_SIZE, arrow); //11
      mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
    }
    if (data == 'x')
    {
      resetdong();
    }
  }
}
