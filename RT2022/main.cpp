//
//  main.cpp
//  RayTracingCourse
//
//  Created by Nishita Kharche on 6/11/22.
//


//int main(int argc, const char * argv[]) {
//    // insert code here...
//    std::cout << "Hello, World!\n";
//    return 0;
//}

#include "color.h"
#include "vec3.h"
#include <iostream>
using namespace std;

int main() {

    // about image
    
    const int width = 256;
    const int height = 256;
    
    //rendering
    
    std::cout << "P3\n" << width << ' ' << height << "\n255\n";

    for (int j = height-1; j >= 0; --j) {
//        cerr << "Lines Remaining Are: " << j << flush ; //error output stream
        for (int i = 0; i < width; ++i) {
            //II
            color pixelColor(double(i) / (width-1), double(j) / (height-1), 0.25);
            writeColor(cout, pixelColor); //writes code for the PPM image
            
        }
    }
}

///Users/nishitakharche/Library/Developer/Xcode/DerivedData/Build/Products/Debug
