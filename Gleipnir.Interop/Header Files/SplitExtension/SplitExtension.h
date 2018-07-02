#pragma once

#define KEEP_EMPTY_ENTRIES						_KeepEmptyEntries
#define OMIT_EMPTY_ENTRIES						_OmitEmptyEntries

#define EXCLUDE_FOLLOWING						_ExcludeFollowing
#define INCLUDE_SINGLE_FOLLOWING				_IncludeSingleFollowing
#define INCLUDE_ALL_FOLLOWING					_IncludeAllFollowing

#define EXCLUDE_TRAILING						_ExcludeTrailing
#define INCLUDE_SINGLE_TRAILING					_IncludeSingleTrailing
#define INCLUDE_ALL_TRAILING					_IncludeAllTrailing

#define COUNT_ENTRIES							_countEntries
#define SEEK_DELIMITERS							_seekDelimiters

/* Only two functions use these. */
#define INCLUDE_SINGLE_TRAILING_GREEDY			_IncludeSingleTrailing_Greedy
#define INCLUDE_SINGLE_FOLLOWING_GREEDY			_IncludeSingleFollowing_Greedy

#define SPLIT_EXTENSION_FUNCTION_PREFIX			_splitExtension_Internal
#define SPLIT_EXTENSION_TRACK_FUNCTION_PREFIX	_splitExtensionTrack_Internal
#define ALLOCATOR_NAME							_fastAllocate

#define STRING_ARRAY							StringArray
#define CHAR_ARRAY								CharArray
#define JAGGED_STRING_ARRAY						JaggedStringArray

#define SPLIT_EXTENSION_DECLARATION_ARGS \
	( \
	_wordEntry * dictionary, \
	split_extension_char* calculation, \
	split_extension_int   calculation_length, \
	split_extension_char* delimiter_begin, \
	split_extension_int   delimiter_length \
	)

#define SPLIT_EXTENSION_INTERNAL_DECLARATION_ARGS \
	( \
	split_extension_char* calculation, \
	split_extension_int   calculation_length, \
	split_extension_char* delimiter_begin, \
	split_extension_int   delimiter_length \
	)

#define __GLEIPNIR_C_FUNCTION_DECLARATION_NAME_(A,B,C,D) A##B##C##D
#define __GLEIPNIR_CLR_ALLOCATOR_DECLARATION_NAME_(A,B) A##B
#define __GLEIPNIR_CLR_ALLOCATOR_DECLARATION_NAME(A,B) __GLEIPNIR_CLR_ALLOCATOR_DECLARATION_NAME_(A,B)

#define SPLIT_EXTENSION_FUNCTION_DECLARE(FUNCTION, FOLLOWING_OPT, TRAILING_OPT, KEEP_OMIT) __GLEIPNIR_C_FUNCTION_DECLARATION_NAME_(FUNCTION, FOLLOWING_OPT, TRAILING_OPT, KEEP_OMIT) SPLIT_EXTENSION_DECLARATION_ARGS
#define SPLIT_EXTENSION_INTERNAL_FUNCTION_DECLARE(FUNCTION, FOLLOWING_OPT, TRAILING_OPT, KEEP_OMIT) __GLEIPNIR_C_FUNCTION_DECLARATION_NAME_(FUNCTION, FOLLOWING_OPT, TRAILING_OPT, KEEP_OMIT) SPLIT_EXTENSION_INTERNAL_DECLARATION_ARGS

#define COUNT_ENTRY_DECLARATION() SPLIT_EXTENSION_INTERNAL_FUNCTION_DECLARE(split_extension_int SPLIT_EXTENSION_CALL_TYPE COUNT_ENTRIES, OPT_FOLLOWING, OPT_TRAILING, OPT_ENTRIES) noexcept
#define SEEK_DELIMITER_DECLARATION() SPLIT_EXTENSION_FUNCTION_DECLARE(_wordEntry* SPLIT_EXTENSION_CALL_TYPE SEEK_DELIMITERS, OPT_FOLLOWING, OPT_TRAILING, OPT_ENTRIES) noexcept

#define COUNT_ENTRY_HEADER_DECLARATION(FUNCTION, FOLLOWING_OPT, TRAILING_OPT, KEEP_OMIT) SPLIT_EXTENSION_INTERNAL_FUNCTION_DECLARE(split_extension_int SPLIT_EXTENSION_CALL_TYPE COUNT_ENTRIES, FOLLOWING_OPT, TRAILING_OPT, KEEP_OMIT) noexcept
#define SEEK_DELIMITER_HEADER_DECLARATION(FUNCTION, FOLLOWING_OPT, TRAILING_OPT, KEEP_OMIT) SPLIT_EXTENSION_FUNCTION_DECLARE(_wordEntry* SPLIT_EXTENSION_CALL_TYPE SEEK_DELIMITERS, FOLLOWING_OPT, TRAILING_OPT, KEEP_OMIT) noexcept

#define __SPLIT_EXTENSION_CLR_FUNCTION(FUNCTION, FOLLOWING_OPT, TRAILING_OPT, KEEP_OMIT) __GLEIPNIR_C_FUNCTION_DECLARATION_NAME_(FUNCTION, FOLLOWING_OPT, TRAILING_OPT, KEEP_OMIT)
#define SPLIT_EXTENSION_CLR_FUNCTION(FOLLOWING_OPT,TRAILING_OPT,KEEP_OMIT, MEMSET) \
	{ \
	array_size = __SPLIT_EXTENSION_CLR_FUNCTION(COUNT_ENTRIES, FOLLOWING_OPT, TRAILING_OPT, KEEP_OMIT)(calculation, data->Length, delimiter_begin, delimiters->Length); \
	MALLOC_METHOD \
	if (!dictionary) \
		return nullptr; \
	MEMSET	\
	__SPLIT_EXTENSION_CLR_FUNCTION(SEEK_DELIMITERS, FOLLOWING_OPT, TRAILING_OPT, KEEP_OMIT)(dictionary, calculation, data->Length, delimiter_begin, delimiters->Length); \
	goto MemAlloc; \
	}


/* You can change these options for more optimal results, they affect every function globally. */
// Testing shows __cdecl to be faster than __stdcall, and __fastcall for me.
#define SPLIT_EXTENSION_CALL_TYPE __cdecl

typedef const wchar_t	split_extension_char; //Keep this wide, as wchar is 2 bytes and char is 1 byte.
typedef int				split_extension_int;  //This can be set to anything your platform supports, it's an arbitrary choice.  It does have some performance impact.

const struct _wordEntry
{
	split_extension_char* _wordBegin;
	split_extension_int _length;
	int pad;
};
