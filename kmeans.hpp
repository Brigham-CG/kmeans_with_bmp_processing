#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <math.h>

using namespace std;

class K_means
{

    public:

        K_means(int k, int d, vector<vector<int>> data)
        {
            this->k = k;
            this->d = d;
            this->data = data;
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

        void print_clusters()
        {
            cout << "[+] Clusters:  \n\n";
            for(int i = 0; i < this->k; i++)
            {   
                cout <<  "Cluster " << i << " c: [ " ;

                for(int j = 0; j < this->d; j++)
                    cout << centroids[i][j]<< " ";
                cout << "] size: "<<cls_ind[i].size() <<"\n\n";

                for(int j = 0; j < cls_ind[i].size(); j++)
                {
                    cout << "[ ";
                    for(int l = 0; l < d; l++)
                        cout << data[cls_ind[i][j]][l] << " ";
                    cout << "]";
                }

                cout << "\n\n";
            }
            cout << endl;
        }

    private:

        int k; // number of clusters
        int d; // dimention of points

        vector<vector<int>> data; // points

        vector<vector<int>> cls_ind; // index of points in clusters

        vector<vector<int>> centroids; // centroids of a cluster

        float manhatan_distance(vector<int> p, vector<int> q)
        {   
            
            float d = 0;

            for(int i = 0; i < p.size(); i++)
                d += abs(p[i]) - abs(q[i]);
            
            return d;
        }

        float euclidean_distance(vector<int> p, vector<int> q)
        {
            float d = 0;

            for(int i = 0; i < p.size(); i++)
                d += pow(p[i] - q[i], 2);
            
            return sqrt(d);
        }

        vector<vector<int>> promedy()
        {
            vector<vector<int>> p;

            for(int l = 0; l < this->k; l++)
            {

                vector<int> p_p(this->d, 0);
                for(int i = 0; i < cls_ind[l].size(); i++)

                    for(int j = 0; j < this->d; j++)
                        p_p[j] += this->data[cls_ind[l][i]][j];
        
                for(int i = 0; i < this->d; i++)
                {
                    if(cls_ind[l].size())                    
                        p_p[i] /= cls_ind[l].size();
                }
                p.push_back(p_p);
            }

            return p;
        }

        bool calc_convergency(vector<vector<int>> prom, vector<int> &last_distance)
        {
            bool sup = 0;
            for(int i = 0; i < this->k; i++)
            {
                float dist = euclidean_distance(prom[i], centroids[i]);
                float conv = abs(dist - last_distance[i] ) / last_distance[i] * 100;
                
                if(conv >2) // mayor al 5%
                    sup = 1;
                last_distance[i] = dist;
            }

            // if(sup)
                centroids = prom;
            

            return sup;

        }

        void make_cluster()
        {
            srand(time(0));
            // select centroids
            

            for(int i = 0; i < k; i++)
            {  
                int ind = rand() % data.size();

                // cout << "ind: " << ind << endl;
                centroids.push_back(data[ind]);
            }
            
            vector<vector<int>> pm;
            vector<int> last_distance(this->k, 0);
            do
            {             
                // for(int i = 0; i < k; i++)
                // {
                //     cout << " c: " << centroids[i][0];
                // }
                // cout << endl;

                // insert element's index into clusters
                cls_ind.clear(); 
                cls_ind.resize(k);
                for(int i = 0; i < data.size(); i++) 
                {
                    float min_d = 1000000000;
                    int ind_j = k - 1;

                    for(int j = 0; j < this->k; j++)
                    {
                        float d = euclidean_distance(data[i], centroids[j]);

                        // cout << "d: " << d << endl;
                        if(d < min_d)
                        {
                            min_d = d;
                            ind_j = j;
                            // cout << "min J: " << j << endl;
                        }
                    }

                    cls_ind[ind_j].push_back(i);

                }

                // for(int i = 0; i < cls_ind.size(); i++)
                // {
                //     for(int j = 0; j < cls_ind[i].size(); j++)
                //     {
                //         cout << data[cls_ind[i][j]][0] << " ";
                //     }
                //     cout << endl;
                // }


                // cout << endl;

                pm = promedy(); // new centroids

                // for(int i = 0; i < k; i++)
                // {
                //     cout << " p: " << pm[i][0];
                // }
                // cout << endl;
                
                // cin.get();

            }while(calc_convergency(pm, last_distance)); // calculate the convergency
        }



};