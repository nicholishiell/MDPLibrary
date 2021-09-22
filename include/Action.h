#ifndef ACTION_H
#define ACTION_H

class Action
{
public:
    
    virtual inline double GetBellmanValue() const;
    virtual inline void SetBellmanValue(const double value);

    virtual inline double GetReward() const;
    virtual inline void SetReward(const double reward);

private:

    // the value as determined by the Bellman Eqn
    double bellmanValue_;

    // reward gained when task is complete
    double reward_;
};

double 
Action::GetBellmanValue() const
{
    return bellmanValue_;
};

void 
Action::SetBellmanValue(const double value)
{
    bellmanValue_ = value;
};

double 
Action::GetReward() const
{
    return reward_;
};

void 
Action::SetReward(const double reward)
{
    reward_ = reward;
};

#endif