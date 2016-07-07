// Copyright (C) 2016 by DVO Games

#pragma once

#include "AutoPtr.h"

#include "Types.h"
#include "Strings.h"
#include "Compare.h"

class File;

class TextFile : public File
{
private:
	friend class FileSystem;

			TextFile		(const PathString& filePath, const unsigned flags);
public:
	/**
	 * Write an C-string into the file.
	 *
	 * @pre The file must end with null terminator if it's not ending with null
	 *      terminator then the behaviour is unexpected.
	 *
	 * @param[in] string The string to be written.
	 * @return @c true if write success @c false otherwise.
	 */
	bool	Write			(const char *const string);

	/**
	 * Write an C-string into the file.
	 *
	 * @pre The file must end with null terminator if it's not ending with null
	 *      terminator then the behaviour is unexpected.
	 *
	 * @param[in] string The string to be written.
	 * @return @c true if write success @c false otherwise.
	 */
	bool	Write			(const wchar_t *const string);

	/**
	 * Read string from the file.
	 *
	 * @param[in/out] string The buffer where to store the read string.
	 * @param[in/out] length On input the size of the buffer given in @a string
	 *                       on output the length of read string.
	 * @return @c true if write success @c false otherwise.
	 */
	bool	Read			(char *const string, size_t& length) const;

	/**
	 * Read string from the file.
	 *
	 * @param[in/out] string The buffer where to store the read string.
	 * @param[in/out] length On input the size of the buffer given in @a string
	 *                       on output the length of read string.
	 * @return @c true if write success @c false otherwise.
	 */
	bool	Read			(wchar_t *const string, size_t& length) const;

	/**
	 * Write string to the file.
	 *
	 * @tparam STRING_CLASS The string class (must inherit from String)
	 * @param[in] string The string to be written.
	 * @return @c true if write success @c false otherwise.
	 */
	template <typename STRING_CLASS>
	bool	Write			(const STRING_CLASS& string);

	/**
	 * Read string from the file.
	 *
	 * The methods starts reading at the file current reading pos.
	 *
	 * In case there the string is too small to fit the whole content the reading
	 * stops. The method will return @c false no reading was performed at all.
	 *
	 * @tparam STRING_CLASS The string class (must inherit from String)
	 * @param[out] string The storage where string will be read.
	 * @return @c true if write success @c false otherwise.
	 */
	template <typename STRING_CLASS>
	bool	Read			(STRING_CLASS& string) const;

	/**
	 * Read string from the file.
	 *
	 * This variant allows reading specified length of the bytes.
	 *
	 * The methods starts reading at the file current reading pos.
	 *
	 * In case there the string is too small to fit the whole content the reading
	 * stops. The method will return @c false no reading was performed at all.
	 *
	 * @tparam STRING_CLASS The string class (must inherit from String)
	 * @param[out] string The storage where string will be read.
	 * @param[in] maxLength The maximum length of the string to be read.
	 * @return @c true if write success @c false otherwise.
	 */
	template <typename STRING_CLASS>
	bool	Read			(STRING_CLASS& string, const size_t maxLength) const;
};

template <typename STRING_CLASS>
bool TextFile::Write(const STRING_CLASS& string)
{
	return Write(string.Data());
}

template <typename STRING_CLASS>
bool TextFile::Read(STRING_CLASS& string) const
{
	static const size_t CHUNK_SIZE = 128;
	size_t length = CHUNK_SIZE;
	typename STRING_CLASS::CharType chunk[CHUNK_SIZE] = { 0 };
	bool success = false;
	while (Read(chunk, length)) {
		ASSERT(length < CHUNK_SIZE);
		chunk[length] = '\0';
		length = CHUNK_SIZE;

		// In case the string would not fit definitely prepare shorter version.
		if ((! string.IsDynamic()) && ((string.Length() + strlen(chunk) + 1) >= string.Capacity())) {
			const unsigned spaceLeft = Min<unsigned>(string.Capacity() - string.Length(), CHUNK_SIZE - 1);
			chunk[spaceLeft - 1] = '\0';
		}

		if (!string.AppendSafe(chunk)) {
			// We don't have space anymore.
			break;
		}

		success = true;
		MemSet(chunk, 0, sizeof(chunk));
	}
	return success;
}

template <typename STRING_CLASS>
bool TextFile::Read(STRING_CLASS& string, const size_t maxLength) const
{
	if (!string.Enlarge(static_cast<unsigned>(maxLength))) {
		return false;
	}

	char *const data =string.Data();
	if(!data) {
		return false;
	}

	size_t length = maxLength;
	if (Read(data, length)) {
		ASSERT(length < string.Capacity());
		data[length] = '\0';
		return true;
	}
	return false;
}

using TextFilePtr = AutoPtr<TextFile>;

/* eof */
