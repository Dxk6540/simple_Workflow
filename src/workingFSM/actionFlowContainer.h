#ifndef _ACTION_FLOW_CONTAINER_H_
#define _ACTION_FLOW_CONTAINER_H_

#include "./actionFlowBase.h"
//context
#define MAX_ACTION_NUM 20





class flowAction: public actionBase{
public:
  virtual flowAction(){};
  virtual ~flowAction(){};

  int attachActionFlow(actionFlowBase* actFlow){
    if(actFlow != 0) _actFlow = actFlow;
    return 1;
  }

  virtual int actionPreparetion(actionFlowBase* base){
    if(_actFlow == 0) return 0;
    _flowRet = 0;
    _actFlow->start();
    _actFlow->actionFlowStart(base->fsmMachine);
    return 1;
  };

  // config function
  virtual int operation(actionFlowBase* base){
    return 0;
  };

  virtual actionState actionStateHandle(actionFlowBase* base){
    if(_actFlow == 0) return ACTION_SUCCESSFUL;
    _flowRet = _actFlow->update();

    if (_flowRet == 1){
      _actFlow->finish();
      return ACTION_SUCCESSFUL;
    }
    return ACTION_CONTINUE;
  };

  actionFlowBase* _actFlow = 0;
  int _flowRet = 0;
};





class actionflowContainer:public actionFlowBase{
public:
  ~actionflowContainer(){
    for(int i = 0; i < curFlowNum; i++) delete actflowSeq[i];
  };

  int addActionFlow(actionFlowBase* newFlow){
    if(newFlow == 0) return 0;

    flowAction* flowAsAct = new flowAction();
    flowAsAct->attachActionFlow(newFlow);
    actflowSeq[curFlowNum] = flowAsAct;
    this->addState(actflowSeq[curFlowNum]);
    curFlowNum++;
    return 1;
  };

  virtual int start(){
    return 0;
  };

  virtual int finish(){
    return 0;
  };

private:
  flowAction* actflowSeq[20];
  int curFlowNum = 0;
};


#endif // _ACTION_FLOW_CONTAINER_H_
