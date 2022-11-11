#include <iostream>
#include <vector>
#include <algorithm>
#include "bmpmini.hpp"
#include "kmeans.hpp"

using namespace std;

int main()
{

    using namespace image;
    BMPMini bmp;

    try {

        bmp.read("samples/lena_color.bmp");
        // bmp.write("lena_color_copy.bmp");

        auto img = bmp.get();

        img.channels = 1;

        std::vector<uint8_t> gray(img.width * img.height);
        struct BGR {
            uint8_t b{ 0 };
            uint8_t g{ 0 };
            uint8_t r{ 0 };
        };

        BGR* color = reinterpret_cast<BGR*>(img.data);

        for(int i = 0; i < img.height * img.width; i++, color++)
        {
            cout << color->b << color->g << color->r << endl;
            
        }

        // img.data = gray.data();
        
        // bmp.write(img, "lena_gray.bmp");

    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return -1;
    }
   
    return 0;

}