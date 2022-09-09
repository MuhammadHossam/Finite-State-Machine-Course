/*
 * Moore Machine where the actions are done as entry action after entering the state.
 */

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
void run_entry_action(light_state_t state);

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
  light_state_t prev_state;
  prev_state = curr_state;
  switch(curr_state)
  {
    case light_OFF:
    {
     switch(input_event)
     {
      case ON:
      {
        curr_state = light_DIM;
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
        break; 
      }
      case ON:
      {
        curr_state = light_MED; 
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
        break; 
      }
      case ON:
      {
        curr_state = light_FULL;
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
        break; 
      }
      case ON:
      {
        curr_state = light_DIM;
        break;
      }
     }
      break;
    }
  }
  /*
   * This if condition defines the entry action.. 
   */
  if(prev_state != curr_state)
  {
    run_entry_action(curr_state);
  }
}

void run_entry_action(light_state_t state)
{
  switch(state)
  {
    case light_OFF:
    {
      change_light_brightness(PWM_OFF);
      break;
    }
    case light_DIM:
    {
      change_light_brightness(PWM_DIM);    
      break;
    }
    case light_MED:
    {
      change_light_brightness(PWM_MED);
      break;
    }
    case light_FULL:
    {
      change_light_brightness(PWM_FULL);
      break;
    }
  }
}
