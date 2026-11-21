#include <stdint.h>
#include <string.h>

#include "displayutils.h"

#include "qprint.h"




texture_t render_text(texture_t bitmap_font, char* str, uint32_t width){

	const uint32_t cw = 7;
	const uint32_t ch = 7;

	uint32_t len = strlen(str);
	uint32_t height = (len / width) + 1;
	uint32_t i=0;
	while(str[i++]) if(str[i] == '\n') height++;

	texture_t t = {width*(cw+1)-1, height*(ch+1)-1, 0};
	t.pixels = malloc(t.width * t.height * sizeof(uint32_t));
	if(!t.pixels){
		qerror("Failed to malloc pixels in render_text\n");
	}
	for(int32_t i = 0; i < t.width*t.height; i++){
		t.pixels[i] = 0xff000000;
	}

	int32_t x = 0;
	int32_t y = 0;

	uint32_t mx = 0;
	uint32_t my = 0;

	i=0;
	while(str[i]){
		if(str[i] == '\n'){
			x = 0;
			y += ch+1;
			i++;
			continue;
		}
		else if('A' <= str[i] && str[i] <= 'M'){
			qprint("AAAAAAAAaa\n");
			mx = (str[i]-'A')*(cw+1);
			my = 0;
		}
		else if('N' <= str[i] && str[i] <= 'Z'){
			mx = (str[i]-'N')*(cw+1);
			my = ch+1;
		}
		else if('a' <= str[i] && str[i] <= 'm'){
			mx = (str[i]-'a')*(cw+1);
			my = 2*(ch+1);
		}
		else if('n' <= str[i] && str[i] <= 'z'){
			mx = (str[i]-'n')*(cw+1);
			my = 3*(ch+1);
		}
		else if('0' <= str[i] && str[i] <= '9'){
			mx = (str[i]-'0')*(cw+1);
			my = 4*(ch+1);
		}
		else if(str[i] == '+'){
			mx = 10*(cw+1);
			my = 4*(ch+1);
		}
		else if(str[i] == '-'){
			mx = 11*(cw+1);
			my = 4*(ch+1);
		}
		else if(str[i] == '='){
			mx = 12*(cw+1);
			my = 4*(ch+1);
		}
		else if(str[i] == '('){
			mx = 0*(cw+1);
			my = 5*(ch+1);
		}
		else if(str[i] == ')'){
			mx = 1*(cw+1);
			my = 5*(ch+1);
		}
		else if(str[i] == '['){
			mx = 2*(cw+1);
			my = 5*(ch+1);
		}
		else if(str[i] == ']'){
			mx = 3*(cw+1);
			my = 5*(ch+1);
		}
		else if(str[i] == '{'){
			mx = 4*(cw+1);
			my = 5*(ch+1);
		}
		else if(str[i] == '}'){
			mx = 5*(cw+1);
			my = 5*(ch+1);
		}
		else if(str[i] == '<'){
			mx = 6*(cw+1);
			my = 5*(ch+1);
		}
		else if(str[i] == '>'){
			mx = 7*(cw+1);
			my = 5*(ch+1);
		}
		else if(str[i] == '/'){
			mx = 8*(cw+1);
			my = 5*(ch+1);
		}
		else if(str[i] == '*'){
			mx = 9*(cw+1);
			my = 5*(ch+1);
		}
		else if(str[i] == ':'){
			mx = 10*(cw+1);
			my = 5*(ch+1);
		}
		else if(str[i] == '#'){
			mx = 11*(cw+1);
			my = 5*(ch+1);
		}
		else if(str[i] == '%'){
			mx = 12*(cw+1);
			my = 5*(ch+1);
		}
		else if(str[i] == '!'){
			mx = 0*(cw+1);
			my = 6*(ch+1);
		}
		else if(str[i] == '?'){
			mx = 1*(cw+1);
			my = 6*(ch+1);
		}
		else if(str[i] == '.'){
			mx = 2*(cw+1);
			my = 6*(ch+1);
		}
		else if(str[i] == ','){
			mx = 3*(cw+1);
			my = 6*(ch+1);
		}
		else if(str[i] == '\''){
			mx = 4*(cw+1);
			my = 6*(ch+1);
		}
		else if(str[i] == '"'){
			mx = 5*(cw+1);
			my = 6*(ch+1);
		}
		else if(str[i] == '@'){
			mx = 6*(cw+1);
			my = 6*(ch+1);
		}
		else if(str[i] == '&'){
			mx = 7*(cw+1);
			my = 6*(ch+1);
		}
		else if(str[i] == '$'){
			mx = 8*(cw+1);
			my = 6*(ch+1);
		}
		else if(str[i] == ' '){
			mx = 12*(cw+1);
			my = 6*(ch+1);
		}
		else{
			mx = 6*(cw+1);
			my = 6*(ch+1);
		}

		for(uint32_t dy=0; dy<ch; dy++){
			for(uint32_t dx=0; dx<cw; dx++){
				qvald(mx);
				qvald(my);
				// t.pixels[((y+dy)*t.width) + (x+dx)] = bitmap_font.pixels[(((ch+1)*my)+dy)*bitmap_font.width + (((cw+1)*mx)+dx)];
				t.pixels[((y+dy)*t.width) + (x+dx)] = bitmap_font.pixels[(my+dy)*bitmap_font.width + mx+dx];
				// t.pixels[(y+dy)*t.width + (x+dx)] = 0xff000000;
				// qvald(x+dx);
			}
		}
		x+=cw+1;
		if(x>=t.width){
			x = 0;
			y+=ch+1;
		}
		i++;
	}
	return t;
}
