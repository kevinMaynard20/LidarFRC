/*
 * jnilidar.c Java Native Interface code for YdLidar driver
 *
 */

#include <jni.h>
#include "YdLidarX4.h"

#include "CYdLidar.h"
#include <iostream>
#include <string>
#include <memory>

using namespace std;
using namespace ydlidar;
CYdLidar laser;


/*
 * Class:     de_konteno_ao_mrover_lidar_YdLidarX4
 * Method:    init
 * Signature: (Ljava/lang/String;IIII)V
 */
JNIEXPORT void JNICALL Java_de_konteno_ao_mrover_lidar_YdLidarX4_init
(JNIEnv *env, jobject, jstring jport, jint jminRange, jint jmaxRange, jint jminAngle, jint jmaxAngle)
{

    printf("__   ______  _     ___ ____    _    ____  \n");
    printf("\\ \\ / /  _ \\| |   |_ _|  _ \\  / \\  |  _ \\ \n");
    printf(" \\ V /| | | | |    | || | | |/ _ \\ | |_) | \n");
    printf("  | | | |_| | |___ | || |_| / ___ \\|  _ <  \n");
    printf("  |_| |____/|_____|___|____/_/   \\_\\_| \\_\\ \n");
    printf("\n");
    fflush(stdout);

    const char *port = env->GetStringUTFChars(jport, nullptr);

    laser.setSerialPort(port);
    laser.setSerialBaudrate(128000);
    // Set and acquire laser band signal quality (only supported by S4B radar)
    laser.setIntensities(false);  //intensity
    laser.setAutoReconnect(true); //hot plug

    // laser.setMinRange(0.1);
    // laser.setMaxRange(4.0);

    laser.setMinRange((int)jminRange / 100.0);
    laser.setMaxRange((int)jmaxRange / 100.0);
    printf("range: %3.3f .. %3.3f\n", laser.getMinRange(), laser.getMaxRange());

    // laser.setMinAngle(-180);
    // laser.setMaxAngle(180);
    laser.setMinAngle((int)jminAngle);
    laser.setMaxAngle((int)jmaxAngle);

    // Set and get to rotate the laser 180 degrees
    laser.setReversion(false);
    // Set and get the laser is a fixed angle resolution
    laser.setFixedResolution(true);
    laser.initialize();
}

bool hardError;
LaserScan scan;
int dist[720];

/*
 * Class:     de_konteno_ao_mrover_lidar_YdLidarX4
 * Method:    scan
 * Signature: ()[I
 */
JNIEXPORT jintArray JNICALL Java_de_konteno_ao_mrover_lidar_YdLidarX4_scan(JNIEnv *env, jobject)
{
    jintArray jdist = env->NewIntArray(720);

    if (laser.doProcessSimple(scan, hardError))
    {
        for (int i = 0; i < scan.ranges.size(); i++)
        {
            float angle = scan.config.min_angle + i * scan.config.ang_increment;
            dist[i] = 100 * scan.ranges[i];
        }
        ydlidar::console.message("Scan received[%llu]: %u ranges", scan.self_time_stamp, (unsigned int)scan.ranges.size());
    }
    else
    {
        ydlidar::console.warning("Failed to get Lidar Data");
        //throw exception
        env->ThrowNew(env->FindClass("java/lang/Exception"), "Failed to get Lidar data");
    }

    env->SetIntArrayRegion(jdist, 0, 720, dist);
    return jdist;
}


/*
 * Class:     de_konteno_ao_mrover_lidar_YdLidarX4
 * Method:    turnOn
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_de_konteno_ao_mrover_lidar_YdLidarX4_turnOn
  (JNIEnv *, jobject)
{
    laser.turnOn();
}

/*
 * Class:     de_konteno_ao_mrover_lidar_YdLidarX4
 * Method:    turnOff
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_de_konteno_ao_mrover_lidar_YdLidarX4_turnOff
  (JNIEnv *, jobject)
{
    laser.turnOff();
}
