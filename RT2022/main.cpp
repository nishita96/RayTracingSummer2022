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

#include "camera.h"

#include "rtweekend.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "material.h"

#include <cstdlib>
#include <iostream>
using namespace std;

color rayColor(const ray& r, const hittable& world, int depth) {
    hit_record rec;
    
    if (depth<=0)
        return color(0,0,0);
    if (world.hit(r, 0.001, infinity, rec)) {
//        point3 target = rec.p + rec.normal + random_unit_vector();
//        return 0.5 * rayColor(ray(rec.p, target - rec.p), world, depth-1);
        
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * rayColor(scattered, world, depth-1);
        return color(0,0,0);
    }
    //horizon background - blue to yellow
    //circular
    //check value 2.829
    auto cosThetaT = (abs( (r.direction().z() + 2.829)/2.0)) / (sqrt( (r.direction().x()* r.direction().x()) + (r.direction().y()*r.direction().y()) + (r.direction().z()*r.direction().z())));
    return (1-cosThetaT)*color(0.3, 0.5, 1.0) + (cosThetaT)*color(0.9, 0.9, 0.7);
}

int main() {

    // about image
    const auto aspectRatio = 16.0/9.0;
    const int width = 300;
    const int height = width / aspectRatio;
    const int samples_per_pixel = 100;
    const int max_depth = 50;
    
    //objects in world 
    hittable_list world;
//    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
//    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));
    
    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
//    auto material_center = make_shared<lambertian>(color(0.7, 0.3, 0.3));
//    auto material_left = make_shared<metal>(color(0.8, 0.8, 0.8), 0.3);
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left = make_shared<dielectric>(1.5);
    auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);
                                                   
    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3( 0.0, 0.0, -1.0), 0.4, material_center));
    world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.6, material_left));
    world.add(make_shared<sphere>(point3( 1.0, 0.0, -1.0), 0.4, material_right));
    
    //camera things
    camera cam;
    
    //rendering
    
    std::cout << "P3\n" << width << ' ' << height << "\n255\n";

    for (int j = height-1; j >= 0; --j) {
//        cerr << "Lines Remaining Are: " << j << flush ; //error output stream
        for (int i = 0; i < width; ++i) {
            color pixelColor(0,0,0);
            //II
            for(int s = 0; s<samples_per_pixel ; s++){
                ray r = cam.get_ray((double(i) / (width-1)),(double(j) / (height-1)));
                pixelColor += rayColor(r, world, max_depth);
            }
            writeColor(cout, pixelColor, samples_per_pixel); //writes code for the PPM image

        }
    }
    cerr << "Done! \n"; //error output stream
}

