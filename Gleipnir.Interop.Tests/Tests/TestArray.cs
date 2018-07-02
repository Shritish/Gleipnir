using System.IO;

namespace Gleipnir.Interop.Tests
{
	internal class TestArray
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

		// Every option is represented here in a singular function with a single paramater for delegate invocation for testing.
		// There are 36 various options in total.
		//Keep & No Track
		public static string[] ExcludeFollowing_ExcludeTrailing_KeepEmptyEntries(string input, params char[] delimiters) => input.SplitExtension(Options.Exclude, Options.Exclude, true, delimiters);
		public static string[] ExcludeFollowing_IncludeSingleTrailing_KeepEmptyEntries(string input, params char[] delimiters) => input.SplitExtension(Options.Exclude, Options.IncludeSingle, true, delimiters);
		public static string[] ExcludeFollowing_IncludeAllTrailing_KeepEmptyEntries(string input, params char[] delimiters) => input.SplitExtension(Options.Exclude, Options.IncludeAll, true, delimiters);
		public static string[] IncludeSingleFollowing_ExcludeTrailing_KeepEmptyEntries(string input, params char[] delimiters) => input.SplitExtension(Options.IncludeSingle, Options.Exclude, true, delimiters);
		public static string[] IncludeSingleFollowing_IncludeAllTrailing_KeepEmptyEntries(string input, params char[] delimiters) => input.SplitExtension(Options.IncludeSingle, Options.IncludeAll, true, delimiters);
		public static string[] IncludeAllFollowing_ExcludeTrailing_KeepEmptyEntries(string input, params char[] delimiters) => input.SplitExtension(Options.IncludeAll, Options.Exclude, true, delimiters);
		public static string[] IncludeAllFollowing_IncludeSingleTrailing_KeepEmptyEntries(string input, params char[] delimiters) => input.SplitExtension(Options.IncludeAll, Options.IncludeSingle, true, delimiters);
		public static string[] IncludeSingleFollowing_IncludeSingleTrailing_KeepEmptyEntries_GreedyFollowing(string input, params char[] delimiters) => input.SplitExtension(Options.IncludeSingle, Options.IncludeSingle, true, StringExtGreed.GreedyFollowing, delimiters);
		public static string[] IncludeSingleFollowing_IncludeSingleTrailing_KeepEmptyEntries_GreedyTrailing(string input, params char[] delimiters) => input.SplitExtension(Options.IncludeSingle, Options.IncludeSingle, true, StringExtGreed.GreedyTrailing, delimiters);

		//Omit & No Track
		public static string[] ExcludeFollowing_ExcludeTrailing_OmitEmptyEntries(string input, params char[] delimiters) => input.SplitExtension(Options.Exclude, Options.Exclude, false, delimiters);
		public static string[] ExcludeFollowing_IncludeSingleTrailing_OmitEmptyEntries(string input, params char[] delimiters) => input.SplitExtension(Options.Exclude, Options.IncludeSingle, false, delimiters);
		public static string[] ExcludeFollowing_IncludeAllTrailing_OmitEmptyEntries(string input, params char[] delimiters) => input.SplitExtension(Options.Exclude, Options.IncludeAll, false, delimiters);
		public static string[] IncludeSingleFollowing_ExcludeTrailing_OmitEmptyEntries(string input, params char[] delimiters) => input.SplitExtension(Options.IncludeSingle, Options.Exclude, false, delimiters);
		public static string[] IncludeSingleFollowing_IncludeAllTrailing_OmitEmptyEntries(string input, params char[] delimiters) => input.SplitExtension(Options.IncludeSingle, Options.IncludeAll, false, delimiters);
		public static string[] IncludeAllFollowing_ExcludeTrailing_OmitEmptyEntries(string input, params char[] delimiters) => input.SplitExtension(Options.IncludeAll, Options.Exclude, false, delimiters);
		public static string[] IncludeAllFollowing_IncludeSingleTrailing_OmitEmptyEntries(string input, params char[] delimiters) => input.SplitExtension(Options.IncludeAll, Options.IncludeSingle, false, delimiters);
		public static string[] IncludeSingleFollowing_IncludeSingleTrailing_OmitEmptyEntries_GreedyFollowing(string input, params char[] delimiters) => input.SplitExtension(Options.IncludeSingle, Options.IncludeSingle, false, StringExtGreed.GreedyFollowing, delimiters);
		public static string[] IncludeSingleFollowing_IncludeSingleTrailing_OmitEmptyEntries_GreedyTrailing(string input, params char[] delimiters) => input.SplitExtension(Options.IncludeSingle, Options.IncludeSingle, false, StringExtGreed.GreedyTrailing, delimiters);

		// Keep & Track
		public static string[][] Track_ExcludeFollowing_ExcludeTrailing_KeepEmptyEntries(string input, params char[] delimiters) => input.SplitExtensionTrack(Options.Exclude, Options.Exclude, true, delimiters);
		public static string[][] Track_ExcludeFollowing_IncludeSingleTrailing_KeepEmptyEntries(string input, params char[] delimiters) => input.SplitExtensionTrack(Options.Exclude, Options.IncludeSingle, true, delimiters);
		public static string[][] Track_ExcludeFollowing_IncludeAllTrailing_KeepEmptyEntries(string input, params char[] delimiters) => input.SplitExtensionTrack(Options.Exclude, Options.IncludeAll, true, delimiters);
		public static string[][] Track_IncludeSingleFollowing_ExcludeTrailing_KeepEmptyEntries(string input, params char[] delimiters) => input.SplitExtensionTrack(Options.IncludeSingle, Options.Exclude, true, delimiters);
		public static string[][] Track_IncludeSingleFollowing_IncludeAllTrailing_KeepEmptyEntries(string input, params char[] delimiters) => input.SplitExtensionTrack(Options.IncludeSingle, Options.IncludeAll, true, delimiters);
		public static string[][] Track_IncludeAllFollowing_ExcludeTrailing_KeepEmptyEntries(string input, params char[] delimiters) => input.SplitExtensionTrack(Options.IncludeAll, Options.Exclude, true, delimiters);
		public static string[][] Track_IncludeAllFollowing_IncludeSingleTrailing_KeepEmptyEntries(string input, params char[] delimiters) => input.SplitExtensionTrack(Options.IncludeAll, Options.IncludeSingle, true, delimiters);
		public static string[][] Track_IncludeSingleFollowing_IncludeSingleTrailing_KeepEmptyEntries_GreedyFollowing(string input, params char[] delimiters) => input.SplitExtensionTrack(Options.IncludeSingle, Options.IncludeSingle, true, StringExtGreed.GreedyFollowing, delimiters);
		public static string[][] Track_IncludeSingleFollowing_IncludeSingleTrailing_KeepEmptyEntries_GreedyTrailing(string input, params char[] delimiters) => input.SplitExtensionTrack(Options.IncludeSingle, Options.IncludeSingle, true, StringExtGreed.GreedyTrailing, delimiters);

		// Omit & No Track
		public static string[][] Track_ExcludeFollowing_ExcludeTrailing_OmitEmptyEntries(string input, params char[] delimiters) => input.SplitExtensionTrack(Options.Exclude, Options.Exclude, false, delimiters);
		public static string[][] Track_ExcludeFollowing_IncludeSingleTrailing_OmitEmptyEntries(string input, params char[] delimiters) => input.SplitExtensionTrack(Options.Exclude, Options.IncludeSingle, false, delimiters);
		public static string[][] Track_ExcludeFollowing_IncludeAllTrailing_OmitEmptyEntries(string input, params char[] delimiters) => input.SplitExtensionTrack(Options.Exclude, Options.IncludeAll, false, delimiters);
		public static string[][] Track_IncludeSingleFollowing_ExcludeTrailing_OmitEmptyEntries(string input, params char[] delimiters) => input.SplitExtensionTrack(Options.IncludeSingle, Options.Exclude, false, delimiters);
		public static string[][] Track_IncludeSingleFollowing_IncludeAllTrailing_OmitEmptyEntries(string input, params char[] delimiters) => input.SplitExtensionTrack(Options.IncludeSingle, Options.IncludeAll, false, delimiters);
		public static string[][] Track_IncludeAllFollowing_ExcludeTrailing_OmitEmptyEntries(string input, params char[] delimiters) => input.SplitExtensionTrack(Options.IncludeAll, Options.Exclude, false, delimiters);
		public static string[][] Track_IncludeAllFollowing_IncludeSingleTrailing_OmitEmptyEntries(string input, params char[] delimiters) => input.SplitExtensionTrack(Options.IncludeAll, Options.IncludeSingle, false, delimiters);
		public static string[][] Track_IncludeSingleFollowing_IncludeSingleTrailing_OmitEmptyEntries_GreedyFollowing(string input, params char[] delimiters) => input.SplitExtensionTrack(Options.IncludeSingle, Options.IncludeSingle, false, StringExtGreed.GreedyFollowing, delimiters);
		public static string[][] Track_IncludeSingleFollowing_IncludeSingleTrailing_OmitEmptyEntries_GreedyTrailing(string input, params char[] delimiters) => input.SplitExtensionTrack(Options.IncludeSingle, Options.IncludeSingle, false, StringExtGreed.GreedyTrailing, delimiters);


		internal delegate string[] invoke_method(string input, params char[] delimiters);

		internal static readonly invoke_method[] _splitExtensionKeep =
		{
			ExcludeFollowing_ExcludeTrailing_KeepEmptyEntries,
			ExcludeFollowing_IncludeSingleTrailing_KeepEmptyEntries,
			ExcludeFollowing_IncludeAllTrailing_KeepEmptyEntries,
			IncludeSingleFollowing_ExcludeTrailing_KeepEmptyEntries,
			IncludeSingleFollowing_IncludeAllTrailing_KeepEmptyEntries,
			IncludeAllFollowing_ExcludeTrailing_KeepEmptyEntries,
			IncludeAllFollowing_IncludeSingleTrailing_KeepEmptyEntries,
			IncludeSingleFollowing_IncludeSingleTrailing_KeepEmptyEntries_GreedyFollowing,
			IncludeSingleFollowing_IncludeSingleTrailing_KeepEmptyEntries_GreedyTrailing
		};

		internal static readonly invoke_method[] _splitExtensionOmit =
		{
			ExcludeFollowing_ExcludeTrailing_OmitEmptyEntries,
			ExcludeFollowing_IncludeSingleTrailing_OmitEmptyEntries,
			ExcludeFollowing_IncludeAllTrailing_OmitEmptyEntries,
			IncludeSingleFollowing_ExcludeTrailing_OmitEmptyEntries,
			IncludeSingleFollowing_IncludeAllTrailing_OmitEmptyEntries,
			IncludeAllFollowing_ExcludeTrailing_OmitEmptyEntries,
			IncludeAllFollowing_IncludeSingleTrailing_OmitEmptyEntries,
			IncludeSingleFollowing_IncludeSingleTrailing_OmitEmptyEntries_GreedyFollowing,
			IncludeSingleFollowing_IncludeSingleTrailing_OmitEmptyEntries_GreedyTrailing
		};

		internal delegate string[][] invoke_track_method(string input, params char[] delimiters);

		internal static readonly invoke_track_method[] _splitExtensionTrackKeep =
		{
			Track_ExcludeFollowing_ExcludeTrailing_KeepEmptyEntries,
			Track_ExcludeFollowing_IncludeSingleTrailing_KeepEmptyEntries,
			Track_ExcludeFollowing_IncludeAllTrailing_KeepEmptyEntries,
			Track_IncludeSingleFollowing_ExcludeTrailing_KeepEmptyEntries,
			Track_IncludeSingleFollowing_IncludeAllTrailing_KeepEmptyEntries,
			Track_IncludeAllFollowing_ExcludeTrailing_KeepEmptyEntries,
			Track_IncludeAllFollowing_IncludeSingleTrailing_KeepEmptyEntries,
			Track_IncludeSingleFollowing_IncludeSingleTrailing_KeepEmptyEntries_GreedyFollowing,
			Track_IncludeSingleFollowing_IncludeSingleTrailing_KeepEmptyEntries_GreedyTrailing
		};

		internal static readonly invoke_track_method[] _splitExtensionTrackOmit =
		{
			Track_ExcludeFollowing_ExcludeTrailing_OmitEmptyEntries,
			Track_ExcludeFollowing_IncludeSingleTrailing_OmitEmptyEntries,
			Track_ExcludeFollowing_IncludeAllTrailing_OmitEmptyEntries,
			Track_IncludeSingleFollowing_ExcludeTrailing_OmitEmptyEntries,
			Track_IncludeSingleFollowing_IncludeAllTrailing_OmitEmptyEntries,
			Track_IncludeAllFollowing_ExcludeTrailing_OmitEmptyEntries,
			Track_IncludeAllFollowing_IncludeSingleTrailing_OmitEmptyEntries,
			Track_IncludeSingleFollowing_IncludeSingleTrailing_OmitEmptyEntries_GreedyFollowing,
			Track_IncludeSingleFollowing_IncludeSingleTrailing_OmitEmptyEntries_GreedyTrailing
		};
	}
}
