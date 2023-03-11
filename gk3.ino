
#include <SPI.h> // подключаем библиотеку SPI.h
#include <MFRC522.h> // библиотека MFRC522.h
#define SS_PIN 10 // конфигурируем константный пин для модуля MFRC522
#define RST_PIN 9 // конфигурируем константный пин для модуля MFRC522
MFRC522 mfrc522(SS_PIN, RST_PIN); // обьявляем  пины в библиотеке MFRC522
unsigned long uidDec, uidDecTemp; // для храниения номера метки в десятичном формате

int sensorValue0 = A0; // аналоговый пин А0
int sensorValue1 = A1; // аналоговый пин А1
int sensorValue2 = A2; // аналоговый пин А2
int sensorValue3 = A3; // аналоговый пин А3

int relay1 = 2; // пин реле 1
int relay2 = 3; // пин реле 2
int relay3 = 4; // пин реле 3
int relay4 = 5; // пин реле 4

void setup() {
  //Serial.begin(9600); // устанавливаем скороть серийного порта
  //Serial.println("Waiting for card..."); // выводим сообщение в серийный порт
  SPI.begin(); //  инициализация SPI
  mfrc522.PCD_Init(); // инициализация MFRC522

  pinMode(sensorValue0, INPUT); // устанавливаем А0 как вход
  pinMode(sensorValue1, INPUT); // устанавливаем А1 как вход
  pinMode(sensorValue2, INPUT); // устанавливаем А2 как вход
  pinMode(sensorValue3, INPUT); // устанавливаем А3 как вход

  pinMode(relay1, OUTPUT); // выход реле 1
  pinMode(relay2, OUTPUT); // выход реле 2
  pinMode(relay3, OUTPUT); // выход реле 3
  pinMode(relay4, OUTPUT); // выход реле 4

  digitalWrite(relay1, HIGH); // устанавливаем на пине высокий логический уровень
  digitalWrite(relay2, HIGH); // устанавливаем на пине высокий логический уровень
  digitalWrite(relay3, HIGH); // устанавливаем на пине высокий логический уровень
  digitalWrite(relay4, HIGH); // устанавливаем на пине высокий логический уровень
}

void loop() {
  sensorValue0 = analogRead(A0); // считываем данные с А0
  sensorValue1 = analogRead(A1); // считываем данные с А1
  sensorValue2 = analogRead(A2); // считываем данные с А2
  sensorValue3 = analogRead(A3); // считываем данные с А3


  if ( ! mfrc522.PICC_IsNewCardPresent()) { // если обнаружена новая метка
    return; // возвращаем значение
  }

  if ( ! mfrc522.PICC_ReadCardSerial()) { // если прочитали серийный номер метки
    return; // возвращаем значение
  }
  uidDec = 0; // первоначальное значение номера метки
  // Выдача серийного номера метки.
  for (byte i = 0; i < mfrc522.uid.size; i++) // присваеваем переменной значение и проверяем размер для метки, если оно больше то присвоить 1
  {
    uidDecTemp = mfrc522.uid.uidByte[i]; // присвоить переменной uidDecTemp тип переменной байт
    uidDec = uidDec * 256 + uidDecTemp; // к uidDec добавить значение uidDecTemp
  }
  //Serial.println("Card UID: "); // выводим сообщение в серийный порт
  //Serial.println(uidDec); // Выводим UID метки в консоль.
  if (uidDec == 2577288845) // Сравниваем Uid метки, если он равен заданому то...
  {
    if (sensorValue0 > 0) {// считываем данные с А0, если значение больше то...
      digitalWrite(relay1, HIGH); // устанавливаем на пине высокий логический уровень
    }
    else // если нет то...
    {
      digitalWrite(relay1, LOW); // устанавливаем на пине низкий логический уровень
    }

    if (sensorValue1 > 0) { // считываем данные с А1, если значение больше то...
      digitalWrite(relay2, HIGH); // устанавливаем на пине высокий логический уровень
    }
    else // если нет то...
    {
      digitalWrite(relay2, LOW); // устанавливаем на пине низкий логический уровень
    }

    if (sensorValue3 == 507) { // считываем данные с А2, если значение больше то...
      digitalWrite(relay3, HIGH); // устанавливаем на пине высокий логический уровень
      delay(190); // устанавливаем задержку
      digitalWrite(relay3, LOW); // устанавливаем на пине низкий логический уровень
      delay(190); // устанавливаем задержку
    }

    if (sensorValue3 == 0) { // считываем данные с А3, если значение больше то...
      digitalWrite(relay4, HIGH); // устанавливаем на пине высокий логический уровень
      delay(200); // устанавливаем задержку
      digitalWrite(relay4, LOW); // устанавливаем на пине низкий логический уровень

      delay(200); // устанавливаем задержку
    }
    else // если нет то...
    {
      digitalWrite(relay3, HIGH); // устанавливаем на пине высокий логический уровень
      digitalWrite(relay4, HIGH); // устанавливаем на пине высокий логический уровень
    }
    if (sensorValue2 == 506) { // считываем данные с А2, если значение больше то...
      digitalWrite(relay3, HIGH); // устанавливаем на пине высокий логический уровень
      digitalWrite(relay4, HIGH); // устанавливаем на пине высокий логический уровень
      delay(200); // устанавливаем задержку
      digitalWrite(relay3, LOW); // устанавливаем на пине низкий логический уровень
      digitalWrite(relay4, LOW); // устанавливаем на пине низкий логический уровень
      delay(200); // устанавливаем задержку
    }
  }

}
