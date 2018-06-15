#pragma once
#ifndef VOCALSTUDIO_STREAM_OUTPUTSTREAM_H
#define VOCALSTUDIO_STREAM_OUTPUTSTREAM_H

#include"StreamBase.h"

namespace vocal_studio
{
	namespace stream
	{
		template <typename T = char, typename Traits = StreamTraits>
		class OutputStream :public StreamBase<T, Traits>
		{
		public:
			virtual ~OutputStream() = default;

			virtual bool isWriteable() const override
			{
				return true;
			}
			virtual bool isReadable() const override
			{
				return false;
			}
			virtual T read() override
			{
				throw std::runtime_error("stream is not readable.");
			}
			virtual std::size_t read(T* buffer, std::size_t count) override
			{
				throw std::runtime_error("stream is not readable.");
			}
			virtual T peek() override
			{
				throw std::runtime_error("stream is not readable.");
			}
			virtual std::size_t peek(T* buffer, std::size_t count) override
			{
				throw std::runtime_error("stream is not readable.");
			}
			virtual void skip() override
			{
				throw std::runtime_error("stream is not readable.");
			}
			virtual void skip(std::size_t count) override
			{
				throw std::runtime_error("stream is not readable.");
			}
		};
	}
}

#endif // !VOCALSTUDIO_STREAM_OUTPUTSTREAM_H
