#ifndef RAY_H
#define RAY_H
#include "vec3.h"
/*
2020.5.19
������
��������ʾΪP(t)=A+tb  AΪ��ʼ�㣬bΪ����tΪ�������������������
*/
class ray {
public:
    //���캯�������ߵ���Ϣ��������ɫ
    ray() {}
    ray(const point3& origin, const vec3& direction)
        : orig(origin), dir(direction)
    {}
    //������ɫ�ͷ���
    point3 origin() const { return orig; }
    vec3 direction() const { return dir; }

    //���������ʽ�Ĺ���
    point3 at(double t) const {
        return orig + t * dir;
    }

public:
    point3 orig;
    vec3 dir;
};
#endif