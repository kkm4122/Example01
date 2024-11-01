#include "pch.h"
#include "Goal.h"
#include "Actor.h"

void Goal::End() {}

void Goal::Render(int step)
{
    char tab[] = {'\t', '\t', '\t', '\t', '\t', '\t', '\t', '\t', '\t', '\t', '\t'};
    tab[step]  = 0;
    AXLOG("%s %s", tab, getName());
}

bool Goal::HandleMessage(const ActorMessage& msg)
{
    return false;
}
