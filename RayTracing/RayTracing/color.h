#ifndef COLOR_H
#define COLOR_H
/*
2020.5.19
��ɫ��
*/
#include "vec3.h"
#include <iostream>

//�����ɫ��Ϣ����׼��
void write_color(std::ostream& out, color pixel_color, int samples_per_pixel) {
    //��ȡ��ɫ����
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    //ƽ�������� ��ֹ���
    auto scale = 1.0 / samples_per_pixel;
    /*
    r *= scale;
    g *= scale;
    b *= scale;
    */
    //�򵥵�٤������� gamma=2.0 �������θ��� 
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    // �޷����
    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

#endif