#pragma once

////////////////////////////////////////////////////////////////////////////////
// The MIT License (MIT)
//
// Copyright (c) 2017 Nicholas Frechette & Animation Compression Library contributors
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#include "acl/core/compiler_utils.h"
#include "acl/core/iallocator.h"
#include "acl/core/error.h"

#include <memory>

ACL_IMPL_FILE_PRAGMA_PUSH

namespace acl
{
	//////////////////////////////////////////////////////////////////////////
	// A basic string class that uses our custom allocator.
	// It is used exclusively for debug purposes.
	//
	// Strings are immutable.
	//////////////////////////////////////////////////////////////////////////
	class String
	{
	public:
		String() : m_allocator(nullptr), m_c_str(nullptr) {}

		String(IAllocator& allocator, const char* c_str, size_t length)
			: m_allocator(&allocator)
		{
			if (length > 0)
			{
#if defined(ACL_HAS_ASSERT_CHECKS) && !defined(NDEBUG)
				for (size_t i = 0; i < length; ++i)
					ACL_ASSERT(c_str[i] != '\0', "String cannot contain NULL terminators");
#endif

				m_c_str = allocate_type_array<char>(allocator, length + 1);
				std::memcpy(m_c_str, c_str, length);
				m_c_str[length] = '\0';
			}
			else
			{
				m_c_str = nullptr;
			}
		}

		String(IAllocator& allocator, const char* c_str)
			: String(allocator, c_str, c_str != nullptr ? std::strlen(c_str) : 0)
		{}

		String(IAllocator& allocator, const String& str)
			: String(allocator, str.c_str(), str.size())
		{}

		~String()
		{
			if (m_allocator != nullptr && m_c_str != nullptr)
				deallocate_type_array(*m_allocator, m_c_str, std::strlen(m_c_str) + 1);
		}

		String(String&& other)
			: m_allocator(other.m_allocator)
			, m_c_str(other.m_c_str)
		{
			new(&other) String();
		}

		String& operator=(String&& other)
		{
			std::swap(m_allocator, other.m_allocator);
			std::swap(m_c_str, other.m_c_str);
			return *this;
		}

		bool operator==(const char* c_str) const
		{
			const size_t this_length = m_c_str == nullptr ? 0 : std::strlen(m_c_str);
			const size_t other_length = c_str == nullptr ? 0 : std::strlen(c_str);
			if (this_length != other_length)
				return false;

			if (this_length == 0)
				return true;

			return std::memcmp(m_c_str, c_str, other_length) == 0;
		}

		bool operator!=(const char* c_str) const { return !(*this == c_str); }

		bool operator==(const String& other) const { return (*this == other.c_str()); }
		bool operator!=(const String& other) const { return !(*this == other.c_str()); }

		const char* c_str() const { return m_c_str != nullptr ? m_c_str : ""; }
		size_t size() const { return m_c_str != nullptr ? std::strlen(m_c_str) : 0; }
		bool empty() const { return m_c_str != nullptr ? (std::strlen(m_c_str) == 0) : true; }

	private:
		IAllocator* m_allocator;
		char* m_c_str;
	};
}

ACL_IMPL_FILE_PRAGMA_POP
