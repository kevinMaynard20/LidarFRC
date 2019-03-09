YDLIDAR SDK PACKAGE V1.3.9 + Java Wrapper
=====================================================================

based on https://github.com/EAIBOT/ydlidar / https://github.com/yangfuyuan/sdk

How to build YDLIDAR Java SDK
=====================================================================
    $ git clone https://github.com/ospringauf/ydlidar.git
    $ cd sdk
    $ cmake .
    $ make			###linux
    $ sudo cp libydlidar_driver.so /usr/local/bin
	$ sudo ldconfig
	$ cd java/de/konteno/ao/mrover/lidar
	$ nano Makefile # set JDKINC path for your system
	$ make
	$ make jar
	$ make test1

Jar file in sdk/mrover-lidar.jar contains the Java driver wrapper. In addition, libydlidar_driver.so must be present on the library path.

How to merge upstream updates
=====================================================================
	$ git remote add upstream https://github.com/EAIBOT/ydlidar.git
	$ git fetch upstream
	$ git merge upstream/master