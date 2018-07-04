using BenchmarkDotNet.Attributes;
using BenchmarkDotNet.Running;
using Gleipnir.Interop.Benchmark.Benchmarks;
using System;

namespace Gleipnir.Interop.Benchmark
{
	public class Program
	{
		public static void Main(string[] args)
		{
			BenchmarkRunner.Run<SplitExtension_Keep>();
			BenchmarkRunner.Run<SplitExtension_Omit>();
			BenchmarkRunner.Run<SplitExtensionTrack_Keep>();
			BenchmarkRunner.Run<SplitExtensionTrack_Omit>();

			//BenchmarkRunner.Run<Program>();
		}

		[Benchmark]
		public static string[] SingleTest()
		{
			string[] dont_optimize_me = null;

			foreach (string test_string in TestArray.SplitStringArray)
				dont_optimize_me = test_string.SplitExtension(SplitOption.Exclude, SplitOption.Exclude, false, TestArray.SplitSeparators);

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
    }
}
