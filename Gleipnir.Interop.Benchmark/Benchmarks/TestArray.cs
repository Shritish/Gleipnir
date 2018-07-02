using System.IO;

namespace Gleipnir.Interop.Benchmark.Benchmarks
{
	internal static class TestArray
	{
		public static char[] SplitSeparators =
{
			Path.DirectorySeparatorChar,
			Path.AltDirectorySeparatorChar
		};

		public static readonly string[] SplitStringArray =
		{
			@"\/aa\/",
			@"one\two\\three\\\four\\\\a",
			@"\one\two\\three\\\four\\\\a\",
			@"\one\1\one\1\one\1\",
			@"one\1\one\1\one\1",
			@"\/two\/2\/two\/2\/two\/",
			@"two\/2\/two\/2\/two",
			@"\/\three\/\3\/\three\/\3\/\three\/\",
			@"three\/\3\/\three\/\3\/\three",
			@"\/\/four\/\/4\/\/four\/\/4\/\/four\/\/",
			@"four\/\/4\/\/four\/\/4\/\/four",
			@"\/\/\/\/\/a+10",
			@"a+10\/\/\/\/\/",
			@"\/\/\/\/\/",
			@"This is a test string.",
			@"",
			@"\",
			@"\/\/\/\/\/a+10*5\/\/\/\/\/a+10*5\/\/\/\/\/a+10*5\/\/\/\/\/a+10*5\/\/\/\/\/a+10*5\/\/\/\/\/"
		};
	}
}
