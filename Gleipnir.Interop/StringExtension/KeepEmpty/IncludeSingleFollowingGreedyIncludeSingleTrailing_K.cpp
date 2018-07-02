#include "stdafx.h"

#define OPT_FOLLOWING	INCLUDE_SINGLE_FOLLOWING_GREEDY
#define OPT_TRAILING	INCLUDE_SINGLE_TRAILING
#define OPT_ENTRIES		KEEP_EMPTY_ENTRIES

COUNT_ENTRY_DECLARATION()
{
	split_extension_char* delimiter;
	split_extension_int count = 0;

	split_extension_char* calculation_end = calculation + calculation_length;
	split_extension_char* delimiter_end = delimiter_begin + delimiter_length;

	int empty_entry_count = 0;

End:
	if (calculation != calculation_end)
	{
		for (delimiter = delimiter_begin; delimiter != delimiter_end; delimiter++)
			if (*delimiter == *calculation)
			{
				++calculation;
				++empty_entry_count;
				goto End;
			}

		if (empty_entry_count)
		{
			count += empty_entry_count - 1;
			empty_entry_count = 0;
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

	count += empty_entry_count;

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

	int empty_entry_count = 0;

	bool following_delimiter = false;

	// bool consume_following_delimiter = true;
	//	bool following_delimiter = false;
	// --word_begin is superior.
End:
	if (calculation != calculation_end)
	{
		for (delimiter = delimiter_begin; delimiter != delimiter_end; delimiter++)
			if (*delimiter == *calculation)
			{
				++calculation;
				++empty_entry_count;
				following_delimiter = true;
				goto End;
			}

		if (empty_entry_count)
		{
			if (--empty_entry_count)
			{
				entries += empty_entry_count;
				empty_entry_count = 0;
			}

			length = 1;
			word_begin = calculation - 1;
		}
		else if (following_delimiter)
		{
			length = 1;
			word_begin = calculation - 1;
			--dictionary[entries - 1]._length;
		}
		else
		{
			length = 0;
			word_begin = calculation;
		}

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
					following_delimiter = true;
					goto End;
				}
		}

		dictionary[entries]._wordBegin = word_begin;
		dictionary[entries]._length = ++length;
	}

	return dictionary;
}
