#include "Ctask.h"
#include "Config.h"
#include "util.h"
#include "C_MStorage.h"

extern C_MStorage g_MStorage;

void Ctask::startTask(int ms_delay, int cnt1, int cnt2, Ctask & taskA, Ctask & taskB)
{
	queue <MS_record>  temp_q;
	MS_record msr;  // MS record msr
	memset(&msr, 0, sizeof(MS_record));

	int bit1 = align_up(cnt1 / ms_delay);
	int bit2 = align_up(cnt2 / ms_delay);

	unsigned int cnt;                              // Interval count


	for (cnt = 0; ; cnt++)
	{
		if (!gRun) break;
		sleepMS(ms_delay);
		read_and_push_to_MS();
		msr.timestamp = get_time();
		if ((cnt & bit1) || (!bit1))
			//---------------------------- activity A	
		{
			payloadA(msr);
			lock_and_push(&taskA, msr);
		}
		//---------------------------- activity B
		if ((cnt & bit2) || (!bit2))
		{
			payloadB(msr);
			lock_and_push(&taskB, msr);
		}
	}
}
//--------------------------------------------------------------------
void Ctask::lock_and_push(Ctask * task, MS_record & msr)
{
	//-----------------here possible insert code for check valid value range in each valid field.
	{
		lock_guard<mutex> lock(task->m_mx);
		task->m_qu.push(msr);
	}
	LOG("ts.%04d flags.%X x.%3f y.%3f z.%3f pit.%3f rol.%3f yaw.%3f  \n",
		msr.timestamp, msr.valid_flags, msr.u.s.x, msr.u.s.y, msr.u.s.z, msr.u.s.pitch, msr.u.s.roll, msr.u.s.yaw);
}
//-------------------------------------------------------------------------
void Ctask::read_and_push_to_MS()
{
	queue <MS_record>  temp_q;
	bool has_record = false;
	MS_record  accum;
	MS_record  temp;
	bool  accum_active = false;
	bool  accum_write;
	{//-------------------------------lock  own task
		lock_guard<mutex> lock(m_mx);
		while (!m_qu.empty())
		{
			has_record = true;
			temp_q.push(m_qu.front());
			m_qu.pop();
		}
	}//----------------Free lock
	if (has_record)
	{//----------------------------------Take lock MS
		lock_guard <mutex> lock(g_MStorage.m_mx);
		while (!temp_q.empty())
		{
			//---------------------------Here try to accumulate values w/ same time stamp and unite values
			temp = temp_q.front();
			LOG("PUSH to MS tid.%x ts.%04d flags.%X x.%3f y.%3f z.%3f pit.%3f rol.%3f yaw.%3f  \n",
				std::this_thread::get_id(),
				temp.timestamp, temp.valid_flags, temp.u.s.x, temp.u.s.y, temp.u.s.z, temp.u.s.pitch, temp.u.s.roll, temp.u.s.yaw);
			accum_write = false;
			if (accum_active)
			{
				//------------check time flags
				accum_write = true;
				if (accum.timestamp = temp.timestamp)
				{
					if (0 == (accum.valid_flags & temp.valid_flags))           //check that possible acum flags
					{
						accum_write = false;
						LOG("PUSH to MS tid.%x combine records\n", std::this_thread::get_id());
						for (int i = 0; i < sizeof(temp.u.fields) / sizeof(temp.u.fields[0]); i++)
						{
							if ((1 << i) & temp.valid_flags)
							{
								accum.u.fields[i] = temp.u.fields[i];
							}
						}
					}
				}
			}
			if (accum_write)
			{
				LOG("PUSH to MS tid.%x write accum \n", std::this_thread::get_id());
				g_MStorage.m_q.push(accum);
				accum_active = false;
			}
			if (!accum_active)
			{
				accum = temp;
				accum_active = true;
			}
			temp_q.pop();

		}
		//-------------------write last element in any
		if (accum_active)
			g_MStorage.m_q.push(accum);
	}//-----------------------------------Free MS lock
}
//eof