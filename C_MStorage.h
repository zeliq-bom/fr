#pragma once

#include <queue>
#include <mutex>

#include "record.h"

class C_MStorage
{
public:
	mutex             m_mx;
	queue <MS_record> m_q;
};


//eof