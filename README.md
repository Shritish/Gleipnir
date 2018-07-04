# Gleipnir
A string library for C#, mainly a faster string.Split implementation with more features.

- **FORWARD**:  
Alright, so this is going to be a rough readme for the time being.  I apologize until I can write out a full and proper README. Beware this is a proper placeholder until I can do appropriate documentation. I'll give some basic details on how to use this library here to fill in temporarily. The library is an Interop library, no setup is required to drop it into any C# project.  Once compiled it will function like any other C# library, and communicate with C# thusly.

However, there are some requirements to get it to compile:

- **REQUIRED**:
    * Visual C++ ATL for your respective processor. (atlstr.h)
    * Visual C++ MFC for your respective processor. (_malloca)
    * C++/CLI support.
      *Note: All of these can be found in Individual Components in Get Tools And Features.*

- **NOT REQUIRED**:
    * BenchmarkDotNet is NOT required unless you want to run Benchmarks, obviously, this project can be excluded from build.
    * The Gleipnir.Interopt.Tests is only there for anyone's testing purposes and convenience, also not required.  
      *These are just benchmarks and tests for internal use or experimenting.*


- **INSTRUCTIONS**:
1.  Add Gleipnir.Interop to any C# project.
1.  Compile Gleipnir.Interop.
    1.  *After you have compiled Gleipnir.Interop, the C++/CLI compiler will generate the appropriate metadata to use in a C# project.*
1.  Add a reference to Gleipnir.Interop under Projects->Solution [x] Gleipnir.Interop
1.  Add "using Gleipnir;" to your C# file.


- **PRIMARY FUNCTIONS INCLUDED**:
```C#
string[][] SplitExtensionTrack(this string data, SplitOption following_option, SplitOption trailing_option, bool keep_empty_entries, SplitGreed greed, params char[] delimiters);
string[] SplitExtension(this string data, SplitOption following_option, SplitOption trailing_option, bool keep_empty_entries, SplitGreed greed, params char[] delimiters);
```

- **CONVENIENCE WRAPPERS**:
```C#
string[] SplitExtension(this string data, SplitOption following_options, SplitOption trailing_options, bool keep_empty_entries, params char[] delimiters);
string[] SplitExtension(this string data, SplitOption following_options, SplitOption trailing_options, params char[] delimiters);
string[] SplitExtension(this string data, bool keep_empty_entries, params char[] delimiters);
string[] SplitExtension(this string data, params char[] delimiters);

string[][] SplitExtensionTrack(this string data, SplitOption following_option, SplitOption trailing_option, bool keep_empty_entries, params char[] delimiters);
string[][] SplitExtensionTrack(this string data, SplitOption following_option, SplitOption trailing_option, params char[] delimiters);
string[][] SplitExtensionTrack(this string data, bool keep_empty_entries, params char[] delimiters);
string[][] SplitExtensionTrack(this string data, params char[] delimiters);
```

- **USING**:  
    Can be used statically, for example:
    ```C#
    Split.SplitExtension("string", 'a', 'b', 'c', ...);
    ```
    
    Can be used as an extension, for example:
    ```C#
    string.SplitExtension('a', 'b', 'c', ...);
    ```
    
    The Options are /somewhat/ self explanatory.
    So for example, to emulate string.Split behavior:
    ```C#
      string TestString = @"test\string";
      TestString.SplitExtension('\\');
    // Output = "test", "string"
    ```
    Or:
    ```C#
      string TestString = @"test\string";
      TestString.SplitExtension(SplitOptions.Exclude, SplitOptions.Exclude, false, '\\');
    // Output = "test", "string"
    ```
- **SplitOption**
    ```C#
    public enum SplitOption
    {
        Exclude, // (Default) Exclude entries from the final output.
        IncludeSingle, // Include a single delimiter in the final output.
        IncludeAll // Include ALL delimiters in the final output.
    }  
    ```

- **SplitGreed**
    ```C#
    public enum SplitGreed
    {
        Following, // (Default) "\test\string\" = "\test" and "\string\"
        Trailing // "\test\string\" = "\test\" and "string\"
    }  
    ```
    *To be used when you're using IncludeSingle (following) and IncludeSingle (trailing), to specify which is more greedy*
    
- **SplitExtensionTrack**  
    Returns a jagged style array which includes all characters up to the end of of the returned string.
     
     ```C#
     string TestString = "this/is/a/test/string";
     string[][] output = TestString.SplitExtensionTrack('/');
     
     foreach(string[] array_output in output)
        Console.WriteLine(array_output[0] + " " + array_output[1]);
     
     /*
			string[*][0]		string[*][1]
			this			this
			this/is			is
			this/is/a		a
			this/is/a/test		test
			this/is/a/test/string	string
      */  
      ```    
In this way, you can process things such as directory paths, etc, and get both the path and the name into separate categories.
    
- **WHY?**
    *  It's faster.  How much faster?  System dependant.  Run the benchmarks, or use your own testing.
    *  It only uses stack memory internally.  Nothing is put on the heap except what is output. (less memory usage)
    *  There is no internal buffer, no extra (heap) memory (native or otherwise) is used, only stack.*
    *  You can extend or modify its functionality through the source code.
    *  It has options for how to handle the delimiters in the output.  
    
        *If the string is over 1MB in size, it will revert to using heap instead of stack memory (slower).  Basically, it'll try to use up the stack.  If there isn't enough stack space available, it'll revert to using heap. (_malloca)*

- **ISSUES:**
1.  IntelliSense doesn't always update as aggressively as if it were a native C# project.  You need a successful build of the interop library for metadata to generate.  If it still doesn't generate (you don't need the metadata to compile), you can remove the project reference and add it back in, again.
1.  The macros (used internally, only) are annoying but necessary for enforcing strict uniform conventions for 18 different C++ functions.

- **CONTRIBUTING:**  
Please do.  Including micro-optimizations. I don't mind the library growing in scope.  
What I do not want:
1. Adding a buffer or using more memory than what is absolutely necessary.  Unless it's a separate set of functions or completely optional through functions.  I'm going for using only as much memory, stack or otherwise, as absolutely necessary.  A roughly (further) 25% speedup can be achieved by removing the entry counters and allocating a _wordEntry (16 bytes) for every character.  This will be achieved in the future by adding a buffer parameter to future functions, and by giving the option for less or more memory usage.  Currently, I have no plans on precisely how to do this.