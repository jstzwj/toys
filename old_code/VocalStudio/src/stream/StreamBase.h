#pragma once
#ifndef VOCALSTUDIO_STREAM_STREAMBASE_H
#define VOCALSTUDIO_STREAM_STREAMBASE_H

#include<exception>
#include<cstdint>

namespace vocal_studio
{
	namespace stream
	{

#define TOCHAR(x) (reinterpret_cast<char *>(std::addressof(x)))

		class StreamTraits
		{
		public:
			enum class PosType { Begin, Current, End };
		};

		template <typename T, typename Traits>
		class StreamBase
		{
		public:
			using CharType = T;
			using PosType = typename Traits::PosType;
			virtual ~StreamBase() = default;
			//read virtual function
			virtual bool isReadable() const = 0;
			virtual T read() = 0;
			virtual std::size_t read(T* buffer, std::size_t count) = 0;

			virtual T peek() { throw std::runtime_error("peeking is not allowed."); }
			virtual std::size_t peek(T* buffer, std::size_t count) { throw std::runtime_error("peeking is not allowed"); }

			virtual void skip() = 0;
			virtual void skip(std::size_t count) = 0;

			//write virtual function
			virtual bool isWriteable() const = 0;
			virtual void write(T value) = 0;
			virtual void write(const T* buffer, std::size_t count) = 0;

			//buffer virtual function
			virtual void flush() = 0;

			//seek virtual function
			virtual bool isSeekable() const = 0;
			virtual std::intmax_t seek(std::intmax_t offset, PosType method) = 0;

			virtual std::intmax_t getPosition() = 0;
		};
	}
}


#endif //VOCALSTUDIO_STREAM_STREAMBASE_H