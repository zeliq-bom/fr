#pragma once
#include <queue>
#include <mutex>

#include "record.h"
#include "C_MStorage.h"

class Ctask
{
public:
	void startTask(int ms_delay, int cnt1, int cnt2, Ctask & task1, Ctask & task2);
	void lock_and_push(Ctask * task,  MS_record & msr);
	virtual void  payloadA(MS_record & msr)=0;
	virtual void  payloadB(MS_record & msr)=0;

private:
	void read_and_push_to_MS();
	mutex m_mx;
	queue <MS_record> m_qu;
    
};


//eof