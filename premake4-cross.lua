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


	project "lib"
		language "C++"
		files { "stlsplit.cpp", "*.h" }
		targetname ("stlsplit")
		links { "admesh" }
		kind "StaticLib"
