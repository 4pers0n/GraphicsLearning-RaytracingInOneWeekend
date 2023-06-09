#include "vec3.h"
#include "ray.h"
#include "color.h"

#include <iostream>

color ray_color(const ray &r)
{
    vec3 unit_direction = unit_vector(r.direction());
    double y = unit_direction.y();
    double t = (y + 1) * 0.5;
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() 
{
    // Image
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera
    const double viewport_height = 2.0;
    const double viewport_width = aspect_ratio * viewport_height;
    const double focal_length = 1.0;

    const point3 origin = point3(0, 0, 0);
    const vec3 horizontal = vec3(viewport_width, 0, 0);
    const vec3 vertical = vec3(0, viewport_height, 0);
    const vec3 lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; j--)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; i++)
        {
            // linear interpolation: (1 - t) * begin + t * end
            double u = double(i - 0) / ((image_width - 1) - 0);  // t = (cur - min) / (max - min) = cur / max
            double v = double(j - 0) / ((image_height - 1) - 0);
            
            ray r = ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";
}