#ifndef STATE_H
#define STATE_H

#include "Util.h"

using namespace Util;

class State
{
public:

    inline State(){};
    inline ~State(){};

    virtual void Update(const ActionSharedPtrVector& action) = 0;
    virtual void UpdateDeterministic(const ActionSharedPtrVector& action) = 0;
    virtual void UpdateExogenous() = 0;

    virtual StateSharedPtr MakeCopy() = 0;

    virtual void Print() const = 0;  
};

#endif