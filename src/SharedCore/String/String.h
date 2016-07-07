// Copyright (C) 2016 by DVO Games

#pragma once

class String
{
public:
	typedef char			CharType;
protected:
	CharType			*m_data;

public:
						String(void)
		: m_data(nullptr)
	{
	}

						String(const CharType *const string)
		: m_data(const_cast<CharType *>(string))
	{
	}

						String(const String& string)
	{
		(*this) = string;
	}

	virtual				~String(void)
	{
		m_data = nullptr;
	}

	// Find first string occurence.
	unsigned		FindFirst(const CharType *const str, const unsigned begin = 0) const
	{
		ASSERT(begin < Length());
		unsigned index = Nil();

		const CharType *const ptr = StrStr(m_data + begin, str);
		if(ptr) {
			index = static_cast<unsigned>(ptr - m_data);
		}
		return index;
	}

	// Find last string occurence.
	unsigned		FindLast(const CharType *const str) const
	{
		unsigned index =  Nil();

		const CharType *ptr = nullptr;
		do
		{
			const unsigned offset (IsNil(index) ? 0 : index);
			ptr = StrStr(m_data + offset, str);
			if(ptr) {
				index = static_cast<unsigned>(ptr - m_data);
			}
		} while(ptr != nullptr);

		return index;
	}

	// Find first character occurence.
	unsigned		FindFirst(const CharType c, const unsigned begin = 0) const
	{
		ASSERT(begin < Length());
		unsigned index = Nil();

		const CharType *const ptr = StrChr(m_data + begin, c);
		if(ptr) {
			index = static_cast<unsigned>(ptr - m_data);
		}
		return index;
	}

	// Find last character occurence.
	unsigned		FindLast(const CharType c) const
	{
		unsigned index = Nil();

		const CharType *const ptr = StrRChr(m_data, c);
		if(ptr) {
			index = static_cast<unsigned>(ptr - m_data);
		}
		return index;
	}

	//! Get char at index.
	CharType		CharAt(const unsigned index) const
	{
		ASSERT(index < Length());
		return m_data[index];
	}

	//! Get char at index (variant allowing negative indexes).
	CharType		CharAt(const int index) const
	{
		unsigned finalIndex = Nil();

		if (index < 0) {
			finalIndex = static_cast<unsigned>(Length() + index);
		}
		else {
			finalIndex = static_cast<unsigned>(index);
		}

		ASSERT(NotNil(finalIndex) && (finalIndex < Length()));
		return m_data[finalIndex];
	}

	//! Get char at index.
	CharType		operator[](const unsigned index) const
	{
		return CharAt(index);
	}

	//! Get char at index (variant allowing negative indexes).
	CharType		operator[](const int index) const
	{
		return CharAt(index);
	}

	//! Get length of string.
	unsigned		Length(void) const
	{
		ASSERT(m_data);
		return StrLen(m_data);
	}

	/**
	 * Calculate capped length of the string.
	 *
	 * In case string is longer than @a limit then calculation opeartion stops
	 * and it returns @a limit.
	 *
	 * @return Length of the string. (Up to @a limit value)
	 */
	unsigned		LengthLimited(const unsigned limit) const
	{
		ASSERT(m_data);
		return StrNLen(m_data, limit);
	}

	/**
	 * Compares two strings.
	 *
	 * @param[in] str The string to compare.
	 * @return 0  in case strings are equal
	 *         -1 in case this is greater
	 *         1  in case str is greater
	 */
	int				Compare(const CharType *const str) const
	{
		return StrCmp(m_data, str);
	}

	//! Check if strings are equal.
	bool			Equals(const CharType *const str) const
	{
		return !StrCmp(m_data, str);
	}

	//! Check if two strings are equal.
	bool			operator==(const CharType *const str) const
	{
		return Equals(str);
	}

	//! Check if two strings are not equal.
	bool			operator!=(const CharType *const str) const
	{
		return !Equals(str);
	}

	//! Check if string is empty.
	bool			IsEmpty(void) const
	{
		ASSERT(m_data);
		return *m_data == 0;
	}

	//! Check if string is not empty.
	bool			NotEmpty(void) const
	{
		ASSERT(m_data);
		return *m_data != 0;
	}

	//! Check if string ends with string.
	bool			EndsWith(const CharType *const str) const
	{
		const unsigned strLen = StrLen(str);
		const unsigned len = Length();

		if (strLen > len) return false;

		return !StrCmp(m_data + (len - strLen), str);
	}

	//! Check if string ends with string.
	bool			StartsWith(const CharType *const str) const
	{
		const unsigned strLen = StrLen(str);
		const unsigned len = Length();

		if (strLen > len) return false;

		return !StrNCmp(m_data, str, strLen);
	}

	//! Get plain string representation.
	const CharType*		Data(void) const		{ ASSERT(m_data); return m_data; }
	operator const CharType *(void) const		{ ASSERT(m_data); return m_data; }
	const CharType * operator*(void) const		{ ASSERT(m_data); return m_data; }

	/**
	 * Return modifiable data pointer.
	 *
	 * Use this method only if you are 100% sure you know what you are doing
	 * and you have enough space to operate with.
	 */
	CharType*			Data(void)
	{
		ASSERT(m_data);
		return m_data;
	}

	/** Copy-assignment operator */
	String& operator=(const String& rhs)
	{
		m_data = rhs.m_data;
		return *this;
	}

};

template <class ALLOCATOR = template DynamicHeapAllocator<char> >
class ManagedString : public String
{
public:
	typedef ALLOCATOR		AllocatorType;
	
private:
	AllocatorType		m_allocator;
public:
	// Default constructor.
						ManagedString(void)
	{
		m_data = m_allocator.Alloc(1);
		m_data[0] = '\0';
	}

	// Copy constructor.
						ManagedString(const ManagedString &str)
	{
		*this = str;
	}

	// Move constructor.
						ManagedString(ManagedString &&str)
	{
		*this = str;
	}

	// C-String conversion constructor.
						ManagedString(const CharType *const str)
	{
		const unsigned stringLength = StrLen(str);
		m_data = m_allocator.Alloc(stringLength + 1);
		StrCpy(m_data, str);
		m_data[stringLength] = '\0';
	}

	//! Destructor.
						~ManagedString(void)
	{
		m_data = nullptr;
		m_allocator.Free();
	}

	//! Append string.
	void				Append(const CharType *const str)
	{
		const unsigned newSize = StrLen(m_data) + StrLen(str) + 1;
		if (newSize > m_allocator.GetBytesSize()) {
			// It is not possible to reallocate static allocator.
			ASSERT(m_allocator.IsDynamic());

			// Make copy of current data.
			AllocatorType allocator;
			CharType *data = allocator.Alloc(m_allocator.GetSize());
			StrCpy(data, m_data);

			// Allocate new data

			m_data = m_allocator.Realloc(newSize);

			StrCpy(m_data, data);
			allocator.Free();
		}

		StrCat(m_data, str);
	}

	/**
	 * Append string. Safe variant.
	 *
	 * This method will not fail in case there will be no way to allocate
	 * enough memory to fit the appended string. It will just return false.
	 *
	 * @param[in] str String to append.
	 * @return @c true if operation succeeds @c false if there is not enough space for the string.
	 */
	bool				AppendSafe(const CharType *const str)
	{
		const unsigned newSize = StrLen(m_data) + StrLen(str) + 1;
		if ((newSize > m_allocator.GetBytesSize()) && (! m_allocator.IsDynamic())) {
			return false;
		}

		Append(str);
		return true;
	}

	//! Append character.
	void				Append(const CharType c)
	{
		const CharType tmpBuffer[2] = { c, 0 };
		Append(tmpBuffer);
	}

	//! Append string.
	ManagedString&		operator+(const CharType *const str)
	{
		Append(str);
		return *this;
	}

	//! Append number.
	ManagedString&		operator+(const unsigned number)
	{
		ManagedString strNumber;
		strNumber.Format("%u", number);
		Append(strNumber);
		return *this;
	}

	//! Append number.
	ManagedString&		operator+(const int number)
	{
		ManagedString strNumber;
		strNumber.Format("%d", number);
		Append(strNumber);
		return *this;
	}

	//! Append string.
	ManagedString&		operator+=(const CharType *const str)
	{
		Append(str);
		return *this;
	}

	//! Append number.
	ManagedString&		operator+(const float number)
	{
		ManagedString strNumber;
		strNumber.Format("%f", number);
		Append(strNumber);
		return *this;
	}

	//! Append number.
	ManagedString&		operator+(const double number)
	{
		ManagedString strNumber;
		strNumber.Format("%f", number);
		Append(strNumber);
		return *this;
	}

	// Sub string.
	void			SubStr(const String& source, const unsigned start, const unsigned end = Nil())
	{
		ASSERT(start < end);
		ASSERT(start < source.Length());
		ASSERT(IsNil(end) || (end < source.Length()));

		const CharType *const dataToCopy = source.Data() + start;
		unsigned dataToCopyLen = 0;
		if (IsNil(end)) {
			dataToCopyLen = source.Length();
		}
		else {
			dataToCopyLen = end - start;
		}

		m_data = m_allocator.Realloc(dataToCopyLen + 1);
		StrNCpy(m_data, dataToCopy, dataToCopyLen);
		m_data[dataToCopyLen] = '\0';
	}

	/**
	 * Cut string at given index.
	 *
	 * @note in case index is greater than length this method has no effect.
	 */
	void			CutAt(const unsigned index)
	{
		ASSERT(index < m_allocator.GetSize());
		m_data[index] = static_cast<CharType>(0);
	}

	//! Get string storage capacity.
	byte			Capacity(void) const
	{
		return m_allocator.GetBytesSize();
	}

	//! Clear string content.
	void			Clear(void)
	{
		ASSERT(m_data);
		memset(m_data, 0, m_allocator.GetBytesSize());
	}

	/**
	 * Replace token with given value.
	 *
	 * @param[out] out The place where to store replaced string (should be empty)
	 * @param[in] what What to replace.
	 * @param[in] with Content to be put when what is found.
	 * @return Number of replaced tokens.
	 */
	unsigned		Replace(ManagedString& out, const CharType* const what, const CharType* const with) const
	{
		const unsigned whatLength = StrLen(what);

		const unsigned currentStringLength = Length();
		if (whatLength > currentStringLength) {
			return 0;
		}

		unsigned replacedTokens = 0;

		for (unsigned i = 0; i < Length();) {
			if (!StrNCmp(m_data + i, what, whatLength)) {
				// NOTE: We take care about eventual buffer overflows in allocators
				// ifself so no check is needed here.

				out.Append(with);

				i += whatLength;
				++ replacedTokens;
				continue;
			}

			out.Append(m_data[i]);
			++i;
		}
		return replacedTokens;
	}

	/**
	 * Replace token with given value - stores the value inside this string.
	 *
	 * @param[in] what What to replace.
	 * @param[in] with Content to be put when what is found.
	 * @return Number of replaced tokens.
	 */
	unsigned		Replace(const CharType* const what, const CharType* const with)
	{
		ManagedString tmp;
		const unsigned replacedTokens = Replace(tmp, what, with);

		// Set value of current string 
		if (replacedTokens > 0) {
			(*this) = tmp;
		}
		return replacedTokens;
	}

	//! Copy operator.
	ManagedString&	operator=(const ManagedString& rhs)
	{
		const unsigned stringLength = rhs.Length();
		m_data = m_allocator.Realloc(stringLength + 1);
		StrCpy(m_data, rhs.m_data);
		m_data[stringLength] = '\0';
		return *this;
	}

	//! Copy operator.
	ManagedString&	operator=(const String& rhs)
	{
		const unsigned stringLength = rhs.Length();
		m_data = m_allocator.Realloc(stringLength + 1);
		StrCpy(m_data, rhs.m_data);
		m_data[stringLength] = '\0';
		return *this;
	}

	/*! Move operator.

		Broken when string is allocated on stack!

	ManagedString&	operator=(ManagedString&& rhs)
	{
		m_allocator.Free();

		m_data = std::move(rhs.m_data);
		m_allocator = std::move(rhs.m_allocator);
		return *this;
	}*/

	//! Move operator.
	ManagedString&	operator=(const CharType* const data)
	{
		const unsigned stringLength = StrLen(data);
		m_data = m_allocator.Realloc(stringLength + 1);
		StrCpy(m_data, data);
		m_data[stringLength] = '\0';
		rhs.Clear();
		return *this;
	}

	//! Format string.
	void Format(const CharType *const buffer, ...)
	{
		va_list args;
		va_start(args, buffer);
		const int desiredBufferSize = VSCPrintF(buffer, args);
		m_data = m_allocator.Realloc(desiredBufferSize + 1);
		SPrintF(m_data, buffer, args);
		m_data[desiredBufferSize] = '\0';
		va_end(args);
	}

	//! Is string dynamic.
	bool IsDynamic(void) const
	{
		return m_allocator.IsDynamic();
	}

	/**
	 * Enlarge buffer size.
	 *
	 * @param[in] newCapacity The capacity to be allocated.
	 * @return @c true if allocation success @c false otherwise.
	 */
	bool Enlarge(const unsigned newCapacity)
	{
		if (newCapacity == m_allocator.GetBytesSize()) {
			return true;
		}

		if (!m_allocator.IsDynamic()) {
			return false;
		}

		AllocatorType allocator;
		const unsigned oldSize = m_allocator.GetSize();
		CharType *data = allocator.Alloc(m_allocator.GetSize());
		StrCpy(data, m_data);

		// Allocate new data

		m_data = m_allocator.Realloc(newCapacity);
		if (!m_data) {
			m_data = m_allocator.Realloc(oldSize);

			// In case the data is still not allocated correctly we are screwed up
			// as the string is no longer useable.
			//
			// At the moment in release build the assert is stripped out from the
			// code so it will simply crash at the StrCpy bellow.
			ASSERT(m_data);

			StrCpy(m_data, data);
			return false;
		}

		StrCpy(m_data, data);
		allocator.Free();
		return true;
	}
};

//! Standard string to managed string add operator.
template <typename ALLOCATOR>
static ManagedString<ALLOCATOR> operator+(const char *const a, const ManagedString<ALLOCATOR>& b)
{
	ManagedString<ALLOCATOR> result(a);
	result.Append(b);
	return result;
}

//! Char type independent Fixed-size string
template <unsigned SIZE>
class FixedString : public ManagedString<FixedAllocator<char, SIZE> >
{
	using ManagedString::ManagedString;
};

//! ANSI Fixed-size string
template <unsigned SIZE>
class AFixedString : public ManagedString<FixedAllocator<char, SIZE> >
{
	using ManagedString::ManagedString;
};

//! ANSI dynamic string
class AString : public ManagedString<DynamicHeapAllocator<char> >
{
	using ManagedString::ManagedString;
};

/* EOF */
