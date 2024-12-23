#pragma once

#define M_PI  3.14159265358979323846

#define LOG       if (gDebug) printf
#define TRI(a)    if (gDebug) printf (#a " %p \n", (void*)a);  //Trace int
#define TRF(a)    if (gDebug) printf (#a " %.3f \n", a);  //Trace float

int align_up(int x);
void sleepMS(int ms);
uint64_t get_time();
float f(uint64_t time);
//eof