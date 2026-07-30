                   /* defines.h */

#ifndef __DEFINES_H__
#define __DEFINES_H__

#define SETBIT(WORD,BP) (WORD=WORD|(1<<BP))
#define CLRBIT(WORD,BP) (WORD=WORD&(~(1<<BP)))
#define STATUSBIT(WORD,BP) ((WORD>>BP)&1)
#define WRITEBIT(WORD,BP,BIT) WORD=WORD&(~(1<<BP))|(BIT<<BP)
#define WRITENIBLE(WORD,SBP,NIBBLE) WORD=WORD&(~(0xf<<SBP))|(NIBBLE<<SBP)
#define WRITEBYTE(WORD,SBP,BYTE) (WORD=WORD&(~(0xff<<SBP))|(BYTE<<SBP))
#define WRITEHALFWORD(WORD,SBP,HALFWORD) WORD=WORD&(~(0xffff<<SBP))|(HALFWORD<<SBP)
#define SSETBIT(WORD,BP) WORD=(1<<BP)
#define SCLRBIT(WORD,BP) WORD=(1<<BP)
#define READNIBBLE(WORD,BP) ((WORD>>BP)&15)
#define READBYTE(WORD,BP) ((WORD>>BP)&0XFF)

#endif











