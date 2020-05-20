#pragma once
#ifndef CAMERA_H
#define CAMERA_H

/*
�������
���ÿ�߱ȡ��ӿڴ�С������ɨ��ؼ���ȣ�
*/
class camera {
public:
    camera(
        point3 lookfrom,//���λ��
        point3 lookat,//Ŀ���λ��
        vec3   vup,//����ʸ��ͶӰ���ӿ�ƽ��ı�׼����
        double vfov, //��ֱ����� �Ƕȱ�ʾ���ӿ�
        double aspect_ratio,
        double aperture,
        double focus_dist//����
    ) {
        //����y����h
        auto theta = degrees_to_radians(vfov);
        auto h = tan(theta / 2);
        
        //�������ӿڳ���
        auto viewport_height = 2.0 * h;
        auto viewport_width = aspect_ratio * viewport_height;

        //�������
        auto w = unit_vector(lookfrom - lookat);
        auto u = unit_vector(cross(vup, w));
        auto v = cross(w, u);

        //��ֵ���λ��
        origin = lookfrom;
        /*
        horizontal = viewport_width * u;
        vertical = viewport_height * v;
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - w;*/
        //���������Ⱦ
        horizontal = focus_dist * viewport_width * u;//�۽�ƽ���ڵ�����ɨ��
        vertical = focus_dist * viewport_height * v;
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - focus_dist * w;

        lens_radius = aperture / 2;
    }

    //��ȡֱ�����䵽���صĹ��ߣ���ʼ�㡢����
    ray get_ray(double s, double t) const {
       // return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
        //������汾
        vec3 rd = lens_radius * random_in_unit_disk();//����ӿڹ���
        vec3 offset = u * rd.x() + v * rd.y();//�������ƫ��
        return ray(
            origin + offset,
            lower_left_corner + s * horizontal + t * vertical - origin - offset
        );
    }

private:
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    double lens_radius;
};
#endif