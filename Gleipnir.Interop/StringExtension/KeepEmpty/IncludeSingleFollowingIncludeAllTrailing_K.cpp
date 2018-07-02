#include "stdafx.h"

#define OPT_FOLLOWING	INCLUDE_SINGLE_FOLLOWING
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
				++calculation;

				if (no_word_entry)
				{
					if (calculation != calculation_end)
					{
						for (delimiter = delimiter_begin; delimiter != delimiter_end; delimiter++)
							if (*delimiter == *calculation)
							{
								++count;
								break;
							}
					}
					else
						return ++count;
				}

				goto End;
			}

		no_word_entry = false;

		while (++calculation != calculation_end)
			for (delimiter = delimiter_begin; delimiter != delimiter_end; delimiter++)
				if (*delimiter == *calculation)
				{
				Middle:
					if (++calculation != calculation_end)
						for (delimiter = delimiter_begin; delimiter != delimiter_end; delimiter++)
							if (*delimiter == *calculation)
								goto Middle;

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
	split_extension_int length;

	split_extension_int following_delimiter = 0;
	bool no_word_entry = true;

End:
	if (calculation != calculation_end)
	{
		for (delimiter = delimiter_begin; delimiter != delimiter_end; delimiter++)
			if (*delimiter == *calculation)
			{
				++calculation;
				following_delimiter = 1;

				if (no_word_entry)
				{
					if (calculation != calculation_end)
					{
						for (delimiter = delimiter_begin; delimiter != delimiter_end; delimiter++)
							if (*delimiter == *calculation)
							{
								++entries;
								break;
							}
					}
					else
					{
						++entries;
						return dictionary;
					}
				}

				goto End;
			}

		length = following_delimiter;
		word_begin = calculation - following_delimiter;

		no_word_entry = false;

		while (++calculation != calculation_end)
		{
			++length;
			for (delimiter = delimiter_begin; delimiter != delimiter_end; delimiter++)
				if (*delimiter == *calculation)
				{
				Middle:
					if (++calculation != calculation_end)
					{
						for (delimiter = delimiter_begin; delimiter != delimiter_end; delimiter++)
							if (*delimiter == *calculation)
							{
								++length;
								goto Middle;
							}
					}
					else
					{
						dictionary[entries]._wordBegin = word_begin;
						dictionary[entries]._length = ++length;
						++entries;
						return dictionary;
					}

					dictionary[entries]._wordBegin = word_begin;
					dictionary[entries]._length = length;
					++entries;
					length = 0;
					following_delimiter = 1;
					goto End;
				}
		}

		dictionary[entries]._wordBegin = word_begin;
		dictionary[entries]._length = ++length;
	}

	return dictionary;
}
