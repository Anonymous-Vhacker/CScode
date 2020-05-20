#ifndef MATERIAL_H
#define MATERIAL_H
class material {
public:
    //ģ�� ���ڲ�����Ҫ 1������ɢ��������  2��ɢ����٣�
    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const=0;
};

//����lambertian����
class lambertian : public material {
public:
    lambertian(const color& a) : albedo(a) {}

    virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const 
    {
        vec3 scatter_direction = rec.normal + random_unit_vector();
        scattered = ray(rec.p, scatter_direction);//ɢ�����
        attenuation = albedo;
        return true;
    }

public:
    color albedo;//�������
};


//ȫ�����������
class metal : public material {
public:
    metal(const color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}//����ģ����

    virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const 
    {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);//���㷴���߷���
        scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());//��ֵ�����ߣ������߼���Ϊ��׼+���ƫ��
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }

public:
    color albedo;//�������
    double fuzz;//ģ���Ȳ���
};

//schlick�ƽ�
double schlick(double cosine, double ref_idx) {
    auto r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}

//Ͷ�����
class dielectric : public material {
public:
    dielectric(double ri) : ref_idx(ri) {}

    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const {
        attenuation = color(1.0, 1.0, 1.0);
        double etai_over_etat;
        if (rec.front_face) {
            etai_over_etat = 1.0 / ref_idx;
        }
        else {
            etai_over_etat = ref_idx;
        }

        vec3 unit_direction = unit_vector(r_in.direction());
        //����cos��sin
        double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
        double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
        if (etai_over_etat * sin_theta > 1.0) {//ȫ���䣬����ĵ�
            vec3 reflected = reflect(unit_direction, rec.normal);
            scattered = ray(rec.p, reflected);
            return true;
        }
        //������
        //schlick�ƽ�������
        double reflect_prob = schlick(cos_theta, etai_over_etat);
        if (random_double() < reflect_prob)
        {
            vec3 reflected = reflect(unit_direction, rec.normal);
            scattered = ray(rec.p, reflected);
            return true;
        }

        vec3 refracted = refract(unit_direction, rec.normal, etai_over_etat);
        scattered = ray(rec.p, refracted);
        return true;
    }

    double ref_idx;//������
};

#endif