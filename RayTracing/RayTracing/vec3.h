#ifndef VEC3_H
#define VEC3_H
#include <cmath>
#include <iostream>

using std::sqrt;
/*
2020.5.19
vec3������ �洢��������
*/
class vec3
{
public:
    //���캯��
    vec3() : e{ 0, 0, 0 } {}
    vec3(double e0, double e1, double e2) : e{ e0, e1, e2 } {}
    //��ά
    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }
    //�����������ʸ�����㣩
    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    double operator[](int i) const { return e[i]; }
    double& operator[](int i) { return e[i]; }

    vec3& operator+=(const vec3& v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3& operator*=(const double t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3& operator/=(const double t)
    {
        return *this *= 1 / t;
    }
    //ģ��
    double length() const
    {
        return sqrt(length_squared());
    }
    double length_squared() const
    {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }
    inline static vec3 random() {//�����������vec3��
        return vec3(random_double(), random_double(), random_double());
    }

    inline static vec3 random(double min, double max) {//��Χ�������������vec3��
        return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }
public:
    double e[3];
};
//���� point��color��Ҫ������������
using point3 = vec3; // ��ά����
using color = vec3;  // RGB��ɫ����

inline std::ostream& operator<<(std::ostream& out, const vec3& v)
{
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}
//ʸ������
inline vec3 operator+(const vec3& u, const vec3& v)
{
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v)
{
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v)
{
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3& v)
{
    return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3& v, double t)
{
    return t * v;
}

inline vec3 operator/(vec3 v, double t)
{
    return (1 / t) * v;
}
//���
inline double dot(const vec3& u, const vec3& v)
{
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}
//���
inline vec3 cross(const vec3& u, const vec3& v)
{
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
        u.e[2] * v.e[0] - u.e[0] * v.e[2],
        u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}
//��һ��
inline vec3 unit_vector(vec3 v)
{
    return v / v.length();
}

//�ڵ�λԲ����������㣨����������˵�ȣ�
vec3 random_in_unit_sphere() {
    while (true) {
        auto p = vec3::random(-1, 1);
        if (p.length_squared() >= 1) continue;//ģ������1�Ͳ��ǣ���������
        return p;
    }
}
//�������浥λ����
vec3 random_unit_vector() {
    auto a = random_double(0, 2 * pi);
    auto z = random_double(-1, 1);
    auto r = sqrt(1 - z * z);
    return vec3(r * cos(a), r * sin(a), z);
}

vec3 random_in_hemisphere(const vec3& normal) {
    vec3 in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0) //�ͷ���ͬ�����Բ
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}
/*
������㺯�� vΪ����⣬nΪ�淨��
��bΪ���߷��������
����ⷽ��=v+2b��nΪ��λ������v���ǣ�����b�ĳ���Ӧ����v��n���
������������vΪ����Ŀ��㵽�ﷴ����������ڵ��������ʼӸ���
v-2v��n*n
*/
vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2 * dot(v, n) * n;
}
//������㺯��������ĵ�
vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    auto cos_theta = dot(-uv, n);
    vec3 r_out_parallel = etai_over_etat * (uv + cos_theta * n);
    vec3 r_out_perp = -sqrt(1.0 - r_out_parallel.length_squared()) * n;
    return r_out_parallel + r_out_perp;
}
//���ɵ�λ�ӿ��ڵ��������ģ�⾰��
vec3 random_in_unit_disk() {
    while (true) {
        auto p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

#endif

