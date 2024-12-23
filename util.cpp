#include <chrono>
#include <thread>
using namespace std;

void sleepMS(int ms)
{
	//std::this_thread::sleep_for(std::chrono::milliseconds(ms));
	this_thread::sleep_for(chrono::milliseconds(ms));
}

int align_up(int x)
{
	unsigned int val = 1,i ;
	for (i = 0; i < 31; i++)
	{
		val <<= 1;
		if (val > x) break;
	}
	return i;
}

float f(uint64_t time)
{
	float y;
	float k = 2.0 / 500;
	float b = -1;

	int x = time % 1000;
	float sign = 1.0;
	if (x >= 500)
	{
		sign = -1.0;
		x -= 500;
		b = 1;
	}
	y = (k * x*sign) + b;

	//TRI(x);
	//TRF(b);
	//TRF(k);
	//TRF(y);
	//TRF(sign);
	//LOG("   time=%p\n ", time);
	return y;

}
uint64_t get_time()
{
	uint64_t milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
		).count();

	static uint64_t zero;
	static bool once = true;
	if (once)
	{
		once = false;
		zero = milliseconds;
	}
	return milliseconds - zero;
}
//eof