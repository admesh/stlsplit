#!lua

solution "stlsplit"
	location ( "." )
	configurations { "Debug", "Release" }
	platforms {"native", "x64", "x32"}
  
	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols", "ExtraWarnings"}

	configuration "Release"
		defines { "NDEBUG" }
		flags { "Optimize", "ExtraWarnings"}    


	project "lib"
		language "C++"
		kind "SharedLib"
		files { "stlsplit.cpp", "*.h" }
		targetdir("build")
		linkoptions { "-Wl,-soname,libstlsplit.so.1" }
		targetname ("stlsplit")
		targetextension (".so.1")

	project "cli"
		kind "ConsoleApp"
		language "C++"
		linkoptions { "-Lbuild" }
		links { ":libstlsplit.so.1", "admesh" }
		files { "cli.cpp" }
		targetdir("build")
		targetname ("stlsplit")

