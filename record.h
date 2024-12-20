#pragma once
#include <stdint.h>

using namespace std;

#define VALID_X 0x001
#define VALID_Y 0x002
#define VALID_Z 0x004
#define VALID_ROLL 0x008
#define VALID_PITCH 0x010
#define VALID_YAW 0x020

struct MS_record
{
	int valid_flags;
	uint64_t timestamp;
	float x, y, z;
	float roll, pitch, yaw;
};

//eof