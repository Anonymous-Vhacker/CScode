#ifndef COMMON_H
#define COMMON_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <cstdlib>
/*���ú�����ͷ�ļ������ļ�*/
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

//����
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

//ʵ�û��㺯��
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180;
}
//�����������
inline double random_double() {
    //[0,1)
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    //[min,max)
    return min + (max - min) * random_double();
}
//�ü����� ���Ʒ���
inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

//ͷ�ļ�
#include "vec3.h"
#include "ray.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "material.h"
#include "camara.h"
#include "aarect.h"


#endif