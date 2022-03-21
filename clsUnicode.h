#ifndef CLSUNICODE_H
#define CLSUNICODE_H

#include <WString.h>

class clsUnicode
{
private:
     const char* GetCharWithCode(const char *uCode);
     const char* GetCodeWithChar(const char *Char, uint8_t sizeChar);

public:
    clsUnicode();
      String FromUCS2(const char*uCode, int Length);
      String FromUCS2(String uCode);
      String ToUCS2(const char*msg);
};

#endif // CLSUNICODE_H
