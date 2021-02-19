/**************************
 * Author: Xiaoke DENG
 * Data: Feb. 19, 2021
 *
 * Description:
 * test first ...
// * ************************/

#include "machineActFlow.h"



actionFlowTest flowTest;
fsmMachineCtrl testFSM(1);
unsigned long startTime = 0;

void setup(){

  ///////////////////////  system inital ...  /////////////////////////////
  Serial.begin(115200); // for communication with Master

  flowTest.configs(10000, 3000);
  Serial.println("begin");
//  testFSM.changeStateWorkflow((actionFlowBase*)&flowTest);
  testFSM.changeStateWorkflow(&flowTest);

  Serial.println("begin2");
  delay(1000);
  startTime = millis();
}

void loop(){
  if((millis() - startTime) > 1000){
    Serial.println("Alive");
    startTime = millis();
  }
  
  testFSM.update();

}
