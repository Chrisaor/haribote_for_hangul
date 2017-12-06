#ifndef HANGUL_CONST_H
#define HANGUL_CONST_H

extern char hangul[0x0000227e];

// static int tempUnionCode;
// static int oldKey;
// static int keyCode;

// static int Double_Jung(void) {
//   	static byte Jung_Table[7][3] = {
//     { 0xad, 0xa3, 0xae },    /* ㅗ, ㅏ, ㅘ */
//     { 0xad, 0xa4, 0xaf },    /* ㅗ, ㅐ, ㅙ */
//     { 0xad, 0xbd, 0xb2 },    /* ㅗ, ㅣ, ㅚ */
//     { 0xb4, 0xa7, 0xb5 },    /* ㅜ, ㅓ, ㅝ */
//     { 0xb4, 0xaa, 0xb6 },    /* ㅜ, ㅔ, ㅞ */
//     { 0xb4, 0xbd, 0xb7 },   /* ㅜ, ㅣ, ㅟ */
//     { 0xbb, 0xbd, 0xbc }    /* ㅡ, ㅣ, ㅢ */
//   };
//   int i;
//    for (i = 0; i < 7; i++) {
// 	    if (Jung_Table[i][0] == oldKey && Jung_Table[i][1] == keyCode)
// 	      return ((keyCode = Jung_Table[i][2]));
// 	  }
// 	  return 0;
// 	}

// static int Double_Jong(void) {
//   static byte Jong_Table[11][3] = {
//     { 0x82, 0x8b, 0xc4 },    /* ㄱ, ㅅ*/
//     { 0x84, 0x8e, 0xc6 },    /* ㄴ, ㅈ*/
//     { 0x84, 0x94, 0xc7 },    /* ㄴ, ㅎ*/
//     { 0x87, 0x82, 0xca },    /* ㄹ, ㄱ*/
//     { 0x87, 0x88, 0xcb },    /* ㄹ, ㅁ*/
//     { 0x87, 0x89, 0xcc },    /* ㄹ, ㅂ*/
//     { 0x87, 0x8b, 0xcd },    /* ㄹ, ㅅ*/
//     { 0x87, 0x92, 0xce },    /* ㄹ, ㅌ*/
//     { 0x87, 0x93, 0xcf },    /* ㄹ, ㅍ*/
//     { 0x87, 0x94, 0xd0 },    /* ㄹ, ㅎ*/
//     { 0x89, 0x8b, 0xd4 }    /* ㅂ, ㅅ*/
//   };
//   int i;
//    for (i = 0; i < 11; i++) {
//     if (Jong_Table[i][0] == oldKey && Jong_Table[i][1] == keyCode)
//       return (keyCode = Jong_Table[i][2]);
//   }
//   return 0;
// }
// int hanAutomata2(int key) { 

// int chKind, canBeJongsung = FALSE;
//   /* 초성코드에 대응하는 종성 코드 */
//   static byte Cho2Jong[] = {  
//     0xc2,  /*  기역                 */ 
//     0xc3,  /*  쌍기역               */
//     0xc5,  /*  니은                 */
//     0xc8,  /*  디귿                 */
//     0x00,  /*  쌍디귿 (해당 없음)   */
//     0xc9,  /*  리을                 */
//     0xd1,  /*  미음                 */
//     0xd3,  /*  비읍                 */
//     0x00,  /*  상비읍 (해당 없음)   */
//     0xd5,  /*  시옷                 */
//     0xd6,  /*  쌍시옷               */
//     0xd7,  /*  이응                 */
//     0xd8,    지읒                 
//     0x00,  /*  쌍지읒 (해당 없음)   */
//     0xd9,  /*  치읓                 */
//     0xda,  /*  키읔                 */  
//     0xdb,  /*  티읕                 */
//     0xdc,  /*  피읖                */
//     0xdd  /*  히읗                 */
//  };

// unsigned char HangulKey;

// typedef HANGUL_STATE_FUNC (*HANGUL_STATE_FUNC)(char* input)

// HANGUL_STATE_FUNC KeyGet(char *input);
// HANGUL_STATE_FUNC HangulStart(char *input);
// HANGUL_STATE_FUNC ChoState(char *input);
// HANGUL_STATE_FUNC JungState(char *input);
// HANGUL_STATE_FUNC D_JungState(char *input);
// HANGUL_STATE_FUNC S_JungState(char *input);
// HANGUL_STATE_FUNC JongState(char *input);
// HANGUL_STATE_FUNC D_JongState(char *input);
// HANGUL_STATE_FUNC FirstFinal(char *input);
// HANGUL_STATE_FUNC SecondFinal(char *input);

// HANGUL_STATE_FUNC KeyGet(char *input) //영어 키보드로 자음과 모음을 나눔
// {
// 	if(input=="Q"&&input=="W"&&input=="E"&&input=="R"&&input=="T"&&input=="A"&&input=="S"&&input=="D"&&input=="F"&&input=="G"&&input=="Z"&&input=="X"&&input=="C"&&input=="V"){
// 		return HangulKey = 0;
// 	}else if(input=="Y"&&input=="U"&&input=="I"&&input=="O"&&input=="P"&&input=="H"&&input=="J"&&input=="K"&&input=="L"&&input=="B"&&input=="N"&&input=="M"){
// 		return HangulKey = 1;
// 	}
// }

// HANGUL_STATE_FUNC HangulStart(char *input)//한글 처음 입력, 0일때 초성, 1일 때 모음 상태
// {
// 	if(HangulKey==0)
// 		return ChoState;
// 	else if(HangulKey==1)
// 		return S_JungState;
// }

// HANGUL_STATE_FUNC ChoState(char *input)
// {
// 	if(HangulKey==1)
// 		return JungState;
// 	else 
// 		return FirstFinal;
// }

// HANGUL_STATE_FUNC JungState(char *input)
// {
// 	if(HangulKey==0&&canBeJongsung)
// 		return JongState;
// 	else if(HangulKey==1&&Double_Jung)
// 		return D_JungState;
// }

// HANGUL_STATE_FUNC JongState(char *input)
// {
// 	if(HangulKey==0&&Double_Jong)
// 		return D_JongState;
// 	else if(HangulKey==1)
// 		return SecondFinal;
// }

// HANGUL_STATE_FUNC D_JongState(char *input)
// {
// 	if(HangulKey==1)
// 		return SecondFinal;
// 	else
// 		return FirstFinal;
// }




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

#endif