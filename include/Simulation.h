#ifndef SIM_H
#define  SIM_H

#include <stdlib.h>
#include <iostream>
#include <algorithm>

#include "Util.h"
#include "Agent.h"
#include "MarkovDecisionProcess.h"

using namespace Util;

class Simulation
{
public:

    inline Simulation();
    inline ~Simulation();

    inline void AddAgent(AgentSharedPtr agent);
    inline void AddMarkovDecisionProcess(MDPSharedPtr mdp);
  
    inline AgentSharedPtr GetAgent() const;
    inline MDPSharedPtr GetMDP() const;

private:

    AgentSharedPtr agent_;
    MDPSharedPtr mdp_;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


class Evaluator : public Simulation
{
public:   

    inline Evaluator();
    inline ~Evaluator();

    inline void Evaluate(const int numberOfRuns = 1);

    inline DoubleVector GetRewards() const;

    inline HistoryOfActions GetHistoryOfActions() const;

private:

    inline void evaluateStep();

    DoubleVector rewards_;

    HistoryOfActions historyOfActions_;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class Trainer : public Simulation
{
public:   

    inline  Trainer();
    inline  ~Trainer();

    inline void TrainForwardDP(const int numberOfRuns = 1);

    inline void TrainBackwardDP(const int numberOfRuns = 1);

private:

    inline void trainingStepForwardDP();
    inline void trainingStepBackwardDP();

    HistoryOfActions decisions_;
    StateSharedPtrVector historyOfStates_;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Simulation::Simulation()
{

};

Simulation::~Simulation()
{
    
};

void 
Simulation::AddMarkovDecisionProcess(MDPSharedPtr mdp)
{
    mdp_ = std::move(mdp);    
};

void 
Simulation::AddAgent(AgentSharedPtr agent)
{
    agent_ = std::move(agent);
};

AgentSharedPtr 
Simulation::GetAgent() const
{
    return agent_;
};

MDPSharedPtr 
Simulation::GetMDP() const
{
    return mdp_;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Evaluator::Evaluator()
{

};

Evaluator::~Evaluator()
{
    
};

void 
Evaluator::Evaluate(const int numberOfRuns)
{
    for(int iRun = 0; iRun < numberOfRuns; iRun++)
    {
        GetMDP()->Return2InitialState();    

        std::cout << "Run #: " << iRun << std::endl;

        while(!GetMDP()->IsEndState())
        {
            evaluateStep();
        }

        rewards_.emplace_back(GetMDP()->GetTotalReward());
    }
};

DoubleVector
Evaluator::GetRewards() const
{
    return rewards_;
};

HistoryOfActions 
Evaluator::GetHistoryOfActions() const
{
    return historyOfActions_;
}

void
Evaluator::evaluateStep()
{
    // Get the decision from the agent and add the tasks to the task list
    const auto decision = GetAgent()->GetDecision(  GetMDP()->GetLegalActions(),
                                                    GetMDP()->GetCurrentState());

    historyOfActions_.emplace_back(decision);

    // Update the state to the post-decision state
    GetMDP()->DecisionUpdate(decision);

    // Update the state to the pre decision state
    GetMDP()->ExogenousUpdate();

    // Update the cumulative Reward/Cost
    GetMDP()->UpdateTotalReward();
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Trainer::Trainer()
{

};

Trainer::~Trainer()
{
    
};

// Implementation of Algorithm in Figure 4.7 pg 141 Powell
void 
Trainer::TrainForwardDP(const int numberOfRuns)
{
    for(int iRun = 0; iRun < numberOfRuns; iRun++)
    {     
        GetMDP()->Return2InitialState();    
        std::cout << "Run #: " << iRun << std::endl;
        while(!GetMDP()->IsEndState())
        {
            trainingStepForwardDP();
        }
    }
};

void 
Trainer::trainingStepForwardDP()
{
    // Solve the decision policy
    const auto decision = GetAgent()->GetDecision(  GetMDP()->GetLegalActions(),
                                                    GetMDP()->GetCurrentState());
    
    // Update the value function
    GetAgent()->UpdateVFAForwardDP(GetMDP()->GetCurrentState(), decision);
    
    // Update the state to the post-decision state
    GetMDP()->DecisionUpdate(decision);

    // Update the state to the pre decision state
    GetMDP()->ExogenousUpdate();

    // Update the cumulative Reward/Cost
    GetMDP()->UpdateTotalReward();
};

void 
Trainer::TrainBackwardDP(const int numberOfRuns)
{
    for(int iRun = 0; iRun < numberOfRuns; iRun++)
    {
        std::cout << "Run #: " << iRun << std::endl;

        historyOfStates_.clear();
        decisions_.clear();    

        GetMDP()->Return2InitialState();
        while(!GetMDP()->IsEndState())
        {   
            trainingStepBackwardDP();
        }

        GetAgent()->UpdateVFABackwardDP(historyOfStates_, decisions_);
    }
};

void 
Trainer::trainingStepBackwardDP()
{
    // Get the decision from the agent and add the tasks to the task list
    const auto decision = GetAgent()->GetDecision(  GetMDP()->GetLegalActions(),
                                                    GetMDP()->GetCurrentState());

    // keep track of decisions in order to use with backward pass update
    decisions_.emplace_back(decision);

    // Update the state to the post-decision state
    GetMDP()->DecisionUpdate(decision);

    // Update the state to the pre decision state
    GetMDP()->ExogenousUpdate();

    // Update the cumulative Reward/Cost
    GetMDP()->UpdateTotalReward();

    // record the date for use with offline learning algorithms
    historyOfStates_.emplace_back(GetMDP()->GetCurrentState()->MakeCopy());
};

#endif