Rugine
====

Rugine is a framework using the rendering system of openGL.

Rugine also provides a set of different demo's,
those are still included here they will be getting their own repository later.

Compiling
---------

Use cmake to create your project files in a separate `build` directory.

Building
-----

On Debian-based Linux, install the following libraries:
	sudo apt-get install -y git cmake doxygen g++ libgl1-mesa-dev libglu1-mesa-dev libxrandr-dev libxi-dev
On Windows and MacOS:
	Install make and cmake, and make sure you have atleast the C++11 compiler installed.
Use those command to build:

	mkdir build
	cd build
	cmake ..
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

Copyright 2018 Rutger Klamer <rutger.klamer@gmail.com>

This project is provided as opensource. Do with it whatever you want.
