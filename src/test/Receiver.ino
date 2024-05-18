#define SERIAL Serial

void setup()
{
    SERIAL.begin(115200);
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    delay(500);

    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
}

void loop()
{

    while (true)
    {
        if (SERIAL.available() > 0){
            if (SERIAL.readStringUntil('\n') == ">> Hello From Sender"){
                Serial.println("ok");
                digitalWrite(13, HIGH);
                break;
            }
        }
    }


}