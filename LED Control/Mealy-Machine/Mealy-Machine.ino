typedef enum{
  OFF,
  ON
}event;
typedef enum{
  light_OFF,
  light_DIM,
  light_MED,
  light_FULL
}light_state_t;

#define PWM_OFF (uint8_t)0U
#define PWM_DIM (uint8_t)80U
#define PWM_MED (uint8_t)150U
#define PWM_FULL (uint8_t)255U

#define LED_PIN (int)9

uint8_t input_event = 0;
event input = OFF;
light_state_t curr_state = light_OFF;
uint8_t led_bright = 0;

void light_state_machine(uint8_t input_event);
void change_light_brightness(uint8_t brightness);

void setup() {
  pinMode(LED_PIN,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
  if (Serial.available() > 0) {
  input_event = Serial.read();
  if(input_event == '0')
  {
    input_event = 0;
    light_state_machine(input_event);
  }
  if(input_event == '1')
  {
    input_event = 1;
    light_state_machine(input_event);
  }
  Serial.println(curr_state);
}
}


void change_light_brightness(uint8_t brightness)
{
   analogWrite(LED_PIN,brightness);
}


void light_state_machine(uint8_t input_event)
{
  switch(curr_state)
  {
    case light_OFF:
    {
     switch(input_event)
     {
      case OFF:
      {
        curr_state = light_OFF;
        led_bright = PWM_OFF;
        break; 
      }
      case ON:
      {
        curr_state = light_DIM;
        led_bright = PWM_DIM;
        break;
      }
     }
      break;
    }
    case light_DIM:
    {
      switch(input_event)
     {
      case OFF:
      {
        curr_state = light_OFF;
        led_bright = PWM_OFF;
        break; 
      }
      case ON:
      {
        curr_state = light_MED;
        led_bright = PWM_MED;
        break;
      }
     }
      break;
    }
    case light_MED:
    {
      switch(input_event)
     {
      case OFF:
      {
        curr_state = light_OFF;
        led_bright = PWM_OFF;
        break; 
      }
      case ON:
      {
        curr_state = light_FULL;
        led_bright = PWM_FULL;
        break;
      }
     }
      break;
    }
    case light_FULL:
    {
      switch(input_event)
     {
      case OFF:
      {
        curr_state = light_OFF;
        led_bright = PWM_OFF;
        break; 
      }
      case ON:
      {
        curr_state = light_DIM;
        led_bright = PWM_DIM;
        break;
      }
     }
      break;
    }
  }
  change_light_brightness(led_bright);
}
