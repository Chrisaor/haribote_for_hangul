/* 그래픽 처리 관계 */

#include "bootpack.h"

void init_palette(void)
{
	static unsigned char table_rgb[16 * 3] = {
		0x00, 0x00, 0x00,	/*  0:흑 */
		0xff, 0x00, 0x00,	/*  1:밝은 빨강 */
		0x00, 0xff, 0x00,	/*  2:밝은 초록 */
		0xff, 0xff, 0x00,	/*  3:밝은 황색 */
		0x00, 0x00, 0xff,	/*  4:밝은 파랑 */
		0xff, 0x00, 0xff,	/*  5:밝은 보라색 */
		0x00, 0xff, 0xff,	/*  6:밝은 물색 */
		0xff, 0xff, 0xff,	/*  7:흰색 */
		0xc6, 0xc6, 0xc6,	/*  8:밝은 회색 */
		0x84, 0x00, 0x00,	/*  9:어두운 빨강 */
		0x00, 0x84, 0x00,	/* 10:어두운 초록 */
		0x84, 0x84, 0x00,	/* 11:어두운 황색 */
		0x00, 0x00, 0x84,	/* 12:어두운 파랑 */
		0x84, 0x00, 0x84,	/* 13:어두운 보라색 */
		0x00, 0x84, 0x84,	/* 14:어두운 물색 */
		0x84, 0x84, 0x84	/* 15:어두운 회색 */
	};
	set_palette(0, 15, table_rgb);
	return;

	/* static char 명령은 데이터 밖에 사용할 수 없지만 DB명령에 상당 */
}

void set_palette(int start, int end, unsigned char *rgb)
{
	int i, eflags;
	eflags = io_load_eflags();			/* 인터럽트 허가 플래그의 값을 기록한다 */
	io_cli(); 					/* 허가 플래그를 0으로 해 인터럽트 금지로 한다 */
	io_out8(0x03c8, start);
	for (i = start; i <= end; i++) {
		io_out8(0x03c9, rgb[0] / 4);
		io_out8(0x03c9, rgb[1] / 4);
		io_out8(0x03c9, rgb[2] / 4);
		rgb += 3;
	}
	io_store_eflags(eflags);	/* 인터럽트 허가 플래그를 원래대로 되돌린다 */
	return;
}

void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1)
{
	int x, y;
	for (y = y0; y <= y1; y++) {
		for (x = x0; x <= x1; x++)
			vram[y * xsize + x] = c;
	}
	return;
}

void init_screen8(char *vram, int x, int y)
{
	boxfill8(vram, x, COL8_008484,  0,     0,      x -  1, y - 29);
	boxfill8(vram, x, COL8_C6C6C6,  0,     y - 28, x -  1, y - 28);
	boxfill8(vram, x, COL8_FFFFFF,  0,     y - 27, x -  1, y - 27);
	boxfill8(vram, x, COL8_C6C6C6,  0,     y - 26, x -  1, y -  1);

	boxfill8(vram, x, COL8_FFFFFF,  3,     y - 24, 59,     y - 24);
	boxfill8(vram, x, COL8_FFFFFF,  2,     y - 24,  2,     y -  4);
	boxfill8(vram, x, COL8_848484,  3,     y -  4, 59,     y -  4);
	boxfill8(vram, x, COL8_848484, 59,     y - 23, 59,     y -  5);
	boxfill8(vram, x, COL8_000000,  2,     y -  3, 59,     y -  3);
	boxfill8(vram, x, COL8_000000, 60,     y - 24, 60,     y -  3);

	boxfill8(vram, x, COL8_848484, x - 47, y - 24, x -  4, y - 24);
	boxfill8(vram, x, COL8_848484, x - 47, y - 23, x - 47, y -  4);
	boxfill8(vram, x, COL8_FFFFFF, x - 47, y -  3, x -  4, y -  3);
	boxfill8(vram, x, COL8_FFFFFF, x -  3, y - 24, x -  3, y -  3);
	return;
}

void putfont8(char *vram, int xsize, int x, int y, char c, char *font)
{
	int i;
	char *p, d /* data */;
	for (i = 0; i < 16; i++) {
		p = vram + (y + i) * xsize + x;
		d = font[i];
		if ((d & 0x80) != 0) { p[0] = c; }
		if ((d & 0x40) != 0) { p[1] = c; }
		if ((d & 0x20) != 0) { p[2] = c; }
		if ((d & 0x10) != 0) { p[3] = c; }
		if ((d & 0x08) != 0) { p[4] = c; }
		if ((d & 0x04) != 0) { p[5] = c; }
		if ((d & 0x02) != 0) { p[6] = c; }
		if ((d & 0x01) != 0) { p[7] = c; }
	}
	return;
}


void putfonts8_asc(char *vram, int xsize, int x, int y, char c, unsigned char *s)
{
	extern char hankaku[4096];
	extern char hangul[8800];


	for (; *s != 0x00; s++) {
		// 만약 첫 비트가 1이면 hangul 을 쓰고 아니면 기존 hankaku를 사용한다.
		unsigned char firstbit = *s >> 7;
		if(firstbit==1){
			short int character_korean = (*s << 8) + *(++s);
			int first = (character_korean >> 10) & 0x1f;
			int sec = (character_korean >> 5) & 0x1f;
			int third = character_korean & 0x1f;

			
			

			//조합형 한글 매핑 규칙
			unsigned char Hangulcode_table[3][28] =
			{
			 	{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 0, 0, 0, 0, 0, 0, 0, 0} , //초성
				{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 0, 0, 0, 0, 0, 0}, //중성
				{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27} //종성
			};

			unsigned char jung_table[2][20] =
			{
			 	{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1}, //종성이 없을 때, 초성에 따른 중성의 벌 수 결정
				{0, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 3, 3, 3} //종성이 존재할 때, 초성에 따른 중성의 벌 수 결정
			};   

			unsigned char cho_jong_table[3][22] =
			{
			 	{0, 0, 2, 0, 2, 1, 2, 1, 2, 3, 0, 2, 1, 3, 3, 1, 2, 1, 3, 3, 1, 1},  //중성에 따른 종성의 벌 수 결정
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 3, 1, 2, 4, 4, 4, 2, 1, 3, 0}, //종성이 없을 때, 중성에 따른 초성의 벌 수 결정
				{0, 5, 5, 5, 5, 5, 5, 5, 5, 6, 7, 7, 7, 6, 6, 7, 7, 7, 6, 6, 7, 5} //종성이 존재할 때, 중성에 따른 초성의 벌 수 결정
			};
			
			char idx_cho = Hangulcode_table[0][first];
			char idx_jung = Hangulcode_table[1][sec];
			char idx_jong = Hangulcode_table[2][third];



			char cho_bul, jung_bul, jong_bul;


			if(third==0){  //종성이 없을 때
				cho_bul = cho_jong_table[1][idx_jung]; //중성에 따른 초성 벌 수 결정
				switch(cho_bul){ //각 벌 수에 따른 오프셋 설정
					case 0:first = first*2 + 0;break; //초성 1벌 받침 없는 ㅏㅐㅑㅒㅓㅔㅕㅖㅣ결합
					case 1:first = first*2 + 0x28;break;//초성 2벌 받침 없는 ㅗㅛㅡ와 결합
					case 2:first = first*2 + 0x50;break;//초성 3벌 받침 없는 ㅜㅠ 와 결합
					case 3:first = first*2 + 0x78;break;//초성 4벌 받침 없는 ㅘㅙㅚㅢ 와 결합
					case 4:first = first*2 + 0xa0;break;//초성 5벌 받침 없는 ㅝㅞㅟ와 결합
				}
				jung_bul = jung_table[0][idx_cho];  //초성에 따른 중성 벌 수 결정
				switch(jung_bul){
					case 0:sec = sec*2 + 0x140;break; //중성 1벌 ㄱㅋ와 결합
					case 1:sec = sec*2 + 0x16c;break; //중성 2벌 ㄱㅋ이외의 결합
				}
				jong_bul = 0;

			}else{
				cho_bul = cho_jong_table[2][idx_jung]; //중성에 따른 초벌 벌 수 결정
				switch(cho_bul){
					case 5:first = first*2 + 0xc8;break;//초성 6벌 받침 있는 ㅏㅐㅑㅒㅓㅔㅕㅖㅣ와 결합
					case 6:first = first*2 + 0xf0;break;//초성 7벌 받침 있는 ㅗㅛㅜㅠㅡ와 결합
					case 7:first = first*2 + 0x118;break;//초성 8벌 받침있는 ㅘㅙㅚㅢㅝㅞㅟ와 결합
				}
				jung_bul = jung_table[1][idx_cho];//초성에 따른 중성 벌 수 결정
				switch(jung_bul){
					case 2:sec = sec*2 + 0x198;break;//중성 3벌 받침 있는 ㄱㅋ와 결합
					case 3:sec = sec*2 + 0x1c4;break;//중성 4벌 받침있는 ㄱㅋ이외의 결합
				}
				jong_bul = cho_jong_table[0][idx_jung]; //중성에 따른 종성 벌 수 결정
				switch(jong_bul){
					case 0:third = third*2 + 0x1f0;break;//종성 1벌 ㅏㅑㅘ와 결합
					case 1:third = third*2 + 0x228;break;//종성 2벌 ㅓㅕㅚㅝㅟㅢㅣ와 결합 
					case 2:third = third*2 + 0x260;break;//종성 3벌 ㅐㅒㅔㅖㅙㅞ와 결합 
					case 3:third = third*2 + 0x298;break;//종성 4벌 ㅗㅛㅜㅠㅡ와 결합
				}
			}

			
			putfont8(vram, xsize, x, y, c, hangul + first * 16);
			putfont8(vram, xsize, x+8, y, c, hangul + (first + 1) * 16);
			putfont8(vram, xsize, x, y, c, hangul + sec * 16);
			putfont8(vram, xsize, x+8, y, c, hangul + (sec+1) * 16);
			putfont8(vram, xsize, x, y, c, hangul + third * 16);
			putfont8(vram, xsize, x+8, y, c, hangul + (third+1) * 16);
			

		}else{
			putfont8(vram, xsize, x, y, c, hankaku + *s * 16);
			x += 8;
		}
		
	}
	return;
}



void init_mouse_cursor8(char *mouse, char bc)
/* 마우스 커서를 준비(16 x16) */
{
	static char cursor[16][16] = {
		"**************..",
		"*OOOOOOOOOOO*...",
		"*OOOOOOOOOO*....",
		"*OOOOOOOOO*.....",
		"*OOOOOOOO*......",
		"*OOOOOOO*.......",
		"*OOOOOOO*.......",
		"*OOOOOOOO*......",
		"*OOOO**OOO*.....",
		"*OOO*..*OOO*....",
		"*OO*....*OOO*...",
		"*O*......*OOO*..",
		"**........*OOO*.",
		"*..........*OOO*",
		"............*OO*",
		".............***"
	};
	int x, y;

	for (y = 0; y < 16; y++) {
		for (x = 0; x < 16; x++) {
			if (cursor[y][x] == '*') {
				mouse[y * 16 + x] = COL8_000000;
			}
			if (cursor[y][x] == 'O') {
				mouse[y * 16 + x] = COL8_FFFFFF;
			}
			if (cursor[y][x] == '.') {
				mouse[y * 16 + x] = bc;
			}
		}
	}
	return;
}

void putblock8_8(char *vram, int vxsize, int pxsize,
	int pysize, int px0, int py0, char *buf, int bxsize)
{
	int x, y;
	for (y = 0; y < pysize; y++) {
		for (x = 0; x < pxsize; x++) {
			vram[(py0 + y) * vxsize + (px0 + x)] = buf[y * bxsize + x];
		}
	}
	return;
}
