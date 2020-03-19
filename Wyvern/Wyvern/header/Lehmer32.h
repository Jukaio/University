// Lehmer32.h

#ifndef __LEHMER_32__
#define __LEHMER_32__

struct Lehmer
{
	static unsigned __int32 lehmer_Seed_;

	static void Set_Lehmer_Seed(unsigned __int32 seed);
	static unsigned __int32 Lehmer32();
	static unsigned __int32 Lehmer32(int mod);
	static unsigned __int32 Lazy_Lehmer32(int mod);

private:
	static long int lazy_Lehmer_Count_;
};


#endif // !__LEHMER_32__
