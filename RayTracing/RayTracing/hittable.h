#pragma once
#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
class material;

/*���߻����ж���*/
struct hit_record {
    point3 p;
    vec3 normal;
    double t;
    shared_ptr<material> mat_ptr;//����
    bool front_face;//�жϷ��߷�������

    inline void set_face_normal(const ray& r, const vec3& outward_normal) { 
        front_face = dot(r.direction(), outward_normal) < 0;//����ж��Ǵ������ڻ��Ǵ������� ���洢���ṹ��
        normal = front_face ? outward_normal : -outward_normal;//���ݵ���趨���߷���
    }
};

class hittable {
public:
    //�麯�� tmax ��min��������ֵ
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif