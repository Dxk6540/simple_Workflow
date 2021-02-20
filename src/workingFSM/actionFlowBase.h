#ifndef _ACTION_FLOW_BASE_H_
#define _ACTION_FLOW_BASE_H_

#include "./actionBase.h"
//context
#define MAX_ACTION_NUM 20
class fsmMachineBase;

class actionFlowBase{
public:
  virtual actionFlowBase(){};
  virtual ~actionFlowBase(){};
//
//  // config function
//  int addState(stateBase newState){
//    stateList
//  }
//

  virtual int start(){

    return 0;
  }


  virtual int finish(){
    return 0;
  }


  int actionFlowStart(fsmMachineBase* machine){
    if (_stateNum == 0) return 0;

    currentActionNum = 0;
    curAct = actionList[0];
    actionList[0]->actionPreparetion(this);

    fsmMachine = machine;
//    Serial.println("flow started");
    return 1;
  }

  //working func
  virtual int update(){
    if (_stateNum == 0) return 1;

    int ret = curAct->operation(this); // be careful about the pter ...
    actionState actFeedback = curAct->actionStateHandle(this);
    switch(actFeedback){
    case ACTION_SUCCESSFUL:
      {
        currentActionNum ++;
        if(currentActionNum == _stateNum){
          fsmMachine = 0;
          return 1; // means successful
        }
        curAct = actionList[currentActionNum];
        curAct->actionPreparetion(this);

        return 0;
      }
      break;
    case ACTION_CONTINUE:
      {
        return 0;
      }
      break;
    case ACTION_ERROR:
      {
        return -1;
      }
      break;
    }

    return -1;
  };

  int addState(actionBase* newAct){
    if(_stateNum == MAX_ACTION_NUM) return 0;
    actionList[_stateNum] = newAct;
    _stateNum ++;
    return 1;

  }

  int removeState(actionBase* actPt){
    if(_stateNum == 0) return 0;
    int actPos = -1;
    for(int i = 0; i < _stateNum; i++){
      if(actionList[i] == actPt) actPos = i;
    }

    if(actPos == -1) return 0;
    actionList[actPos] = 0;
    for(int i = actPos + 1; i < _stateNum; i++){
      actionList[i-1] = actionList[i];
    }
    actionList[_stateNum - 1] = 0;
    _stateNum --;
    return 1;
  }

public:

  int _stateNum = 0;
  int currentActionNum;
  fsmMachineBase* fsmMachine = 0;
  actionBase* curAct = 0;
  actionBase* actionList[MAX_ACTION_NUM];
};



#endif // _ACTION_FLOW_BASE_H_
