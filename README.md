RUEngine
====

RUEngine is a framework using the rendering system of openGL.

Compiling
---------

Use cmake to create your project files in a separate `build` directory.

> You should always be able to delete the `build` directory without losing your work! Whatever you do, work in the `src` directory!

Documentation
-------------

Documentation will be added soon using doxygen.

Linux
-----

On Debian-based Linux, install the following libraries:

	sudo apt-get install -y git cmake doxygen g++ libgl1-mesa-dev libglu1-mesa-dev libxrandr-dev libxi-dev

Run `bootstrap.sh` or:

	mkdir build
	cd build
	cmake -Wno-dev ..
	make

Then you can run the demo:

	./ruengine

Make sure to add any new files you create to the `CMakeLists.txt` file.

Mac OS X
--------

Install the following:

- XCode + commandline developer tools
- git
- cmake
- doxygen

Run `bootstrap.sh` or:

	mkdir build
	cd build
	cmake -Wno-dev ..
	make

Then you can run the demo:

	./ruengine

Make sure to add any new files you create to the `CMakeLists.txt` file.

MS Windows (VS2015)
-------------------

No support yet! I'll update it as soon as possible.

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
# RUEngine
