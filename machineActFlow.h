#ifndef _MACHINE_ACT_FLOW_H_
#define _MACHINE_ACT_FLOW_H_

#include "./src/workingFSM/fsmMachineBase.h"
#include <Arduino.h>

/***
usage of the fsm Workflow class:

  the fsmMachineBase() is a unified interface for workflow.



*/


class fsmMachineCtrl:public fsmMachineBase{
public:
  fsmMachineCtrl(){};
  fsmMachineCtrl(int input){
    machineResource = input;
  };

  public:
  int machineResource = 0;
};







class actionIdle:public actionBase{
};












































class fsmTestAct1:public actionBase{
public:
  int setDelayTime(int time){
    waitingTime = time;
    return 1;
  };

  virtual int actionPreparetion(actionFlowBase* base){
    fsmMachineCtrl* tempPter = (fsmMachineCtrl*) base->fsmMachine;
    Serial.println("test act 1 preparation");
//    Serial.println(machine->_state);
    timeCnt = 0;

    return 1;
  };

  // config function
  virtual int operation(actionFlowBase* base){
    timeCnt = timeCnt + 1;
    delay(1);
    return 0;
  };

  virtual actionState actionStateHandle(actionFlowBase* base){
    if( timeCnt > waitingTime ){
      Serial.println("end act 1");
      Serial.println(timeCnt);

      return ACTION_SUCCESSFUL;
    }

    return ACTION_CONTINUE;
  };

private:
  int timeCnt = 0;
  int waitingTime = 0;
};




class fsmTestAct2:public actionBase{
public:
  int setDelayTime(int time){
    waitingTime = time;
    timeCnt = 0;
    return 1;
  };

  virtual int actionPreparetion(actionFlowBase* base){
    fsmMachineCtrl* tempPter = (fsmMachineCtrl*) base->fsmMachine;
    Serial.println("test act 2 preparation");

    return 1;
  };

  // config function
  virtual int operation(actionFlowBase* base){
    timeCnt = timeCnt + 1;
    delay(1);
  };

  virtual actionState actionStateHandle(actionFlowBase* base){
    if( timeCnt > waitingTime ){
      Serial.println("end act 2");
      Serial.println(waitingTime);

      return ACTION_SUCCESSFUL;
    }

    return ACTION_CONTINUE;
  };

private:
  int timeCnt = 0;
  int waitingTime = 0;
};





class actionFlowTest:public actionFlowBase{
public:
//  actionFlowTest(){};

  int configs(int wait1, int wait2){
    wait11 = wait1;
    wait21 = wait2;
    return 1;
  };

  virtual int start(){
    actA = new fsmTestAct1();
    actA->setDelayTime(wait11);
    this->addState(actA);

    actB = new fsmTestAct2();
    actB->setDelayTime(wait21);
    this->addState(actB);

    actC = new fsmTestAct2();
    actC->setDelayTime(wait21);
    this->addState(actC);

    Serial.println("act wkflow start");
    return 0;
  };

  virtual int finish(){
    delete actA;
    delete actB;
    delete actC;

    return 0;
  };

private:
  fsmTestAct1* actA = 0;
  fsmTestAct2* actB = 0;
  fsmTestAct2* actC = 0;
  int wait11 = 0;
  int wait21 = 0;

};






#endif // _MACHINE_ACT_FLOW_H_
