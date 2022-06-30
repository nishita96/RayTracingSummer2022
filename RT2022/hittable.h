//
//  hittable.h
//  RT2022
//
//  Created by Nishita Kharche on 6/29/22.
//

#ifndef hittable_h
#define hittable_h

#include "ray.h"

struct hit_record {
    point3 p;
    vec3 normal;
    double t;
    bool front_face;
    
    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;//cos90-cos180 < 0, hence its towards the ray, hence front face
        normal = front_face ? outward_normal :-outward_normal;
    }
};

class hittable {
    public:
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};


#endif /* hittable_h */
