#pragma once
#include "preDefines.h"
#include <deque>

template <class T>
class IDsystem
{
public:
    unsigned int Add(T* aa)
	{ 
		unsigned int idx;
        
		if (mActorList.size() >= 128 && mFreeNoList.size() > 0)
        {
            idx = mFreeNoList.front();
            mFreeNoList.pop_front();
            mActorList[idx] = aa;
        }
        else
        {
			idx = mActorList.size();
            mActorList.push_back(aa);
        }

        return idx;
	}

    void Delete(unsigned int idx)
    {
        if (idx == UINT32_MAX) return;

        mActorList[idx] = nullptr;
        mFreeNoList.push_back(idx);
    }


	std::vector<T*> mActorList;
	std::deque<unsigned int>  mFreeNoList;

};