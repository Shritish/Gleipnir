using BenchmarkDotNet.Attributes;
using System;

namespace Gleipnir.Interop.Benchmark.Benchmarks
{
	public class SplitExtension_Omit
	{
		private static string[] _testSplitExtension(SplitOption following_option, SplitOption trailing_option, bool keep_empty_entries, SplitGreed greed = SplitGreed.Trailing)
		{
			string[] dont_optimize_me = null;

			foreach (string test_string in TestArray.SplitStringArray)
				dont_optimize_me = test_string.SplitExtension(following_option, trailing_option, keep_empty_entries, greed, TestArray.SplitSeparators);

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
		public static string[] Exclude_Exclude_OmitEmptyEntries() => _testSplitExtension(SplitOption.Exclude, SplitOption.Exclude, false);

		[Benchmark]
		public static string[] Exclude_IncludeSingleTrailing_OmitEmptyEntries() => _testSplitExtension(SplitOption.Exclude, SplitOption.IncludeSingle, false);

		[Benchmark]
		public static string[] Exclude_IncludeAllTrailing_OmitEmptyEntries() => _testSplitExtension(SplitOption.Exclude, SplitOption.IncludeAll, false);

		[Benchmark]
		public static string[] IncludeSingleFollowing_Exclude_OmitEmptyEntries() => _testSplitExtension(SplitOption.IncludeSingle, SplitOption.Exclude, false);

		[Benchmark]
		public static string[] IncludeSingleFollowing_IncludeAllTrailing_OmitEmptyEntries() => _testSplitExtension(SplitOption.IncludeSingle, SplitOption.IncludeAll, false);

		[Benchmark]
		public static string[] IncludeAllFollowing_Exclude_OmitEmptyEntries() => _testSplitExtension(SplitOption.IncludeAll, SplitOption.Exclude, false);

		[Benchmark]
		public static string[] IncludeAllFollowing_IncludeSingleTrailing_OmitEmptyEntries() => _testSplitExtension(SplitOption.IncludeAll, SplitOption.IncludeSingle, false);

		[Benchmark]
		public static string[] IncludeSingleFollowing_IncludeSingleTrailing_OmitEmptyEntries_GreedyFollowing() => _testSplitExtension(SplitOption.IncludeSingle, SplitOption.IncludeSingle, false, SplitGreed.Following);

		[Benchmark]
		public static string[] IncludeSingleFollowing_IncludeSingleTrailing_OmitEmptyEntries_GreedyTrailing() => _testSplitExtension(SplitOption.IncludeSingle, SplitOption.IncludeSingle, false, SplitGreed.Trailing);
	}
}
