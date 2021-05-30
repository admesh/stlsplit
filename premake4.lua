#!lua

solution "stlsplit"
	location ( "." )
	targetdir("build")
	configurations { "Debug", "Release" }
	platforms {"native", "x64", "x32"}

	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols", "ExtraWarnings"}

	configuration "Release"
		defines { "NDEBUG" }
		flags { "Optimize", "ExtraWarnings"}    

        project "static-lib"
                language "C++"
                kind "StaticLib"
                files { "stlsplit.cpp", "*.h" }
                targetname ("stlsplit")
                links { "admesh" }

	project "lib"
		language "C++"
		kind "SharedLib"
		files { "stlsplit.cpp", "*.h" }
		targetname ("stlsplit")
		links { "admesh" }
		configuration { "linux" }
			targetextension (".so.1")
			linkoptions { "-Wl,-soname,libstlsplit.so.1" }
			postbuildcommands { "ln -sf libstlsplit.so.1 build/libstlsplit.so" }
			--cleancommands { "rm build/libstlsplit.so || :" }
		configuration { "macosx" }
			targetextension (".1.dylib")
			postbuildcommands { "ln -sf libstlsplit.1.dylib build/libstlsplit.dylib" }
			--cleancommands { "rm build/libstlsplit.dylib || :" }

	project "cli"
		kind "ConsoleApp"
		language "C++"
		linkoptions { "-Lbuild" }
		files { "cli.cpp" }
		targetname ("stlsplit")
		links { "lib", "admesh" }
