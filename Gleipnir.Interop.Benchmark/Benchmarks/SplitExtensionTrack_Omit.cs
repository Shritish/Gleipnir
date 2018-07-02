using BenchmarkDotNet.Attributes;
using System;

namespace Gleipnir.Interop.Benchmark.Benchmarks
{
	public class SplitExtensionTrack_Omit
	{
		private static string[][] _testSplitExtension(Options following_option, Options trailing_option, bool keep_empty_entries, StringExtGreed greed = StringExtGreed.GreedyTrailing)
		{
			string[][] dont_optimize_me = null;

			foreach (string test_string in TestArray.SplitStringArray)
				dont_optimize_me = test_string.SplitExtensionTrack(following_option, trailing_option, keep_empty_entries, greed, TestArray.SplitSeparators);

			return dont_optimize_me;
		}

		[Benchmark(Baseline = true)]
		public static string[] TestCSharpSplit()
		{
			string[] dont_optimize_me = null;

			foreach (string test_string in TestArray.SplitStringArray)
				dont_optimize_me = test_string.Split(TestArray.SplitSeparators, StringSplitOptions.RemoveEmptyEntries);

			return dont_optimize_me;
		}

		[Benchmark]
		public static string[][] Exclude_Exclude_OmitEmptyEntries() => _testSplitExtension(Options.Exclude, Options.Exclude, false);

		[Benchmark]
		public static string[][] Exclude_IncludeSingleTrailing_OmitEmptyEntries() => _testSplitExtension(Options.Exclude, Options.IncludeSingle, false);

		[Benchmark]
		public static string[][] Exclude_IncludeAllTrailing_OmitEmptyEntries() => _testSplitExtension(Options.Exclude, Options.IncludeAll, false);

		[Benchmark]
		public static string[][] IncludeSingleFollowing_Exclude_OmitEmptyEntries() => _testSplitExtension(Options.IncludeSingle, Options.Exclude, false);

		[Benchmark]
		public static string[][] IncludeSingleFollowing_IncludeAllTrailing_OmitEmptyEntries() => _testSplitExtension(Options.IncludeSingle, Options.IncludeAll, false);

		[Benchmark]
		public static string[][] IncludeAllFollowing_Exclude_OmitEmptyEntries() => _testSplitExtension(Options.IncludeAll, Options.Exclude, false);

		[Benchmark]
		public static string[][] IncludeAllFollowing_IncludeSingleTrailing_OmitEmptyEntries() => _testSplitExtension(Options.IncludeAll, Options.IncludeSingle, false);

		[Benchmark]
		public static string[][] IncludeSingleFollowing_IncludeSingleTrailing_OmitEmptyEntries_GreedyFollowing() => _testSplitExtension(Options.IncludeSingle, Options.IncludeSingle, false, StringExtGreed.GreedyFollowing);

		[Benchmark]
		public static string[][] IncludeSingleFollowing_IncludeSingleTrailing_OmitEmptyEntries_GreedyTrailing() => _testSplitExtension(Options.IncludeSingle, Options.IncludeSingle, false, StringExtGreed.GreedyTrailing);
	}
}
