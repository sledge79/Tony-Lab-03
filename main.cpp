
#include "mbed.h"
#include "LSM6DSLSensor.h"

#define PI 3.141592654

static DevI2C devI2c(PB_11,PB_10);
static LSM6DSLSensor acc_gyro(&devI2c,0xD4,D4,D5); // high address


float compute (int x, int y, int z, int x_ref, int y_ref, int z_ref) {
    
    float dot_product = x * x_ref + y * y_ref + z * z_ref;
    float magnitude1 = sqrt(x * x + y * y + z * z);
    float magnitude2 = sqrt(x_ref * x_ref + y_ref * y_ref + z_ref * z_ref);
    float angle_radians = acos(dot_product / (magnitude1 * magnitude2));
    float angle_degrees = angle_radians * 180.0 / PI;

    return angle_degrees;
}


/* Simple main function */
int main() {
    uint8_t id;
    int32_t axes[3];
    float res=0;
    acc_gyro.init(NULL);

    acc_gyro.enable_x();
    acc_gyro.enable_g();

    printf("This is an accelerometer example running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    acc_gyro.read_id(&id);
    printf("LSM6DSL accelerometer & gyroscope = 0x%X\r\n", id);

    while(1) {

        acc_gyro.get_x_axes(axes);
        res =(axes[0], axes[1], axes[2]);
        printf("LSM6DSL: %6d, %6d, %6d, %3.2f\r\n", axes[0], axes[1], axes[2], res);


        thread_sleep_for(2000);

    }
}