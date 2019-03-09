# Makefile for YdLidar driver
#

BASEDIR = ../../../../../..
JAVADIR = $(BASEDIR)/java
CDIR    = $(BASEDIR)/c
JFLAGS = -Xlint
#JDKINC = -I /usr/lib/jvm/java-7-openjdk-amd64/include
#JDKINC = -I /usr/lib/jvm/java-8-oracle/include -I /usr/lib/jvm/java-8-oracle/include/linux
JDKINC = -I /usr/lib/jvm/zulu-embedded-8-armhf/include -I /usr/lib/jvm/zulu-embedded-8-armhf/include/linux
#JDKINC = -I /opt/jdk1.7.0_67/include -I /opt/jdk1.7.0_67/include/linux


# Set SIMD compile params based on architecture
ifeq ("$(ARCH)","armv7l")
  SIMD_FLAGS = -mfpu=neon
else ifeq ("$(ARCH)","i686")
  SIMD_FLAGS = -msse3
else
  ARCH = sisd
endif


ALL = liblidar.so YdLidarX4.class jar

all: $(ALL)

#libydlidar_driver.so must be installed in /usr/local/lib

jar: liblidar.so YdLidarX4.class NativeUtils.class
	jar cvf $(BASEDIR)/mrover-lidar.jar -C $(JAVADIR) .

liblidar.so: jnilidar.o
	gcc -shared -fpic -Wl,-soname,liblidar.so -o liblidar.so jnilidar.o $(BASEDIR)/libydlidar_driver.so

jnilidar.o: jnilidar.c YdLidarX4.h
	c++   \
		-I$(BASEDIR)/include -I$(BASEDIR)/src -I$(BASEDIR) $(JDKINC) \
		-std=c++11 -std=c++11   -std=c++11  -fPIC -c jnilidar.c


YdLidarX4.class: YdLidarX4.java
	javac -classpath $(JAVADIR) YdLidarX4.java

NativeUtils.class: NativeUtils.java
	javac -classpath $(JAVADIR) NativeUtils.java


YdLidarX4.h: YdLidarX4.class
	javah -o YdLidarX4.h -classpath $(JAVADIR) -jni de.konteno.ao.mrover.lidar.YdLidarX4

	
test1:
	java -Djava.library.path=. -classpath $(JAVADIR) de.konteno.ao.mrover.lidar.YdLidarX4

test2:
	java -cp $(BASEDIR)/mrover-lidar.jar de.konteno.ao.mrover.lidar.YdLidarX4

clean:
		rm -f *.class *.o *.h *.so *~

backup:
		cp *.java bak
		cp Makefile bak
