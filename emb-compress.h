/*! @file emb-compress.h */
#ifndef EMB_COMPRESS_H
#define EMB_COMPRESS_H

#include "emb-pattern.h"

#include "api-start.h"
#ifdef __cplusplus
extern "C" {
#endif

extern EMB_PRIVATE void EMB_CALL husExpand(unsigned char* input, unsigned char* output, int compressedSize, int _269);
extern EMB_PRIVATE int EMB_CALL husCompress(unsigned char* _266, unsigned long _inputSize, unsigned char* _267, int _269, int _235);

/*****************************************
 * HUS Expand Functions
 ****************************************/
extern EMB_PRIVATE void EMB_CALL husExpand_258(int _259, unsigned char* _260, int _261, unsigned short* _262, unsigned short _263);
extern EMB_PRIVATE void EMB_CALL husExpand_257(void);
extern EMB_PRIVATE void EMB_CALL husExpand_256(int _219);
extern EMB_PRIVATE void EMB_CALL husExpand_255(void);
extern EMB_PRIVATE void EMB_CALL husExpand_253(short _254, short _220, short _221);
extern EMB_PRIVATE unsigned short EMB_CALL husExpand_252(int _219);
extern EMB_PRIVATE void EMB_CALL husExpand_251(void);
extern EMB_PRIVATE unsigned short EMB_CALL husExpand_250(void);
extern EMB_PRIVATE unsigned short EMB_CALL husExpand_249(void);

extern EMB_PRIVATE void EMB_CALL husExpand(unsigned char* input, unsigned char* output, int compressedSize, int _269);
extern EMB_PRIVATE int EMB_CALL husExpand_expand(void);
extern EMB_PRIVATE void EMB_CALL husExpand_cleanup(void);

/*****************************************
 * HUS Compress Functions
 ****************************************/
extern EMB_PRIVATE void EMB_CALL husCompress_196(void);
extern EMB_PRIVATE void EMB_CALL husCompress_197(void);
extern EMB_PRIVATE void EMB_CALL husCompress_198(void);
extern EMB_PRIVATE void EMB_CALL husCompress_199(short _200, short _201);
extern EMB_PRIVATE void EMB_CALL husCompress_202(unsigned short _203, unsigned short _204);
extern EMB_PRIVATE void EMB_CALL husCompress_205(void);
extern EMB_PRIVATE void EMB_CALL husCompress_206(void);
extern EMB_PRIVATE void EMB_CALL husCompress_207(void);
extern EMB_PRIVATE void EMB_CALL husCompress_208(int _209, unsigned short _203);
extern EMB_PRIVATE void EMB_CALL husCompress_210(void);
extern EMB_PRIVATE int EMB_CALL husCompress_211(int _212, unsigned short* _213, unsigned char* _214, unsigned short* _215);
extern EMB_PRIVATE void EMB_CALL husCompress_216(unsigned short* _217);
extern EMB_PRIVATE void EMB_CALL husCompress_218(short _219, short _220, short _221);
extern EMB_PRIVATE void EMB_CALL husCompress_222(void);
extern EMB_PRIVATE void EMB_CALL husCompress_223(short _203);
extern EMB_PRIVATE void EMB_CALL husCompress_224(unsigned short _204);
extern EMB_PRIVATE void EMB_CALL husCompress_225(int _226, unsigned short* _187, short* _177, short _227);
extern EMB_PRIVATE void EMB_CALL husCompress_228(int _229);
extern EMB_PRIVATE void EMB_CALL husCompress_230(int _219, unsigned char* _209, unsigned short* _231);
extern EMB_PRIVATE void EMB_CALL husCompress_232(int _226);

/* extern EMB_PRIVATE int EMB_CALL husCompress(unsigned char* _266, unsigned long _inputSize, unsigned char* _267, int _269, int _235);
extern EMB_PRIVATE int EMB_CALL husCompress(unsigned char* _233, unsigned long _inputSize, unsigned char* _202, int _234, int _235);*/
extern EMB_PRIVATE void EMB_CALL husCompress_cleanup(void);
extern EMB_PRIVATE int EMB_CALL husCompress_compress(void);

/*TODO: macros are nasty, bleh */
#define husCompress_445(_200,_446)((short)((_446<<_154)^(_278[_200+2]))&(_153-1))
#define husCompress_447(_200,_201){short _204;if((_204=_163[_201])!=_157)_164[_204]=_200;_164[_200]=_201;_163[_200]=_204;_163[_201]=_200;}
#define husCompress_448(s){short _204;if((_204=_164[s])!=_157){_164[s]=_157;_163[_204]=_157;}}

#ifdef __cplusplus
}
#endif /* __cplusplus */
#include "api-stop.h"

#endif /* EMB_COMPRESS_H */

/* kate: bom off; indent-mode cstyle; indent-width 4; replace-trailing-space-save on; */
