#define GENERAL_SWITCH_PIN 5 // 8
#define DIRECTION_PIN 4 // 9
#define UP_SWITCH_PIN 3 // 10
#define DOWN_SWITCH_PIN 2 // 11
#define BUTTON_UP_PIN 1 // 12
#define BUTTON_DOWN_PIN 0 // 13

#define TEST_PIN 6

int up_switch = 0;
int down_switch = 0;

int button_up_stat = 0;
int button_down_stat = 0;

int move_to_down = 0;
int move_to_up = 0;

void setup() {
  pinMode(GENERAL_SWITCH_PIN, OUTPUT);
  pinMode(DIRECTION_PIN, OUTPUT);
  
  pinMode(UP_SWITCH_PIN, INPUT);
  pinMode(DOWN_SWITCH_PIN, INPUT);
  pinMode(BUTTON_DOWN_PIN, INPUT);
  pinMode(BUTTON_UP_PIN, INPUT);
  
  pinMode(TEST_PIN, OUTPUT);
  digitalWrite(TEST_PIN, HIGH);
  
  button_up_stat = 0;
  button_down_stat = 0;
  
  up_switch = 0;
  down_switch = 0;
  
  move_to_down = 0;
  move_to_up = 0;
}

void disable_outputs()
{
  digitalWrite(DIRECTION_PIN, LOW);
  digitalWrite(GENERAL_SWITCH_PIN, LOW);
}

void drive_up(int value)
{
  digitalWrite(GENERAL_SWITCH_PIN, value);
}

void drive_down(int value)
{
  int delay_time = value == LOW ? 1 : 150;
  digitalWrite(DIRECTION_PIN, value);
  delay(delay_time);
  digitalWrite(GENERAL_SWITCH_PIN, value);
}

void loop() {
  // Get switches status
  up_switch = digitalRead(UP_SWITCH_PIN);
  down_switch = digitalRead(DOWN_SWITCH_PIN);
  
  // Get the read from the buttons
  // If the button was pressed once, it records that value and for the 
  // subsequent loops, the vars will keep their values until 
  // one of the switches are activated
  button_down_stat = digitalRead(BUTTON_DOWN_PIN) || button_down_stat;
  button_up_stat = digitalRead(BUTTON_UP_PIN) || button_up_stat;
  
  // Determine if we should move to the down or to the up
  move_to_down = button_down_stat == HIGH && down_switch == LOW;
  move_to_up = button_up_stat == HIGH && up_switch == LOW;
  
  // If both are pressed, do nothing
  if(move_to_down && move_to_up)
  {
    disable_outputs();
    return;
  }
  
  // Write to outputs
  drive_up(move_to_up);
  drive_down(move_to_down);
  
  // Disable outputs if the switches get activated
  button_down_stat = !down_switch;
  button_up_stat = !up_switch;
}
