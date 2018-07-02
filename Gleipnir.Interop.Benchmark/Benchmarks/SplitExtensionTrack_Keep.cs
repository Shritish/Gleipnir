using BenchmarkDotNet.Attributes;
using System;

namespace Gleipnir.Interop.Benchmark.Benchmarks
{
	public class SplitExtensionTrack_Keep
	{
		private static string[][] _testSplitExtension(Options following_option, Options trailing_option, bool keep_empty_entries, StringExtGreed greed = StringExtGreed.GreedyTrailing)
		{
			string[][] dont_optimize_me = null;

			foreach (string test_string in TestArray.SplitStringArray)
				dont_optimize_me = test_string.SplitExtensionTrack(following_option, trailing_option, keep_empty_entries, greed, TestArray.SplitSeparators);

			return dont_optimize_me;
		}

		[Benchmark(Baseline = true)]
		public static string[] TestCSharpSplitKeepEmpty()
		{
			string[] dont_optimize_me = null;

			foreach (string test_string in TestArray.SplitStringArray)
				dont_optimize_me = test_string.Split(TestArray.SplitSeparators, StringSplitOptions.None);

			return dont_optimize_me;
		}

		[Benchmark]
		public static string[][] Exclude_Exclude_KeepEmptyEntries() => _testSplitExtension(Options.Exclude, Options.Exclude, true);

		[Benchmark]
		public static string[][] Exclude_IncludeSingleTrailing_KeepEmptyEntries() => _testSplitExtension(Options.Exclude, Options.IncludeSingle, true);

		[Benchmark]
		public static string[][] Exclude_IncludeAllTrailing_KeepEmptyEntries() => _testSplitExtension(Options.Exclude, Options.IncludeAll, true);

		[Benchmark]
		public static string[][] IncludeSingleFollowing_Exclude_KeepEmptyEntries() => _testSplitExtension(Options.IncludeSingle, Options.Exclude, true);

		[Benchmark]
		public static string[][] IncludeSingleFollowing_IncludeAllTrailing_KeepEmptyEntries() => _testSplitExtension(Options.IncludeSingle, Options.IncludeAll, true);

		[Benchmark]
		public static string[][] IncludeAllFollowing_Exclude_KeepEmptyEntries() => _testSplitExtension(Options.IncludeAll, Options.Exclude, true);

		[Benchmark]
		public static string[][] IncludeAllFollowing_IncludeSingleTrailing_KeepEmptyEntries() => _testSplitExtension(Options.IncludeAll, Options.IncludeSingle, true);

		[Benchmark]
		public static string[][] IncludeSingleFollowing_IncludeSingleTrailing_KeepEmptyEntries_GreedyFollowing() => _testSplitExtension(Options.IncludeSingle, Options.IncludeSingle, true, StringExtGreed.GreedyFollowing);

		[Benchmark]
		public static string[][] IncludeSingleFollowing_IncludeSingleTrailing_KeepEmptyEntries_GreedyTrailing() => _testSplitExtension(Options.IncludeSingle, Options.IncludeSingle, true, StringExtGreed.GreedyTrailing);
	}
}
