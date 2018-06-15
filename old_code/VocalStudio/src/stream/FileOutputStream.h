#pragma once
#ifndef VOCALSTUDIO_STREAM_FILEOUTPUTSTREAM_H
#define VOCALSTUDIO_STREAM_FILEOUTPUTSTREAM_H

#include<cstdio>
#include<exception>
#include<stdexcept>
#include<sstream>

#include"OutputStream.h"
namespace vocal_studio
{
	namespace stream
	{
		template<class T,class CharType=char>
		inline void outputHelper(OutputStream<CharType>& stream_,const T &value)
		{
			stream_.write(reinterpret_cast<const char *>(&value),sizeof(T));
		}



		class FileOutputStream :public OutputStream<char>
		{
		protected:
			std::FILE * file;
		public:
			FileOutputStream(std::FILE* file_) : file(file_) {}
			FileOutputStream(const FileOutputStream& src) = delete;
			FileOutputStream(FileOutputStream&& src) : file(src.file)
			{
				src.file = nullptr;
			}
			virtual ~FileOutputStream() = default;

			FileOutputStream& operator =(const FileOutputStream& src) = delete;
			FileOutputStream& operator =(FileOutputStream&& src)
			{
				file = src.file;
				src.file = nullptr;
				return *this;
			}
			
			//write virtual function
			virtual void write(CharType value)
			{
				write(&value,1);
			}
			virtual void write(const CharType* buffer, std::size_t count)
			{
				std::fwrite(buffer,sizeof(CharType),count,file);
			}

			//buffer virtual function
			virtual void flush() {}

			//seek virtual function
			virtual bool isSeekable() const
			{
				return true;
			}
			virtual std::intmax_t seek(std::intmax_t offset, PosType method)
			{
				int seek_pos;
				switch (method)
				{
				case PosType::Begin:
					seek_pos = SEEK_SET;
					break;
				case PosType::End:
					seek_pos = SEEK_END;
					break;
				case PosType::Current:
					seek_pos = SEEK_CUR;
					break;
				default:
					throw std::runtime_error("Unknown postype.");
				}
				return std::fseek(file, offset, seek_pos);
			}

			virtual std::intmax_t getPosition()
			{
				return std::ftell(file);
			}
		};
	}
}



#endif // !VOCALSTUDIO_STREAM_FILEOUTPUTSTREAM_H
