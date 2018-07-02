#include "stdafx.h"

#define OPT_FOLLOWING	EXCLUDE_FOLLOWING
#define OPT_TRAILING	INCLUDE_ALL_TRAILING
#define OPT_ENTRIES		KEEP_EMPTY_ENTRIES

COUNT_ENTRY_DECLARATION()
{
	split_extension_char* delimiter;
	split_extension_int count = 0;

	split_extension_char* calculation_end = calculation + calculation_length;
	split_extension_char* delimiter_end = delimiter_begin + delimiter_length;

	bool no_word_entry = true;

End:
	if (calculation != calculation_end)
	{
		for (delimiter = delimiter_begin; delimiter != delimiter_end; delimiter++)
			if (*delimiter == *calculation)
			{
				if (no_word_entry)
					++count;

				++calculation;
				goto End;
			}

		while (++calculation != calculation_end)
			for (delimiter = delimiter_begin; delimiter != delimiter_end; delimiter++)
				if (*delimiter == *calculation)
				{
				Middle:
					if (++calculation != calculation_end)
						for (delimiter = delimiter_begin; delimiter != delimiter_end; delimiter++)
							if (*delimiter == *calculation)
								goto Middle;

					no_word_entry = false;
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

	bool no_word_entry = true;

End:
	if (calculation != calculation_end)
	{
		for (delimiter = delimiter_begin; delimiter != delimiter_end; delimiter++)
			if (*delimiter == *calculation)
			{
				++calculation;

				if (no_word_entry)
					++entries;

				goto End;
			}

		word_begin = calculation;

		while (++calculation != calculation_end)
		{
			++length;
			for (delimiter = delimiter_begin; delimiter != delimiter_end; delimiter++)
				if (*delimiter == *calculation)
				{
				Middle:
					if (++calculation != calculation_end)
						for (delimiter = delimiter_begin; delimiter != delimiter_end; delimiter++)
							if (*delimiter == *calculation)
							{
								++length;
								goto Middle;
							}

					dictionary[entries]._wordBegin = word_begin;
					dictionary[entries]._length = ++length;
					++entries;

					length = 0;
					no_word_entry = false;
					goto End;
				}
		}

		dictionary[entries]._wordBegin = word_begin;
		dictionary[entries]._length = ++length;
	}

	return dictionary;
}

