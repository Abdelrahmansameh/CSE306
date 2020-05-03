#include <iostream> 
#include "Scene.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "Vector.h"
#include <list>
#include <vector>
#include <algorithm>
#include "ray.h"

int main() {
	Sphere red( 940, Vector(0, 1000, 0), Vector(1, 0, 0), false);
	Sphere green( 940, Vector(0, 0, -1000), Vector(0, 1, 0), false);
	Sphere blue( 990, Vector(0, -1000, 0), Vector(0, 0, 1), false);
	Sphere pink(940, Vector(0, 0, 1000), Vector(1, 0, 1), false);
	Sphere object( 10, Vector(0, 0, 0), Vector(1, 1, 1), false, false);
	Vector light_source = Vector(-10, 20, 40);

	Sphere myspheres[] = { red, blue, green, pink, object };
	std::list<Sphere> spheres (myspheres, myspheres + sizeof(myspheres) / sizeof(Sphere));
	Scene myScene = Scene(spheres);
	Vector Q = Vector(0, 0, 55); 
	const int W = 600;                             
	const int H = 512;                             
	double fov = PI / 2;                          
	unsigned char img[W*H * 3];           
	
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			Vector V;
			V[0] = Q[0] + 0.5 + j - (W / 2);
			V[1] = Q[1] - i - 0.5 + (H / 2);
			V[2] = Q[2] - (W / (2 * tan(fov / 2)));
			Vector n = (V - Q) / (V - Q).norm();
			Ray r = Ray(Q, n);
			int RPP = 100; //Rays per pixel
			Vector color = Vector(0., 0., 0.);
			for (int k = 0; k <RPP ; ++k){
				Vector tmp = myScene.getColor(r, 10, light_source, 100000);
				color = color+ tmp;
			}
			color = color / RPP;
			double power = 1. / 2.2;
			img[(i*W + j) * 3 + 0] = std::min(255., std::max(0., pow(color[0], power) * 255));
			img[(i*W + j) * 3 + 1] = std::min(255., std::max(0., pow(color[1], power) * 255));
			img[(i*W + j) * 3 + 2] = std::min(255., std::max(0., pow(color[2], power) * 255));
		}
	}
	stbi_write_png("test.png", W, H, 3, img, 0); 
	return 0;

}