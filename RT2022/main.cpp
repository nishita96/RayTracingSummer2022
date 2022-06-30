//
//  main.cpp
//  RT2022
//
//  Created by Nishita Kharche.
//


//int main(int argc, const char * argv[]) {
//    // insert code here...
//    std::cout << "Hello, World!\n";
//    return 0;
//}

#include "color.h"
#include "vec3.h"
#include "ray.h"

#include "rtweekend.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"

#include <cstdlib>
#include <iostream>
using namespace std;

color rayColor(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1,1,1));
    }
    //horizon background - blue to yellow
    //circular
    auto cosThetaT = (abs( (r.direction().z() + 2.829)/2.0)) / (sqrt( (r.direction().x()* r.direction().x()) + (r.direction().y()*r.direction().y()) + (r.direction().z()*r.direction().z())));
    return (1-cosThetaT)*color(0.3, 0.5, 1.0) + (cosThetaT)*color(0.9, 0.9, 0.7);
}

int main() {

    // about image
    const auto aspectRatio = 16.0/9.0;
    const int width = 600;
    const int height = width / aspectRatio;
    
    //objects in world 
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));
    
    //camera viewport
    auto viewportHeight = 2.0;
    auto viewportWidth = aspectRatio * viewportHeight;
    
    auto focal_length = 1.0;
    auto origin = point3(0, 0, 0); //viewing origin
    auto horizontal = vec3(viewportWidth, 0, 0);
    auto vertical = vec3(0, viewportHeight, 0);
    
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);
    
    //rendering
    
    std::cout << "P3\n" << width << ' ' << height << "\n255\n";

    for (int j = height-1; j >= 0; --j) {
//        cerr << "Lines Remaining Are: " << j << flush ; //error output stream
        for (int i = 0; i < width; ++i) {
            //II
            auto rdirection = lower_left_corner
            + (double(i) / (width-1))*horizontal
            + (double(j) / (height-1))*vertical;// - origin;
            ray r(origin, rdirection);

            color pixelColor = rayColor(r,world);
            writeColor(cout, pixelColor); //writes code for the PPM image

        }
    }
    cerr << "Done! \n"; //error output stream
}

