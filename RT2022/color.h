//
//  color.h
//  RayTracingCourse
//
//  Created by Nishita Kharche on 6/12/22.
//

#ifndef color_h
#define color_h

#include "vec3.h"
#include <iostream>
using namespace std;

void writeColor(ostream &out, color pixelColor){
    // all colour componenets[0,255] for each pixel
    out << static_cast<int>(255.999 * pixelColor.x() ) << ' ' << static_cast<int>(255.999 * pixelColor.y() ) << ' ' << static_cast<int>(255.999 * pixelColor.z() ) << '\n';
}

#endif /* color_h */
