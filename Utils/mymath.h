/***
*mymath.h
*
*       
*
*Purpose:
*       This file defined the functions and variables used by users
*       to fast computation the result of trigonometric functions and
*       the square root.
****/
#include "stm32l1xx_hal.h"
#include "stdbool.h"
#include "math.h"
#include "float.h"
#ifndef __MY_MATH_H___
#define __MY_MATH_H___
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus
//#define TRUE 1
//#define FALSE 0
#define LOCATION_SCALING_FACTOR             111318.84502145034f
#define LOCATION_SCALING_FACTOR_INV         (1/LOCATION_SCALING_FACTOR)
#define REAL   float
#define TAN_MAP_RES                         0.003921569f     /* (smallest non-zero value in table) */
#define RAD_PER_DEG                         0.017453293f
#define TAN_MAP_SIZE                        256
#define ISFINITE(x) isfinite(x)
#ifndef M_PI_F
#define M_PI_F 3.14159265358979323846f
#endif

#ifndef M_PI_2_F
#define M_PI_2_F (M_PI / 2.0f)
#endif

#define M_PI 3.141592653589793f
#define M_2PI         (M_PI * 2)

#ifndef M_PI_2
#define M_PI_2    		(M_PI / 2)
#endif

#define Gravity	9.80665f	
#define GRAVITY_MSS	Gravity
#define CONSTANTS_ONE_G GRAVITY_MSS
#define	DEG_TO_RAD  (M_PI_F / 180.0f)	
#define RAD_TO_DEG	(180.0f / M_PI_F)

#define my_3_norm(x,y,z) (my_sqrt(my_pow((x)) + my_pow((y)) + my_pow((z))))
#define my_2_norm(x,y) (my_sqrt(my_pow((x)) + my_pow((y))))

#define my_pow(a) ((a)*(a))
#define safe_div(numerator,denominator,safe_value) ( (denominator == 0) ? (safe_value) : ((numerator)/(denominator)) )
#define ABS(x) ( (x)>0?(x):-(x) )
#define my_labs(x) ( (x)>0?(x):-(x) )
#define LIMIT( x,min,max ) ( (x) < (min)  ? (min) : ( (x) > (max) ? (max) : (x) ) )

#define my_pow_2_curve(in,a,max) (((1.0f - (a)) + (a) *abs((in) / (max))) * in)

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define MAX max
#define MIN min

#define ARRAY_SIZE(_arr) (sizeof(_arr) / sizeof(_arr[0]))
    
float ToRad(float x);
float ToDeg(float x);
float radians(float deg);
float degrees(float rad);

#define constrain(_x, _min, _max)	(((_x) < (_min)) ? (_min) : (((_x) > (_max)) ? (_max) : (_x)))

float constrain_float(float amt, float low, float high);
int16_t constrain_int16(int16_t amt, int16_t low, int16_t high);
int32_t constrain_int32(int32_t amt, int32_t low, int32_t high);
int16_t constrain_uint16(uint16_t amt, uint16_t low, uint16_t high);
int32_t constrain_uint32(uint32_t amt, uint32_t low, uint32_t high);

#define RadiansToCentiDegrees(x) (float)(x) * RAD_TO_DEG * 100.0f
float safe_asin(float v);
float safe_sqrt(float v);
float my_abs(float f);
REAL fast_atan2(REAL y, REAL x);
//float my_pow(float a);
float my_sqrt(float number);
double mx_sin(double rad);
double my_sin(double rad);
float my_cos(double rad);
float my_deathzoom(float x,float ,float zoom);
float my_deathzoom_2(float x,float ,float zoom);

float my_deadzone_p(float x,float zone);
float my_deadzone_n(float x,float zone);

//float To_180_degrees(float x);
//double To_180_degrees_db(double x);
//float my_pow_2_curve(float in,float a,float max);
//float safe_div(float numerator ,float denominator,float sv);
float linear_interpolation_5(float range[5],float interpolation[5],float in);//range 必须从小到大


uint8_t char_To_Hex(char x);
bool is_zero(float T);
bool is_equal(float v_1, float v_2);
bool is_negative(float T);
bool is_positive(float v);

void swap(short *a,short *b);

float pythagorous2(float a, float b);
float pythagorous3(float a, float b, float c);
float sq(float v);
float norm2(float a, float b);
float norm3(float a, float b ,float c);

float wrap_360(float angle, float unit_mod);
float wrap_180(float angle, float unit_mod);

float wrap_180_cd(float angle);
float wrap_360_cd(float angle);

float wrap_2PI(float radian);
float wrap_PI(float radian);
#define wrap_pi wrap_PI
#define wrap_2pi wrap_2PI
bool judgment_range_valid_float(float value ,float value_min,float value_max );
bool judgment_range_valid_int(int value ,int value_min,int value_max );
float norm_2d(const float first, const float second);
void Math_UB482_2_DjiA3_Vector2CoordinateConversion(const float fXRaw ,const float fYRaw ,float fAngleErr_Deg ,float * pfX ,float *pfY);
void location_diff(double fLocA_lat_Deg, 
                    double fLocA_lng_Deg,
                    double fLocB_lat_Deg,
                    double fLocB_lng_Deg,
                    double *pfPosX,
                    double *pfPosY);

void location_offset(double *pfLat_Deg,double *pfLng_Deg,const float fNorthOffset, const float fEastOffset);


#ifdef __cplusplus
}
#endif //__cplusplus
#endif

