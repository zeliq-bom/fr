
#include <thread>

#include "Ctask.h"

#include "Config.h"
#include "util.h"

bool gRun = true;
bool gDebug = true;

C_MStorage g_MStorage;


class Ctask10 : public Ctask
{
	virtual void payloadA(MS_record & msr)
	{
		msr.valid_flags = VALID_Z;
		msr.u.s.z = f(msr.timestamp);
	}
	virtual void payloadB(MS_record & msr)
	{
		msr.valid_flags = VALID_ROLL;
		msr.u.s.roll = f(msr.timestamp)*M_PI;
	}
};

class Ctask20 : public Ctask
{
	virtual void payloadA(MS_record & msr)
	{
		msr.valid_flags = VALID_X;
		msr.u.s.x = f(msr.timestamp);
	}
	virtual void payloadB(MS_record & msr)
	{
		msr.valid_flags = VALID_PITCH;
		msr.u.s.pitch = f(msr.timestamp)*M_PI;
	}
};

class Ctask40 : public Ctask
{
	virtual void payloadA(MS_record & msr)
	{
		msr.valid_flags = VALID_Y;
		msr.u.s.y = f(msr.timestamp);
	}
	 void payloadB(MS_record & msr)
	{
		msr.valid_flags = VALID_YAW;
		msr.u.s.yaw = f(msr.timestamp)*M_PI;
	}
};


Ctask10 g_task10;
Ctask20 g_task20;
Ctask40 g_task40;



void Task10()
{
	g_task10.startTask(10, 20, 40, g_task20, g_task40);
}
void Task20()
{
	g_task20.startTask(20, 20, 40, g_task10, g_task40);
}


void Task40()
{
	g_task40.startTask(40, 40, 40, g_task10, g_task20);
}


int main()
{
	//---------------------------test F
	//f(0);
	//f(100);
	//f(500);
	//f(600);
	//f(800);
	//f(2100);

	std::thread t10(Task10);
	std::thread t20(Task20);
	std::thread t40(Task40);
	sleepMS(3 * 100);
	gRun = false;
	t10.join();
	t20.join();
	t40.join();

}
//eof