// khai báo thư viện
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


//Motor PINs
#define IN1 D0
#define IN2 D1
#define IN3 D2
#define IN4 D3

// biến điều hướng cho xe
bool forward = 0;
bool backward = 0;
bool left = 0;
bool right = 0;

// cấu hình wifi và blynk app
char auth[] = "b1kuU6v6cN_0d_7nwjTK-7ugZuxyPElv"; // blynk auth token
char ssid[] = "Thang Hue T3"; // tên wifi
char pass[] = "88888888"; // mật khẩu wifi


void setup() {
  // mở serial ở baud rate 9600
  Serial.begin(9600);

  // thiết đăt các chân ở chế độ output
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  // bắt đầu app blynk
  // blynk auth token, tên wifi, pass wifi, tên server blynk, port
  Blynk.begin(auth, ssid, pass,"blynk-server.com", 8080);

}


// hàm đọc dữ liệu từ blynk, param.asInt hàm lấy giá trị về số nguyên
BLYNK_WRITE(V0) {
  forward = param.asInt();
}

BLYNK_WRITE(V1) {
  backward = param.asInt();
}

BLYNK_WRITE(V2) {
  left = param.asInt();
}

BLYNK_WRITE(V3) {
  right = param.asInt();
}
// hàm điều hướng xe
void smartcar() {
  // nếu biến forward trả về giá trị = 1 thì gọi hàm carforward, bên dưới tương tự
  if (forward == 1) {
    carforward();
    Serial.println("carforward");
  } else if (backward == 1) {
    carbackward();
    Serial.println("carbackward");
  } else if (left == 1) {
    carturnleft();
    Serial.println("carfleft");
  } else if (right == 1) {
    carturnright();
    Serial.println("carright");
  } else if (forward == 0 && backward == 0 && left == 0 && right == 0) {
    carStop();    
    Serial.println("carstop");
}
  
}
void loop() {
  Blynk.run();

  smartcar();
}
// hàm điều hướng xe
// hàm tiến lên
void carforward() {
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, HIGH);

  digitalWrite (IN1, LOW);
  digitalWrite (IN2, HIGH);
}
// hàm đi lùi
void carbackward() {
  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW);

  digitalWrite (IN1, HIGH);
  digitalWrite (IN2, LOW);

}
// quay động cơ phải
void carturnright() {
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, LOW);

  digitalWrite (IN3, LOW);
  digitalWrite (IN4, HIGH);
}
// quay động cơ trái
void carturnleft() {
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, HIGH);

  digitalWrite (IN3, LOW);
  digitalWrite (IN4, LOW);
}
// hàm dừng xe
void carStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
