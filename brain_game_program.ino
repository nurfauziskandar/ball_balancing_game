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

int sensor1 = 12;
int sensor2 = 8;
int sensor3 = 9;
int sensor4 = 7;

int dataS1;
int dataS2;
int dataS3;
int dataS4;

const int trigPin_bawah = 5;
const int echoPin_bawah = 6;
long duration_bawah;
int jarak_bawah;

const int trigPin_atas = 3;
const int echoPin_atas = 4;
long duration_atas;
int jarak_atas;

void setup()
{
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, 2);
  Serial.begin(115200);
  pinMode(trigPin_bawah, OUTPUT);
  pinMode(echoPin_bawah, INPUT);
  pinMode(trigPin_atas, OUTPUT);
  pinMode(echoPin_atas, INPUT);
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  delay(5000);
  Serial.write('1');
}

void ping_bawah() {
  digitalWrite(trigPin_bawah, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_bawah, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_bawah, LOW);
  duration_bawah = pulseIn(echoPin_bawah, HIGH);
  jarak_bawah = duration_bawah * 0.034 / 2;
}

void ping_atas() {
  digitalWrite(trigPin_atas, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_atas, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_atas, LOW);
  duration_atas = pulseIn(echoPin_atas, HIGH);
  jarak_atas = duration_atas * 0.034 / 2;
}

void baca_sensor()
{
  dataS1 = digitalRead(sensor1);
  dataS2 = digitalRead(sensor2);
  dataS3 = digitalRead(sensor3);
  dataS4 = digitalRead(sensor4);
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

  // baca sensor
  baca_sensor();
  ping_atas();
  ping_bawah();
  if (dataS1 == 0)
  {
    mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
    mx.setBuffer(((0 + 1)*COL_SIZE) - 1, COL_SIZE, arrow); //1
    mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

    mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
    mx.setBuffer(((1 + 1)*COL_SIZE) - 1, COL_SIZE, arrow); //2
    mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
    Serial.write('w');/////////////////////////////////////////////serial w
    mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
    mx.setBuffer(((2 + 1)*COL_SIZE) - 1, COL_SIZE, arrow); //3
    mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  }
  if (dataS2 == 0)
  {
    mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
    mx.setBuffer(((3 + 1)*COL_SIZE) - 1, COL_SIZE, arrow); //4
    mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
    Serial.write('l');/////////////////////////////////////////////serial l
    mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
    mx.setBuffer(((4 + 1)*COL_SIZE) - 1, COL_SIZE, arrow); //5
    mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  }
  if (dataS3 == 0)
  {
    mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
    mx.setBuffer(((5 + 1)*COL_SIZE) - 1, COL_SIZE, arrow); //6
    mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
    Serial.write('q');/////////////////////////////////////////////serial q
    mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
    mx.setBuffer(((6 + 1)*COL_SIZE) - 1, COL_SIZE, arrow); //7
    mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  }
  if (dataS4 == 0)
  {
    mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
    mx.setBuffer(((7 + 1)*COL_SIZE) - 1, COL_SIZE, arrow); //8
    mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
    Serial.write('a');/////////////////////////////////////////////serial a
    mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
    mx.setBuffer(((8 + 1)*COL_SIZE) - 1, COL_SIZE, arrow); //9
    mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
    mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
    mx.setBuffer(((9 + 1)*COL_SIZE) - 1, COL_SIZE, arrow); //10
    mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  }
  ping_atas();
  ping_bawah();
  while (jarak_bawah < 10)
  {
    Serial.write('s');
    delay(500);
    Serial.write('3');
    delay(3800);
    Serial.write('x');
    resetdong();
  }
  ping_atas();
  ping_bawah();
  while (jarak_atas > 5)
  {
    Serial.write('A');/////////////////////////////////////////////serial A
    mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
    mx.setBuffer(((10 + 1)*COL_SIZE) - 1, COL_SIZE, arrow); //11
    mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
    while (1)
    {
      ping_bawah();
      while (jarak_bawah < 10)
      {
        Serial.write('s');
        delay(500);
        Serial.write('2');
        delay(3800);
        Serial.write('x');
        resetdong();
      }
    }
  }
}

/*
  void loop()
  {
  ping_atas();
  ping_bawah();
  Serial.println(jarak_atas);
  while (jarak_atas > 5)
  {
    Serial.println("siap menang");
    ping_bawah();
    while (jarak_bawah < 10)
    {
      Serial.println("menang");
    }
  }
  }*/
