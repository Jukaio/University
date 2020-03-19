// Lehmer32.cpp

#include "Lehmer32.h"
#include "Service.h"
#include "Time.h"
#include <chrono>

unsigned __int32 Lehmer::lehmer_Seed_ = 0;
long int Lehmer::lazy_Lehmer_Count_ = LONG_MIN;

void Lehmer::Set_Lehmer_Seed(unsigned __int32 seed)
{
	lehmer_Seed_ = seed;
}

unsigned __int32  Lehmer::Lehmer32()
{
	lehmer_Seed_ += 0xe120fc15;
	unsigned __int64 temp;
	temp = (unsigned __int64)lehmer_Seed_ * 0x4a39b70d;
	unsigned __int32 m_1 = (temp >> 32) ^ temp;
	temp = (unsigned __int64)m_1 * 0x12fad5c9;
	unsigned __int32 m_2 = (temp >> 32) ^ temp;
	return m_2;
}

unsigned __int32 Lehmer::Lehmer32(int mod)
{
	return Lehmer::Lehmer32() % mod;
}

unsigned __int32 Lehmer::Lazy_Lehmer32(int mod)
{
	lazy_Lehmer_Count_++;
	if (lazy_Lehmer_Count_ >= LONG_MAX-1)
		lazy_Lehmer_Count_ = LONG_MIN;

	long int run_Time_Ticks = Service<Time>::Get()->Run_Time().As_Miliseconds();
	long int system_Time = (long int)std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	Set_Lehmer_Seed(run_Time_Ticks + system_Time + lazy_Lehmer_Count_);
	return Lehmer::Lehmer32() % mod;
}


