#pragma once
#ifndef RAPIDPARSER_FILEUNIQUEID
#define RAPIDPARSER_FILEUNIQUEID
#include<cinttypes>
namespace rpr
{
	namespace vfs
	{
		/// <summary>
		/// The class specifics a unique file.
		/// </summary>
		class FileUniqueID
		{
		private:
			uint64_t  device;
			uint64_t file;
		public:
			/// <summary>
			/// Initializes a new instance of the <see cref="FileUniqueID"/> class.
			/// </summary>
			FileUniqueID() = default;
			/// <summary>
			/// Initializes a new instance of the <see cref="FileUniqueID"/> class.
			/// </summary>
			/// <param name="device">The device.</param>
			/// <param name="file">The file.</param>
			FileUniqueID(uint64_t  device, uint64_t file) :device(device), file(file) {}
		public:
			/// <summary>
			/// Gets the file.
			/// </summary>
			/// <returns></returns>
			uint64_t getFile() { return file; }
			/// <summary>
			/// Gets the device.
			/// </summary>
			/// <returns></returns>
			uint64_t getDevice() { return device; }
			/// <summary>
			/// Operator=s the specified other.
			/// </summary>
			/// <param name="other">The other.</param>
			/// <returns></returns>
			bool operator = (FileUniqueID & other)const { return this->device == other.device&&this->file == other.file; }
			/// <summary>
			/// Operator!=s the specified other.
			/// </summary>
			/// <param name="other">The other.</param>
			/// <returns></returns>
			bool operator != (FileUniqueID & other)const { return this->device != other.device || this->file != other.file; }
		};
	}
}

#endif // !RAPIDPARSER_FILEUNIQUEID
