#include "Image.h"
#include "../ppm/ppm.h"
#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;
using namespace math;
namespace imaging{


	bool Image::load(const std::string & filename, const std::string & format) {

		ifstream ifs(filename, ios::in | ios::binary);
		if (ifs.is_open()) {

			string f;
			ifs >> f;
			ifs >> width;
			ifs >> height;
			ifs.close();
			int *w = new int;
			int *h = new int;
			*w = width;
			*h = height;
			const char * c = filename.c_str();
			float *buf = ReadPPM(c, w, h);
			unsigned char *b = reinterpret_cast<unsigned char *>(buf);
			if (buf != NULL) {
				 vector<Vec3<float>> buffer;
				const vector<Vec3<float>> neg (1);

				for (int i = 0; i < width * height; i++) {
					buffer[i].r = (float)b[3 * i] / 255;
					buffer[i].g = (float)b[3 * i + 1] / 255;
					buffer[i].b = (float)b[3 * i + 2] / 255;
					buffer[i].operator-(neg[1]);
					
				}

				return true;
			}
		}
		return false;

	}

	bool Image::save(const std::string & filename, const std::string & format) {
		if (buffer.size=0 || format != "ppm" || format != "PPM") return false;
		float * buf;
		unsigned char* b = new unsigned char[3 * width*height];
		for (int i = 0; i<width*height; i++) {
			b[3 * i] = (float)buffer[i].r * 255;
			b[3 * i + 1] = (float)buffer[i].g * 255;
			b[3 * i + 2] = (float)buffer[i].b * 255;
		}

		buf = reinterpret_cast<float *>(b);
		const char * form = filename.c_str();
		if(WritePPM(buf, width, height, form)) return true;
		return false;
	}





}