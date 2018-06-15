#pragma once
#ifndef VOCALSTUDIO_STREAM_INPUTSTREAM_H
#define VOCALSTUDIO_STREAM_INPUTSTREAM_H

#include<exception>
#include"StreamBase.h"

namespace vocal_studio
{
	namespace stream
	{
		template <typename T = char, typename Traits = StreamTraits>
		class InputStream :public StreamBase<T, Traits>
		{
		public:
			virtual ~InputStream() = default;

			virtual bool isReadable() const override
			{
				return true;
			}
			virtual bool isWriteable() const override
			{
				return false;
			}
			virtual void write(T value) override
			{
				throw std::runtime_error("stream is not writeable.");
			}
			virtual void write(const T* buffer, std::size_t count) override
			{
				throw std::runtime_error("stream is not writeable.");
			}
		};
	}
}

#endif // !VOCALSTUDIO_STREAM_INPUTSTREAM_H
