Visual Studio Natvis Royale 
===========================

Visual Studio 2012 introduced a new type visualization framework (natvis) for customizing the way C++ types are displayed in the debugger.
This file (royale.natvis) will add debugger support for the Royale types (Pair, String, Vector).

https://code.msdn.microsoft.com/Writing-type-visualizers-2eae77a2

Please copy the royale.natvis file into one of the following directories :

- %VSINSTALLDIR%\Common7\Packages\Debugger\Visualizers (requires admin access)
- %USERPROFILE%\My Documents\Visual Studio 2012\Visualizers\ (depending on the Visual Studio version)