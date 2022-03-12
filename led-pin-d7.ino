
const pin_t MY_LED = D7;


SYSTEM_THREAD(ENABLED);

int ledToggle(String command)
{
    if (command.equals("on"))
    {
        digitalWrite(MY_LED, HIGH);
        return 1;
    }
    else if (command.equals("off"))
    {
        digitalWrite(MY_LED, LOW);
        return 0;
    }
    else
    {
        
        return -1;
    }
}
void setup()
{
	
	pinMode(MY_LED, OUTPUT);
	
	Particle.function("led", ledToggle);
	
}


void loop()
{
	//m
	digitalWrite(MY_LED, HIGH);
    delay(300);
    digitalWrite(MY_LED, LOW);
    delay(700);
    digitalWrite(MY_LED, HIGH);
    delay(1000);
    digitalWrite(MY_LED, LOW);
    delay(3000);

	//e
    digitalWrite(MY_LED, HIGH);
    delay(400);
    digitalWrite(MY_LED, LOW);
    delay(700);
    digitalWrite(MY_LED, HIGH);
    delay(250); 
    digitalWrite(MY_LED, LOW);
    delay(3000);
    //g
    digitalWrite(MY_LED, HIGH);
    delay(400);
    digitalWrite(MY_LED, LOW);
    delay(700);
    digitalWrite(MY_LED, HIGH);
    delay(500);
    digitalWrite(MY_LED, LOW);
    delay(3000);
	//a
	digitalWrite(MY_LED, HIGH);
    delay(1000);
    digitalWrite(MY_LED, LOW);
    delay(700);
    digitalWrite(MY_LED, HIGH);
    delay(350);
    digitalWrite(MY_LED, LOW);
    delay(3000);
}

