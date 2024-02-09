/**
 * A simple example of reading step/dir communication
 *  - this example uses software interrupts - this code is intended primarily
 *    for Arduino UNO/Mega and similar boards with very limited number of interrupt pins
*/

#include <SimpleFOC.h>
// software interrupt library
#include <PciManager.h>
#include <PciListenerImp.h>


// angle
float received_angle = 0;

// StepDirListener( step_pin, dir_pin, counter_to_value)
StepDirListener step_dir = StepDirListener(4, 5, 2.0f*_PI/200.0); // receive the angle in radians
void onStep() { step_dir.handle(); }

// If no available hardware interrupt pins use the software interrupt
PciListenerImp listenStep(step_dir.pin_step, onStep);

void setup() {

  Serial.begin(115200);

  // init step and dir pins
  step_dir.init();
  // enable software interrupts
  PciManager.registerListener(&listenStep);
  // attach the variable to be updated on each step (optional)
  // the same can be done asynchronously by calling step_dir.getValue();
  step_dir.attach(&received_angle);

  Serial.println(F("Step/Dir listening."));
  _delay(1000);
}

void loop() {
    Serial.print(received_angle);
    Serial.print("\t");
    Serial.println(step_dir.getValue());
    _delay(500);
}
