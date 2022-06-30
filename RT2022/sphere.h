//
//  sphere.h
//  RT2022
//
//  Created by Nishita Kharche on 6/29/22.
//

#ifndef sphere_h
#define sphere_h

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
    public:
        sphere() {}
        sphere(point3 cen, double r) : center(cen), radius(r) {};
    
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
    
    public:
        point3 center;
        double radius;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    
    //calculating values of (t) at intersection from ray
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    //removing factor of 2
    auto half_b = dot(oc, r.direction());
    auto c = dot(oc, oc) - radius*radius;
    
    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false; //no solution -> no intersection
    auto sqrtd = sqrt(discriminant);
    
    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }
    
    rec.t = root;
    rec.p = r.at(rec.t);
//    rec.normal = (rec.p - center) / radius;
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
        
    return true;
}

#endif /* sphere_h */
