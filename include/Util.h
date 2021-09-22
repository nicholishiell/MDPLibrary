#ifndef UTILITY_H
#define  UTILITY_H

#include <memory>
#include <array>
#include <vector>
#include <limits>
#include <string>
#include <cmath>

class Agent;
class Action;
class MarkovDecisionProcess;
class State;

namespace Util
{  
    using StateSharedPtr = std::shared_ptr<State>;
    using StateVector = std::vector<State>;
    using StateSharedPtrVector = std::vector<StateSharedPtr>;

    using AgentSharedPtr = std::shared_ptr<Agent>;
    using MDPSharedPtr = std::shared_ptr<MarkovDecisionProcess>;

    using ActionSharedPtr = std::shared_ptr<Action>;
    using ActionSharedPtrVector = std::vector<ActionSharedPtr>;
    using HistoryOfActions = std::vector<ActionSharedPtrVector>;

    using StateAction = std::pair<StateSharedPtr, ActionSharedPtr>;

    using DoubleVector = std::vector<double>;
}

#endif