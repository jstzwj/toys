#pragma once
#ifndef RAPIDPARSER_BASIC_TIMEVALUE
#define RAPIDPARSER_BASIC_TIMEVALUE
#include<cinttypes>
#include<chrono>
namespace rpr
{
	namespace basic
	{
		class TimeValue
		{
			typedef uint64_t SecondType;
			typedef uint32_t NanoSecondType;
		private:
			SecondType seconds;
			NanoSecondType nano_seconds;
		public:




		};


	}
}

#endif // !RAPIDPARSER_BASIC_TIMEVALUE
