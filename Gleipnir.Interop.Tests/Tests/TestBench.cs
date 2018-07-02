using System;

namespace Gleipnir.Interop.Tests
{
	internal class TestBench
	{
		private static readonly string[] _intro =
		{
			"Licensed under Apache 2.0 license for fair use.",
			"Authored by Tyler Ross.",
			"",
			"Test Battery: ",
			"Select Test: ",
			"(1) All tests.",
			"(2) All tests without confirmation.",
			"(3) Group tests.",
			"(4) Group tests without confirmation.",
			"(5) Single unit tests.",
			"(6) Single unit tests without confirmation.",
			"(7/Esc) Exit."
		};

		private enum TestSelection
		{
			AllTests,
			AllTestsNoConfirm,
			GroupTests,
			GroupTestsNoConfirm,
			SingleUnitTests,
			SingleUnitTestsNoConfirm,
			Exit
		}

		private TestSelection _selectionChoice;

		public bool RunTestBench()
		{
			foreach (string intro_string in _intro)
				Console.WriteLine(intro_string);

			ConsoleKeyInfo intro_selection = Console.ReadKey();

			switch (intro_selection.Key)
			{
				case ConsoleKey.NumPad1:
				case ConsoleKey.D1:
					_selectionChoice = TestSelection.AllTests;
					while (DecideCompare())
						continue;
					break;
				case ConsoleKey.NumPad2:
				case ConsoleKey.D2:
					_selectionChoice = TestSelection.AllTestsNoConfirm;
					while (DecideCompare())
						continue;
					break;
				case ConsoleKey.NumPad3:
				case ConsoleKey.D3:
					_selectionChoice = TestSelection.GroupTests;
					while (DecideCompare())
						continue;
					break;
				case ConsoleKey.NumPad4:
				case ConsoleKey.D4:
					_selectionChoice = TestSelection.GroupTestsNoConfirm;
					while (DecideCompare())
						continue;
					break;
				case ConsoleKey.NumPad5:
				case ConsoleKey.D5:
					_selectionChoice = TestSelection.SingleUnitTests;
					while (DecideCompare())
						continue;
					break;
				case ConsoleKey.NumPad6:
				case ConsoleKey.D6:
					_selectionChoice = TestSelection.SingleUnitTestsNoConfirm;
					while (DecideCompare())
						continue;
					break;
				case ConsoleKey.NumPad7:
				case ConsoleKey.D7:
				case ConsoleKey.Escape:
					_selectionChoice = TestSelection.Exit;
					return false;
				default:
					Console.WriteLine(Environment.NewLine + "Selection not understood." + Environment.NewLine);
					return true;
			}

#if TestBenchTwoPointOh
			if (_comparisonChoice == Comparison.Exit || _selectionChoice == TestSelection.Exit)
#else
			if (_selectionChoice == TestSelection.Exit)
#endif
				return false;

			switch (_selectionChoice)
			{
				case TestSelection.AllTests:
					while (RunAllTests(true))
						continue;
					break;
				case TestSelection.AllTestsNoConfirm:
					while (RunAllTests(false))
						continue;
					Console.WriteLine("End of test, push a key to exit.");
					Console.ReadKey();
					break;
				case TestSelection.GroupTests:
					while (RunGroupTests(true, false))
						continue;
					break;
				case TestSelection.GroupTestsNoConfirm:
					while (RunGroupTests(false, false))
						continue;
					Console.WriteLine("End of test, push a key to exit.");
					Console.ReadKey();
					break;
				case TestSelection.SingleUnitTests:
					while (RunGroupTests(true, true))
						continue;
					break;
				case TestSelection.SingleUnitTestsNoConfirm:
					while (RunGroupTests(false, true))
						continue;
					Console.WriteLine("End of test, push a key to exit.");
					Console.ReadKey();
					break;
				default:
					Console.WriteLine(Environment.NewLine + "Selection not understood." + Environment.NewLine);
					return true;
			}

			return false;
		}

		// TODO: In the future, maybe.. I dunno, I'm pretty lazy about this.
#if TestBenchTwoPointOh
		private static readonly string[] _compare_result_intro =
{
			"",
			"Compare Results to internal array to ensure accuracy?",
			"(1) Yes",
			"(2) No",
			"(3/Esc) Exit"
		};

		private enum Comparison
		{
			DoCompare,
			DoNotCompare,
			Exit
		}

		private Comparison _comparisonChoice;
#endif
		public bool DecideCompare() =>
#if TestBenchTwoPointOh

			foreach (string intro_string in _compare_result_intro)
				Console.WriteLine(intro_string);

			ConsoleKeyInfo compare_selection = Console.ReadKey();

			switch (compare_selection.Key)
			{
				case ConsoleKey.NumPad1:
				case ConsoleKey.D1:
					_comparisonChoice = Comparison.DoCompare;
					return false;
				case ConsoleKey.NumPad2:
				case ConsoleKey.D2:
					_comparisonChoice = Comparison.DoNotCompare;
					return false;
				case ConsoleKey.NumPad3:
				case ConsoleKey.D3:
				case ConsoleKey.Escape:
					_comparisonChoice = Comparison.Exit;
					return false;
				default:
					Console.WriteLine(Environment.NewLine + "Selection not understood." + Environment.NewLine);
					return true;
			}
#endif
			false;


		private static readonly string[] _run_all_tests_intro =
		{
			"",
			"Running All Tests:",
		};

		public bool RunAllTests(bool confirm)
		{
			foreach (string intro_string in _run_all_tests_intro)
				Console.WriteLine(intro_string);

			_runTest(GroupSelection.Omit, confirm, false);
			_runTest(GroupSelection.Keep, confirm, false);
			_runTest(GroupSelection.OmitTrack, confirm, false);
			_runTest(GroupSelection.KeepTrack, confirm, false);

			return false;
		}

		private enum GroupSelection
		{
			Omit,
			Keep,
			OmitTrack,
			KeepTrack
		}

		private static readonly string[] _run_group_tests_intro =
		{
			"",
			"Select Group:",
			"(1) Omit.",
			"(2) Keep.",
			"(3) Omit with tracking string.",
			"(4) Keep with tracking string.",
			"(5/Esc) Exit."
		};

		public bool RunGroupTests(bool confirm, bool select)
		{
			foreach (string intro_string in _run_group_tests_intro)
				Console.WriteLine(intro_string);

			ConsoleKeyInfo group_select = Console.ReadKey();

			switch (group_select.Key)
			{
				case ConsoleKey.NumPad1:
				case ConsoleKey.D1:
					return _runTest(GroupSelection.Omit, confirm, select);
				case ConsoleKey.NumPad2:
				case ConsoleKey.D2:
					return _runTest(GroupSelection.Keep, confirm, select);
				case ConsoleKey.NumPad3:
				case ConsoleKey.D3:
					return _runTest(GroupSelection.OmitTrack, confirm, select);
				case ConsoleKey.NumPad4:
				case ConsoleKey.D4:
					return _runTest(GroupSelection.KeepTrack, confirm, select);
				case ConsoleKey.NumPad5:
				case ConsoleKey.D5:
				case ConsoleKey.Escape:
					return false;
				default:
					Console.WriteLine(Environment.NewLine + "Selection not understood." + Environment.NewLine);
					return true;
			}
		}

		private static bool _runTest(GroupSelection group, bool confirm, bool select)
		{
			if (select)
			{
				Console.WriteLine();

				int selection = 0;
				ConsoleKeyInfo key_entry;

				switch (group)
				{
					case GroupSelection.Omit:
						foreach (TestArray.invoke_method action in TestArray._splitExtensionOmit)
							Console.WriteLine("(" + (selection++) + ") " + action.Method.Name.Replace('_', ' '));
						key_entry = Console.ReadKey();

						if (key_entry.KeyChar.IsDigit())
						{
							int index = (int) char.GetNumericValue(key_entry.KeyChar);

							if (index >= 0 && index <= TestArray._splitExtensionOmit.Length)
							{
								TestArray.invoke_method action = TestArray._splitExtensionOmit[index];

								Console.WriteLine("Running Function [" + action.Method.Name + "]");

								foreach (string input in TestArray.SplitStringArray)
								{
									Console.WriteLine("Processing string [" + input + "]");
									if (!_display_result(action.Invoke(input, TestArray.SplitSeparators), confirm))
										return true;
								}

							}
							return true;
						}
						goto default;
					case GroupSelection.Keep:
						foreach (TestArray.invoke_method action in TestArray._splitExtensionKeep)
							Console.WriteLine("(" + (selection++) + ") " + action.Method.Name.Replace('_', ' '));
						key_entry = Console.ReadKey();

						if (key_entry.KeyChar.IsDigit())
						{
							int index = (int)char.GetNumericValue(key_entry.KeyChar);

							if (index >= 0 && index <= TestArray._splitExtensionKeep.Length)
							{
								TestArray.invoke_method action = TestArray._splitExtensionKeep[index];

								Console.WriteLine("Running Function [" + action.Method.Name + "]");

								foreach (string input in TestArray.SplitStringArray)
								{
									Console.WriteLine("Processing string [" + input + "]");
									if (!_display_result(action.Invoke(input, TestArray.SplitSeparators), confirm))
										return true;
								}

							}
							return true;
						}
						goto default;
					case GroupSelection.OmitTrack:
						foreach (TestArray.invoke_track_method action in TestArray._splitExtensionTrackOmit)
							Console.WriteLine("(" + (selection++) + ") " + action.Method.Name.Replace('_', ' '));
						key_entry = Console.ReadKey();

						if (key_entry.KeyChar.IsDigit())
						{
							int index = (int)char.GetNumericValue(key_entry.KeyChar);

							if (index >= 0 && index <= TestArray._splitExtensionTrackOmit.Length)
							{
								TestArray.invoke_track_method action = TestArray._splitExtensionTrackOmit[index];

								Console.WriteLine("Running Function [" + action.Method.Name + "]");

								foreach (string input in TestArray.SplitStringArray)
								{
									Console.WriteLine("Processing string [" + input + "]");
									if (!_display_result(action.Invoke(input, TestArray.SplitSeparators), confirm))
										return true;
								}

							}
							return true;
						}
						goto default;
					case GroupSelection.KeepTrack:
						foreach (TestArray.invoke_track_method action in TestArray._splitExtensionTrackKeep)
							Console.WriteLine("(" + (selection++) + ") " + action.Method.Name.Replace('_', ' '));
						key_entry = Console.ReadKey();

						if (key_entry.KeyChar.IsDigit())
						{
							int index = (int)char.GetNumericValue(key_entry.KeyChar);

							if (index >= 0 && index <= TestArray._splitExtensionTrackKeep.Length)
							{
								TestArray.invoke_track_method action = TestArray._splitExtensionTrackKeep[index];

								Console.WriteLine("Running Function [" + action.Method.Name + "]");

								foreach (string input in TestArray.SplitStringArray)
								{
									Console.WriteLine("Processing string [" + input + "]");
									if (!_display_result(action.Invoke(input, TestArray.SplitSeparators), confirm))
										return true;
								}

							}
							return true;
						}
						goto default;
					default:
						Console.WriteLine(Environment.NewLine + "Selection not understood." + Environment.NewLine);
						return true;
				}
			}
			else
				switch (group)
				{
					case GroupSelection.Omit:
					{
						foreach (TestArray.invoke_method action in TestArray._splitExtensionOmit)
						{
							Console.WriteLine("Running Function [" + action.Method.Name + "]");
							foreach (string input in TestArray.SplitStringArray)
							{
								Console.WriteLine("Processing string [" + input + "]");
								if (!_display_result(action.Invoke(input, TestArray.SplitSeparators), confirm))
									return false;
							}
						}
					}
					break;
					case GroupSelection.Keep:
					{
						foreach (TestArray.invoke_method action in TestArray._splitExtensionKeep)
						{
							Console.WriteLine("Running Function [" + action.Method.Name + "]");
							foreach (string input in TestArray.SplitStringArray)
							{
								Console.WriteLine("Processing string [" + input + "]");
								if (!_display_result(action.Invoke(input, TestArray.SplitSeparators), confirm))
									return false;
							}
						}
					}
					break;
					case GroupSelection.OmitTrack:
					{
						foreach (TestArray.invoke_track_method action in TestArray._splitExtensionTrackOmit)
						{
							Console.WriteLine("Running Function [" + action.Method.Name + "]");
							foreach (string input in TestArray.SplitStringArray)
							{
								Console.WriteLine("Processing string [" + input + "]");
								if (!_display_result(action.Invoke(input, TestArray.SplitSeparators), confirm))
									return false;
							}
						}
					}
					break;
					case GroupSelection.KeepTrack:
					{
						foreach (TestArray.invoke_track_method action in TestArray._splitExtensionTrackKeep)
						{
							Console.WriteLine("Running Function [" + action.Method.Name + "]");
							foreach (string input in TestArray.SplitStringArray)
							{
								Console.WriteLine("Processing string [" + input + "]");
								if (!_display_result(action.Invoke(input, TestArray.SplitSeparators), confirm))
									return false;
							}
						}
					}
					break;
				}
			return false;
		}

		private static bool _display_result(string[][] data, bool confirm)
		{
			foreach (string[] test in data)
			{
				string display = "string[1] = [" + test[1] + "] ";
				Console.WriteLine(display.PadRight(25) + "string[0] = [" + test[0] + "]");

				if (confirm)
					if (!_displayPressKey())
						return false;
			}

			return true;
		}

		private static bool _display_result(string[] data, bool confirm)
		{
			foreach (string test in data)
				Console.WriteLine("String = [" + test + "]");

			if (confirm)
				if (!_displayPressKey())
					return false;

			return true;
		}

		private static bool _displayPressKey()
		{
			Console.WriteLine("Press a key.");

			if (Console.ReadKey().Key == ConsoleKey.Escape)
				return false;

			Console.SetCursorPosition(0, Console.CursorTop - 1);
			return true;
		}
	}
}
