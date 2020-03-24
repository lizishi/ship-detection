#include "function.h"

MatComplex read_tiff(string path)
{
    TIFF* tif = TIFFOpen(path.data(), "r");
    if (tif) 
    {
        int16 * buf;
        tstrip_t strip;
        uint32 w, h;

        TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &w);
	    TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &h);
        int w_int = (int)w;
        int h_int = (int)h;
        MatComplex Y(h_int, w_int);

        int i_pointer = 0;
        int j_pointer = 0;
        buf = (int16*) _TIFFmalloc(TIFFStripSize(tif));
        for (strip = 0; strip < TIFFNumberOfStrips(tif); strip++)
        {
            int bytes = TIFFReadEncodedStrip(tif, strip, buf, (tsize_t) -1);
            if (bytes == -1)
            {
                std::cout<<"something wrong when read Strip"<<endl;
                return MatComplex(1, 1);
            }
            for (int i=0;i< bytes / 2;i+=2)
            {
                float real = (float)buf[i];
                float image = (float)buf[i+1];
                Y[i_pointer * w_int + j_pointer] = Complex(real, image);

                j_pointer += 1;
                if (j_pointer >= w_int)
                {
                    j_pointer = 0;
                    i_pointer += 1;
                    if (i_pointer >= h_int) break;
                }
            }
        }
        _TIFFfree(buf);
        TIFFClose(tif);
        return Y;
    }
    MatComplex res = MatComplex(1,1);
    return MatComplex(1, 1);
}

float get_T_PWF(int p, float Pfa, int maxIter, double ep, double x0)
{
    double x, fx, dfx;
    double P = (double)Pfa;
    for (int i=0; i< maxIter;i++)
    {
        fx = exp(-x0) * (1 + x0 + pow(x0, 2)/ 2) - P;
        dfx = -exp(-x0) * (pow(x0, 2)/ 2);
        x = x0 - fx / dfx;
        // std::cout<<x<<' '<<x0<<' '<<fx<<' '<<dfx<<'\n';
        if ((fx < ep) and (fx > -ep)) break; 
        x0 = x;
    }
    return (float)x;
}

bool f_pwf(const MatComplex & HH, const MatComplex & HV,const MatComplex & VV, int N, MatFloat &Y)
{
    // std::cout<<"N: "<<N<<std::endl;
    int h = HH.get_size1();
    int w = HH.get_size2();
    int pad_num = N / 2;

    MatComplex HH_padded = HH.pad(pad_num, pad_num);
    MatComplex HV_padded = HV.pad(pad_num, pad_num);
    MatComplex VV_padded = VV.pad(pad_num, pad_num);

    // std::cout<<"padded Completed"<<std::endl;

    int num = N * N - 1;
    int w1 = HH_padded.get_size2();
    for (int i=pad_num; i<pad_num+h; i++)
    {
        for (int j=pad_num; j<pad_num+w; j++)
        {
            // std::cout<<(i - pad_num)<<' '<<(j - pad_num)<<std::endl;
            MatComplex clutter(3, num);
            int count = 0;
            for (int k=i-pad_num; k<=i+pad_num; k++)
            {
                for (int l=j-pad_num; l<=j+pad_num; l++)
                {
                    if ((k==i) and (l==j)) continue;
                    clutter[0*num+count] = HH_padded[k*w1+l];
                    clutter[1*num+count] = HV_padded[k*w1+l];
                    clutter[2*num+count] = VV_padded[k*w1+l];
                    // std::cout<<k<<' '<<l<<'\n';
                    // std::cout<<count<<':'<<HH_padded[k*w1+l]<<' '<<HV_padded[k*w1+l]<<' '<<VV_padded[k*w1+l]<<'\n';
                    count++;
                }
            }
            // std::cout<<clutter.get_size1()<<' '<<clutter.get_size2()<<std::endl;
            MatComplex sigma_c = clutter * clutter.t() / num;
            // std::cout<<clutter<<std::endl;
            // std::cout<<clutter.t()<<std::endl;

            MatComplex data(3, 1);
            data[0] = HH_padded[i*w1+j];
            data[1] = HV_padded[i*w1+j];
            data[2] = VV_padded[i*w1+j];
            // std::cout<<data<<std::endl;
            // float temp = (data.t() * sigma_c.inv() * data)[0].abs();
            // std::cout<<sigma_c<<std::endl;
            // std::cout<<sigma_c.inv()<<std::endl;
            // std::cout<<data.t() * sigma_c.inv()<<std::endl;
            // std::cout<<data.t() * sigma_c.inv() * data<<std::endl;
            // std::cout<<(data.t() * sigma_c.inv() * data)[0]<<std::endl;
            // std::cout<<temp<<std::endl;
            // Y[(i-pad_num) * w + (j-pad_num)] = temp;
            Y[(i-pad_num) * w + (j-pad_num)] = (data.t() * sigma_c.inv() * data)[0].abs();
        }
    }
    return true;
}

bool f_rs(const MatComplex & HH, const MatComplex & HV, MatFloat & Y)
{
    int h = HH.get_size1();
    int w = HH.get_size2(); 
    Complex ** HH_data = HH.get_data();
    Complex ** HV_data = HV.get_data();
    for (int i=0;i<h;i++)
    {
        for (int j=0;j<w;j++)
        {
            Complex S_HH = HH_data[i][j];
            Complex S_HV = HV_data[i][j];
            Y[i*w + j] = (S_HH * S_HV).abs();
        }
    }
    return true;
}

bool write_png_file(string filename , MatUint8 out) //生成一个新的png图像
{
    std::cout<<"saving in the "<<filename<<'\n';
	png_structp png_ptr;
	png_infop 	info_ptr;
	png_byte color_type;
	png_byte ** row_pointers;
	FILE *fp = fopen(filename.data(), "wb");
	if (NULL == fp) {
		cout<<"open failed ...2\n";
		return false;
	}
	//1: 初始化libpng结构体  
	png_ptr	= png_create_write_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
	if (!png_ptr) {
		std::cout<<"png_create_write_struct failed ...\n";
		return false;
	}
	//2: 初始化png_infop结构体 ， 
	//此结构体包含了图像的各种信息如尺寸，像素位深, 颜色类型等等
	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		std::cout<<"png_create_info_struct failed ...\n";
		return false;
	}
	//3: 设置错误返回点
	if (setjmp(png_jmpbuf(png_ptr))) {
		std::cout<<"error during init_io ...\n";
		return false;
	}
	//4:绑定文件IO到Png结构体
	png_init_io(png_ptr, fp);
	if (setjmp(png_jmpbuf(png_ptr))) {
		std::cout<<"error during init_io ...\n";
		return false;
	}
	color_type = PNG_COLOR_TYPE_GRAY;
	//5：设置以及写入头部信息到Png文件
	png_set_IHDR(png_ptr, info_ptr, out.get_size2(), out.get_size1(), 8,
	color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
	png_write_info(png_ptr, info_ptr);
	if (setjmp(png_jmpbuf(png_ptr))) {
		std::cout<<"error during init_io ...\n";
		return false;
	}
	int i, j, pos = 0;
    int h = out.get_size1();
    int w = out.get_size2();
	row_pointers = new png_byte *[h];
	for (i = 0; i < h; i++) {
		row_pointers[i] = new png_byte [w];
		for (j = 0; j < w; j++) {
            row_pointers[i][j] = out[pos++];
		}
	}
	//6: 写入rgb数据到Png文件
	png_write_image(png_ptr, (png_bytepp)row_pointers);
	if (setjmp(png_jmpbuf(png_ptr))) {
		std::cout<<("error during init_io ...\n");
		return false;
	}
	//7: 写入尾部信息
	png_write_end(png_ptr, NULL);
	//8:释放内存 ,销毁png结构体
	for (i = 0; i < h; i ++)
		delete []row_pointers[i];
	delete []row_pointers;
	png_destroy_write_struct(&png_ptr, &info_ptr);
	fclose(fp);
    std::cout<<"saved "<<filename<<'\n';
	return true;
}