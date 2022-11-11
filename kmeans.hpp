#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class K_means
{

    int k;
    int d;

    vector<vector<int>> data;

    vector<vector<int>> cls_ind;

    vector<vector<int>> centroids;

        float manhatan_distance(vector<int> p, vector<int> q)
        {   
            
            float d = 0;

            for(int i = 0; i < p.size(); i++)
                d += abs(p[i]) + abs(q[i]);
            
            return d;

        }

        vector<vector<int>> promedy()
        {

            vector<vector<int>> p;

            for(int l = 0; l < this->k; l++)
            {

                vector<int> p_p(this->d, 0);
                for(int i = 0; i < cls_ind[l].size(); i++)

                    for(int j = 0; j < this->d; j++)
                        p_p[j] += this->data[i][j];
        
                for(int i = 0; i < this->d; i++)
                    p_p[i] /= cls_ind[l].size();
                    
                p.push_back(p_p);

            }
            return p;
        }

        bool calc_convergency(vector<vector<int>> prom, vector<int> &last_distance)
        {
            bool sup = 0;
            for(int i = 0; i < this->k; i++)
            {
                float dist = manhatan_distance(prom[i], centroids[i]);
                float conv = abs(dist - last_distance[i] ) / last_distance[i] * 100;
                
                if(conv > 5) // mayor al 5%
                    sup = 1;
                last_distance[i] = dist;
            }

            return sup;

        }

        void make_cluster()
        {
            srand(time(0));
            // select centroids
            
            for(int i = 0; i < k; i++)
            {  
                int ind = rand() % data.size();                
                centroids.push_back(data[ind]);
            }
            

            vector<vector<int>> pm;
            vector<int> last_distance(this->k, 0);
            do
            {               
                // insert element's index into clusters
                for(int i = 0; i < data.size(); i++) 
                {

                    int min_d = 1000000000;
                    int ind_j = k - 1;

                    for(int j = 0; j < this->k; j++)
                    {
                        int d = manhatan_distance(data[i], centroids[j]);

                        if(d < min_d)
                        {
                            min_d = d;
                            ind_j = j;
                        }
                    }

                    cls_ind[ind_j].push_back(i);
                }

                pm = promedy(); // new centroids

            }while(calc_convergency(pm, last_distance)); // calculate the convergency
        }

    public:

        K_means(int k, int d, vector<vector<int>> data)
        {
            this->k = k;
            this->d = d;
            this->data = data;
            this->cls_ind.resize(k);
            make_cluster();
        }

        vector<vector<int>> get_clusters()
        {
            return cls_ind;
        }

        vector<vector<int>> get_centroids()
        {
            return centroids;
        }  
};