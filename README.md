Rugine
====

Rugine is a framework using the rendering system of openGL.

Compiling
---------

Use cmake to create your project files in a separate `build` directory.

When changing I'd suggest making them in source directory and run CMake after you want to test, Otherwise CMake will write over the shaders in the build directory.

Documentation
-------------

Documentation will be added soon using doxygen.

Building
-----

On Debian-based Linux, install the following libraries:
	sudo apt-get install -y git cmake doxygen g++ libgl1-mesa-dev libglu1-mesa-dev libxrandr-dev libxi-dev
On Windows and MacOS:
	Install make and cmake, and make sure you have atleast the C++11 compiler installed.
Use those command to build:

	mkdir build
	cd build
	cmake -Wno-dev ..
	make

Then you can run the demo:

	./demo


  Documentation
  -----
    Make sure doxygen is installed
    the use these commands

      doxygen Doxyfile

Libraries
---------

- glfw: <http://www.glfw.org/>
- glew: <http://glew.sourceforge.net/>
- glm: <http://glm.g-truc.net/>

Links
-----

- <http://learnopengl.com/>

License
-------

Copyright 2017 Rutger Klamer <rutger.klamer@gmail.com>

This project is provided as opensource. If you decide to use this projects I'd like to recieve some credits but it's not needed.
#Rugine
