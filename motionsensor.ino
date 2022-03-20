
int input;              
int ms_val = 0;         
int IR_count = 0;       

void setup() {

  pinMode(D3, INPUT);                                                   
  pinMode(D7, OUTPUT);
 Particle.subscribe("hook-response/Infrared Motion Sensor", msfunc, MY_DEVICES);        
}

int msfunc (const char *event, const char *data) {
    if (strcmp(String(data), "HIGH") == 0) {            
        ms_val = HIGH;                              
    }
    else {
        ms_val = LOW;                                   
    }
    
    return ms_val;                                      
}

void loop() {
    
    input = digitalRead(D3);                            
    if (input == HIGH)                          
    {
        IR_count = IR_count + 1;                        
        
        if (ms_val == HIGH && input == HIGH) {          
            Particle.publish("Detect", "True");         
            digitalWrite(D7, HIGH);
        }
        
        delay(500);
    }
    
    else {
        digitalWrite(D7, LOW);
        
        delay(500);                                     
    }
    
    if (Time.second() == 30) {                                                                                  
        Particle.publish( "Counter", "{ \"IR Triggers\": \"" + String(IR_count) + "\"}", 60, PRIVATE);          
    }
    
delay(1000);
}