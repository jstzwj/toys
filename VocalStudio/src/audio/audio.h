#ifndef VOCALSTUDIO_AUDIO_AUDIO_H
#define VOCALSTUDIO_AUDIO_AUDIO_H

#include<vector>
#include<utility>
#include<cstdint>


namespace vocal_studio
{
	class AudioAttr
	{
	public:
		uint32_t channels;
		uint32_t samplesPerSec;
		uint32_t bitsPerSample;
		uint32_t getAvgBytesPerSec()const
		{
			return bitsPerSample*channels*samplesPerSec /8;
		}
		uint32_t getBlockAlign()const
		{
			return bitsPerSample*channels / 8;
		}
	};

	template<class SampleType = uint16_t>
	class Audio
	{
	public:
		AudioAttr attribute;
		std::vector<SampleType> left;
		std::vector<SampleType> right;

		uint32_t dataSize()const
		{
			return sizeof(SampleType)*(left.size() + right.size());
		}
		uint32_t samplesNum()const
		{
			return left.size();
		}
		void push_back(const std::pair<SampleType, SampleType> &sample)
		{
			left.push_back(sample.first);
			if(attribute.channels==2)
				right.push_back(sample.second);
		}
		void push_back(SampleType sample)
		{
			left.push_back(sample);
			if (attribute.channels == 2)
				right.push_back(sample);
		}
		
	};
	using Audio16 = Audio < uint16_t >;
}

#endif // !VOCALSTUDIO_AUDIO_AUDIO_H
