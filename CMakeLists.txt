# CMake entry point
cmake_minimum_required (VERSION 2.6)
project (ruengine)

# delete CMakeCache.txt from the build directory when you edit these options
####################################################################
OPTION(MAKE_RUENGINE "Create RUEngine" ON)
####################################################################

if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like 'build')" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()


if(UNIX)
	#set(CMAKE_CXX_FLAGS "-Wall -std=c++0x -pedantic -O2 -g -pg")
	#set(CMAKE_CXX_FLAGS "-Wall -Wstrict-aliasing -std=c++0x -O2")

	set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

	# valgrind --leak-check=full ./demo
	# ./demo # creates cmon.out
	# gprof demo gmon.out > analysis.txt
	#set(CMAKE_CXX_FLAGS "-Wall -pg -std=c++11")
endif(UNIX)


if(WIN32)
	# On Visual 2005 and above, this module can set the debug working directory
	list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-1c73e35")
	include(CreateLaunchers)
	include(MSVCMultipleProcessCompile) # /MP

	if(MINGW)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	ELSE(MINGW)
		add_definitions( "/W3 /D_CRT_SECURE_NO_WARNINGS /wd4514 /nologo" ) # suppress pedantic warnings
	endif(MINGW)
endif(WIN32)


# Compile external dependencies
find_package(OpenGL REQUIRED)

add_subdirectory (external)

include_directories(
	${CMAKE_SOURCE_DIR}/external/glfw-3.0.3/include/GLFW
	${CMAKE_SOURCE_DIR}/external/glm-0.9.8.4
	${CMAKE_SOURCE_DIR}/external/glew-1.9.0/include
	${CMAKE_SOURCE_DIR}/external
  ${CMAKE_SOURCE_DIR}/external/irrKlang
  ${CMAKE_SOURCE_DIR}/RUEngine
	${CMAKE_SOURCE_DIR}/.
)

link_directories(
	${CMAKE_SOURCE_DIR}/external/glfw-3.0.3/src
	${CMAKE_SOURCE_DIR}/external/glew-1.9.0
	${CMAKE_SOURCE_DIR}/external
)


set(ALL_GRAPHICS_LIBS
	${OPENGL_LIBRARY}
	GLFW_303
	GLEW_190
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

####################################################################
# RUEngine                                                         #
####################################################################
IF(MAKE_RUENGINE)

  set(SOURCES

  ##SOIL IMAGE LOADER
  external/SOIL2/etc1_utils.c
  external/SOIL2/etc1_utils.h
  external/SOIL2/image_DXT.c
  external/SOIL2/image_DXT.h
  external/SOIL2/image_helper.c
  external/SOIL2/image_helper.h
  external/SOIL2/jo_jpeg.h
  external/SOIL2/pkm_helper.h
  external/SOIL2/pvr_helper.h
  external/SOIL2/SOIL2.c
  external/SOIL2/SOIL2.h
  external/SOIL2/stb_image_write.h
  external/SOIL2/stb_image.h
  external/SOIL2/stbi_DDS_c.h
  external/SOIL2/stbi_DDS.h
  external/SOIL2/stbi_ext_c.h
  external/SOIL2/stbi_ext.h
  external/SOIL2/stbi_pkm_c.h
  external/SOIL2/stbi_pkm.h
  external/SOIL2/stbi_pvr_c.h
  external/SOIL2/stbi_pvr.h
  ##END SOIL IMAGE LOADER

  	RUEngine/Demos/main.cpp
  	RUEngine/Engine/Display.cpp
    RUEngine/Engine/Input.cpp
    RUEngine/Engine/Renderer.cpp
    RUEngine/Engine/Shader.cpp
    RUEngine/Engine/Camera.h
    RUEngine/Engine/Mesh.cpp
    RUEngine/Engine/Superscene.cpp
    RUEngine/Engine/Texture.cpp
    RUEngine/Demos/Scene.cpp
    RUEngine/Demos/Scene0.cpp
    RUEngine/Demos/Scene1.cpp
    RUEngine/Demos/Scene2.cpp
    RUEngine/Maths/Time.cpp
    RUEngine/Engine/Entity.cpp
    RUEngine/Engine/ResourceManager.cpp
    RUEngine/Engine/Light.cpp
    RUEngine/Engine/OBJloader.cpp
    RUEngine/Engine/Superscene.cpp
    RUEngine/Engine/SceneManager.cpp
    )

    add_executable(ruengine ${SOURCES})

  target_link_libraries(ruengine ${ALL_GRAPHICS_LIBS}   )
  file(
  	COPY ${CMAKE_SOURCE_DIR}/RUEngine/Shaders
  	DESTINATION ${CMAKE_BINARY_DIR}
  )

  file(
  	COPY ${CMAKE_SOURCE_DIR}/RUEngine/Assets
  	DESTINATION ${CMAKE_BINARY_DIR}
  )

ENDIF()
