#ifndef MDP_H
#define  MDP_H

#include <memory>
#include <vector>

#include "Util.h"
#include "State.h"

using namespace Util;

class MarkovDecisionProcess
{
public:
    inline  MarkovDecisionProcess();
    inline  ~MarkovDecisionProcess();     
    
    virtual void Return2InitialState() = 0; 

    virtual void DecisionUpdate(const ActionSharedPtrVector& actions) = 0; 
    virtual void ExogenousUpdate() = 0;

    inline double GetTotalReward() const;
    inline  void SetTotalReward(const double reward);
    virtual void UpdateTotalReward() = 0; 
    
    virtual bool IsEndState() const = 0;

    virtual ActionSharedPtrVector GetLegalActions() const = 0; 

    inline  void SetCurrentState(const StateSharedPtr state);
    inline  StateSharedPtr GetCurrentState() const;
    
    inline  void SetInitialState(const StateSharedPtr state);
    inline  StateSharedPtr GetInitialState() const;

    virtual void Print() const = 0;

private:

    virtual double calculateExpectedReward( const StateSharedPtr state, 
                                            const ActionSharedPtr decision) = 0;
  
    StateSharedPtr initialState_;
    StateSharedPtr currentState_;

    double totalReward_;
};

MarkovDecisionProcess::MarkovDecisionProcess()
{
};

MarkovDecisionProcess::~MarkovDecisionProcess()
{ 
};

void 
MarkovDecisionProcess::SetInitialState(const StateSharedPtr state)
{
    initialState_ = state;
};

StateSharedPtr 
MarkovDecisionProcess::GetInitialState() const
{
    return initialState_;
};

void 
MarkovDecisionProcess::SetCurrentState(const StateSharedPtr state)
{
    currentState_ = state;
};

StateSharedPtr 
MarkovDecisionProcess::GetCurrentState() const
{
    return currentState_;
};

void
MarkovDecisionProcess::SetTotalReward(const double reward)
{
    totalReward_ = reward;
};

double 
MarkovDecisionProcess::GetTotalReward() const
{
    return totalReward_;
};

#endif