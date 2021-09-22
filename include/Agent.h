#ifndef AGENT_H
#define  AGENT_H

#include <unordered_map>
#include <string>

#include "Util.h"
#include "State.h"
#include "Action.h"

class Agent
{
public:

    virtual ActionSharedPtrVector GetDecision(  const ActionSharedPtrVector legalActions,
                                                const StateSharedPtr state) const = 0;

    virtual void UpdateVFABackwardDP(   const StateSharedPtrVector& trajectory,
                                        const HistoryOfActions& actions) = 0;
    
    virtual void UpdateVFAForwardDP(const StateSharedPtr& currentState,
                                    const ActionSharedPtrVector& action) = 0;
};

#endif