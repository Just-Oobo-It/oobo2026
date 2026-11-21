#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
// #include "lib/quarklib/qprint.h"


/*

	hey so uuuhhh i never really intended for anyone to read this so uuhh, its ugly af i prototyped it in 30 minutes drunk on sleep deprivation, please dont read any code further down here :c

*/


/*

	i made a large amount of little fixes here and there to be ready for the hackathon so hopefully this works but ts ugly af lmfao

*/

float qfloor(float volatile f){

	float volatile t = f;
	int* volatile p = (int* volatile)&t;
	
	const char s = ((*p)>>31)&1;
	const unsigned char exp = ((*p)>>23)&0xff;
	const signed char e = exp - 128;
	
	if(e<-1) t=0.f;
	
	const int m_s = 23;
	
	const int mask = ((1<<(m_s-e - 1)) - 1) & !(e>=m_s);
	// if(e < m_s){
	// 	*p &= ~mask;
	// }
	*p &= ~mask;
	if(s && (t!=f)) t-=1.f;
	
	return t;
}

void send_float(double f, int lm, int pm){

	char c;
	float base = 10.f;
	int bi = 10;
	float t;
	float rounded;
	float d=1.f;
	int e=0;	//will hold how many [[base]] digits the whole part takes
	// float whole = 0;

	/*
		Rounding 
	*/
	//i know its very ugly and there's probably a way either with base changes or built in rounding functions but yea i just fast forward in the number to check the n+1 decimal and see if i need to round by adding 1.f*10^-pm

	float rounding = 1.f;
	
	int j =0;
	t = f;
	if(f<0.f) t*=-1.f;
	t = t-qfloor(t);
	t *= base;
	while(j<pm){
		t -= qfloor(t);
		t*= base;
		rounding /= base;
		j++;
	}
	if(qfloor(t) < 5.f){
		rounding = 0.f;
	}
	if(f<0.f) rounding *= -1.f;
	rounded = f + rounding;
	// printf("rounding : %f, rounded = %f\n", rounding, rounded);

	/*
		Negative numbers :3
	*/
	if(rounded < 0.f){
		c = '-';
		write(1, &c, 1);
		rounded *= -1.f;
	}

	t=rounded;

	// qvald(e);
	while(t>=1.){
		t/=base;
		d*=base;
		e++;
	}

	// qlog("e : %d")
	/*
		Account for lenght_modifier lm by putting spaces first if needed
	*/
	int s = lm-e;
	if(-1.0 < rounded && rounded < 1.0) s-=1;	//account for first digit = 0 (might need to do it above)
	if(f < 0.f) s-=1;	//account for negative sign taking 1 space
	while(s>0){
		c = ' ';
		write(1, &c, 1);
		s--;
	}



	int i=0;
	while(i<e){
		
		d/=base;
		c = '0' + ((int)qfloor((rounded/d))%bi);
		// if(((f/d) - qfloor(f/d)) > 0.5f) c++;
		if(i==0 && rounded==1.f) c = '1';
		write(1, &c, 1);
		i++;
	}

	/*
		Account for f < 1.f edge case (it wouldn't print the 0 if it's the first digit)
	*/
	if(rounded < 1.f){
		c = '0' + (rounded==1.f);
		// c = '0';
		write(1, &c, 1);
	}
	c = '.';
	write(1, &c, 1);

	// /*
	// 	Rounding 
	// */
	// //i know its very ugly and there's probably a way either with base changes or built in rounding functions but yea i just fast forward in the number to check the n+1 decimal and see if i need to round by adding 1.f*10^-pm
	//
	// // float rounding = 1.f;
	// rounding = 1.f;
	//
	// i=0;
	// t = f-qfloor(f);
	// t *= base;
	// while(i<pm){
	// 	t -= qfloor(t);
	// 	t*= base;
	// 	rounding /= base;
	// 	i++;
	// }
	// if(qfloor(t) < 5.f){
	// 	rounding = 0.f;
	// }
	// if(f < 0.f) rounding *= 1.f;
	// t = f - qfloor(f) + rounding;
	
	t = rounded;	//reusing same rounded

	i=0;
	t *= base;
	while(i<pm){
		c = '0' + (int)(qfloor(t))%10;	//could use a %bi to be sure but like its never supposed to be outside of the [0.f,10.f[ range here
		t -= qfloor(t);
		t *= base;
		write(1, &c, 1);
		i++;
	}

}

void send_int(int n, int lm, char hex){
	
	char c;
	
	char neg = 0;

	if(n == 0){
		c = '0';
		write(1, &c, 1);
		return;
	}
	if(n < 0){
		neg = 1;
		c = '-';
		write(1, &c, 1);
		n *= -1;
	}

	int base = 10;
	if(hex) base = 16;
	
	int t=n;
	int d=1;
	int e=0;
	while(t>0){
		t/=base;
		d*=base;
		e++;
	}
	int s = lm-e;
	if(neg) s-=1;	//account for - taking 1 space
	while(s > 0){
		c = ' ';
		if(hex) c='0';
		write(1, &c, 1);
		s--;
	}

	int i=0;
	while(i<e){
		d/=base;
		c = '0' + ((n/d)%base);
		if(hex && '9'<c) c+= 'a' - '0' - 10;
		write(1, &c, 1);
		i++;
	}

	return;
}

int parse_lm(int* ip, char* str){
	
	int l = 0;
	int base=10;
	int i = *ip;
	// printf("i = %d\n", i);

	if(str[i] == '0'){
		i++;
		base = 8;
	}
	while(('0' <= str[i] && str[i] <= '9')){
		l*=base;
		l+=str[i]-'0';
		i++;
	}
	*ip = i;
	// printf("i = %d\n", i);
	return l;
}

// int count_args(char* str){
// 	int count=0;
// 	int i=0;
// 	while(str[i]) if(str[i] == '%') count++;
// 	return count;
// }

void qesc(){
	write(1, "\e[", 2);
}
void qend(){
	write(1, "m", 1);
}
void qres(){
	write(1, "\e[0m", 4);
}

void qcolor(int n){
	qesc();
	send_int(n, 0, 0);
	qend();
}


void qprint(char* str, ...){
	
	va_list ap;

	// char c;
	char* ss;

	int i=0;
	int lenght_modifier;
	int precision_modifier;
	// int base;

	char modifiers = 0;

	va_start(ap, str);
	while(str[i]){
		
		if(str[i] == '%'){
			i++;
			if(!str[i]) return;
			// printf("i = %d\n", i);
			lenght_modifier = parse_lm(&i, str);
			precision_modifier = 4;
			if(str[i] == '.'){
				i++;
				if(!str[i]) return;
				precision_modifier = parse_lm(&i, str);
			}
			// printf("i = %d\n", i);
			switch(str[i]){
				case 'd':
					send_int(va_arg(ap, int), lenght_modifier, 0);
					break;
				case 'x':
					send_int(va_arg(ap, int), lenght_modifier, 1);
					break;
				case 'f':
					send_float(va_arg(ap, double), lenght_modifier, precision_modifier);
					break;
				case 's':
					ss = va_arg(ap, char*);
					while(*(ss++)) write(1, ss-1, 1);
					break;
				default:
					// c = 'e';
					// write(1, &(str[i]), 1);
					// printf("0x%x", str[i]);
					break;
			}
		}
		else if(str[i] == '$'){
			i++;
			switch(str[i]){
				case '0':
					qres();
					break;
				case 'b':
					modifiers^=0x01;
					qcolor((21*(~modifiers&0x01)) + 1);
					break;
				case 'c':
					i++;
					if(!str[i]) return;
					switch(str[i]){
						case 'r':
							qcolor(91);
							break;
						case 'g':
							qcolor(92);
							break;
						case 'b':
							qcolor(94);
							break;
						case 'm':
							qcolor(95);
							break;
						default:
							break;
					}
					break;
				default:
					break;
			}
		}
		else{
			write(1, &(str[i]), 1);
		}
		i++;
	}
	va_end(ap);
}
