#include "vec3.h"
#include "color.h"

#include <iostream>

int main() 
{
    // Image

    const int image_width = 1024;
    const int image_height = 1024;

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; j--)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; i++)
        {
            // linear interpolation: (1 - t) * 0 + t * 255
            double r = double(i) / (image_width - 1);  // t = (cur - min) / (max - min) = cur / max
            double g = double(j) / (image_height - 1);
            double b = 0.25;

            color pixel_color(r, g, b);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";
}