//
//  color.h
//  RT2022
//
//  Created by Nishita Kharche.
//

#ifndef color_h
#define color_h

#include "vec3.h"
#include <iostream>
using namespace std;

void writeColor(ostream &out, color pixelColor, int samples_per_pixel){
    auto r = pixelColor.x();
    auto g = pixelColor.y();
    auto b = pixelColor.z();
    
    // Divide the color by the number of samples & and gamma-correct for gamma=2.0.
    auto scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);
    
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

#endif /* color_h */
