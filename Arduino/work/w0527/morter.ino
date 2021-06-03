#define ENA 10
#define ENB 5
#define EN1 9
#define EN2 8
#define EN3 7
#define EN4 6
int Motor_speed=100; // 모터 속도 PWM 100으로 설정 0~255
void setup()
{
// PWM 제어핀 출력 설정
pinMode(ENA,OUTPUT);
pinMode(ENB,OUTPUT);
// 방향 제어핀 출력 설정
pinMode(EN1,OUTPUT);
pinMode(EN2,OUTPUT);
pinMode(EN3,OUTPUT);
pinMode(EN4,OUTPUT);
}
void loop()
{
// 모터 A,B 정방향
digitalWrite(EN1, HIGH);   // 모터A 설정 
digitalWrite(EN2, LOW);  
analogWrite(ENA, Motor_speed);  
digitalWrite(EN3, HIGH);  // 모터B설정
digitalWrite(EN4, LOW);   
analogWrite(ENB, Motor_speed);  
delay(3000);          // 3초동안 정방향 회전
// 모터A,B 역방향
digitalWrite(EN1, LOW);  // 모터A설정
digitalWrite(EN2, HIGH);  
analogWrite(ENA, Motor_speed);  
 digitalWrite(EN3, LOW); // 모터B설정
digitalWrite(EN4, HIGH);   
analogWrite(ENB, Motor_speed);  
delay(3000);       // 3초동안 역방향 회전
}
