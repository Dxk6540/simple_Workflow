/**************************
 * Author: Xiaoke DENG
 * Data: Feb. 19, 2021
 *
 * Description:
 * The example of using the simple workflow library.
// * ************************/
#ifndef _MACHINE_ACT_FLOW_H_
#define _MACHINE_ACT_FLOW_H_
#include <Arduino.h>

// include the actionFlowBase.h file before you use
#include "./src/workingFSM/fsmMachineBase.h"


/***
usage of the fsm Workflow class:

  the fsmMachineBase() is a unified interface for workflow.



/************ Step1: create interface ***********/
// first create your own updating interface by inheriting the fsmMachineBase class.
// the fsmMachineBase is an universial interface to call all the workflow.
// we will call it periodically in a loop.

class fsmMachineCtrl:public fsmMachineBase{
public:
  fsmMachineCtrl(){};
  fsmMachineCtrl(int input){
    machineResource = input;
  };

  public:
  int machineResource = 0;
};





/************ Step2: create action ***********/
// then create the single actions classes by inheriting from the actionBase class.
// three function need to be implement here, which are actionPreparetion(), operation() and actionStateHandle().
//
// actionPreparetion() will be called before the periodically execution of the action. 
//(just before the periodically execution)
//
// operation() will be called periodically.
//
// actionStateHandle() will be called after the every exection of operation(), and return an actionState.
// the actionState will be checked by fsmMachineBase to decide if this action is finished and need to launch the next action.
// the default actionStateHandle() will return an ACTION_SUCCESSFUL.
// ACTION_SUCCESSFUL: action is finished and need to launch the next action. 
// ACTION_CONTINUE: action is not finished yet.

class fsmTestAct1:public actionBase{
public:
// some config function. 
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




/************ Step3: create an action workflow ***********/
// create your own action flow!
//
// start() will be called when you change to this action flow.
// Now I often create the actions in it. I may change it in the future ...
//
// finish() is the task to be done after the end of this workflow.
//
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
