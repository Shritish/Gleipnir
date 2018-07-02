#include "stdafx.h"

#define OPT_FOLLOWING	INCLUDE_ALL_FOLLOWING
#define OPT_TRAILING	INCLUDE_SINGLE_TRAILING
#define OPT_ENTRIES		KEEP_EMPTY_ENTRIES

COUNT_ENTRY_DECLARATION()
{
	split_extension_char* delimiter;
	split_extension_int count = 0;

	split_extension_char* calculation_end = calculation + calculation_length;
	split_extension_char* delimiter_end = delimiter_begin + delimiter_length;

	split_extension_int empty_entry_counter = 0;

End:
	if (calculation != calculation_end)
	{
		for (delimiter = delimiter_begin; delimiter != delimiter_end; delimiter++)
			if (*delimiter == *calculation)
			{
				++empty_entry_counter;
				++calculation;
				goto End;
			}

		empty_entry_counter = 0;

		while (++calculation != calculation_end)
			for (delimiter = delimiter_begin; delimiter != delimiter_end; delimiter++)
				if (*delimiter == *calculation)
				{
					++count;
					++calculation;
					goto End;
				}

		++count;
	}

	return count + empty_entry_counter;
}

SEEK_DELIMITER_DECLARATION()
{

	split_extension_char* delimiter;
	split_extension_char* word_begin = calculation;

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
				++length;
				goto End;
			}

		while (++calculation != calculation_end)
		{
			++length;
			for (delimiter = delimiter_begin; delimiter != delimiter_end; delimiter++)
				if (*delimiter == *calculation)
				{
					dictionary[entries]._wordBegin = word_begin;
					dictionary[entries]._length = ++length;
					++entries;
					word_begin = ++calculation;
					length = 0;
					goto End;
				}
		}

		dictionary[entries]._wordBegin = word_begin;
		dictionary[entries]._length = ++length;
	}

	return dictionary;
}