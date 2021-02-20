/** the united interface for state work flow.
 *
 * \param
 * \param
 * \return
 *
 */

#ifndef _FSM_MACHINE_BASE_H_
#define _FSM_MACHINE_BASE_H_


#include <Arduino.h>
#include "./actionFlowBase.h"
#include "./actionFlowContainer.h"


class fsmMachineBase{
public:
  fsmMachineBase();
  ~fsmMachineBase(){};

  int update(){
    if(actionWorkflow == 0) return 0;
    int ret = actionWorkflow->update();
    if (ret == 1){
      actionWorkflow->finish();
      actionWorkflow = 0;
    }
    return ret;
  };


  int changeStateWorkflow(actionFlowBase* newFlow){
    if(newFlow == 0) return 0;
    actionWorkflow = newFlow;
    actionWorkflow->start();
    actionWorkflow->actionFlowStart(this);
    return 1;
  };

private:

  actionFlowBase* actionWorkflow = 0;
};








#endif // _FSM_MACHINE_BASE_H_
