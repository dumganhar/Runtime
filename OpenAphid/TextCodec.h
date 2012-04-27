/*
Copyright 2012 Aphid Mobile

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
 
   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

 */

/*
 * Copyright (C) 2004, 2006 Apple Computer, Inc.  All rights reserved.
 * Copyright (C) 2006 Alexey Proskuryakov <ap@nypop.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#ifndef OpenAphid_TextCodec_h
#define OpenAphid_TextCodec_h

#include <memory>
#include <wtf/Noncopyable.h>
#include <wtf/PassOwnPtr.h>
#include <wtf/Vector.h>
#include <wtf/unicode/Unicode.h>
#include <wtf/text/WTFString.h>

namespace Aphid {
	class TextEncoding;
	
	// Specifies what will happen when a character is encountered that is
	// not encodable in the character set.
	enum UnencodableHandling {
		// Substitutes the replacement character "?".
		QuestionMarksForUnencodables,
		
		// Encodes the character as an XML entity. For example, U+06DE
		// would be "&#1758;" (0x6DE = 1758 in octal).
		EntitiesForUnencodables,
		
		// Encodes the character as en entity as above, but escaped
		// non-alphanumeric characters. This is used in URLs.
		// For example, U+6DE would be "%26%231758%3B".
		URLEncodedEntitiesForUnencodables,
	};
	
	typedef char UnencodableReplacementArray[32];
	
	class TextCodec : public Noncopyable {
	public:
		virtual ~TextCodec();
		
		Aphid::String decode(const char* str, size_t length, bool flush = false)
		{
			bool ignored;
			return decode(str, length, flush, false, ignored);
		}
		
		virtual Aphid::String decode(const char*, size_t length, bool flush, bool stopOnError, bool& sawError) = 0;
		virtual ATF::CString encode(const UChar*, size_t length, UnencodableHandling) = 0;
		
		// Fills a null-terminated string representation of the given
		// unencodable character into the given replacement buffer. 
		// The length of the string (not including the null) will be returned.
		static int getUnencodableReplacement(unsigned codePoint, UnencodableHandling, UnencodableReplacementArray);
	};
	
	typedef void (*EncodingNameRegistrar)(const char* alias, const char* name);
	
	typedef PassOwnPtr<TextCodec> (*NewTextCodecFunction)(const TextEncoding&, const void* additionalData);
	typedef void (*TextCodecRegistrar)(const char* name, NewTextCodecFunction, const void* additionalData);
	
}

#endif
