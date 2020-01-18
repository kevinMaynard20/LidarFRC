package de.konteno.ao.mrover.lidar;

import de.konteno.ao.mrover.lidar.NativeUtils;

public class YdLidarX4 {

	static {
		// System.loadLibrary("lidar");
		try {
			System.loadLibrary("lidar");
		} catch (UnsatisfiedLinkError e) {
			try {
				// during runtime. .SO within .JAR
				NativeUtils.loadLibraryFromJar("/de/konteno/ao/mrover/lidar/liblidar.so");
				System.out.println("loaded liblidar.so from jar");
			} catch (java.io.IOException e1) {
				throw new RuntimeException(e1);
			}
		}
	}

	public native void init(String port, int minRange, int maxRange, int minAngle, int maxAngle);

	public native int[] scan();

	public native void turnOn();

	public native void turnOff();

	public static void main(String[] args) throws Exception {
		YdLidarX4 x = new YdLidarX4();
		x.init("/dev/ttyS0", 10, 500, -180, 180);

		x.turnOff();
		Thread.sleep(5000);
		x.turnOn();

		for (int n = 0; n < 3; ++n) {

			int[] dist = x.scan();
			for (int d : dist) {
				System.out.print(d + " ");
			}
			System.out.println();
			// x.turnOff();
			Thread.sleep(2000);
		}
	}
}
