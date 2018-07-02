#include "stdafx.h"

#define OPT_FOLLOWING	EXCLUDE_FOLLOWING
#define OPT_TRAILING	INCLUDE_SINGLE_TRAILING
#define OPT_ENTRIES		OMIT_EMPTY_ENTRIES

COUNT_ENTRY_DECLARATION()
{
	split_extension_char* delimiter;
	split_extension_int count = 0;

	split_extension_char* calculation_end = calculation + calculation_length;
	split_extension_char* delimiter_end = delimiter_begin + delimiter_length;

End:
	if (calculation != calculation_end)
	{
		for (delimiter = delimiter_begin; delimiter != delimiter_end; delimiter++)
			if (*delimiter == *calculation)
			{
				++calculation;
				goto End;
			}

		while (++calculation != calculation_end)
			for (delimiter = delimiter_begin; delimiter != delimiter_end; delimiter++)
				if (*delimiter == *calculation)
				{
					++calculation;
					++count;
					goto End;
				}

		++count;
	}

	return count;
}

SEEK_DELIMITER_DECLARATION()
{
	split_extension_char* delimiter;
	split_extension_char* word_begin;

	split_extension_char* calculation_end = calculation + calculation_length;
	split_extension_char* delimiter_end = delimiter_begin + delimiter_length;

	split_extension_int entries = 0;
	split_extension_int length = 0;

End:
	if (calculation != calculation_end)
	{
		for (delimiter = delimiter_begin; delimiter != delimiter_end; delimiter++)
			if (*delimiter == *calculation)
			{
				++calculation;
				goto End;
			}

		word_begin = calculation;

		while (++calculation != calculation_end)
		{
			++length;
			for (delimiter = delimiter_begin; delimiter != delimiter_end; delimiter++)
				if (*delimiter == *calculation)
				{
					++calculation;
					dictionary[entries]._wordBegin = word_begin;
					dictionary[entries]._length = ++length;
					++entries;
					length = 0;
					goto End;
				}
		}

		dictionary[entries]._wordBegin = word_begin;
		dictionary[entries]._length = ++length;
	}

	return dictionary;
}