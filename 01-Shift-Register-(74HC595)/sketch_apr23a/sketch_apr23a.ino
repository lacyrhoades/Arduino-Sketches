// Pin names based on https://www.nxp.com/documents/data_sheet/74HC_HCT595.pdf

int serial_clock_pin = 2; // SHCP, Shift register clock
int serial_data_pin = 4; // DS, Serial data input
int register_clock_pin = 6; // STCP, Storage Clock, finalizes a series of serial inputs
int clear_pin = 8; // MR, Clear / Reset all storage (active LOW)
int output_enable_pin = 10; // OE, Enable output (active LOW) otherwise all output pins are LOW

void setup() {
  pinMode(serial_clock_pin, OUTPUT);
  pinMode(serial_data_pin, OUTPUT);
  pinMode(register_clock_pin, OUTPUT);
  pinMode(clear_pin, OUTPUT);
  pinMode(output_enable_pin, OUTPUT);

  // set default running values
  digitalWrite(serial_clock_pin, LOW);
  digitalWrite(serial_data_pin, LOW);
  digitalWrite(register_clock_pin, LOW);
  digitalWrite(clear_pin, HIGH); // "clear" pin is "active LOW" so default HIGH
  digitalWrite(output_enable_pin, HIGH); // same as "clear"

  // clear out entire register and return to normal
  digitalWrite(clear_pin, LOW);
  digitalWrite(clear_pin, HIGH);

  // just constantly show output
  // you could flash the output with this
  // alternatively, you can hard-wire this to ground
  // if you don't need to control it
  digitalWrite(output_enable_pin, LOW);
  
  // super slow just so we can watch it all happen
  Serial.begin(1);
}

void loop() {
  send(0b01010101);
  delay(1000);
  send(0b11111111);
  delay(1000);
  send(0b10101010);
  delay(1000);
  send(0b11111111);
  delay(1000);
}

void send(int number) {  
  // signal we will begin writing
  digitalWrite(register_clock_pin, LOW);
  
  // send each bit over the wire
  // tick the clock after each bit
  shiftOut(serial_data_pin, serial_clock_pin, MSBFIRST, number);
  
  // signal we are done writing out
  digitalWrite(register_clock_pin, HIGH);
}
