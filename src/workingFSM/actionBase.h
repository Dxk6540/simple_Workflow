#ifndef _ACTION_BASE_H_
#define _ACTION_BASE_H_
class actionFlowBase;

typedef enum actionState{
  ACTION_SUCCESSFUL = 1,
  ACTION_CONTINUE = 0,
  ACTION_ERROR = -1,
} actionState;

class actionBase{
public:
  virtual actionBase(){};
  virtual ~actionBase(){};
  virtual int actionPreparetion(actionFlowBase* ){};

  // config function
  virtual int operation(actionFlowBase* ) {};
  virtual actionState actionStateHandle(actionFlowBase* ){
    return ACTION_SUCCESSFUL;
  }
//  virtual int changeState(stateFlowBase* ) = 0;
};


#endif // _ACTION_BASE_H_
