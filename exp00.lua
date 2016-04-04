
solution "opengl_exp"
	configurations {"Debug", "Release"}

project "map"
	language "C++"
	kind "WindowedApp"
	
	files {
		"**.hpp",
		"**.cpp"
	}
	
	links{
		"SDL2main",
		"SDL2",
		"glload",
		"glutil",
		"glmath",
		"opengl32"
	}
	
	includedirs{
		"../freefont/include",
		"../freefont/include/freetype2",
		"../SDL/include",
		"../glsdk_0_5_2/glload/include",
		"../glsdk_0_5_2/glutil/include",
		"../glsdk_0_5_2/boost",
		"../glsdk_0_5_2/glm"
	}
	
	libdirs{
		"../freefont/lib",
		"../SDL/lib/x86",
		"../glsdk_0_5_2/glload/lib",
		"../glsdk_0_5_2/glutil/lib",
		"../glsdk_0_5_2/glutil/lib"
	}