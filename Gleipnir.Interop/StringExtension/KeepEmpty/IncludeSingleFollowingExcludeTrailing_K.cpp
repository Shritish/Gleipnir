#include "stdafx.h"

#define OPT_FOLLOWING	INCLUDE_SINGLE_FOLLOWING
#define OPT_TRAILING	EXCLUDE_TRAILING
#define OPT_ENTRIES		KEEP_EMPTY_ENTRIES

COUNT_ENTRY_DECLARATION()
{
	split_extension_char* delimiter;
	split_extension_int count = 0;

	split_extension_char* calculation_end = calculation + calculation_length;
	split_extension_char* delimiter_end = delimiter_begin + delimiter_length;

	bool following_delimiter = false;

End:
	if (calculation != calculation_end)
	{
		for (delimiter = delimiter_begin; delimiter != delimiter_end; delimiter++)
			if (*delimiter == *calculation)
			{
				++calculation;

				if (following_delimiter)
					++count;
				else following_delimiter = true;

				goto End;
			}

		while (++calculation != calculation_end)
			for (delimiter = delimiter_begin; delimiter != delimiter_end; delimiter++)
				if (*delimiter == *calculation)
				{
					++calculation;
					++count;
					following_delimiter = true;
					goto End;
				}

		return ++count;
	}

	if (following_delimiter)
		++count;

	return count;
}

SEEK_DELIMITER_DECLARATION()
{
	split_extension_char* delimiter;
	split_extension_char* word_begin;

	split_extension_char* calculation_end = calculation + calculation_length;
	split_extension_char* delimiter_end = delimiter_begin + delimiter_length;

	split_extension_int entries = 0;
	split_extension_int length;

	bool following_delimiter = false;

End:
	if (calculation != calculation_end)
	{
		for (delimiter = delimiter_begin; delimiter != delimiter_end; delimiter++)
			if (*delimiter == *calculation)
			{
				++calculation;

				if (following_delimiter)
					++entries;
				else following_delimiter = true;

				goto End;
			}

		length = following_delimiter;
		word_begin = calculation - (split_extension_int)following_delimiter;

		while (++calculation != calculation_end)
		{
			++length;
			for (delimiter = delimiter_begin; delimiter != delimiter_end; delimiter++)
				if (*delimiter == *calculation)
				{
					++calculation;
					dictionary[entries]._wordBegin = word_begin;
					dictionary[entries]._length = length;
					++entries;
					following_delimiter = true;
					goto End;
				}
		}

		dictionary[entries]._wordBegin = word_begin;
		dictionary[entries]._length = ++length;
	}

	return dictionary;
}
