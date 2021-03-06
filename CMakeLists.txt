# CMake entry point
cmake_minimum_required (VERSION 2.6)
project (ruengine)

# delete CMakeCache.txt from the build directory when you edit these options
####################################################################
OPTION(MAKE_DEMO "Create DEMO" ON)
OPTION(MAKE_NMHD "Create NormalMap vs HighDetail" OFF)
OPTION(MAKE_GOL "Create Game of Life" OFF)
OPTION(MAKE_LA "Create Langtons Ant" OFF)
OPTION(MAKE_BB "Create Brian's Brain" OFF)
OPTION(MAKE_WW "Create Wire World" OFF)
OPTION(MAKE_MAZE "Create Maze" OFF)
OPTION(MAKE_MB "Create Mustache Bot" ON)

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
      ${CMAKE_SOURCE_DIR}/external/freetype2/include
      ${CMAKE_SOURCE_DIR}/external/freetype2
  ${CMAKE_SOURCE_DIR}/external/irrKlang
  ${CMAKE_SOURCE_DIR}/RUEngine
	${CMAKE_SOURCE_DIR}/.
)

link_directories(
	${CMAKE_SOURCE_DIR}/external/glfw-3.0.3/src
	${CMAKE_SOURCE_DIR}/external/glew-1.9.0
	${CMAKE_SOURCE_DIR}/external
      ${CMAKE_SOURCE_DIR}/external/freetype2/include
      ${CMAKE_SOURCE_DIR}/external/freetype2
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

set(SOILSOURCE
  ##SOIL IMAGE LOADER
  external/SOIL2/etc1_utils.c
  external/SOIL2/etc1_utils.h
  external/SOIL2/image_DXT.c
  external/SOIL2/image_DXT.h  external/SOIL2/image_helper.c
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
)

set(RUGINESOURCE
    RUEngine/Engine/Display.cpp
    RUEngine/Engine/Input.cpp
    RUEngine/Engine/Renderer.cpp
    RUEngine/Engine/Shader.cpp
    RUEngine/Engine/Camera.h
    RUEngine/Engine/Mesh.cpp
    RUEngine/Engine/Superscene.cpp
    RUEngine/Engine/Texture.cpp
    RUEngine/Maths/Time.cpp
    RUEngine/Engine/Entity.cpp
    RUEngine/Engine/ResourceManager.cpp
    RUEngine/Engine/Light.cpp
    RUEngine/Engine/OBJloader.cpp
    RUEngine/Engine/Superscene.cpp
    RUEngine/Engine/SceneManager.cpp
    RUEngine/Engine/Skybox.cpp
    RUEngine/Engine/Framebuffer.cpp
    RUEngine/Engine/Raycast.cpp
    RUEngine/Engine/Water.cpp
    RUEngine/Engine/Terrain.cpp
    RUEngine/Maths/Collision.cpp
  )

####################################################################
# Rugine DEMO                                                        #
####################################################################
IF(MAKE_DEMO)
  set(SOURCES
    RUEngine/Demos/main.cpp
    RUEngine/Demos/Scene.cpp
    RUEngine/Demos/Scene0.cpp
    RUEngine/Demos/Scene1.cpp
    RUEngine/Demos/Scene2.cpp
    RUEngine/Demos/Scene3.cpp
  )

  add_executable(demo ${SOURCES} ${SOILSOURCE} ${RUGINESOURCE})

  target_link_libraries(demo ${ALL_GRAPHICS_LIBS}   )
  file(
  	COPY ${CMAKE_SOURCE_DIR}/RUEngine/Shaders
  	DESTINATION ${CMAKE_BINARY_DIR}
  )

  file(
  	COPY ${CMAKE_SOURCE_DIR}/RUEngine/Demos/Assets
  	DESTINATION ${CMAKE_BINARY_DIR}
  )

  include_directories("external/freetype2/include")
ENDIF()



####################################################################
# Rugine Normalmap vs High Detail                                  #
####################################################################
IF(MAKE_NMHD)
  set(SOURCES
    RUEngine/NMHD/main.cpp
    RUEngine/NMHD/Scene.cpp
    RUEngine/NMHD/Scene0.cpp
  )

  add_executable(NMHD ${SOURCES} ${SOILSOURCE} ${RUGINESOURCE})

  target_link_libraries(NMHD ${ALL_GRAPHICS_LIBS}   )
  file(
  	COPY ${CMAKE_SOURCE_DIR}/RUEngine/Shaders
  	DESTINATION ${CMAKE_BINARY_DIR}
  )

  file(
  	COPY ${CMAKE_SOURCE_DIR}/RUEngine/NMHD/Assets
  	DESTINATION ${CMAKE_BINARY_DIR}
  )

ENDIF()

####################################################################
# Rugine Game of life			                           #
####################################################################
IF(MAKE_GOL)
  set(SOURCES
    RUEngine/GOL/main.cpp
    RUEngine/GOL/Scene.cpp
  )

  add_executable(GOL ${SOURCES} ${SOILSOURCE} ${RUGINESOURCE})

  target_link_libraries(GOL ${ALL_GRAPHICS_LIBS}   )
  file(
  	COPY ${CMAKE_SOURCE_DIR}/RUEngine/Shaders
  	DESTINATION ${CMAKE_BINARY_DIR}
  )


ENDIF()

####################################################################
# Rugine Langtons ant		                                   #
####################################################################
IF(MAKE_LA)
  set(SOURCES
    RUEngine/LA/main.cpp
    RUEngine/LA/Scene.cpp
  )

  add_executable(LA ${SOURCES} ${SOILSOURCE} ${RUGINESOURCE})

  target_link_libraries(LA ${ALL_GRAPHICS_LIBS}   )
  file(
  	COPY ${CMAKE_SOURCE_DIR}/RUEngine/Shaders
  	DESTINATION ${CMAKE_BINARY_DIR}
  )


ENDIF()

####################################################################
# Rugine Brians Brain		                                   #
####################################################################
IF(MAKE_BB)
  set(SOURCES
    RUEngine/BB/main.cpp
    RUEngine/BB/Scene.cpp
  )

  add_executable(BB ${SOURCES} ${SOILSOURCE} ${RUGINESOURCE})

  target_link_libraries(BB ${ALL_GRAPHICS_LIBS}   )
  file(
  	COPY ${CMAKE_SOURCE_DIR}/RUEngine/Shaders
  	DESTINATION ${CMAKE_BINARY_DIR}
  )


ENDIF()

####################################################################
# Rugine Wireworld		                                   #
####################################################################
IF(MAKE_WW)
  set(SOURCES
    RUEngine/WW/main.cpp
    RUEngine/WW/Scene.cpp
  )

  add_executable(WW ${SOURCES} ${SOILSOURCE} ${RUGINESOURCE})

  target_link_libraries(WW ${ALL_GRAPHICS_LIBS}   )
  file(
  	COPY ${CMAKE_SOURCE_DIR}/RUEngine/Shaders
  	DESTINATION ${CMAKE_BINARY_DIR}
  )

  file(
  	COPY ${CMAKE_SOURCE_DIR}/RUEngine/WW/Assets
  	DESTINATION ${CMAKE_BINARY_DIR}
  )

ENDIF()

####################################################################
# Rugine Maze generator + solver                                   #
####################################################################
IF(MAKE_MAZE)
  set(SOURCES
    RUEngine/MAZE/main.cpp
    RUEngine/MAZE/Scene.cpp
  )

  add_executable(MAZE ${SOURCES} ${SOILSOURCE} ${RUGINESOURCE})

  target_link_libraries(MAZE ${ALL_GRAPHICS_LIBS}   )
  file(
  	COPY ${CMAKE_SOURCE_DIR}/RUEngine/Shaders
  	DESTINATION ${CMAKE_BINARY_DIR}
  )


ENDIF()

####################################################################
# Rugine Mustache bot		                                   #
####################################################################
IF(MAKE_MB)
  set(SOURCES
    RUEngine/MB/main.cpp
		RUEngine/MB/StartMenu.cpp
    RUEngine/MB/Scene.cpp
		RUEngine/MB/Scene1.cpp
		RUEngine/MB/RailTrack.cpp
		RUEngine/MB/Bullet.cpp
		RUEngine/MB/Mirror.cpp
		RUEngine/MB/Wall.cpp
		RUEngine/MB/Enemy.cpp
		RUEngine/MB/CameraEffects.cpp;
  )

  add_executable(MB ${SOURCES} ${SOILSOURCE} ${RUGINESOURCE})

  target_link_libraries(MB ${ALL_GRAPHICS_LIBS}   )
  file(
  	COPY ${CMAKE_SOURCE_DIR}/RUEngine/Shaders
  	DESTINATION ${CMAKE_BINARY_DIR}
  )

	file(
	COPY ${CMAKE_SOURCE_DIR}/RUEngine/Demos/Assets
	DESTINATION ${CMAKE_BINARY_DIR}
	)


ENDIF()
