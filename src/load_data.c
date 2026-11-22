#include <stdint.h>
#include "qprint.h"
#include "stb_image.h"

#include "config.h"

#include "compute_efficiency.h"

int** load_data(){
	
	int** ret = malloc(sizeof(int*)*ENVIRONMENT_FACTORS_COUNT);
	for(int i=0; i<ENVIRONMENT_FACTORS_COUNT; i++){
		ret[i] = malloc(sizeof(int) * WIDTH * HEIGHT);
	}
	
	int height, width;
	uint32_t* pixels;
	
	char* sources[ENVIRONMENT_FACTORS_COUNT] = {
		"assets/ewind_processed.png",
		"assets/eheat_processed.png",
		"assets/ehumidity_processed.png",
		"assets/eprecipitation_procesed.png",
		"assets/esunlight_processed_best_i_could.png",
		"assets/ecloud_processed.png"
	};

	for(int i=0; i<ENVIRONMENT_FACTORS_COUNT; i++){
		pixels = (uint32_t*)stbi_load(sources[i], &width, &height, NULL, 4);
		if(!pixels){
			qerror("Failed to load %s\n", sources[i]);
		}
		for(int y=0; y<HEIGHT; y++){
			for(int x=0; x<WIDTH; x++){
				ret[i][y*WIDTH + x] = (int)(pixels[(y*height/HEIGHT)*width + (x*width/WIDTH)] & 0xff);
			}
		}
		free(pixels);
	}
	return ret;
}
