//
//  ray.h
//  RT2022
//
//  Created by Nishita Kharche.
//

#ifndef ray_h
#define ray_h

#include "vec3.h"

//ray as a function P(t) = A + tB
class ray {
    public:ray() {}
        ray(const point3& origin, const vec3& direction):orig(origin), direc(direction) {}

        point3 origin() const {return orig; }
        vec3 direction() const {return direc; }
    
        point3 at(double t) const {
            return orig + direc*t;
        }
    
    public:
        point3 orig;
        vec3 direc;
};

#endif /* ray_h */

