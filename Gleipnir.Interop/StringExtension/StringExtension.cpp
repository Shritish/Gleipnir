using namespace System;
using namespace System::Runtime::CompilerServices;

#if false
namespace System::Runtime::CompilerServices
{
	/// <summary>
	/// Indicates that a method is an extension method, or that a class or assembly contains extension methods.
	/// </summary>
	[AttributeUsage(AttributeTargets::Method | AttributeTargets::Class | AttributeTargets::Assembly)]
	ref struct ExtensionAttribute : public Attribute { };
}
#endif

namespace Gleipnir
{
	[Extension]
	public ref class StringExtension abstract sealed
	{
	public:
		/// <summary>
		/// Determines whether this instance ends with any of the listed characters.
		/// </summary>
		/// <param name="string">Specified string.</param>
		/// <param name="value">Array of characters to test against.</param>
		/// <returns></returns>
		[Extension]
		static bool EndsWith(String ^ string, ... array<const Char> ^ value)
		{
			if (string->Length != 0 && value->Length != 0)
				for each(char c in value)
					if (string[string->Length - 1] == c)
						return true;

			return false;
		}

		/// <summary>
		/// Determines whether this instance is a letter.
		/// </summary>
		/// <param name="c">Specified Char.</param>
		/// <returns>
		///   <c>true</c> if the specified c is letter; otherwise, <c>false</c>.
		/// </returns>
		[Extension]
		static bool IsLetter(const Char c)
		{
			return Char::IsLetter(c);
		}

		/// <summary>
		/// Determines whether this instance is a digit.
		/// </summary>
		/// <param name="c">Specified Char.</param>
		/// <returns>
		///   <c>true</c> if the specified c is digit; otherwise, <c>false</c>.
		/// </returns>
		[Extension]
		static bool IsDigit(const Char c)
		{
			return Char::IsDigit(c);
		}

		/// <summary>
		/// Determines whether this is a letter or digit.
		/// </summary>
		/// <param name="c">Specified Char.</param>
		/// <returns>
		///   <c>true</c> if [is letter or digit] [the specified c]; otherwise, <c>false</c>.
		/// </returns>
		[Extension]
		static bool IsLetterOrDigit(const Char c)
		{
			return Char::IsLetterOrDigit(c);
		}

		/// <summary>
		/// Determines whether this instance is latin1.
		/// </summary>
		/// <param name="c">Specified Char.</param>
		/// <returns>
		///   <c>true</c> if the specified ch is latin1; otherwise, <c>false</c>.
		/// </returns>
		[Extension]
		static bool IsLatin1(const Char c)
		{
			return c <= '\x00ff';
		}

		/// <summary>
		/// Determines whether this instance is ASCII.
		/// </summary>
		/// <param name="c">Specified Char.</param>
		/// <returns>
		///   <c>true</c> if the specified c is ASCII; otherwise, <c>false</c>.
		/// </returns>
		[Extension]
		static bool IsAscii(const Char c)
		{
			return c <= '\x007f';
		}
	};
}