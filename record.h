#pragma once
#include <stdint.h>

using namespace std;

enum VF {
	VALID_X		=0x001,
	VALID_Y		=0x002,
	VALID_Z		=0x004,
	VALID_ROLL	=0x008,
	VALID_PITCH	=0x010,
	VALID_YAW	=0x020
};


struct MS_record
{
	VF valid_flags;
	uint64_t timestamp;
	union u
	{
		float fields[6];
		struct s{
			float x, y, z;
			float roll, pitch, yaw;
		}s;
	}u;
};

//eof