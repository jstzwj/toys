#pragma once
#ifndef RAPIDPARSER_STATUS
#define RAPIDPARSER_STATUS

#include<string>
#include<cinttypes>
#include<cctype>

#include"FileUniqueID.h"
namespace rpr
{
	namespace vfs
	{
		class Status
		{
		public:
			/// <summary>
			/// Initializes a new instance of the <see cref="Status"/> class.
			/// </summary>
			Status();

			Status(std::string Name, FileUniqueID UID, llvm::sys::TimeValue MTime, uint32_t User, uint32_t Group, uint64_t Size, llvm::sys::fs::file_type Type, llvm::sys::fs::perms Perms);

			/// <summary>
			/// Gets the name.
			/// </summary>
			/// <returns>
			///The name of the file.
			///</returns>
			std::string 	getName() const;

			llvm::sys::fs::file_type 	getType() const;

			llvm::sys::fs::perms 	getPermissions() const;

			llvm::sys::TimeValue 	getLastModificationTime() const;

			llvm::sys::fs::UniqueID 	getUniqueID() const;

			/// <summary>
			/// Gets the user.
			/// </summary>
			/// <returns></returns>
			uint32_t 	getUser() const;

			/// <summary>
			/// Gets the group.
			/// </summary>
			/// <returns></returns>
			uint32_t 	getGroup() const;

			/// <summary>
			/// Gets the size.
			/// </summary>
			/// <returns></returns>
			uint64_t 	getSize() const;

			bool 	equivalent(const Status &Other) const;

			/// <summary>
			/// Determines whether this instance is directory.
			/// </summary>
			/// <returns></returns>
			bool 	isDirectory() const;

			/// <summary>
			/// Determines whether [is regular file].
			/// </summary>
			/// <returns></returns>
			bool 	isRegularFile() const;

			/// <summary>
			/// Determines whether this instance is other.
			/// </summary>
			/// <returns></returns>
			bool 	isOther() const;

			/// <summary>
			/// Determines whether this instance is symlink.
			/// </summary>
			/// <returns></returns>
			bool 	isSymlink() const;

			/// <summary>
			/// Determines whether [is status known].
			/// </summary>
			/// <returns></returns>
			bool 	isStatusKnown() const;

			/// <summary>
			/// Determines whether this file is exists.
			/// </summary>
			/// <returns></returns>
			bool 	exists() const;

			static Status 	copyWithNewName(const Status &In, std::string NewName);

			static Status 	copyWithNewName(const llvm::sys::fs::file_status &In, std::string NewName);

			bool 	IsVFSMapped;
		};
	}
}

#endif // !RAPIDPARSER_STATUS
