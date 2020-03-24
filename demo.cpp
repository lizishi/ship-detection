#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include "function.h"
using namespace std;

// float Pfa_list [] =  {0.1, 0.01, 0.001, 0.0001};
// int N_list [] = {5, 7, 9, 11, 13, 15};

int main()
{
    string dir = "./radar_image_croped/";

    string HH_path = dir + "imagery_HH.tif";
    cout<<HH_path<<endl;
    const MatComplex HH = read_tiff(HH_path);
    cout<<HH_path<<" Loading Completed"<<endl;

    Complex ** HH_data = HH.get_data();

    string HV_path = dir + "imagery_HV.tif";
    cout<<HV_path<<endl;
    const MatComplex HV = read_tiff(HV_path);
    cout<<HV_path<<" Loading Completed"<<endl;

    string VV_path = dir + "imagery_VV.tif";
    cout<<VV_path<<endl;
    const MatComplex VV = read_tiff(VV_path);
    cout<<VV_path<<" Loading Completed"<<endl;
    
    cout<<"image load done!"<<endl;
    int h = HH.get_size1();
    int w = HH.get_size2();

    cout<<h<<' '<<w<<endl;

    float Pfa = 0.001;
    int N = 15;
    MatFloat Y(h, w);
    float T = get_T_PWF(3, Pfa);

    if (f_pwf(HH, HV, VV, N, Y))
    {
        string save_Y_path = "./Y_pwf.png";
        write_png_file(save_Y_path, (MatUint8)Y);    

        MatUint8 result(h, w);
        for (int x=0;x<h;x++)
        {
            for (int y=0;y<w;y++)
            {
                result[x*w+y] = Y[x*w+y]>T?255:0;
            }
        }

        string save_result_path = "./result_pwf.png";
        write_png_file(save_result_path, result);
    }
    
    MatFloat RS(h, w);
    float threshold = 0.15;
    if (f_rs(HH, HV, 5, RS))
    {
        string save_Y_path = "./Y_rs.png";
        write_png_file(save_Y_path, (MatUint8)RS);    

        MatUint8 result(h, w);
        for (int x=0;x<h;x++)
        {
            for (int y=0;y<w;y++)
            {
                result[x*w+y] = RS[x*w+y]>threshold?255:0;
                if (x<5 and y<5) std::cout<<(int)result[x*w+y]<<' ';
            }
            if (x < 5) std::cout<<'\n';
        }

        string save_result_path = "./result_rs.png";
        write_png_file(save_result_path, result);
    }

    // for (int i=0;i<6;i++)
    // {
    //     int N = N_list[i];
    //     for (int j=0;j<4;j++)
    //     {
    //         float Pfa = Pfa_list[j];

    //         char* dir_path;
    //         sprintf(dir_path, "/nvme/lizishi/ShipDetection/PWF_%d_%8f", N, Pfa);
    //         mkdir(dir_path, S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
    //         std::cout<<"N: "<<N<<"Pfa: "<<Pfa<<std::endl;
    //         MatFloat Y(h, w);

    //         float T = get_T_PWF(3, Pfa);
    //         std::cout<<"T: "<<T<<std::endl;
    //         if (f_pwf(HH, HV, VV, N, Y))
    //         {
    //             string save_Y_path = (string)dir_path + (string)"/Y.png";
    //             write_png_file(save_Y_path, (MatUint8)Y);    

    //             MatUint8 result(h, w);
    //             for (int x=0;x<h;x++)
    //             {
    //                 for (int y=0;y<w;y++)
    //                 {
    //                     result[x*w+y] = Y[x*w+y]>T?255:0;
    //                 }
    //             }

    //             string save_result_path = (string)dir_path + (string)"/result.png";
    //             write_png_file(save_result_path, result);
    //         }
    //     }
    // }
    return 0;
}