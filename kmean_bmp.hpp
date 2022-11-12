#include <iostream>
#include <vector>
// #include <algorithm>
#include "bmpmini.hpp"
#include "kmeans.hpp"
#include <bits/stdc++.h>
using namespace std;

int min_val(int a, int b)
{   
    return a < b? a : b;
}

int max_val(int a, int b)
{   
    return a > b? a : b;
}

class Kmeans_bmp
{
    void process_image(string filename, int k)
    {
        using namespace image;
        BMPMini bmp;

        try{
            bmp.read(filename);

            auto img = bmp.get();

            img.channels = 1;

            struct BGR {
                uint8_t b{ 0 };
                uint8_t g{ 0 };
                uint8_t r{ 0 };

                uint8_t get()
                {
                    return (uint8_t) min_val((int)r + (int)g +(int)b, 255);
                //  return (uint8_t)min_val(max_val( r + g +  b, 0.0), 255.0); 
                }

            };


            BGR* color = reinterpret_cast<BGR*>(img.data);

            vector<vector<int>> data;
            
            for(int i = 0; i < img.height * img.width; i++, color++) // convert data in image
            { 

                // cout << (int)img.data[i] << " ";

                vector<int> pixel;
                pixel.push_back((int)color->b);
                pixel.push_back((int)color->g);
                pixel.push_back((int)color->r);
                data.push_back(pixel);
                // cout << pixel[0] << " " << pixel[1] << " " <<pixel[2];
                // cin.get();
            }

            K_means cluster(k, 3, data); // tree dimentions (b,g,r)

            vector<vector<int>> centroids = cluster.get_centroids();

            for(int i = 0; i < centroids.size(); i++)
            {
                cout << centroids[i][0] << " " << centroids[i][1] << " " << centroids[i][2] << endl; 
            }

            vector<vector<int>> ind_cls = cluster.get_clusters();

            vector<BGR> w;

            for(int i = 0; i < k;  i++)
            {
                BGR pixel_w;
                pixel_w.b = centroids[i][0];
                pixel_w.b = centroids[i][1];
                pixel_w.b = centroids[i][2];
                w.push_back(pixel_w);
            }
            
            for(int i = 0; i < k; i++) // convert pixel to data from pixels
            {
                for(int j = 0; j < ind_cls[i].size(); j++)
                {
                    img.data[ind_cls[i][j]] = w[i].get();
                }
            }

            // cluster.print_clusters();
            
            bmp.write(img, filename.substr(0, filename.find(".bmp")) + "_kmeans.bmp");
            
        }
        catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
            return;
        }
    }

    public:
        Kmeans_bmp(string filename, int k)
        {
            process_image(filename, k);
        }


};

