/**************************
 * Author: Xiaoke DENG
 * Data: Feb. 19, 2021
 *
 * Description:
 * test first ...
// * ************************/

#include "machineActFlow.h"


/************ Step4: instantiate the interface and the action flow ***********/
actionFlowTest flowTest;
actionFlowTest flowTest2;
fsmMachineCtrl testFSM(1);
unsigned long startTime = 0;

void setup(){

  ///////////////////////  system inital ...  /////////////////////////////
  Serial.begin(115200); // for communication with Master


/************ Step5: config the action flow before you are going to start it ***********/
  flowTest.configs(10000, 3000);
  flowTest2.configs(2000, 5000);  
  Serial.println("begin");

/*** Step6: change to the instantiated and configed action flow, the the interface will run it ***/
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
/******* Step7: call the interface to run the action flow ***********/
// return 1 means successful
  int ret = testFSM.update();
  if(ret == 1){
    testFSM.changeStateWorkflow(&flowTest2);
    Serial.println("end of a flow!!!!!");
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    
  }
  
  
}
