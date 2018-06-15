#ifndef VOCALSTUDIO_AUDIO_WAV_WAV_H
#define VOCALSTUDIO_AUDIO_WAV_WAV_H

#include<cstdint>
#include<cstring>
#include<iostream>
#include<exception>

#include"../audio.h"
#include"../../stream/FileInputStream.h"
#include"../../stream/InputStream.h"
#include"../../stream/OutputStream.h"

namespace vocal_studio
{
	using byte = unsigned char;
	enum RiffBlockType { UNKNOWN, HEADER, FORMAT, FACT, DATA };

#pragma pack (1)

	struct RIFF_header
	{
		char szRiffID[4];  // 'R','I','F','F'
		uint32_t dwRiffSize;
		char szRiffFormat[4]; // 'W','A','V','E'
	};

	enum FORMAT_TAG
	{
		WAVE_FORMAT_PCM = 1
	};

	struct WAVE_format
	{
		uint16_t wFormatTag;
		uint16_t wChannels;
		uint32_t dwSamplesPerSec;
		uint32_t dwAvgBytesPerSec;
		uint16_t wBlockAlign;
		uint16_t wBitsPerSample;
	};

	struct FMT_block
	{
		char  szFmtID[4]; // 'f','m','t',' '
		uint32_t  dwFmtSize;
		WAVE_format wavFormat;
	};

	struct FACT_block
	{
		char  szFactID[4]; // 'f','a','c','t'
		uint32_t  dwFactSize;
	};

	struct DATA_block
	{
		char szDataID[4]; // 'd','a','t','a'
		uint32_t dwDataSize;
	};

	struct Data_chunk_16d
	{
		uint16_t data_left;
		uint16_t data_rght;
	};
	struct Data_chunk_16s
	{
		uint16_t data1;
		uint16_t data2;
	};

#pragma pack ()
	class WaveWriter
	{
	public:
		using StreamType = stream::OutputStream<char>;
		StreamType &data_source;

		WaveWriter(StreamType & stream)
			:data_source(stream) {}
		template<class SampleType>
		void write(const Audio<SampleType>& audio)
		{
			//write riff header
			data_source.write("RIFF", 4);
			stream::outputHelper<uint32_t>(data_source, audio.dataSize() + 44 - 8);
			data_source.write("WAVE", 4);

			//write format block
			data_source.write("fmt ", 4);
			stream::outputHelper<uint32_t>(data_source, 16);
			stream::outputHelper<uint16_t>(data_source, FORMAT_TAG::WAVE_FORMAT_PCM);
			stream::outputHelper<uint16_t>(data_source, audio.attribute.channels);
			stream::outputHelper<uint32_t>(data_source, audio.attribute.samplesPerSec);
			stream::outputHelper<uint32_t>(data_source, audio.attribute.getAvgBytesPerSec());
			stream::outputHelper<uint16_t>(data_source, audio.attribute.getBlockAlign());
			stream::outputHelper<uint16_t>(data_source, audio.attribute.bitsPerSample);

			//write data block
			data_source.write("data", 4);
			stream::outputHelper<uint32_t>(data_source, audio.dataSize());
			//write data
			for (uint32_t i = 0; i < audio.samplesNum();++i)
			{
				stream::outputHelper<SampleType>(data_source, audio.left[i]);
				if(audio.attribute.channels==2)
					stream::outputHelper<SampleType>(data_source, audio.right[i]);
			}
		}
	};

	class WaveReader
	{
	public:
		using StreamType = stream::InputStream<char>;
		StreamType &data_source;

		WaveReader(stream::InputStream<char> & stream)
			:data_source(stream) {}

		Audio16 read()
		{
			Audio16 result;
			//Read Riff header
			RIFF_header header;
			data_source.read(header.szRiffID, sizeof(header.szRiffID));
			if (strcmp(header.szRiffID, "RIFF"))
			{
				data_source.read(reinterpret_cast<char *>(&header.dwRiffSize),sizeof(header.dwRiffSize));
				data_source.read(header.szRiffFormat, sizeof(header.szRiffFormat));
				if (strcmp(header.szRiffFormat, "WAVE") != 0)
				{
					throw std::exception("Can not use WaveReader to read the file.");
				}
			}
			else
			{
				throw std::exception("Wave file header can not be found.");
			}

			//Read riff format
			FMT_block format;
			WAVE_format wave_format;
			data_source.read(format.szFmtID, sizeof(format.szFmtID));
			if (strcmp(format.szFmtID, "fmt "))
			{
				data_source.read(reinterpret_cast<char *>(&format.dwFmtSize), sizeof(format.dwFmtSize));
				
				//Read wave format
				data_source.read(reinterpret_cast<char *>(&wave_format.wFormatTag), sizeof(wave_format.wFormatTag));
				if (wave_format.wFormatTag != FORMAT_TAG::WAVE_FORMAT_PCM)
				{
					throw std::exception("Do not support the wave format.");
				}
				data_source.read(reinterpret_cast<char *>(&wave_format.wChannels), sizeof(wave_format.wChannels));
				data_source.read(reinterpret_cast<char *>(&wave_format.dwSamplesPerSec), sizeof(wave_format.dwSamplesPerSec));
				data_source.read(reinterpret_cast<char *>(&wave_format.dwAvgBytesPerSec), sizeof(wave_format.dwAvgBytesPerSec));
				data_source.read(reinterpret_cast<char *>(&wave_format.wBlockAlign), sizeof(wave_format.wBlockAlign));
				data_source.read(reinterpret_cast<char *>(&wave_format.wBitsPerSample), sizeof(wave_format.wBitsPerSample));
				result.attribute.channels = wave_format.wChannels;
				result.attribute.samplesPerSec = wave_format.dwSamplesPerSec;
				result.attribute.bitsPerSample = wave_format.wBitsPerSample;
				data_source.seek(format.dwFmtSize- sizeof(wave_format.wChannels)- sizeof(wave_format.dwSamplesPerSec), StreamType::PosType::Current);
			}
			else
			{
				throw std::exception("Wave file format can not be found.");
			}
			//Read fact and data blocks
			FACT_block fact;
			data_source.read(fact.szFactID, 4);
			if (strcmp(fact.szFactID, "fact"))
			{
				//TODO
				data_source.seek(sizeof(FACT_block)-sizeof(fact.szFactID), StreamType::PosType::Current);
			}
			else
			{
				data_source.seek(-4, StreamType::PosType::Current);
			}
			DATA_block data;
			data_source.read(data.szDataID, 4);
			if (strcmp(data.szDataID, "data"))
			{
				data_source.read(reinterpret_cast<char *>(&data.dwDataSize), sizeof(data.dwDataSize));
			}
			else
			{
				throw std::exception("Unknown block type.");
			}
			uint32_t blockAlign = result.attribute.channels*result.attribute.bitsPerSample;
			if (result.attribute.channels == 2)
			{
				if (result.attribute.bitsPerSample == 16)
				{
					for (uint32_t i = 0; i < data.dwDataSize / blockAlign; ++i)
					{
						uint16_t lft, rht;
						data_source.read(reinterpret_cast<char *>(&lft), sizeof(lft));
						data_source.read(reinterpret_cast<char *>(&rht), sizeof(rht));
						result.left.push_back(lft);
						result.left.push_back(rht);
					}
				}
				else
				{
					throw std::exception("Do not support 8 bit now.");
				}
			}
			else
			{
				throw std::exception("Do not support 1 channel now.");
			}
			return result;
		}
	};
}

#endif //VOCALSTUDIO_AUDIO_WAV_WAV_H
