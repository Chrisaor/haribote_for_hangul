/* bootpack의 메인 */

#include "bootpack.h"
#include <stdio.h>

void HariMain(void)
{
	struct BOOTINFO *binfo = (struct BOOTINFO *) ADR_BOOTINFO;
	unsigned char s[40], mcursor[256];
	int mx, my;

	init_gdtidt();
	init_pic();
	io_sti(); /* IDT/PIC의 초기화가 끝났으므로 CPU의 인터럽트 금지를 해제 */

	init_palette();
	init_screen8(binfo->vram, binfo->scrnx, binfo->scrny);
	mx = (binfo->scrnx - 16) / 2; /* 화면 중앙이 되도록 좌표 계산 */
	my = (binfo->scrny - 28 - 16) / 2;
	init_mouse_cursor8(mcursor, COL8_008484);
	putblock8_8(binfo->vram, binfo->scrnx, 16, 16, mx, my, mcursor, 16);
	
	//한글 문자 출력을 위한 배열 (1배열 = 1글자)
	unsigned char s1[20], s2[20], s3[20], s4[20], s5[20], s6[20], s7[20],
				s8[20], s9[20], s10[20], s11[20], s12[20], s13[20], s14[20],
				s15[20], s16[20], s17[20], s18[20], s19[20], k1[2], k2[2], k3[2];

    
	//    ㄱ~ㅎ       ㅑ(3)    ㄹㅁ(10)    
	// 1 [000/10] [00/011] [0/1010] 한글비트
	s1[0] = 0x84, s1[1] = 0x6a;
	s2[0] = 0x88, s2[1] = 0x6a;
	s3[0] = 0x8c, s3[1] = 0x6a;
	s4[0] = 0x90, s4[1] = 0x6a;
	s5[0] = 0x94, s5[1] = 0x6a;
	s6[0] = 0x98, s6[1] = 0x6a;
	s7[0] = 0x9c, s7[1] = 0x6a;
	s8[0] = 0xa0, s8[1] = 0x6a;
	s9[0] = 0xa4, s9[1] = 0x6a;
	s10[0] = 0xa8, s10[1] = 0x6a;
	s11[0] = 0xac, s11[1] = 0x6a;
	s12[0] = 0xb0, s12[1] = 0x6a;
	s13[0] = 0xb4, s13[1] = 0x6a;
	s14[0] = 0xb8, s14[1] = 0x6a;
	s15[0] = 0xbc, s15[1] = 0x6a;
	s16[0] = 0xc0, s16[1] = 0x6a;
	s17[0] = 0xc4, s17[1] = 0x6a;
	s18[0] = 0xc8, s18[1] = 0x6a;
	s19[0] = 0xcc, s19[1] = 0x6a;

	putfonts8_asc(binfo->vram, binfo->scrnx, 0, 0, COL8_FFFFFF, s1);
	putfonts8_asc(binfo->vram, binfo->scrnx, 16, 0, COL8_FFFFFF, s2);
	putfonts8_asc(binfo->vram, binfo->scrnx, 32, 0, COL8_FFFFFF, s3);
	putfonts8_asc(binfo->vram, binfo->scrnx, 48, 0, COL8_FFFFFF, s4);
	putfonts8_asc(binfo->vram, binfo->scrnx, 64, 0, COL8_FFFFFF, s5);
	putfonts8_asc(binfo->vram, binfo->scrnx, 80, 0, COL8_FFFFFF, s6);
	putfonts8_asc(binfo->vram, binfo->scrnx, 96, 0, COL8_FFFFFF, s7);
	putfonts8_asc(binfo->vram, binfo->scrnx, 112, 0, COL8_FFFFFF, s8);
	putfonts8_asc(binfo->vram, binfo->scrnx, 128, 0, COL8_FFFFFF, s9);
	putfonts8_asc(binfo->vram, binfo->scrnx, 144, 0, COL8_FFFFFF, s10);
	putfonts8_asc(binfo->vram, binfo->scrnx, 160, 0, COL8_FFFFFF, s11);
	putfonts8_asc(binfo->vram, binfo->scrnx, 176, 0, COL8_FFFFFF, s12);
	putfonts8_asc(binfo->vram, binfo->scrnx, 192, 0, COL8_FFFFFF, s13);
	putfonts8_asc(binfo->vram, binfo->scrnx, 208, 0, COL8_FFFFFF, s14);
	putfonts8_asc(binfo->vram, binfo->scrnx, 224, 0, COL8_FFFFFF, s15);
	putfonts8_asc(binfo->vram, binfo->scrnx, 240, 0, COL8_FFFFFF, s16);
	putfonts8_asc(binfo->vram, binfo->scrnx, 256, 0, COL8_FFFFFF, s17);
	putfonts8_asc(binfo->vram, binfo->scrnx, 272, 0, COL8_FFFFFF, s18);
	putfonts8_asc(binfo->vram, binfo->scrnx, 288, 0, COL8_FFFFFF, s19);


	k1[0] = 0x84, k1[1] = 0x00; //ㄱ
	k2[0] = 0x80, k2[1] = 0x40; //ㅏ
	k3[0] = 0x80, k2[1] = 0x00; //fill




	putfonts8_asc(binfo->vram, binfo->scrnx, 0, 32, COL8_FFFFFF, k1);
	putfonts8_asc(binfo->vram, binfo->scrnx, 16, 32, COL8_FFFFFF, k2);

	io_out8(PIC0_IMR, 0xf9); /* PIC1와 키보드를 허가(11111001) */
	io_out8(PIC1_IMR, 0xef); /* 마우스를 허가(11101111) */

	for (;;) {
		io_hlt();
	}
}
