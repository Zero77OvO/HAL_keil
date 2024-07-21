#include "head_files.h"

short aacx, aacy, aacz;    // ���ٶȼ�
short gyrox, gyroy, gyroz; // ���ٶȼ�


typedef struct Angles
{
    float pitch;
    float roll;
    float yaw;
} eulerianAngles_t;
float gx0, gy0, gz0;
float a_x, a_y, a_z, g_x, g_y, g_z = 0;
float AX, AY, AZ, GX, GY, GZ = 0;
float AX_old, AY_old, AZ_old = 0;
#define new_weight 0.65f
#define old_weight 0.35f
float GX_Zero = -62;
float GY_Zero = -32;
float GZ_Zero = -3;
void IMUFliter()
{
    int i;
    float acc[3] = {0}, gyro[3] = {0};

    for (i = 0; i < 3; i++)
    {
        GetImuMsg();
        acc[0] += aacx;
        acc[1] += aacy;
        acc[2] += aacz;
        gyro[0] += gyrox;
        gyro[1] += gyroy;
        gyro[2] += gyroz;
    }
    gx0 = gyro[0] / 3.0f; // ���������Ǿ�ֹϵ����
    gy0 = gyro[1] / 3.0f;
    gz0 = gyro[2] / 3.0f;

    AX = acc[0] / 3.0f;
    AY = acc[1] / 3.0f;
    AZ = acc[2] / 3.0f;
		
    GX = gx0 - GX_Zero; // ȥ��Ư֮��������ǲɼ�ֵ
    GY = gy0 - GY_Zero;
    GZ = gz0 - GZ_Zero;

    g_x = GX * 0.001063686f; // ��������3.14/180/16.5
    g_y = GY * 0.001063686f;
    g_z = GZ * 0.001063686f;
    a_x = AX * new_weight + AX_old * old_weight;
    a_y = AY * new_weight + AY_old * old_weight;
    a_z = AZ * new_weight + AZ_old * old_weight;

    AX_old = a_x;
    AY_old = a_y;
    AZ_old = a_z;
}
/****************************��̬�����ں�***************************/
/* ��̬�����ں�
�������gx��gy��gz�ֱ��Ӧ������Ľ��ٶȣ���λ�ǻ���/��
�������ax��ay��az�ֱ��Ӧ������ļ��ٶ����ݣ�
���ڼ��ٶȵ������ϴ��ڶ�ȡ��ʱ��������ǲ��õ�ͨ�˲�
*/
#define delta_T 0.01f       // 5ms����һ��//0.005f
float I_ex, I_ey, I_ez;      // ������
eulerianAngles_t eulerAngle; // ŷ����
float param_Kp = 8.0;        // ���ٶȼƵ��������ʱ�������,̫��������Ƽ��ٶȼƶ�����̫С�޷�����  //50
float param_Ki = 0.2;        // �������������ʵĻ������� 0.2
float q0 = 1;                // ��ʼ��Ԫ������
float q1, q2, q3 = 0;
void IMU_AHRSupdate_noMagnetic(float gx, float gy, float gz, float ax, float ay, float az) // ��Ԫ����ȡ
{
    float halfT = 0.5f * delta_T;
    float vx, vy, vz; // ��ǰ�Ļ�������ϵ�ϵ�������λ����
    float ex, ey, ez; // ��Ԫ������ֵ����ٶȼƲ���ֵ�����
    float q0q0 = q0 * q0;
    float q0q1 = q0 * q1;
    float q0q2 = q0 * q2;
    //        float q0q3 = q0 * q3;
    float q1q1 = q1 * q1;
    //        float q1q2 = q1 * q2;
    float q1q3 = q1 * q3;
    float q2q2 = q2 * q2;
    float q2q3 = q2 * q3;
    float q3q3 = q3 * q3;

    // �Լ��ٶ����ݽ��й�һ�� �õ���λ���ٶ�
    // ���ٶȼƲ����������������ax��ay��az
    float norm = invSqrt(ax * ax + ay * ay + az * az);
    ax = ax * norm;
    ay = ay * norm;
    az = az * norm;

    // �����vx��vy��vz����ʵ��������һ����̬����Ԫ��������������ڵ�ǰ������ϵ�ϵ�������λ������
    vx = 2 * (q1q3 - q0q2);
    vy = 2 * (q0q1 + q2q3);
    vz = q0q0 - q1q1 - q2q2 + q3q3;

    // ����֮�����������������ϴ���̬�ͼ��ٶȼƲ��������̬֮�����
    ex = ay * vz - az * vy;
    ey = az * vx - ax * vz;
    ez = ax * vy - ay * vx;

    // �ò���������PI����������ƫ��
    // ͨ������ param_Kp��param_Ki �������������Կ��Ƽ��ٶȼ����������ǻ�����̬���ٶȡ�
    I_ex += delta_T * ex;
    I_ey += delta_T * ey;
    I_ez += delta_T * ez;
    gx = gx + param_Kp * ex + param_Ki * I_ex;
    gy = gy + param_Kp * ey + param_Ki * I_ey;
    gz = gz + param_Kp * ez + param_Ki * I_ez;

    /*����Ϊֹ��ʹ�ü��ٶȼ����ݶ����������ݵ������Ѿ���ɣ��������̬�����е�����ں�*/
    /*���������Ԫ��΢�ַ��̣�ʹ������������������ݶ�ʱ����֣��õ���ǰ��̬����Ԫ����ʾ����Ȼ�������Ԫ���ĵ�λ������*/

    // ��Ԫ��΢�ַ��̣�����halfTΪ�������ڵ�1/2��gx gy gzΪ�����ǽ��ٶȣ����¶�����֪��������ʹ����һ��������������Ԫ��΢�ַ���
    q0 = q0 + (-q1 * gx - q2 * gy - q3 * gz) * halfT;
    q1 = q1 + (q0 * gx + q2 * gz - q3 * gy) * halfT;
    q2 = q2 + (q0 * gy - q1 * gz + q3 * gx) * halfT;
    q3 = q3 + (q0 * gz + q1 * gy - q2 * gx) * halfT;

    norm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
    q0 = q0 * norm;
    q1 = q1 * norm;
    q2 = q2 * norm;
    q3 = q3 * norm;
}
/****************************���ټ���1/sqrt(x)�ĺ���***************************/
float invSqrt(float x)
{
    float halfx = 0.5f * x;
    float y = x;
    long i = *(long *)&y;
    i = 0x5f3759df - (i >> 1);
    y = *(float *)&i;
    y = y * (1.5f - (halfx * y * y));
    return y;
}

/****************************��Ԫ����ȡŷ����***************************/
float Trans[3] = {0,0,0};
void Angle_get(void)
{
    IMUFliter();
    IMU_AHRSupdate_noMagnetic(g_x, g_y, g_z, a_x, a_y, a_z); // ��ȡ��Ԫ��

    // ������Ԫ�������������ŷ���ǵ�ת����ϵ������Ԫ��ת����ŷ����
    eulerAngle.pitch = -asin(-2 * q1 * q3 + 2 * q0 * q2) * 57.3;                                    // pitch   57.3=180/3.14
    eulerAngle.roll = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2 * q2 + 1) * 57.3;      // roll
    eulerAngle.yaw = atan2(2 * q1 * q2 + 2 * q0 * q3, -2 * q2 * q2 - 2 * q3 * q3 + 1) * 57.3; // yaw
    Trans[0] = eulerAngle.pitch;
    Trans[1] = eulerAngle.roll;
    Trans[2] = eulerAngle.yaw;
}
void GetImuMsg()
{
    MPU_Get_Accelerometer(&aacx, &aacy, &aacz); // �õ����ٶ�
    MPU_Get_Gyroscope(&gyrox, &gyroy, &gyroz);  // �õ����ٶ�
}

