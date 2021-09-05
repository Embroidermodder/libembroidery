#include "embroidery.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void husExpand_258(int _259, unsigned char* _260, int _261, unsigned short* _262, unsigned short _263);
void husExpand_256(int _219);
void husExpand_255(void);
void husExpand_253(short _254, short _220, short _221);
unsigned short husExpand_252(int _219);
unsigned short husExpand_250(void);
unsigned short husExpand_249(void);

void husExpand(unsigned char* input, unsigned char* output, int compressedSize, int _269);
int husExpand_expand(void);
void husExpand_cleanup(void);

void husCompress_197(void);
void husCompress_198(void);
void husCompress_199(short _200, short _201);
void husCompress_202(unsigned short _203, unsigned short _204);
void husCompress_207(void);
void husCompress_208(int _209, unsigned short _203);
void husCompress_210(void);
int husCompress_211(int _212, unsigned short* _213, unsigned char* _214, unsigned short* _215);
void husCompress_216(unsigned short* _217);
void husCompress_218(short _219, short _220, short _221);
void husCompress_222(void);
void husCompress_223(short _203);
void husCompress_224(unsigned short _204);
void husCompress_225(int _226, unsigned short* ushortptr_187, short* shortptr_177, short _227);
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
unsigned short* ushortptr_187;
unsigned short* ushortptr_188;
unsigned short* ushortptr_189;
unsigned short* ushortptr_190;
unsigned short* ushortptr_191;
unsigned short* ushortptr_192;
unsigned short* ushortptr_193;
unsigned short* ushortptr_194;
unsigned short* ushortptr_240;
unsigned short* ushortptr_241;
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
    return (short)((_446 << 4) ^ (_278[_200 + 2])) & 4095;
}

void husCompress_447(short _200, short _201)
{
    short _204;
    _204 = shortptr_163[_201];
    if (_204 != -1)
        shortptr_164[_204] = _200;
    shortptr_164[_200] = _201;
    shortptr_163[_200] = _204;
    shortptr_163[_201] = _200;
}

void husCompress_448(short s)
{
    short _204;
    _204 = shortptr_164[s];
    if (_204 != -1) {
        shortptr_164[s] = -1;
        shortptr_163[_204] = -1;
    }
}

void husExpand(unsigned char* input, unsigned char* output, int compressedSize, int _269)
{
    /* only ever called with _269 = 10, so short_175 = 1024 */
    currentPosition = 0;
    outputPosition = 0;
    currentIndex = 0;
    inputBufferSize = (512);
    mStatus = 0;
    outputArray = output;
    inputArray = input;
    inputSize = (512);

    remainingBytes = compressedSize;
    if (_269 > 14 || _269 < 10) {
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

    ucharptr_166 = (unsigned char*)calloc(short_175 + 2, sizeof(unsigned char));
    ushortptr_240 = (unsigned short*)calloc(4096, sizeof(unsigned short));
    ushortptr_241 = (unsigned short*)calloc(256, sizeof(unsigned short));
    ushortptr_189 = (unsigned short*)calloc(1021, sizeof(unsigned short));
    ushortptr_190 = (unsigned short*)calloc(1021, sizeof(unsigned short));
    ucharptr_180 = (unsigned char*)calloc(511, sizeof(unsigned char));
    ucharptr_181 = (unsigned char*)calloc(19, sizeof(unsigned char));

    if (ucharptr_166 == NULL || ushortptr_189 == NULL || ushortptr_190 == NULL || ucharptr_180 == NULL || ucharptr_181 == NULL || ushortptr_240 == NULL || ushortptr_241 == NULL || inputBuffer == NULL) {
        mStatus = -1;
    }

    husExpand_expand();
    husExpand_cleanup();
}

void husExpand_cleanup(void)
{
    free(ucharptr_166);
    free(ushortptr_189);
    free(ushortptr_190);
    free(ucharptr_180);
    free(ucharptr_181);
    free(ushortptr_240);
    free(ushortptr_241);
}

void husExpand_253(short _254, short _220, short _221)
{
    short _226, _203, _219;
    unsigned short _283;
    _219 = husExpand_252(_220);
    if (_219 == 0) {
        _203 = husExpand_252(_220);
        memset(ucharptr_181, 0, _254);
        for (_226 = 0; _226 < 256; _226++)
            ushortptr_241[_226] = _203;
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
        husExpand_258(_254, ucharptr_181, 8, ushortptr_241, (256));
    }
}

int husExpand_expand(void)
{
    short _200 = 0;
    unsigned char* _278 = ucharptr_166;
    short _279 = short_175;
    short _280 = short_176;
    _243 = 0;
    _244 = 0;
    short_182 = 0;
    _245 = 0;
    short_172 = 0;
    _246 = 0;
    husExpand_256(16);

    while (_243 < 5) {
        short _203;
        if ((_203 = (short)husExpand_249()) <= (255)) {
            _278[_200] = (unsigned char)_203;
            if (++_200 >= _279) {
                _200 = 0;
                memcpy(&outputArray[outputPosition], _278, _279);
                outputPosition += _279;
            }
        } else {
            short _226;
            short _276 = (short)(_203 - ((255) + 1 - (3)));
            if (_276 == (257))
                break;
            _226 = (short)((_200 - husExpand_250() - 1) & _280);
            if (_226 < _279 - (256) - 1 && _200 < _279 - (256) - 1) {
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
        husExpand_253((19), (5), 3);
        husExpand_255();
        husExpand_253((15), (5), -1);
        if (mStatus < 0)
            return 0;
    }
    _244--;
    _276 = ushortptr_240[short_182 >> 4];
    if (_276 >= (511)) {
        _283 = 1U << 3;
        do {
            if (short_182 & _283)
                _276 = ushortptr_190[_276];
            else
                _276 = ushortptr_189[_276];
            _283 >>= 1;
        } while (_276 >= (511));
    }
    husExpand_256(ucharptr_180[_276]);
    return _276;
}

unsigned short husExpand_250(void)
{
    unsigned short _276, _283;
    _276 = ushortptr_241[short_182 >> 8];
    if (_276 >= (15)) {
        _283 = 1U << 7;
        do {
            if (short_182 & _283)
                _276 = ushortptr_190[_276];
            else
                _276 = ushortptr_189[_276];
            _283 >>= 1;
        } while (_276 >= (15));
    }
    husExpand_256(ucharptr_181[_276]);
    if (_276 != 0) {
        _276--;
        _276 = (short)((1U << _276) + husExpand_252(_276));
    }
    return _276;
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
    short _219 = (short)husExpand_252((9));
    if (_219 == 0) {
        _203 = (short)husExpand_252((9));
        memset(ucharptr_180, 0, 511);
        for (_226 = 0; _226 < (4096); _226++) {
            ushortptr_240[_226] = (unsigned short)_203;
        }
    } else {
        _226 = 0;
        while (_226 < _219) {
            _203 = (short)ushortptr_241[short_182 >> 8];
            if (_203 >= (19)) {
                unsigned short _283 = (unsigned short)1U << 7;
                do {
                    if ((short_182 & _283) != 0) {
                        _203 = (short)ushortptr_190[_203];
                    } else {
                        _203 = (short)ushortptr_189[_203];
                    }
                    _283 >>= 1;
                } while (_203 >= (19));
            }
            husExpand_256(ucharptr_181[_203]);
            if (_203 <= 2) {
                if (_203 == 0) {
                    _203 = 1;
                } else {
                    if (_203 == 1) {
                        _203 = (short)(husExpand_252(4) + 3);
                    } else {
                        _203 = (short)(husExpand_252((9)) + 20);
                    }
                }
                while (--_203 >= 0) {
                    ucharptr_180[_226++] = 0;
                }
            } else {
                ucharptr_180[_226++] = (unsigned char)(_203 - 2);
            }
        }
        while (_226 < (511)) {
            ucharptr_180[_226++] = 0;
        }
        husExpand_258((511), ucharptr_180, 12, ushortptr_240, (4096));
    }
}

void husExpand_256(int _219)
{
    while (_219 > short_172) {
        _219 -= short_172;
        short_182 = (unsigned short)((short_182 << short_172) + (_245 >> (8 - short_172)));
        if (_246 <= 0) {
            currentIndex = 0;

            if (remainingBytes >= 0 && remainingBytes < (512)) {
                inputBuffer = &inputArray[currentPosition];
                currentPosition += remainingBytes;
                _246 = (short)remainingBytes;
                remainingBytes -= _246;
                inputBufferSize = _246;
            } else {
                inputBuffer = &inputArray[currentPosition];
                currentPosition += (512);
                _246 = (512);
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

void husExpand_258(int _259, unsigned char* _260, int _261, unsigned short* _262, unsigned short _263)
{
    unsigned short _277[17], _287[17], _288[18], *_204;
    unsigned int _226, _289, _209, _290, _291, _292, _293, _283;
    _287[0] = 0;

    memset(_277, 0, 17*sizeof(unsigned short));
    for (_226 = 0; (int)_226 < _259; _226++)
        _277[_260[_226]]++;

    _288[0] = 0;
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
                    ushortptr_190[_292] = ushortptr_189[_292] = 0;
                    *_204 = (unsigned short)_292++;
                }
                if (_289 & _283)
                    _204 = &ushortptr_190[*_204];
                else
                    _204 = &ushortptr_189[*_204];
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
    if (_269 > (14) || _269 < (10)) {
        mStatus = -1;
        short_175 = 2;
    } else {
        short_175 = (short)(1 << _269);
    }
    short_176 = (short)(short_175 - 1);

    ucharptr_166 = (unsigned char*)calloc(short_175 + 258, sizeof(unsigned char));
    shortptr_163 = (short*)calloc(short_175 + 4096, sizeof(short));
    shortptr_164 = (short*)calloc(short_175, sizeof(short));
    ucharptr_165 = (unsigned char*)calloc(8192, sizeof(unsigned char));
    ucharptr_179 = (unsigned char*)calloc(512, sizeof(unsigned char));
    ushortptr_189 = (unsigned short*)calloc(1021, sizeof(unsigned short));
    ushortptr_190 = (unsigned short*)calloc(1021, sizeof(unsigned short));
    shortptr_177 = (short*)calloc(512, sizeof(short));
    ucharptr_180 = (unsigned char*)calloc(511, sizeof(unsigned char));
    ushortptr_191 = (unsigned short*)calloc(1021, sizeof(unsigned short));
    ushortptr_192 = (unsigned short*)calloc(511, sizeof(unsigned short));
    ucharptr_181 = (unsigned char*)calloc(19, sizeof(unsigned char));
    ushortptr_193 = (unsigned short*)calloc(29, sizeof(unsigned short));
    ushortptr_194 = (unsigned short*)calloc(19, sizeof(unsigned short));

    if (!ucharptr_166 || !shortptr_163 || !shortptr_164 || !ucharptr_165 || !ucharptr_179 || !ushortptr_189 || !ushortptr_190 || !shortptr_177 || !ucharptr_180 || !ushortptr_191 || !ushortptr_192 || !ucharptr_181 || !ushortptr_193 || !ushortptr_194) {
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
    free(ushortptr_189);
    free(ushortptr_190);
    free(shortptr_177);
    free(ucharptr_180);
    free(ushortptr_191);
    free(ushortptr_192);
    free(ucharptr_181);
    free(ushortptr_193);
    free(ushortptr_194);
}

void husCompress_223(short _203)
{
    husCompress_208(ucharptr_180[_203], ushortptr_192[_203]);
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
    memset(ushortptr_191, 0, 511*sizeof(unsigned short));
    memset(ushortptr_193, 0, 15*sizeof(unsigned short));
    short_173 = 0;
    short_172 = 0;
    short_182 = 0;
    short_171 = 0;
    short_170 = 0;
    short_185 = 1;
    short_184 = 0;
    short_186 = 0;
    ucharptr_165[0] = 0;
    short_183 = (8192);
    short_183 -= (unsigned short)((3 * CHAR_BIT) + 6);
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
    _201 = (short)(((_278[_200] << (4)) ^ (_278[_200 + 1])) & ((4096) - 1));
    _201 = (short)(husCompress_445(_200, _201, _278) + _279);
    while (_209 > (256) + 4 && !short_170) {
        husCompress_199(_200, _201);
        if (short_168 < (3)) {
            husCompress_202(_278[_200], 0);
            husCompress_447(_200, _201);
            _200++;
            _201 = (short)(husCompress_445(_200, _201, _278) + _279);
            _209--;
        } else {
            _209 -= short_168;
            husCompress_202((unsigned short)(short_168 + UCHAR_MAX - 2), short_169);
            while (--short_168 >= 0) {
                husCompress_447(_200, _201);
                _200++;
                _201 = (short)(husCompress_445(_200, _201, _278) + _279);
            }
        }
    }
    for (; _209 < (256); _209++) {
        int _203;
        if (inputPosition >= inputLength)
            break;
        _203 = (int)(unsigned char)inputArray[inputPosition];
        inputPosition += 1;
        _278[s] = (unsigned char)_203;
        if (s < (256) - 1)
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
            if (s < (256) - 1)
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
        husCompress_202((257) + (UCHAR_MAX + 1 - (3)), 0);
    husCompress_197();
    return outputPosition;
}

void husCompress_197(void)
{
    if (!short_170) {
        husCompress_207();
    }
    if (!short_170) {
        husCompress_208(CHAR_BIT - 1, 0);
        if (short_171) {
            husCompress_210();
        }
    }
    short_171 = 0;
    short_183 = 0;
    short_184 = 0;
}

void husCompress_198(void)
{
    int i;
    short* _450;
    _450 = &shortptr_163[short_175];

    for (i = (4096); i > 0; i--)
        *_450++ = (-1);
    _450 = shortptr_164;
    for (i = short_175; i > 0; i--)
        *_450++ = (-1);
}

void husCompress_199(short _200, short _201)
{
    unsigned char* _451;
    unsigned char* _278;
    short _226, _452, _204, _453;
    _452 = (128);
    short_168 = 0;
    _451 = &ucharptr_166[_200];
    _204 = _201;
    while ((_204 = shortptr_163[_204]) != (-1)) {
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
        for (_226 = 3; _226 < (256); _226++)
            if (_451[_226] != _278[_226])
                break;
        if (_226 > short_168) {
            _453 = (short)(_200 - _204 - 1);
            if (_453 < 0)
                _453 += short_175;
            if (_453 >= short_175)
                break;
            short_169 = _453;
            if ((short_168 = _226) >= (256))
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
    ushortptr_191[_203]++;
    if (_203 >= (1U << CHAR_BIT)) {
        ucharptr_165[short_186] |= (unsigned char)short_185;
        ucharptr_165[short_184++] = (unsigned char)_204;
        ucharptr_165[short_184++] = (unsigned char)(_204 >> CHAR_BIT);
        _203 = 0;
        while (_204) {
            _203++;
            _204 >>= 1;
        }
        ushortptr_193[_203]++;
    }
}

void husCompress_207(void)
{
    unsigned int _226, _289, _229, _454, _455;
    unsigned int _456 = 0;
    unsigned short _217[2 * (19) - 1];
    _229 = husCompress_211((511), ushortptr_191, ucharptr_180, ushortptr_192);
    _455 = ushortptr_191[_229];
    husCompress_208(16, (unsigned short)_455);
    if (_229 >= (511)) {
        husCompress_216(_217);
        _229 = husCompress_211((19), _217, ucharptr_181, ushortptr_194);
        if (_229 >= (19)) {
            husCompress_218((19), (5), 3);
        } else {
            husCompress_208((5), 0);
            husCompress_208((5), (unsigned short)_229);
        }
        husCompress_222();
    } else {
        husCompress_208((5), 0);
        husCompress_208((5), 0);
        husCompress_208((9), 0);
        husCompress_208((9), (unsigned short)_229);
    }
    _229 = husCompress_211((15), ushortptr_193, ucharptr_181, ushortptr_194);
    if (_229 >= (15)) {
        husCompress_218((15), (5), -1);
    } else {
        husCompress_208((5), 0);
        husCompress_208((5), (unsigned short)_229);
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
    for (_226 = 0; _226 < (511); _226++)
        ushortptr_191[_226] = 0;
    for (_226 = 0; _226 < (15); _226++)
        ushortptr_193[_226] = 0;
}

void husCompress_208(int _209, unsigned short _203)
{
    _203 <<= 16 - _209;
    short_182 |= (unsigned short)(_203 >> short_172);
    if ((short_172 += (short)_209) >= 8) {
        if (short_171 >= (512))
            husCompress_210();
        ucharptr_179[short_171++] = (unsigned char)(short_182 >> CHAR_BIT);
        if ((short_172 = (unsigned short)(short_172 - CHAR_BIT)) < CHAR_BIT)
            short_182 <<= CHAR_BIT;
        else {
            if (short_171 >= (512))
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
    ushortptr_187 = _213;
    ucharptr_178 = _214;
    _292 = short_174;
    _227 = 0;
    shortptr_177[1] = 0;
    for (_226 = 0; _226 < short_174; _226++) {
        ucharptr_178[_226] = 0;
        if (ushortptr_187[_226]) {
            shortptr_177[++_227] = (short)_226;
        }
    }
    if (_227 < 2) {
        _215[shortptr_177[1]] = 0;
        return shortptr_177[1];
    }
    for (_226 = _227 / 2; _226 >= 1; _226--) {
        husCompress_225(_226, ushortptr_187, shortptr_177, _227);
    }
    ushortptr_188 = _215;
    do {
        _226 = shortptr_177[1];
        if (_226 < short_174) {
            *ushortptr_188++ = (unsigned short)_226;
        }
        shortptr_177[1] = shortptr_177[_227--];
        husCompress_225(1, ushortptr_187, shortptr_177, _227);
        _276 = shortptr_177[1];
        if (_276 < short_174)
            *ushortptr_188++ = (unsigned short)_276;
        _289 = _292++;
        ushortptr_187[_289] = (unsigned short)(ushortptr_187[_226] + ushortptr_187[_276]);
        shortptr_177[1] = (short)_289;
        husCompress_225(1, ushortptr_187, shortptr_177, _227);
        ushortptr_189[_289] = (unsigned short)_226;
        ushortptr_190[_289] = (unsigned short)_276;
    } while (_227 > 1);
    ushortptr_188 = _215;
    husCompress_228(_289);
    husCompress_230(_212, _214, _215);
    return _289;
}

void husCompress_216(unsigned short* _217)
{
    short _226, _289, _219, _277;
    memset(_217, 0, 19*sizeof(unsigned short));
    _219 = 511;
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
    _219 = (511);
    while (_219 > 0 && ucharptr_180[_219 - 1] == 0)
        _219--;
    husCompress_208((9), _219);
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
                    husCompress_208(ucharptr_181[0], ushortptr_194[0]);
            } else if (_277 <= 18) {
                husCompress_208(ucharptr_181[1], ushortptr_194[1]);
                husCompress_208(4, (unsigned short)(_277 - 3));
            } else if (_277 == 19) {
                husCompress_208(ucharptr_181[0], ushortptr_194[0]);
                husCompress_208(ucharptr_181[1], ushortptr_194[1]);
                husCompress_208(4, 15);
            } else {
                husCompress_208(ucharptr_181[2], ushortptr_194[2]);
                husCompress_208((9), (unsigned short)(_277 - 20));
            }
        } else
            husCompress_208(ucharptr_181[_289 + 2], ushortptr_194[_289 + 2]);
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
    husCompress_208(ucharptr_181[_203], ushortptr_194[_203]);
    if (_203 > 1)
        husCompress_208(_203 - 1, _204);
}

void husCompress_225(int _226, unsigned short* ushortptr_187, short* shortptr_177, short _227)
{
    int _276, _289;
    _289 = shortptr_177[_226];
    while ((_276 = 2 * _226) <= _227) {
        if (_276 < _227 && ushortptr_187[shortptr_177[_276]] > ushortptr_187[shortptr_177[_276 + 1]])
            _276++;
        if (ushortptr_187[_289] <= ushortptr_187[shortptr_177[_276]])
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
    memset(ushortptr_167, 0, 17*sizeof(unsigned short));
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
            ucharptr_178[*ushortptr_188++] = (unsigned char)_226;
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
        husCompress_232(ushortptr_189[_226]);
        husCompress_232(ushortptr_190[_226]);
        short_173--;
    }
}
