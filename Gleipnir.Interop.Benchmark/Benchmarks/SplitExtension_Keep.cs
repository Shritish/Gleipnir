using BenchmarkDotNet.Attributes;
using System;

namespace Gleipnir.Interop.Benchmark.Benchmarks
{
	public class SplitExtension_Keep
	{
		private static string[] _testSplitExtension(SplitOption following_option, SplitOption trailing_option, bool keep_empty_entries, SplitGreed greed = SplitGreed.Trailing)
		{
			string[] dont_optimize_me = null;

			foreach (string test_string in TestArray.SplitStringArray)
				dont_optimize_me = test_string.SplitExtension(following_option, trailing_option, keep_empty_entries, greed, TestArray.SplitSeparators);

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
		public static string[] Exclude_Exclude_KeepEmptyEntries() => _testSplitExtension(SplitOption.Exclude, SplitOption.Exclude, true);

		[Benchmark]
		public static string[] Exclude_IncludeSingleTrailing_KeepEmptyEntries() => _testSplitExtension(SplitOption.Exclude, SplitOption.IncludeSingle, true);

		[Benchmark]
		public static string[] Exclude_IncludeAllTrailing_KeepEmptyEntries() => _testSplitExtension(SplitOption.Exclude, SplitOption.IncludeAll, true);

		[Benchmark]
		public static string[] IncludeSingleFollowing_Exclude_KeepEmptyEntries() => _testSplitExtension(SplitOption.IncludeSingle, SplitOption.Exclude, true);

		[Benchmark]
		public static string[] IncludeSingleFollowing_IncludeAllTrailing_KeepEmptyEntries() => _testSplitExtension(SplitOption.IncludeSingle, SplitOption.IncludeAll, true);

		[Benchmark]
		public static string[] IncludeAllFollowing_Exclude_KeepEmptyEntries() => _testSplitExtension(SplitOption.IncludeAll, SplitOption.Exclude, true);

		[Benchmark]
		public static string[] IncludeAllFollowing_IncludeSingleTrailing_KeepEmptyEntries() => _testSplitExtension(SplitOption.IncludeAll, SplitOption.IncludeSingle, true);

		[Benchmark]
		public static string[] IncludeSingleFollowing_IncludeSingleTrailing_KeepEmptyEntries_GreedyFollowing() => _testSplitExtension(SplitOption.IncludeSingle, SplitOption.IncludeSingle, true, SplitGreed.Following);

		[Benchmark]
		public static string[] IncludeSingleFollowing_IncludeSingleTrailing_KeepEmptyEntries_GreedyTrailing() => _testSplitExtension(SplitOption.IncludeSingle, SplitOption.IncludeSingle, true, SplitGreed.Trailing);
	}
}
