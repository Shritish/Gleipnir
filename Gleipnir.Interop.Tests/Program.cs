using System;

namespace Gleipnir.Interop.Tests
{
	class Program
	{
#pragma warning disable IDE1006 // Naming Styles
		static void Main(string[] args)
		{
			while (new TestBench().RunTestBench())
				continue;
		}
#pragma warning restore IDE1006 // Naming Styles
	}
}
