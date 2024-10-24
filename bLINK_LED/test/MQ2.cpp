// int LED = 32 ;            /*pin LED được xác định*/
// int Sensor_input = 4 ;    /*Chân kỹ thuật số 5 cho đầu vào cảm biến*/
// void setup ( ) {
//   Serial. bắt đầu ( 115200 ) ;  /*tốc độ truyền cho giao tiếp nối tiếp*/
//   pinMode ( LED, OUTPUT ) ;  /*Đèn LED được đặt làm Đầu ra*/
// }
// void loop ( ) {
//   int sensor_Aout = analogRead ( Sensor_input ) ;  /*Chức năng đọc giá trị analog*/
//   Serial. in ( "Cảm biến khí: " ) ;  
//   Nối tiếp. in ( cảm biến_Aout ) ;   /*Đọc giá trị được in*/
//   Serial. in ( " \t " ) ;
//   Nối tiếp. in ( " \t " ) ;
//   if ( sensor_Aout > 1800 ) {    /*if điều kiện có ngưỡng 1800*/
//     Serial. println ( "Khí" ) ;  
//     ghi kỹ thuật số (LED, CAO ) ; /*Đèn LED đặt ở mức CAO nếu phát hiện thấy Gas */
//   }
//   other {
//     Serial. println ( "No Gas" ) ;
//     kỹ thuật sốWrite ( LED, THẤP ) ;  /*Đèn LED đặt ở mức THẤP nếu KHÔNG phát hiện khí */
//   }
//   độ trễ ( 1000 ) ;                 /*TRỄ 1 giây*/
// }
#include <Arduino.h>

int led[] = {13, 25, 26, 33, 32};

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 5; i++) {
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], HIGH);
  }
}

void loop() {
  Serial.println ("Cam bien khi Gas\t");

  int sensor = analogRead(4);
  Serial.println (sensor);

  if ( sensor > 1800 ){
    Serial.println ("Gas\t");
    for ( int i =0 ; i<5; i++){
      digitalWrite(led[i],0);
      delay(100);
      digitalWrite(led[i],1);
    }
  }
  else {
    Serial.println("No Gas\t");
    for ( int i =0 ; i < 5; i++){
      digitalWrite(led[i],1);
      delay(100);
    }
  }
}

