#define SERIAL Serial

void setup()
{
    SERIAL.begin(115200);
    SERIAL.println(">> Hello From Sender");
}

void loop()
{
    delay(500);
    SERIAL.println("Status: 200");
}