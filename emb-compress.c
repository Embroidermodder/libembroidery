#include "embroidery.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MACRO_132 (CHAR_BIT * sizeof(unsigned short))
#define MACRO_138 (10)
#define MACRO_139 (8)
#define MACRO_140 (256)
#define byte_MAX (255)
#define MACRO_141 (byte_MAX + MACRO_140)
#define MACRO_142 (15)
#define MACRO_143 (9)
#define MACRO_144 (MACRO_140 + 1)
#define MACRO_145 (19)
#define MACRO_147 (5)
#define MACRO_148 (4096)
#define MACRO_149 (256)

#define MACRO_152 (MACRO_145)
#define MACRO_153 (4096)
#define MACRO_154 (4)
#define MACRO_155 (8192)
#define MACRO_156 (512)
#define MACRO_157 (-1)
#define MACRO_158 (128)
#define MACRO_159 (512)
#define MACRO_540 (5)
#define bufferSize (512)

void husExpand_258(int _259, unsigned char* _260, int _261, unsigned short* _262, unsigned short _263);
void husExpand_257(void);
void husExpand_256(int _219);
void husExpand_255(void);
void husExpand_253(short _254, short _220, short _221);
unsigned short husExpand_252(int _219);
void husExpand_251(void);
unsigned short husExpand_250(void);
unsigned short husExpand_249(void);

void husExpand(unsigned char* input, unsigned char* output, int compressedSize, int _269);
int husExpand_expand(void);
void husExpand_cleanup(void);

void husCompress_196(void);
void husCompress_197(void);
void husCompress_198(void);
void husCompress_199(short _200, short _201);
void husCompress_202(unsigned short _203, unsigned short _204);
void husCompress_205(void);
void husCompress_206(void);
void husCompress_207(void);
void husCompress_208(int _209, unsigned short _203);
void husCompress_210(void);
int husCompress_211(int _212, unsigned short* _213, unsigned char* _214, unsigned short* _215);
void husCompress_216(unsigned short* _217);
void husCompress_218(short _219, short _220, short _221);
void husCompress_222(void);
void husCompress_223(short _203);
void husCompress_224(unsigned short _204);
void husCompress_225(int _226, unsigned short* _187, short* shortptr_177, short _227);
void husCompress_228(int _229);
void husCompress_230(int _219, unsigned char* _209, unsigned short* _231);
void husCompress_232(int _226);

/* int husCompress(unsigned char* _266, unsigned long _inputSize, unsigned char* _267, int _269, int _235);
int husCompress(unsigned char* _233, unsigned long _inputSize, unsigned char* _202, int _234, int _235);*/
void husCompress_cleanup(void);
int husCompress_compress(void);

short* shortptr_163;
short* shortptr_164;
unsigned char* ucharptr_165;
unsigned char* ucharptr_166;
unsigned short ushortptr_167[17];
short short_168;
short short_169;
short short_170;
short short_171;
short short_172;
short short_173;
short short_174;
short short_175;
short short_176;
short* shortptr_177;
unsigned char* ucharptr_178;
unsigned char* ucharptr_179;
unsigned char* ucharptr_180;
unsigned char* ucharptr_181;
unsigned short short_182;
unsigned short short_183;
unsigned short short_184;
unsigned short short_185;
unsigned short short_186;
unsigned short* _187;
unsigned short* _188;
unsigned short* _189;
unsigned short* _190;
unsigned short* _191;
unsigned short* _192;
unsigned short* _193;
unsigned short* _194;
unsigned short* _240;
unsigned short* _241;
short _243;
unsigned short _244;
unsigned char _245;
short _246;
int _531;
unsigned long _533;
unsigned long _534;

int mStatus;
int currentIndex;
long remainingBytes;
int inputSize;
int inputBufferSize;
int inputLength;
unsigned char* outputArray;
unsigned char* inputArray;
unsigned char* inputBuffer;
int currentPosition;
int inputPosition;
int outputPosition;

short husCompress_445(short _200, short _446, unsigned char *_278)
{
    return ((short)((_446 << MACRO_154) ^ (_278[_200 + 2])) & (MACRO_153 - 1));
}

void husCompress_447(short _200, short _201)
{
    short _204;
    if ((_204 = shortptr_163[_201]) != MACRO_157)
        shortptr_164[_204] = _200;
    shortptr_164[_200] = _201;
    shortptr_163[_200] = _204;
    shortptr_163[_201] = _200;
}

void husCompress_448(short s)
{
    short _204;
    _204 = shortptr_164[s];
    if (_204 != MACRO_157) {
        shortptr_164[s] = MACRO_157;
        shortptr_163[_204] = MACRO_157;
    }
}

void husExpand(unsigned char* input, unsigned char* output, int compressedSize, int _269)
{
    currentPosition = 0;
    outputPosition = 0;
    currentIndex = 0;
    inputBufferSize = bufferSize;
    mStatus = 0;
    outputArray = output;
    inputArray = input;
    inputSize = bufferSize;

    remainingBytes = compressedSize;
    if (_269 > (14) || _269 < MACRO_138) {
        mStatus = -1;
        short_175 = 2;
    } else {
        short_175 = (short)(1 << _269);
    }
    short_172 = 0;
    _243 = 0;
    _246 = 0;
    _244 = 0;
    _245 = 0;

    short_176 = (short)(short_175 - 1);

    ucharptr_166 = (unsigned char*)malloc(sizeof(unsigned char) * (short_175 + 2));
    if (ucharptr_166)
        memset(ucharptr_166, 0, (short_175 + 2) * sizeof(unsigned char));
    _240 = (unsigned short*)malloc(sizeof(unsigned short) * (MACRO_148));
    if (_240)
        memset(_240, 0, (MACRO_148) * sizeof(unsigned short));
    _241 = (unsigned short*)malloc(sizeof(unsigned short) * (MACRO_149));
    if (_241)
        memset(_241, 0, (MACRO_149) * sizeof(unsigned short));
    _189 = (unsigned short*)malloc(sizeof(unsigned short) * (2 * MACRO_141 - 1));
    if (_189)
        memset(_189, 0, (2 * MACRO_141 - 1) * sizeof(unsigned short));
    _190 = (unsigned short*)malloc(sizeof(unsigned short) * (2 * MACRO_141 - 1));
    if (_190)
        memset(_190, 0, (2 * MACRO_141 - 1) * sizeof(unsigned short));
    ucharptr_180 = (unsigned char*)malloc(sizeof(unsigned char) * (MACRO_141));
    if (ucharptr_180)
        memset(ucharptr_180, 0, (MACRO_141) * sizeof(unsigned char));
    ucharptr_181 = (unsigned char*)malloc(sizeof(unsigned char) * (MACRO_152));
    if (ucharptr_181)
        memset(ucharptr_181, 0, (MACRO_152) * sizeof(unsigned char));

    if (ucharptr_166 == NULL || _189 == NULL || _190 == NULL || ucharptr_180 == NULL || ucharptr_181 == NULL || _240 == NULL || _241 == NULL || inputBuffer == NULL) {
        mStatus = -1;
    }

    husExpand_expand();
    husExpand_cleanup();
}

void husExpand_cleanup(void)
{
    free(ucharptr_166);
    free(_189);
    free(_190);
    free(ucharptr_180);
    free(ucharptr_181);
    free(_240);
    free(_241);
}

void husExpand_253(short _254, short _220, short _221)
{
    short _226, _203, _219;
    unsigned short _283;
    _219 = husExpand_252(_220);
    if (_219 == 0) {
        _203 = husExpand_252(_220);
        for (_226 = 0; _226 < _254; _226++)
            ucharptr_181[_226] = 0;
        for (_226 = 0; _226 < 256; _226++)
            _241[_226] = _203;
    } else {
        _226 = 0;
        while (_226 < _219) {
            _203 = (short)(short_182 >> 13);
            if (_203 == 7) {
                _283 = 1U << 12;
                while (_283 & short_182) {
                    _283 >>= 1;
                    _203++;
                }
            }
            husExpand_256((_203 < 7) ? 3 : _203 - 3);
            ucharptr_181[_226++] = (unsigned char)_203;
            if (_226 == _221) {
                _203 = husExpand_252(2);
                while (--_203 >= 0)
                    ucharptr_181[_226++] = 0;
            }
        }
        while (_226 < _254)
            ucharptr_181[_226++] = 0;
        husExpand_258(_254, ucharptr_181, 8, _241, MACRO_149);
    }
}

int husExpand_expand(void)
{
    short _200 = 0;
    unsigned char* _278 = ucharptr_166;
    short _279 = short_175;
    short _280 = short_176;
    _243 = 0;
    husExpand_251();

    while (_243 < 5) {
        short _203;
        if ((_203 = (short)husExpand_249()) <= byte_MAX) {
            _278[_200] = (unsigned char)_203;
            if (++_200 >= _279) {
                _200 = 0;
                memcpy(&outputArray[outputPosition], _278, _279);
                outputPosition += _279;
            }
        } else {
            short _226;
            short _276 = (short)(_203 - (byte_MAX + 1 - (3)));
            if (_276 == MACRO_144)
                break;
            _226 = (short)((_200 - husExpand_250() - 1) & _280);
            if (_226 < _279 - MACRO_140 - 1 && _200 < _279 - MACRO_140 - 1) {
                while (--_276 >= 0)
                    _278[_200++] = _278[_226++];
            } else {
                while (--_276 >= 0) {
                    _278[_200] = _278[_226];
                    if (++_200 >= _279) {
                        _200 = 0;
                        memcpy(&outputArray[outputPosition], _278, _279);
                        outputPosition += _279;
                    }
                    _226 = (short)((_226 + 1) & _280);
                }
            }
        }
    }
    if (_200 != 0) {
        memcpy(&outputArray[outputPosition], _278, _200);
        outputPosition += _200;
    }
    return 0;
}

unsigned short husExpand_249(void)
{
    unsigned short _276, _283;
    if (_244 == 0) {
        _244 = husExpand_252(16);
        husExpand_253(MACRO_145, MACRO_147, 3);
        husExpand_255();
        husExpand_253(MACRO_142, MACRO_540, -1);
        if (mStatus < 0)
            return 0;
    }
    _244--;
    _276 = _240[short_182 >> 4];
    if (_276 >= MACRO_141) {
        _283 = 1U << 3;
        do {
            if (short_182 & _283)
                _276 = _190[_276];
            else
                _276 = _189[_276];
            _283 >>= 1;
        } while (_276 >= MACRO_141);
    }
    husExpand_256(ucharptr_180[_276]);
    return _276;
}

unsigned short husExpand_250(void)
{
    unsigned short _276, _283;
    _276 = _241[short_182 >> 8];
    if (_276 >= MACRO_142) {
        _283 = 1U << 7;
        do {
            if (short_182 & _283)
                _276 = _190[_276];
            else
                _276 = _189[_276];
            _283 >>= 1;
        } while (_276 >= MACRO_142);
    }
    husExpand_256(ucharptr_181[_276]);
    if (_276 != 0) {
        _276--;
        _276 = (short)((1U << _276) + husExpand_252(_276));
    }
    return _276;
}

void husExpand_251(void)
{
    _244 = 0;
    husExpand_257();
}

unsigned short husExpand_252(int _219)
{
    unsigned short _284 = (unsigned short)(short_182 >> (16 - _219));
    husExpand_256(_219);
    return _284;
}

void husExpand_255(void)
{
    short _226, _203;
    short _219 = (short)husExpand_252(MACRO_143);
    if (_219 == 0) {
        _203 = (short)husExpand_252(MACRO_143);
        for (_226 = 0; _226 < MACRO_141; _226++)
            ucharptr_180[_226] = 0;
        for (_226 = 0; _226 < MACRO_148; _226++)
            _240[_226] = (unsigned short)_203;
    } else {
        _226 = 0;
        while (_226 < _219) {
            _203 = (short)_241[short_182 >> 8];
            if (_203 >= MACRO_145) {
                unsigned short _283 = (unsigned short)1U << 7;
                do {
                    if ((short_182 & _283) != 0) {
                        _203 = (short)_190[_203];
                    } else {
                        _203 = (short)_189[_203];
                    }
                    _283 >>= 1;
                } while (_203 >= MACRO_145);
            }
            husExpand_256(ucharptr_181[_203]);
            if (_203 <= 2) {
                if (_203 == 0) {
                    _203 = 1;
                } else {
                    if (_203 == 1) {
                        _203 = (short)(husExpand_252(4) + 3);
                    } else {
                        _203 = (short)(husExpand_252(MACRO_143) + 20);
                    }
                }
                while (--_203 >= 0) {
                    ucharptr_180[_226++] = 0;
                }
            } else {
                ucharptr_180[_226++] = (unsigned char)(_203 - 2);
            }
        }
        while (_226 < MACRO_141) {
            ucharptr_180[_226++] = 0;
        }
        husExpand_258(MACRO_141, ucharptr_180, 12, _240, MACRO_148);
    }
}

void husExpand_256(int _219)
{
    while (_219 > short_172) {
        _219 -= short_172;
        short_182 = (unsigned short)((short_182 << short_172) + (_245 >> (8 - short_172)));
        if (_246 <= 0) {
            currentIndex = 0;

            if (remainingBytes >= 0 && remainingBytes < bufferSize) {
                inputBuffer = &inputArray[currentPosition];
                currentPosition += remainingBytes;
                _246 = (short)remainingBytes;
                remainingBytes -= _246;
                inputBufferSize = _246;
            } else {
                inputBuffer = &inputArray[currentPosition];
                currentPosition += bufferSize;
                _246 = bufferSize;
                inputBufferSize = _246;
            }
            if (_246 <= 0)
                _243++;
        }
        _245 = inputBuffer[currentIndex++];
        _246--;
        short_172 = 8;
    }
    short_172 = (short)(short_172 - _219);
    short_182 = (unsigned short)((short_182 << _219) + (_245 >> (8 - _219)));
    _245 <<= _219;
}

void husExpand_257(void)
{
    short_182 = 0;
    _245 = 0;
    short_172 = 0;
    _246 = 0;
    husExpand_256(16);
}

void husExpand_258(int _259, unsigned char* _260, int _261, unsigned short* _262, unsigned short _263)
{
    unsigned short _277[17], _287[17], _288[18], *_204;
    unsigned int _226, _289, _209, _290, _291, _292, _293, _283;
    _288[0] = 0;
    _277[0] = 0;
    _287[0] = 0;

    for (_226 = 1; _226 <= 16; _226++)
        _277[_226] = 0;
    for (_226 = 0; (int)_226 < _259; _226++)
        _277[_260[_226]]++;
    _288[1] = 0;
    for (_226 = 1; _226 <= 16; _226++)
        _288[_226 + 1] = (unsigned short)(_288[_226] + (_277[_226] << (16 - _226)));
    if (_288[17] != (unsigned short)(1U << 16)) {
        mStatus = -1;
        _243 = 10;
        return;
    }
    _291 = 16 - _261;
    for (_226 = 1; (int)_226 <= _261; _226++) {
        _288[_226] >>= _291;
        _287[_226] = (unsigned short)(1U << (_261 - _226));
    }
    while (_226 <= 16) {
        _287[_226] = (unsigned short)(1U << (16 - _226));
        _226++;
    }
    _226 = _288[_261 + 1] >> _291;
    if (_226 != (unsigned short)(1U << 16)) {
        _289 = 1U << _261;
        while (_226 != _289)
            _262[_226++] = 0;
    }
    _292 = _259;
    _283 = 1U << (15 - _261);
    for (_290 = 0; (int)_290 < _259; _290++) {
        if ((_209 = _260[_290]) == 0)
            continue;
        _293 = _288[_209] + _287[_209];
        if ((int)_209 <= _261) {
            if (_293 > _263) {
                mStatus = -1;
                _243 = 10;
                return;
            }
            for (_226 = _288[_209]; _226 < _293; _226++)
                _262[_226] = (unsigned short)_290;
        } else {
            _289 = _288[_209];
            _204 = &_262[_289 >> _291];
            _226 = _209 - _261;
            while (_226 != 0) {
                if (*_204 == 0) {
                    _190[_292] = _189[_292] = 0;
                    *_204 = (unsigned short)_292++;
                }
                if (_289 & _283)
                    _204 = &_190[*_204];
                else
                    _204 = &_189[*_204];
                _289 <<= 1;
                _226--;
            }
            *_204 = (unsigned short)_290;
        }
        _288[_209] = (unsigned short)_293;
    }
}

int husCompress(unsigned char* _266, unsigned long _inputSize, unsigned char* _267, int _269, int _235)
{
    int returnVal;
    inputArray = _266;
    outputArray = _267;
    _531 = _235;
    if (_269 > (14) || _269 < MACRO_138) {
        mStatus = -1;
        short_175 = 2;
    } else {
        short_175 = (short)(1 << _269);
    }
    short_176 = (short)(short_175 - 1);

    ucharptr_166 = (unsigned char*)malloc(sizeof(unsigned char) * (short_175 + MACRO_140 + 2));
    if (ucharptr_166)
        memset(ucharptr_166, 0, (short_175 + MACRO_140 + 2) * sizeof(unsigned char));
    shortptr_163 = (short*)malloc(sizeof(short) * (short_175 + MACRO_153));
    if (shortptr_163)
        memset(shortptr_163, 0, (short_175 + MACRO_153) * sizeof(short));
    shortptr_164 = (short*)malloc(sizeof(short) * (short_175));
    if (shortptr_164)
        memset(shortptr_164, 0, (short_175) * sizeof(short));
    ucharptr_165 = (unsigned char*)malloc(sizeof(unsigned char) * (MACRO_155));
    if (ucharptr_165)
        memset(ucharptr_165, 0, (MACRO_155) * sizeof(unsigned char));
    ucharptr_179 = (unsigned char*)malloc(sizeof(unsigned char) * (MACRO_156));
    if (ucharptr_179)
        memset(ucharptr_179, 0, (MACRO_156) * sizeof(unsigned char));
    _189 = (unsigned short*)malloc(sizeof(unsigned short) * (2 * MACRO_141 - 1));
    if (_189)
        memset(_189, 0, (2 * MACRO_141 - 1) * sizeof(unsigned short));
    _190 = (unsigned short*)malloc(sizeof(unsigned short) * (2 * MACRO_141 - 1));
    if (_190)
        memset(_190, 0, (2 * MACRO_141 - 1) * sizeof(unsigned short));
    shortptr_177 = (short*)malloc(sizeof(short) * (MACRO_141 + 1));
    if (shortptr_177)
        memset(shortptr_177, 0, (MACRO_141 + 1) * sizeof(short));
    ucharptr_180 = (unsigned char*)malloc(sizeof(unsigned char) * (MACRO_141));
    if (ucharptr_180)
        memset(ucharptr_180, 0, (MACRO_141) * sizeof(unsigned char));
    _191 = (unsigned short*)malloc(sizeof(unsigned short) * (2 * MACRO_141 - 1));
    if (_191)
        memset(_191, 0, (2 * MACRO_141 - 1) * sizeof(unsigned short));
    _192 = (unsigned short*)malloc(sizeof(unsigned short) * (MACRO_141));
    if (_192)
        memset(_192, 0, (MACRO_141) * sizeof(unsigned short));
    ucharptr_181 = (unsigned char*)malloc(sizeof(unsigned char) * (MACRO_152));
    if (ucharptr_181)
        memset(ucharptr_181, 0, (MACRO_152) * sizeof(unsigned char));
    _193 = (unsigned short*)malloc(sizeof(unsigned short) * (2 * MACRO_142 - 1));
    if (_193)
        memset(_193, 0, (2 * MACRO_142 - 1) * sizeof(unsigned short));
    _194 = (unsigned short*)malloc(sizeof(unsigned short) * (MACRO_152));
    if (_194)
        memset(_194, 0, (MACRO_152) * sizeof(unsigned short));

    if (!ucharptr_166 || !shortptr_163 || !shortptr_164 || !ucharptr_165 || !ucharptr_179 || !_189 || !_190 || !shortptr_177 || !ucharptr_180 || !_191 || !_192 || !ucharptr_181 || !_193 || !_194) {
        mStatus = -1;
    }
    _533 = 0;
    _534 = _inputSize;
    inputLength = _inputSize;
    inputPosition = 0;
    outputPosition = 0;

    returnVal = husCompress_compress();
    husCompress_cleanup();
    return returnVal;
}

void husCompress_cleanup(void)
{
    free(ucharptr_166);
    free(shortptr_163);
    free(shortptr_164);
    free(ucharptr_165);
    free(ucharptr_179);
    free(_189);
    free(_190);
    free(shortptr_177);
    free(ucharptr_180);
    free(_191);
    free(_192);
    free(ucharptr_181);
    free(_193);
    free(_194);
}

void husCompress_223(short _203)
{
    husCompress_208(ucharptr_180[_203], _192[_203]);
}

int husCompress_compress(void)
{
    short _209;
    short _201;
    short _200;
    short s;
    int _231;
    unsigned char* _278;
    short _280;
    short _279;
    _278 = ucharptr_166;
    _280 = short_176;
    _279 = short_175;
    _231 = 0;
    husCompress_196();
    husCompress_198();
    _200 = 0;

    memcpy(_278, &inputArray[inputPosition], _279);

    inputPosition += _279;
    if (inputPosition > inputLength) {
        _209 = (short)(inputLength - inputPosition);
    } else {
        _209 = _279;
    }
    s = (short)(_209 & _280);
    short_169 = 0;
    short_168 = 0;
    _201 = (short)(((_278[_200] << MACRO_154) ^ (_278[_200 + 1])) & (MACRO_153 - 1));
    _201 = (short)(husCompress_445(_200, _201, _278) + _279);
    while (_209 > MACRO_140 + 4 && !short_170) {
        husCompress_199(_200, _201);
        if (short_168 < (3)) {
            husCompress_202(_278[_200], 0);
            husCompress_447(_200, _201);
            _200++;
            _201 = (short)(husCompress_445(_200, _201, _278) + _279);
            _209--;
        } else {
            _209 -= short_168;
            husCompress_202((unsigned short)(short_168 + (UCHAR_MAX + 1 - (3))), short_169);
            while (--short_168 >= 0) {
                husCompress_447(_200, _201);
                _200++;
                _201 = (short)(husCompress_445(_200, _201, _278) + _279);
            }
        }
    }
    for (; _209 < MACRO_140; _209++) {
        int _203;
        if (inputPosition >= inputLength)
            break;
        _203 = (int)(unsigned char)inputArray[inputPosition];
        inputPosition += 1;
        _278[s] = (unsigned char)_203;
        if (s < MACRO_140 - 1)
            _278[s + _279] = _278[s];
        husCompress_448(s);
        s = (short)((s + 1) & (_280));
    }
    while (_209 > 0 && !short_170) {
        husCompress_199(_200, _201);
        if (short_168 > _209)
            short_168 = _209;
        if (short_168 < (3)) {
            short_168 = 1;
            husCompress_202(_278[_200], 0);
        } else
            husCompress_202((unsigned short)(short_168 + (UCHAR_MAX + 1 - (3))), short_169);
        while (--short_168 >= 0) {
            int _203;
            if (inputPosition >= inputLength)
                break;
            _203 = (int)(unsigned char)inputArray[inputPosition];
            inputPosition += 1;
            _278[s] = (unsigned char)_203;
            if (s < MACRO_140 - 1)
                _278[s + _279] = _278[s];
            husCompress_448(s);
            s = (short)((s + 1) & (_280));
            husCompress_447(_200, _201);
            _200 = (short)((_200 + 1) & (_280));
            _201 = (short)(husCompress_445(_200, _201, _278) + _279);
        }
        while (short_168-- >= 0) {
            husCompress_447(_200, _201);
            _200 = (short)((_200 + 1) & _280);
            _201 = (short)(husCompress_445(_200, _201, _278) + _279);
            _209--;
        }
        if (mStatus < 0)
            return 1;
    }
    if (!short_170)
        husCompress_202(MACRO_144 + (UCHAR_MAX + 1 - (3)), 0);
    husCompress_197();
    return outputPosition;
}

void husCompress_196(void)
{
    int i;
    for (i = 0; i < MACRO_141; i++)
        _191[i] = 0;
    for (i = 0; i < MACRO_142; i++)
        _193[i] = 0;
    short_173 = 0;
    husCompress_205();
    short_170 = 0;
    short_185 = 1;
    short_184 = 0;
    short_186 = 0;
    ucharptr_165[0] = 0;
    short_183 = MACRO_155;
    short_183 -= (unsigned short)((3 * CHAR_BIT) + 6);
}

void husCompress_197(void)
{
    if (!short_170)
        husCompress_207();
    husCompress_206();
    short_183 = 0;
    short_184 = 0;
}

void husCompress_198(void)
{
    int i;
    short* _450;
    _450 = &shortptr_163[short_175];

    for (i = MACRO_153; i > 0; i--)
        *_450++ = MACRO_157;
    _450 = shortptr_164;
    for (i = short_175; i > 0; i--)
        *_450++ = MACRO_157;
}

void husCompress_199(short _200, short _201)
{
    unsigned char* _451;
    unsigned char* _278;
    short _226, _452, _204, _453;
    _452 = MACRO_158;
    short_168 = 0;
    _451 = &ucharptr_166[_200];
    _204 = _201;
    while ((_204 = shortptr_163[_204]) != MACRO_157) {
        if (--_452 < 0)
            break;
        _278 = &ucharptr_166[_204];
        if (_451[short_168] != _278[short_168])
            continue;
        if (_451[0] != _278[0])
            continue;
        if (_451[1] != _278[1])
            continue;
        if (_451[2] != _278[2])
            continue;
        for (_226 = 3; _226 < MACRO_140; _226++)
            if (_451[_226] != _278[_226])
                break;
        if (_226 > short_168) {
            _453 = (short)(_200 - _204 - 1);
            if (_453 < 0)
                _453 += short_175;
            if (_453 >= short_175)
                break;
            short_169 = _453;
            if ((short_168 = _226) >= MACRO_140)
                break;
        }
    }
}

void husCompress_202(unsigned short _203, unsigned short _204)
{
    if ((short_185 >>= 1) == 0) {
        short_185 = 1U << (CHAR_BIT - 1);
        if (short_184 >= short_183) {
            husCompress_207();
            if (short_170)
                return;
            short_184 = 0;
        }
        short_186 = short_184++;
        ucharptr_165[short_186] = 0;
    }
    ucharptr_165[short_184++] = (unsigned char)_203;
    _191[_203]++;
    if (_203 >= (1U << CHAR_BIT)) {
        ucharptr_165[short_186] |= (unsigned char)short_185;
        ucharptr_165[short_184++] = (unsigned char)_204;
        ucharptr_165[short_184++] = (unsigned char)(_204 >> CHAR_BIT);
        _203 = 0;
        while (_204) {
            _203++;
            _204 >>= 1;
        }
        _193[_203]++;
    }
}

void husCompress_205(void)
{
    short_172 = 0;
    short_182 = 0;
    short_171 = 0;
}

void husCompress_206(void)
{
    if (!short_170) {
        husCompress_208(CHAR_BIT - 1, 0);
        if (short_171) {
            husCompress_210();
        }
    }
    short_171 = 0;
}

void husCompress_207(void)
{
    unsigned int _226, _289, _229, _454, _455;
    unsigned int _456 = 0;
    unsigned short _217[2 * MACRO_145 - 1];
    _229 = husCompress_211(MACRO_141, _191, ucharptr_180, _192);
    _455 = _191[_229];
    husCompress_208(16, (unsigned short)_455);
    if (_229 >= MACRO_141) {
        husCompress_216(_217);
        _229 = husCompress_211(MACRO_145, _217, ucharptr_181, _194);
        if (_229 >= MACRO_145) {
            husCompress_218(MACRO_145, MACRO_147, 3);
        } else {
            husCompress_208(MACRO_147, 0);
            husCompress_208(MACRO_147, (unsigned short)_229);
        }
        husCompress_222();
    } else {
        husCompress_208(MACRO_147, 0);
        husCompress_208(MACRO_147, 0);
        husCompress_208(MACRO_143, 0);
        husCompress_208(MACRO_143, (unsigned short)_229);
    }
    _229 = husCompress_211(MACRO_142, _193, ucharptr_181, _194);
    if (_229 >= MACRO_142) {
        husCompress_218(MACRO_142, MACRO_540, -1);
    } else {
        husCompress_208(MACRO_540, 0);
        husCompress_208(MACRO_540, (unsigned short)_229);
    }
    _454 = 0;
    for (_226 = 0; _226 < _455; _226++) {
        if (_226 % CHAR_BIT == 0)
            _456 = ucharptr_165[_454++];
        else
            _456 <<= 1;
        if (_456 & (1U << (CHAR_BIT - 1))) {
            husCompress_223((short)(ucharptr_165[_454++] + (1U << CHAR_BIT)));
            _289 = ucharptr_165[_454++];
            _289 += ucharptr_165[_454++] << CHAR_BIT;
            husCompress_224((short)_289);
        } else
            husCompress_223(ucharptr_165[_454++]);
        if (short_170)
            return;
    }
    for (_226 = 0; _226 < MACRO_141; _226++)
        _191[_226] = 0;
    for (_226 = 0; _226 < MACRO_142; _226++)
        _193[_226] = 0;
}

void husCompress_208(int _209, unsigned short _203)
{
    _203 <<= 16 - _209;
    short_182 |= (unsigned short)(_203 >> short_172);
    if ((short_172 += (short)_209) >= 8) {
        if (short_171 >= MACRO_156)
            husCompress_210();
        ucharptr_179[short_171++] = (unsigned char)(short_182 >> CHAR_BIT);
        if ((short_172 = (unsigned short)(short_172 - CHAR_BIT)) < CHAR_BIT)
            short_182 <<= CHAR_BIT;
        else {
            if (short_171 >= MACRO_156)
                husCompress_210();
            ucharptr_179[short_171++] = (unsigned char)short_182;
            short_172 = (unsigned short)(short_172 - CHAR_BIT);
            short_182 = (unsigned short)(_203 << (_209 - short_172));
        }
    }
}

void husCompress_210(void)
{
    if (short_171 <= 0)
        return;
    if (_531 && (_533 += short_171) >= _534)
        short_170 = 1;
    else {
        memcpy(outputArray + outputPosition, ucharptr_179, short_171);
        outputPosition += short_171;
    }
    short_171 = 0;
}

int husCompress_211(int _212, unsigned short* _213, unsigned char* _214, unsigned short* _215)
{
    int _226, _276, _289, _292;
    short _227;
    short_174 = (short)_212;
    _187 = _213;
    ucharptr_178 = _214;
    _292 = short_174;
    _227 = 0;
    shortptr_177[1] = 0;
    for (_226 = 0; _226 < short_174; _226++) {
        ucharptr_178[_226] = 0;
        if (_187[_226]) {
            shortptr_177[++_227] = (short)_226;
        }
    }
    if (_227 < 2) {
        _215[shortptr_177[1]] = 0;
        return shortptr_177[1];
    }
    for (_226 = _227 / 2; _226 >= 1; _226--) {
        husCompress_225(_226, _187, shortptr_177, _227);
    }
    _188 = _215;
    do {
        _226 = shortptr_177[1];
        if (_226 < short_174) {
            *_188++ = (unsigned short)_226;
        }
        shortptr_177[1] = shortptr_177[_227--];
        husCompress_225(1, _187, shortptr_177, _227);
        _276 = shortptr_177[1];
        if (_276 < short_174)
            *_188++ = (unsigned short)_276;
        _289 = _292++;
        _187[_289] = (unsigned short)(_187[_226] + _187[_276]);
        shortptr_177[1] = (short)_289;
        husCompress_225(1, _187, shortptr_177, _227);
        _189[_289] = (unsigned short)_226;
        _190[_289] = (unsigned short)_276;
    } while (_227 > 1);
    _188 = _215;
    husCompress_228(_289);
    husCompress_230(_212, _214, _215);
    return _289;
}

void husCompress_216(unsigned short* _217)
{
    short _226, _289, _219, _277;
    for (_226 = 0; _226 < MACRO_145; _226++)
        _217[_226] = 0;
    _219 = MACRO_141;
    while (_219 > 0 && ucharptr_180[_219 - 1] == 0)
        _219--;
    _226 = 0;
    while (_226 < _219) {
        _289 = ucharptr_180[_226++];
        if (_289 == 0) {
            _277 = 1;
            while (_226 < _219 && ucharptr_180[_226] == 0) {
                _226++;
                _277++;
            }
            if (_277 <= 2)
                _217[0] += _277;
            else if (_277 <= 18)
                _217[1]++;
            else if (_277 == 19) {
                _217[0]++;
                _217[1]++;
            } else
                _217[2]++;
        } else {
            _217[_289 + 2]++;
        }
    }
}

void husCompress_218(short _219, short _220, short _221)
{
    short _226, _289;
    while (_219 > 0 && ucharptr_181[_219 - 1] == 0)
        _219--;
    husCompress_208(_220, _219);
    _226 = 0;
    while (_226 < _219) {
        _289 = ucharptr_181[_226++];
        if (_289 <= 6) {
            husCompress_208(3, _289);
        } else
            husCompress_208(_289 - 3, (unsigned short)(USHRT_MAX << 1));
        if (_226 == _221) {
            while (_226 < 6 && ucharptr_181[_226] == 0)
                _226++;
            husCompress_208(2, (unsigned short)(_226 - 3));
        }
    }
}

void husCompress_222(void)
{
    short _226, _289, _219, _277;
    _219 = MACRO_141;
    while (_219 > 0 && ucharptr_180[_219 - 1] == 0)
        _219--;
    husCompress_208(MACRO_143, _219);
    _226 = 0;
    while (_226 < _219) {
        _289 = ucharptr_180[_226++];
        if (_289 == 0) {
            _277 = 1;
            while (_226 < _219 && ucharptr_180[_226] == 0) {
                _226++;
                _277++;
            }
            if (_277 <= 2) {
                for (_289 = 0; _289 < _277; _289++)
                    husCompress_208(ucharptr_181[0], _194[0]);
            } else if (_277 <= 18) {
                husCompress_208(ucharptr_181[1], _194[1]);
                husCompress_208(4, (unsigned short)(_277 - 3));
            } else if (_277 == 19) {
                husCompress_208(ucharptr_181[0], _194[0]);
                husCompress_208(ucharptr_181[1], _194[1]);
                husCompress_208(4, 15);
            } else {
                husCompress_208(ucharptr_181[2], _194[2]);
                husCompress_208(MACRO_143, (unsigned short)(_277 - 20));
            }
        } else
            husCompress_208(ucharptr_181[_289 + 2], _194[_289 + 2]);
    }
}

void husCompress_224(unsigned short _204)
{
    unsigned short _203, _457;
    _203 = 0;
    _457 = _204;
    while (_457) {
        _203++;
        _457 >>= 1;
    }
    husCompress_208(ucharptr_181[_203], _194[_203]);
    if (_203 > 1)
        husCompress_208(_203 - 1, _204);
}

void husCompress_225(int _226, unsigned short* _187, short* shortptr_177, short _227)
{
    int _276, _289;
    _289 = shortptr_177[_226];
    while ((_276 = 2 * _226) <= _227) {
        if (_276 < _227 && _187[shortptr_177[_276]] > _187[shortptr_177[_276 + 1]])
            _276++;
        if (_187[_289] <= _187[shortptr_177[_276]])
            break;
        shortptr_177[_226] = shortptr_177[_276];
        _226 = _276;
    }
    shortptr_177[_226] = (unsigned short)_289;
}

void husCompress_228(int _229)
{
    int _226, _289;
    unsigned int _458;
    for (_226 = 0; _226 <= 16; _226++)
        ushortptr_167[_226] = 0;
    husCompress_232(_229);
    _458 = 0;
    for (_226 = 16; _226 > 0; _226--)
        _458 += ushortptr_167[_226] << (16 - _226);
    while (_458 != (1U << 16)) {
        ushortptr_167[16]--;
        for (_226 = 15; _226 > 0; _226--) {
            if (ushortptr_167[_226] != 0) {
                ushortptr_167[_226]--;
                ushortptr_167[_226 + 1] = (unsigned short)(ushortptr_167[_226 + 1] + 2);
                break;
            }
        }
        _458--;
    }
    for (_226 = 16; _226 > 0; _226--) {
        _289 = ushortptr_167[_226];
        while (--_289 >= 0)
            ucharptr_178[*_188++] = (unsigned char)_226;
    }
}

void husCompress_230(int _219, unsigned char* _209, unsigned short* _231)
{
    int i;
    unsigned short _288[18];
    _288[1] = 0;
    for (i = 1; i <= 16; i++)
        _288[i + 1] = (unsigned short)((_288[i] + ushortptr_167[i]) << 1);
    for (i = 0; i < _219; i++)
        _231[i] = _288[_209[i]]++;
}

void husCompress_232(int _226)
{
    if (_226 < short_174)
        ushortptr_167[(short_173 < 16) ? short_173 : 16]++;
    else {
        short_173++;
        husCompress_232(_189[_226]);
        husCompress_232(_190[_226]);
        short_173--;
    }
}
