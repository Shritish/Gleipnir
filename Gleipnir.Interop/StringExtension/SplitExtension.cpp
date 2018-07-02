//#pragma unmanaged
#include "stdafx.h"
#include <atlstr.h>
#include "Gleipnir.Interop.h"

using namespace System;
using namespace System::Runtime::CompilerServices;

// So, internally this is sealed, this just unseals it to generate proper metadata.
namespace System::Runtime::CompilerServices
{
	/// <summary>
	/// Indicates that a method is an extension method, or that a class or assembly contains extension methods.
	/// </summary>
	[AttributeUsage(AttributeTargets::Method | AttributeTargets::Class | AttributeTargets::Assembly)]
	ref struct ExtensionAttribute : public Attribute { };
}

namespace Gleipnir
{
	[assembly:System::CLSCompliant(true)];

	/// <summary>
	/// List of options for including or excluding trailing or following characters.
	/// </summary>
	public enum class Options
	{
		/// <summary>
		/// Exclude trailing or following characters.
		/// </summary>
		Exclude,
		/// <summary>
		/// Include trailing or following characters.
		/// </summary>
		IncludeSingle,
		/// <summary>
		/// Include all trailing or following characters.
		/// </summary>
		IncludeAll,
	};

	/// <summary>
	/// Specifies whether to be greedy with following or trailing when calculating both following_option.IncludeSingle and trailing_option.IncludeSingle.
	/// </summary>
	public enum class StringExtGreed
	{
		/// <summary>
		/// Be greedy with following delimiters, example: "\example\string\" will result in "\example" and "\string\"
		/// </summary>
		GreedyFollowing,
		/// <summary>
		/// Be greedy with trailing delimiters, example: "\example\string\" will result in "\example\" and "string\"
		/// </summary>
		GreedyTrailing
	};

	typedef array<array<String ^, 1> ^> JAGGED_STRING_ARRAY;
	typedef array<String ^, 1>			STRING_ARRAY;
	typedef array<const wchar_t, 1>		CHAR_ARRAY;

#define MALLOC_METHOD	dictionary = (struct _wordEntry *)_malloca(sizeof(struct _wordEntry) * array_size);
#define MEMSET_METHOD	memset(dictionary, 0 , sizeof(struct _wordEntry) * array_size);
#define MEMSET_NULL		/* Null */

	[Extension]
	public ref class Split abstract sealed
	{
	public:
		/// <summary>
		/// string[*] will contain the tokenized string.
		/// <para>This defaults to excluding all delimiters, not keeping empty entries, and GreedyFollowing.</para>
		/// </summary>
		/// <param name="data">The data to process.</param>
		/// <param name="delimiters">Character list of delimiters.</param>
		/// <returns>
		/// A jagged array of tokenized strings.
		/// </returns>
		/// <exception cref="NotSupportedException">
		/// StringExtension::Invalid Option Type.
		/// or
		/// StringExtension::Invalid Option Type.
		/// or
		/// There is no functionable logic that supports IncludeAll following delimiters, and IncludeAll trailing delimiters.
		/// or
		/// StringExtension::Invalid Option Type.
		/// or
		/// StringExtension::Invalid Option Type.
		/// </exception>
		[Extension]
		static inline STRING_ARRAY ^ SplitExtension(String ^ data, ... CHAR_ARRAY ^delimiters)
		{
			return SplitExtension(data, Options::Exclude, Options::Exclude, false, StringExtGreed::GreedyFollowing, delimiters);
		}
		/// <summary>
		/// string[*] will contain the tokenized string.
		/// <para>This defaults to excluding all delimiters, not keeping empty entries, and GreedyFollowing.</para>
		/// <para>This defaults to excluding all delimiters, and GreedyFollowing.</para>
		/// </summary>
		/// <param name="data">The data to process.</param>
		/// <param name="keep_empty_entries">If set to <c>true</c> keep empty entries as string.Empty.</param>
		/// <param name="delimiters">Character list of delimiters.</param>
		/// <returns>
		/// A jagged array of tokenized strings.
		/// </returns>
		/// <exception cref="NotSupportedException">
		/// StringExtension::Invalid Option Type.
		/// or
		/// StringExtension::Invalid Option Type.
		/// or
		/// There is no functionable logic that supports IncludeAll following delimiters, and IncludeAll trailing delimiters.
		/// or
		/// StringExtension::Invalid Option Type.
		/// or
		/// StringExtension::Invalid Option Type.
		/// </exception>
		[Extension]
		static inline STRING_ARRAY ^ SplitExtension(String ^ data, const bool keep_empty_entries, ... CHAR_ARRAY ^ delimiters)
		{
			return SplitExtension(data, Options::Exclude, Options::Exclude, keep_empty_entries, StringExtGreed::GreedyFollowing, delimiters);
		}
		/// <summary>
		/// string[*] will contain the tokenized string.
		/// <para>This defaults to excluding all delimiters, not keeping empty entries, and GreedyFollowing.</para>
		/// <para>This defaults to not keeping empty entries and GreedyFollowing.</para>
		/// </summary>
		/// <param name="data">The data to process.</param>
		/// <param name="following_option">Following Options::</param>
		/// <param name="trailing_option">Trailing Options::</param>
		/// <param name="delimiters">Character list of delimiters.</param>
		/// <returns>
		/// A jagged array of tokenized strings.
		/// </returns>
		/// <exception cref="NotSupportedException">
		/// StringExtension::Invalid Option Type.
		/// or
		/// StringExtension::Invalid Option Type.
		/// or
		/// There is no functionable logic that supports IncludeAll following delimiters, and IncludeAll trailing delimiters.
		/// or
		/// StringExtension::Invalid Option Type.
		/// or
		/// StringExtension::Invalid Option Type.
		/// </exception>
		[Extension]
		static inline STRING_ARRAY ^ SplitExtension(String ^ data, Options following_options, Options trailing_options, ... CHAR_ARRAY ^ delimiters)
		{
			return SplitExtension(data, following_options, trailing_options, false, StringExtGreed::GreedyFollowing, delimiters);
		}
		/// <summary>
		/// string[*] will contain the tokenized string.
		/// <para>This defaults to excluding all delimiters, not keeping empty entries, and GreedyFollowing.</para>
		/// <para>This defaults to not specifying greed.</para>
		/// </summary>
		/// <param name="data">The data to process.</param>
		/// <param name="following_option">Following Options::</param>
		/// <param name="trailing_option">Trailing Options::</param>
		/// <param name="keep_empty_entries">If set to <c>true</c> keep empty entries as string.Empty.</param>
		/// <param name="delimiters">Character list of delimiters.</param>
		/// <returns>
		/// A jagged array of tokenized strings.
		/// </returns>
		/// <exception cref="NotSupportedException">
		/// StringExtension::Invalid Option Type.
		/// or
		/// StringExtension::Invalid Option Type.
		/// or
		/// There is no functionable logic that supports IncludeAll following delimiters, and IncludeAll trailing delimiters.
		/// or
		/// StringExtension::Invalid Option Type.
		/// or
		/// StringExtension::Invalid Option Type.
		/// </exception>
		[Extension]
		static inline STRING_ARRAY ^ SplitExtension(String ^ data, Options following_options, Options trailing_options, const bool keep_empty_entries, ... CHAR_ARRAY ^ delimiters)
		{
			return SplitExtension(data, following_options, trailing_options, keep_empty_entries, StringExtGreed::GreedyFollowing, delimiters);
		}

		/// <summary>
		/// string[*] will contain the tokenized string.
		/// <para>This defaults to excluding all delimiters, not keeping empty entries, and GreedyFollowing.</para>
		/// </summary>
		/// <param name="data">The data to process.</param>
		/// <param name="following_option">Following Options::</param>
		/// <param name="trailing_option">Trailing Options::</param>
		/// <param name="keep_empty_entries">If set to <c>true</c> keep empty entries as string.Empty.</param>
		/// <param name="greed">Greedy Following, or Greedy Trailing.</param>
		/// <param name="delimiters">Character list of delimiters.</param>
		/// <returns>
		/// An array of tokenized strings.
		/// </returns>
		/// <exception cref="NotSupportedException">
		/// StringExtension::Invalid Option Type.
		/// or
		/// StringExtension::Invalid Option Type.
		/// or
		/// There is no functionable logic that supports IncludeAll following delimiters, and IncludeAll trailing delimiters.
		/// or
		/// StringExtension::Invalid Option Type.
		/// or
		/// StringExtension::Invalid Option Type.
		/// </exception>
		[Extension]
		static STRING_ARRAY ^ SplitExtension(
			String ^ data,
			Options following_option,
			Options trailing_option,
			const bool keep_empty_entries,
			StringExtGreed greed,
			... CHAR_ARRAY ^ delimiters)
		{
#if false
			if (delimiters->Length == 0)
				delimiters = whitespace;
#endif
			pin_ptr<const wchar_t> calculation = _PointerToString(data);
			pin_ptr<const wchar_t> delimiter_begin = &delimiters[0];

			split_extension_int array_size;
			_wordEntry* __restrict dictionary;
			_wordEntry* __restrict word;

			//size_t compute_size;

			STRING_ARRAY ^stringArray;
			interior_ptr<String ^> string_ptr;

			__try
			{
				switch (following_option)
				{
				case Options::Exclude:
					switch (trailing_option)
					{
					case Options::Exclude:
					{
						if (keep_empty_entries)
							SPLIT_EXTENSION_CLR_FUNCTION(EXCLUDE_FOLLOWING, EXCLUDE_TRAILING, KEEP_EMPTY_ENTRIES, MEMSET_METHOD)
						else
							SPLIT_EXTENSION_CLR_FUNCTION(EXCLUDE_FOLLOWING, EXCLUDE_TRAILING, OMIT_EMPTY_ENTRIES, MEMSET_NULL)
					}
					case Options::IncludeSingle:
					{
						if (keep_empty_entries)
							SPLIT_EXTENSION_CLR_FUNCTION(EXCLUDE_FOLLOWING, INCLUDE_SINGLE_TRAILING, KEEP_EMPTY_ENTRIES, MEMSET_METHOD)
						else
							SPLIT_EXTENSION_CLR_FUNCTION(EXCLUDE_FOLLOWING, INCLUDE_SINGLE_TRAILING, OMIT_EMPTY_ENTRIES, MEMSET_NULL)
					}
					case Options::IncludeAll:
					{
						if (keep_empty_entries)
							SPLIT_EXTENSION_CLR_FUNCTION(EXCLUDE_FOLLOWING, INCLUDE_ALL_TRAILING, KEEP_EMPTY_ENTRIES, MEMSET_METHOD)
						else
							SPLIT_EXTENSION_CLR_FUNCTION(EXCLUDE_FOLLOWING, INCLUDE_ALL_TRAILING, OMIT_EMPTY_ENTRIES, MEMSET_NULL)
					}
					default:
						throw (gcnew NotSupportedException("StringExtension::Invalid Option Type."));
					}
				case Options::IncludeSingle:
					switch (trailing_option)
					{
					case Options::Exclude:
					{
						if (keep_empty_entries)
							SPLIT_EXTENSION_CLR_FUNCTION(INCLUDE_SINGLE_FOLLOWING, EXCLUDE_TRAILING, KEEP_EMPTY_ENTRIES, MEMSET_METHOD)
						else
							SPLIT_EXTENSION_CLR_FUNCTION(INCLUDE_SINGLE_FOLLOWING, EXCLUDE_TRAILING, OMIT_EMPTY_ENTRIES, MEMSET_NULL)
					}
					case Options::IncludeSingle:
					{
						if (keep_empty_entries)
						{
							if (greed == StringExtGreed::GreedyTrailing)
								SPLIT_EXTENSION_CLR_FUNCTION(INCLUDE_SINGLE_FOLLOWING_GREEDY, INCLUDE_SINGLE_TRAILING, KEEP_EMPTY_ENTRIES, MEMSET_METHOD)
							else
								SPLIT_EXTENSION_CLR_FUNCTION(INCLUDE_SINGLE_FOLLOWING_GREEDY, INCLUDE_SINGLE_TRAILING, KEEP_EMPTY_ENTRIES, MEMSET_METHOD)
						}
						else
						{
							if (greed == StringExtGreed::GreedyTrailing)
								SPLIT_EXTENSION_CLR_FUNCTION(INCLUDE_SINGLE_FOLLOWING, INCLUDE_SINGLE_TRAILING_GREEDY, OMIT_EMPTY_ENTRIES, MEMSET_NULL)
							else
								SPLIT_EXTENSION_CLR_FUNCTION(INCLUDE_SINGLE_FOLLOWING, INCLUDE_SINGLE_TRAILING_GREEDY, OMIT_EMPTY_ENTRIES, MEMSET_NULL)
						}
					}
					case Options::IncludeAll:
					{
						if (keep_empty_entries)
							SPLIT_EXTENSION_CLR_FUNCTION(INCLUDE_SINGLE_FOLLOWING, INCLUDE_ALL_TRAILING, OMIT_EMPTY_ENTRIES, MEMSET_METHOD)
						else
							SPLIT_EXTENSION_CLR_FUNCTION(INCLUDE_SINGLE_FOLLOWING, INCLUDE_ALL_TRAILING, OMIT_EMPTY_ENTRIES, MEMSET_NULL)
					}
					default:
						throw (gcnew NotSupportedException("StringExtension::Invalid Option Type."));
					}
				case Options::IncludeAll:
					switch (trailing_option)
					{
					case Options::Exclude:
					{
						if (keep_empty_entries)
							SPLIT_EXTENSION_CLR_FUNCTION(INCLUDE_ALL_FOLLOWING, EXCLUDE_TRAILING, KEEP_EMPTY_ENTRIES, MEMSET_METHOD)
						else
							SPLIT_EXTENSION_CLR_FUNCTION(INCLUDE_ALL_FOLLOWING, EXCLUDE_TRAILING, OMIT_EMPTY_ENTRIES, MEMSET_NULL)
					}
					case Options::IncludeSingle:
					{
						if (keep_empty_entries)
							SPLIT_EXTENSION_CLR_FUNCTION(INCLUDE_ALL_FOLLOWING, INCLUDE_SINGLE_TRAILING, KEEP_EMPTY_ENTRIES, MEMSET_METHOD)
						else
							SPLIT_EXTENSION_CLR_FUNCTION(INCLUDE_ALL_FOLLOWING, INCLUDE_SINGLE_TRAILING, OMIT_EMPTY_ENTRIES, MEMSET_NULL)
					}
					case Options::IncludeAll:
					{
						throw (gcnew NotSupportedException("There is no functionable logic that supports IncludeAll following delimiters, and IncludeAll trailing delimiters."));
					}
					default:
						throw (gcnew NotSupportedException("StringExtension::Invalid Option Type."));
					}
				default:
					throw (gcnew NotSupportedException("StringExtension::Invalid Option Type."));
				}

			MemAlloc:

				if (array_size == 0)
					return gcnew STRING_ARRAY(0);

				word = dictionary;

				stringArray = gcnew STRING_ARRAY(array_size);
				string_ptr = &stringArray[0];

				for (int i = stringArray->Length; i != 0; i--)
				{
					//if (word->_length)
					*string_ptr = gcnew String(word->_wordBegin, 0, word->_length);
					++string_ptr;
					++word;
				}

				_freea(dictionary);
				return stringArray;
			}
			__except ((EXCEPTION_STACK_OVERFLOW == GetExceptionCode())
				? EXCEPTION_EXECUTE_HANDLER
				: EXCEPTION_CONTINUE_SEARCH)
			{
				_resetstkoflw();
				return nullptr;
			}
		}

		/*
			this/is/a/test/string will become

			string[*][0]			string[*][1]
			this					this
			this/is					is
			this/is/a				a
			this/is/a/test			test
			this/is/a/test/string	string
		*/

		/// <summary>
		/// string[*][0] will contain all characters up to the end of the token.
		/// <para>string[*][1] contains just the tokenized string.</para>
		/// <para>This defaults to excluding all delimiters, not keeping empty entries, and GreedyFollowing.</para>
		/// </summary>
		/// <param name="data">The data to process.</param>
		/// <param name="delimiters">Character list of delimiters.</param>
		/// <returns>
		/// A jagged array of tokenized strings.
		/// </returns>
		/// <exception cref="NotSupportedException">
		/// StringExtension::Invalid Option Type.
		/// or
		/// StringExtension::Invalid Option Type.
		/// or
		/// There is no functionable logic that supports IncludeAll following delimiters, and IncludeAll trailing delimiters.
		/// or
		/// StringExtension::Invalid Option Type.
		/// or
		/// StringExtension::Invalid Option Type.
		/// </exception>
		[Extension]
		static inline JAGGED_STRING_ARRAY^ SplitExtensionTrack(String ^ data, ... CHAR_ARRAY ^ delimiters)
		{
			return SplitExtensionTrack(data, Options::Exclude, Options::Exclude, false, StringExtGreed::GreedyFollowing, delimiters);
		}

		/// <summary>
		/// string[*][0] will contain all characters up to the end of the token.
		/// <para>string[*][1] contains just the tokenized string.</para>
		/// <para>This defaults to excluding all delimiters, and GreedyFollowing.</para>
		/// </summary>
		/// <param name="data">The data to process.</param>
		/// <param name="keep_empty_entries">If set to <c>true</c> keep empty entries as string.Empty.</param>
		/// <param name="delimiters">Character list of delimiters.</param>
		/// <returns>
		/// A jagged array of tokenized strings.
		/// </returns>
		/// <exception cref="NotSupportedException">
		/// StringExtension::Invalid Option Type.
		/// or
		/// StringExtension::Invalid Option Type.
		/// or
		/// There is no functionable logic that supports IncludeAll following delimiters, and IncludeAll trailing delimiters.
		/// or
		/// StringExtension::Invalid Option Type.
		/// or
		/// StringExtension::Invalid Option Type.
		/// </exception>
		[Extension]
		static inline JAGGED_STRING_ARRAY^ SplitExtensionTrack(String ^ data, const bool keep_empty_entries, ... CHAR_ARRAY ^ delimiters)
		{
			return SplitExtensionTrack(data, Options::Exclude, Options::Exclude, keep_empty_entries, StringExtGreed::GreedyFollowing, delimiters);
		}
		/// <summary>
		/// string[*][0] will contain all characters up to the end of the token.
		/// <para>string[*][1] contains just the tokenized string.</para>
		/// <para>This defaults to not keeping empty entries and GreedyFollowing.</para>
		/// </summary>
		/// <param name="data">The data to process.</param>
		/// <param name="following_option">Following Options::</param>
		/// <param name="trailing_option">Trailing Options::</param>
		/// <param name="delimiters">Character list of delimiters.</param>
		/// <returns>
		/// A jagged array of tokenized strings.
		/// </returns>
		/// <exception cref="NotSupportedException">
		/// StringExtension::Invalid Option Type.
		/// or
		/// StringExtension::Invalid Option Type.
		/// or
		/// There is no functionable logic that supports IncludeAll following delimiters, and IncludeAll trailing delimiters.
		/// or
		/// StringExtension::Invalid Option Type.
		/// or
		/// StringExtension::Invalid Option Type.
		/// </exception>
		[Extension]
		static inline JAGGED_STRING_ARRAY^ SplitExtensionTrack(String ^ data, Options following_option, Options trailing_option, ... CHAR_ARRAY ^ delimiters)
		{
			return SplitExtensionTrack(data, following_option, trailing_option, false, StringExtGreed::GreedyFollowing, delimiters);
		}

		/// <summary>
		/// string[*][0] will contain all characters up to the end of the token.
		/// <para>string[*][1] contains just the tokenized string.</para>
		/// <para>This defaults to not specifying greed.</para>
		/// </summary>
		/// <param name="data">The data to process.</param>
		/// <param name="following_option">Following Options::</param>
		/// <param name="trailing_option">Trailing Options::</param>
		/// <param name="keep_empty_entries">If set to <c>true</c> keep empty entries as string.Empty.</param>
		/// <param name="delimiters">Character list of delimiters.</param>
		/// <returns>
		/// A jagged array of tokenized strings.
		/// </returns>
		/// <exception cref="NotSupportedException">
		/// StringExtension::Invalid Option Type.
		/// or
		/// StringExtension::Invalid Option Type.
		/// or
		/// There is no functionable logic that supports IncludeAll following delimiters, and IncludeAll trailing delimiters.
		/// or
		/// StringExtension::Invalid Option Type.
		/// or
		/// StringExtension::Invalid Option Type.
		/// </exception>
		[Extension]
		static inline JAGGED_STRING_ARRAY^ SplitExtensionTrack(String ^ data, Options following_option, Options trailing_option, const bool keep_empty_entries, ... CHAR_ARRAY ^ delimiters)
		{
			return SplitExtensionTrack(data, following_option, trailing_option, keep_empty_entries, StringExtGreed::GreedyFollowing, delimiters);
		}

		/// <summary>
		/// string[*][0] will contain all characters up to the end of the token.
		/// <para>string[*][1] contains just the tokenized string.</para>
		/// </summary>
		/// <param name="data">The data to process.</param>
		/// <param name="following_option">Following Options::</param>
		/// <param name="trailing_option">Trailing Options::</param>
		/// <param name="keep_empty_entries">If set to <c>true</c> keep empty entries as string.Empty.</param>
		/// <param name="greed">Greedy Following, or Greedy Trailing.</param>
		/// <param name="delimiters">Character list of delimiters.</param>
		/// <returns>
		/// A jagged array of tokenized strings.
		/// </returns>
		/// <exception cref="NotSupportedException">
		/// StringExtension::Invalid Option Type.
		/// or
		/// StringExtension::Invalid Option Type.
		/// or
		/// There is no functionable logic that supports IncludeAll following delimiters, and IncludeAll trailing delimiters.
		/// or
		/// StringExtension::Invalid Option Type.
		/// or
		/// StringExtension::Invalid Option Type.
		/// </exception>
		[Extension]
		static JAGGED_STRING_ARRAY^ SplitExtensionTrack(
			String ^ data,
			Options following_option,
			Options trailing_option,
			const bool keep_empty_entries,
			StringExtGreed greed,
			... CHAR_ARRAY ^ delimiters)
		{
#if false
			if (delimiters->Length == 0)
				delimiters = whitespace;
#endif
			/*
			Question for any experts out there, if I eat up all my stack memory with _malloca, do I have to declare
			all of these here?  If not, maybe moving these to their respective blocks will make things more easily
			readable.
			*/

			pin_ptr<const wchar_t> calculation = _PointerToString(data);
			pin_ptr<const wchar_t> delimiter_begin = &delimiters[0];

			__try
			{
				_wordEntry* __restrict dictionary;
				_wordEntry* __restrict word;

				JAGGED_STRING_ARRAY ^stringArray;
				interior_ptr<STRING_ARRAY ^> array_ptr;

				split_extension_int array_size;
				int track_length = 0;

				switch (following_option)
				{
				case Options::Exclude:
					switch (trailing_option)
					{
					case Options::Exclude:
					{
						if (keep_empty_entries)
							SPLIT_EXTENSION_CLR_FUNCTION(EXCLUDE_FOLLOWING, EXCLUDE_TRAILING, KEEP_EMPTY_ENTRIES, MEMSET_METHOD)
						else
							SPLIT_EXTENSION_CLR_FUNCTION(EXCLUDE_FOLLOWING, EXCLUDE_TRAILING, OMIT_EMPTY_ENTRIES, MEMSET_NULL)
					}
					case Options::IncludeSingle:
					{
						if (keep_empty_entries)
							SPLIT_EXTENSION_CLR_FUNCTION(EXCLUDE_FOLLOWING, INCLUDE_SINGLE_TRAILING, KEEP_EMPTY_ENTRIES, MEMSET_METHOD)
						else
							SPLIT_EXTENSION_CLR_FUNCTION(EXCLUDE_FOLLOWING, INCLUDE_SINGLE_TRAILING, OMIT_EMPTY_ENTRIES, MEMSET_NULL)
					}
					case Options::IncludeAll:
					{
						if (keep_empty_entries)
							SPLIT_EXTENSION_CLR_FUNCTION(EXCLUDE_FOLLOWING, INCLUDE_ALL_TRAILING, KEEP_EMPTY_ENTRIES, MEMSET_METHOD)
						else
							SPLIT_EXTENSION_CLR_FUNCTION(EXCLUDE_FOLLOWING, INCLUDE_ALL_TRAILING, OMIT_EMPTY_ENTRIES, MEMSET_NULL)
					}
					default:
						throw (gcnew NotSupportedException("StringExtension::Invalid Option Type."));
					}
				case Options::IncludeSingle:
					switch (trailing_option)
					{
					case Options::Exclude:
					{
						if (keep_empty_entries)
							SPLIT_EXTENSION_CLR_FUNCTION(INCLUDE_SINGLE_FOLLOWING, EXCLUDE_TRAILING, KEEP_EMPTY_ENTRIES, MEMSET_METHOD)
						else
							SPLIT_EXTENSION_CLR_FUNCTION(INCLUDE_SINGLE_FOLLOWING, EXCLUDE_TRAILING, OMIT_EMPTY_ENTRIES, MEMSET_NULL)
					}
					case Options::IncludeSingle:
					{
						if (keep_empty_entries)
						{
							if (greed == StringExtGreed::GreedyTrailing)
								SPLIT_EXTENSION_CLR_FUNCTION(INCLUDE_SINGLE_FOLLOWING_GREEDY, INCLUDE_SINGLE_TRAILING, KEEP_EMPTY_ENTRIES, MEMSET_METHOD)
							else
								SPLIT_EXTENSION_CLR_FUNCTION(INCLUDE_SINGLE_FOLLOWING_GREEDY, INCLUDE_SINGLE_TRAILING, KEEP_EMPTY_ENTRIES, MEMSET_METHOD)
						}
						else
						{
							if (greed == StringExtGreed::GreedyTrailing)
								SPLIT_EXTENSION_CLR_FUNCTION(INCLUDE_SINGLE_FOLLOWING, INCLUDE_SINGLE_TRAILING_GREEDY, OMIT_EMPTY_ENTRIES, MEMSET_NULL)
							else
								SPLIT_EXTENSION_CLR_FUNCTION(INCLUDE_SINGLE_FOLLOWING, INCLUDE_SINGLE_TRAILING_GREEDY, OMIT_EMPTY_ENTRIES, MEMSET_NULL)
						}
					}
					case Options::IncludeAll:
					{
						if (keep_empty_entries)
							SPLIT_EXTENSION_CLR_FUNCTION(INCLUDE_SINGLE_FOLLOWING, INCLUDE_ALL_TRAILING, KEEP_EMPTY_ENTRIES, MEMSET_METHOD)
						else
							SPLIT_EXTENSION_CLR_FUNCTION(INCLUDE_SINGLE_FOLLOWING, INCLUDE_ALL_TRAILING, OMIT_EMPTY_ENTRIES, MEMSET_NULL)
					}
					default:
						throw (gcnew NotSupportedException("StringExtension::Invalid Option Type."));
					}
				case Options::IncludeAll:
					switch (trailing_option)
					{
					case Options::Exclude:
					{
						if (keep_empty_entries)
							SPLIT_EXTENSION_CLR_FUNCTION(INCLUDE_ALL_FOLLOWING, EXCLUDE_TRAILING, KEEP_EMPTY_ENTRIES, MEMSET_METHOD)
						else
							SPLIT_EXTENSION_CLR_FUNCTION(INCLUDE_ALL_FOLLOWING, EXCLUDE_TRAILING, OMIT_EMPTY_ENTRIES, MEMSET_NULL)
					}
					case Options::IncludeSingle:
					{
						if (keep_empty_entries)
							SPLIT_EXTENSION_CLR_FUNCTION(INCLUDE_ALL_FOLLOWING, INCLUDE_SINGLE_TRAILING, KEEP_EMPTY_ENTRIES, MEMSET_METHOD)
						else
							SPLIT_EXTENSION_CLR_FUNCTION(INCLUDE_ALL_FOLLOWING, INCLUDE_SINGLE_TRAILING, OMIT_EMPTY_ENTRIES, MEMSET_NULL)
					}
					case Options::IncludeAll:
					{
						throw (gcnew NotSupportedException("There is no functionable logic that supports IncludeAll following delimiters, and IncludeAll trailing delimiters."));
					}
					default:
						throw (gcnew NotSupportedException("StringExtension::Invalid Option Type."));
					}
				default:
					throw (gcnew NotSupportedException("StringExtension::Invalid Option Type."));
				}

			MemAlloc:

				if (array_size == 0)
					return gcnew JAGGED_STRING_ARRAY(0);

				stringArray = gcnew JAGGED_STRING_ARRAY(array_size);
				word = dictionary;

				array_ptr = &stringArray[0];

				if (keep_empty_entries)
				{
					// Since we're keeping all of our empty entries, we can use some basic math instead of pointer math here.
					// We can't combine both because keep_empty_entries returns word->_wordBegin with a nullptr, so no ptr math for those.
					for (int i = array_size; i != 0; i--)
					{
						// This is slow, but not too bad.  A small price to pay for the complexity of using a jagged array.
						*array_ptr = gcnew STRING_ARRAY(2);

						if (word->_length)
						{
							track_length += word->_length;

							array_ptr[0][0] = data->Substring(0, track_length);
							array_ptr[0][1] = gcnew String(word->_wordBegin, 0, word->_length);
						}
						else
						{
							++track_length;

							array_ptr[0][0] = data->Substring(0, track_length);
							array_ptr[0][1] = String::Empty;
						}

						++array_ptr;
						++word;
					}
				}
				else
				{
					for (int i = array_size; i != 0; i--)
					{
						*array_ptr = gcnew STRING_ARRAY(2);

						/*
							I'm certain that using ptr math here is a pretty nasty way of doing this, however I can't think
							of a superior way that doesn't involve some major restructuring that won't sacrifice speed for
							both the tracking and non tracking sides.  Any ideas are welcome.
						*/
						if (word->_length)
						{
							array_ptr[0][0] = data->Substring(0, (int)(word->_wordBegin - calculation + word->_length));
							array_ptr[0][1] = gcnew String(word->_wordBegin, 0, word->_length);
						}
						else
						{
							array_ptr[0][0] = data->Substring(0, (int)(word->_wordBegin - calculation + 1));
							array_ptr[0][1] = String::Empty;
						}

						++array_ptr;
						++word;
					}
				}

				_freea(dictionary);
				return stringArray;
			}
			__except ((EXCEPTION_STACK_OVERFLOW == GetExceptionCode())
				? EXCEPTION_EXECUTE_HANDLER
				: EXCEPTION_CONTINUE_SEARCH)
			{
				_resetstkoflw();
				return nullptr;
			}
		}

	internal:
		// Latin1
		static CHAR_ARRAY ^ whitespace = { (Char) ' ', (Char) '\x0009', (Char) '\x000d', (Char) '\x00a0', (Char) '\x0085' };

#if false
		inline __const_Char_ptr PtrToStringChars(__const_String_handle s) {

			_Byte_ptr bp = const_cast<_Byte_ptr>(reinterpret_cast<__const_Byte_ptr>(s));
			if (bp != _NULLPTR) {
				unsigned offset = System::Runtime::CompilerServices::RuntimeHelpers::OffsetToStringData;
				bp += offset;
			}
			return reinterpret_cast<__const_Char_ptr>(bp);
		}
#endif
		// Bypass null check (it's handled)
		static inline __const_Char_ptr _PointerToString(String ^s)
		{
			_Byte_ptr char_ptr = const_cast<_Byte_ptr>(reinterpret_cast<__const_Byte_ptr>(s));
			unsigned offset = System::Runtime::CompilerServices::RuntimeHelpers::OffsetToStringData;
			char_ptr += offset;
			return reinterpret_cast<__const_Char_ptr>(char_ptr);
		}
	};
}