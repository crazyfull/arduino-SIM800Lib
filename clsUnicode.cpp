#include "clsUnicode.h"
#include <wchar.h>
#include <cstring>
#include <SoftwareSerial.h>

#define ITEM_CHAR_LENGTH 4
#define ITEM_UCODE_LENGTH 5

typedef struct {
    char a[ITEM_CHAR_LENGTH] = {0};
    char b[ITEM_UCODE_LENGTH] = {0};
} Item;

Item UList[] = {
    {"	", "0009"}, {"\n", "000A"}, {" ", "0020"}, {"!", "0021"}, {"\"", "0022"}, {"#", "0023"},
    {"$", "0024"}, {"%", "0025"}, {"&", "0026"}, {"'", "0027"}, {"(", "0028"}, {")", "0029"},
    {"*", "002A"}, {"+", "002B"}, {",", "002C"}, {"-", "002D"}, {".", "002E"}, {"/", "002F"},
    {"0", "0030"}, {"1", "0031"}, {"2", "0032"}, {"3", "0033"}, {"4", "0034"}, {"5", "0035"},
    {"6", "0036"}, {"7", "0037"}, {"8", "0038"}, {"9", "0039"}, {":", "003A"}, {";", "003B"},
    {"<", "003C"}, {"=", "003D"}, {">", "003E"}, {"?", "003F"}, {"@", "0040"}, {"A", "0041"},
    {"B", "0042"}, {"C", "0043"}, {"D", "0044"}, {"E", "0045"}, {"F", "0046"}, {"G", "0047"},
    {"H", "0048"}, {"I", "0049"}, {"J", "004A"}, {"K", "004B"}, {"L", "004C"}, {"M", "004D"},
    {"N", "004E"}, {"O", "004F"}, {"P", "0050"}, {"Q", "0051"}, {"R", "0052"}, {"S", "0053"},
    {"T", "0054"}, {"U", "0055"}, {"V", "0056"}, {"W", "0057"}, {"X", "0058"}, {"Y", "0059"},
    {"Z", "005A"}, {"[", "005B"}, {"\\", "005C"}, {"]", "005D"}, {"^", "005E"}, {"_", "005F"},
    {"`", "0060"}, {"a", "0061"}, {"b", "0062"}, {"c", "0063"}, {"d", "0064"}, {"e", "0065"},
    {"f", "0066"}, {"g", "0067"}, {"h", "0068"}, {"i", "0069"}, {"j", "006A"}, {"k", "006B"},
    {"l", "006C"}, {"m", "006D"}, {"n", "006E"}, {"o", "006F"}, {"p", "0070"}, {"q", "0071"},
    {"r", "0072"}, {"s", "0073"}, {"t", "0074"}, {"u", "0075"}, {"v", "0076"}, {"w", "0077"},
    {"x", "0078"}, {"y", "0079"}, {"z", "007A"}, {"{", "007B"}, {"|", "007C"}, {"}", "007D"},
    {"~", "007E"}, {"¡", "00A1"}, {"¢", "00A2"}, {"£", "00A3"}, {"¥", "00A5"}, {"¦", "00A6"},
    {"§", "00A7"}, {"©", "00A9"}, {"«", "00AB"}, {"¬", "00AC"}, {"®", "00AE"}, {"¯", "00AF"},
    {"¶", "00B6"}, {"»", "00BB"}, {"¿", "00BF"}, {"Î", "00CE"}, {"×", "00D7"}, {"á", "00E1"},
    {"â", "00E2"}, {"ä", "00E4"}, {"æ", "00E6"}, {"î", "00EE"}, {"÷", "00F7"}, {"Ā", "0100"},
    {"ā", "0101"}, {"č", "010D"}, {"ē", "0113"}, {"ġ", "0121"}, {"ī", "012B"}, {"ō", "014D"},
    {"š", "0161"}, {"Ū", "016A"}, {"ū", "016B"}, {"ż", "017C"}, {"ž", "017E"}, {"Ɛ", "0190"},
    {"ǧ", "01E7"}, {"ɒ", "0252"}, {"ɛ", "025B"}, {"ɡ", "0261"}, {"ɢ", "0262"}, {"ɣ", "0263"},
    {"ʃ", "0283"}, {"ʒ", "0292"}, {"ʔ", "0294"}, {"ʾ", "02BE"}, {"ʿ", "02BF"}, {"ː", "02D0"},
    {"̇", "0307"}, {"̈", "0308"}, {"̯", "032F"}, {"̱", "0331"}, {"͡", "0361"}, {"β", "03B2"},
    {"Հ", "0540"}, {"ա", "0561"}, {"ե", "0565"}, {"յ", "0575"}, {"ն", "0576"}, {"ր", "0580"},
    {"،", "060C"}, {"؛", "061B"}, {"؟", "061F"}, {"ء", "0621"}, {"آ", "0622"}, {"أ", "0623"},
    {"ؤ", "0624"}, {"إ", "0625"}, {"ئ", "0626"}, {"ا", "0627"}, {"ب", "0628"}, {"ة", "0629"},
    {"ت", "062A"}, {"ث", "062B"}, {"ج", "062C"}, {"ح", "062D"}, {"خ", "062E"}, {"د", "062F"},
    {"ذ", "0630"}, {"ر", "0631"}, {"ز", "0632"}, {"س", "0633"}, {"ش", "0634"}, {"ص", "0635"},
    {"ض", "0636"}, {"ط", "0637"}, {"ظ", "0638"}, {"ع", "0639"}, {"غ", "063A"}, {"ـ", "0640"},
    {"ف", "0641"}, {"ق", "0642"}, {"ك", "0643"}, {"ل", "0644"}, {"م", "0645"}, {"ن", "0646"},
    {"ه", "0647"}, {"و", "0648"}, {"ى", "0649"}, {"ي", "064A"}, {"ً", "064B"}, {"ٌ", "064C"},
    {"ٍ", "064D"}, {"َ", "064E"}, {"ُ", "064F"}, {"ِ", "0650"}, {"ّ", "0651"}, {"ْ", "0652"},
    {"ٔ", "0654"}, {"ٕ", "0655"}, {"٠", "0660"}, {"١", "0661"}, {"٢", "0662"}, {"٣", "0663"},
    {"٤", "0664"}, {"٥", "0665"}, {"٦", "0666"}, {"٧", "0667"}, {"٨", "0668"}, {"٩", "0669"},
    {"٪", "066A"}, {"ٮ", "066E"}, {"ٯ", "066F"}, {"ٱ", "0671"}, {"ٹ", "0679"}, {"پ", "067E"},
    {"چ", "0686"}, {"ڈ", "0688"}, {"ڑ", "0691"}, {"ژ", "0698"}, {"ڡ", "06A1"}, {"ڤ", "06A4"},
    {"ک", "06A9"}, {"گ", "06AF"}, {"ں", "06BA"}, {"ۀ", "06C0"}, {"ۆ", "06C6"}, {"ی", "06CC"},
    {"ې", "06D0"}, {"ے", "06D2"}, {"ە", "06D5"}, {"ۤ", "06E4"}, {"۰", "06F0"}, {"۱", "06F1"},
    {"۲", "06F2"}, {"۳", "06F3"}, {"۴", "06F4"}, {"۵", "06F5"}, {"۶", "06F6"}, {"۷", "06F7"},
    {"۸", "06F8"}, {"۹", "06F9"}, {"द", "0926"}, {"न", "0928"}, {"ह", "0939"}, {"ა", "10D0"},
    {"თ", "10D7"}, {"ი", "10D8"}, {"ლ", "10DA"}, {"რ", "10E0"}, {"უ", "10E3"}, {"ქ", "10E5"},
    {" ", "2003"}, {"‌", "200C"}, {"‎", "200E"}, {"–", "2013"}, {"—", "2014"}, {"•", "2022"},
    {"…", "2026"}, {"‰", "2030"}, {"‾", "203E"}, {"€", "20AC"}, {"™", "2122"}, {"≈", "2248"},
    {"≠", "2260"}, {"◌", "25CC"}, {"❊", "274A"}, {"中", "4E2D"}, {"文", "6587"}, {"﮲", "FBB2"},
    {"﮳", "FBB3"}, {"﮴", "FBB4"}, {"﮵", "FBB5"}, {"﮶", "FBB6"}, {"﮹", "FBB9"}, {"ﺀ", "FE80"},
    {"ﺁ", "FE81"}, {"ﺂ", "FE82"}, {"ﺍ", "FE8D"}, {"ﺎ", "FE8E"}, {"ﺏ", "FE8F"}, {"ﺐ", "FE90"},
    {"ﺑ", "FE91"}, {"ﺒ", "FE92"}, {"ﺓ", "FE93"}, {"ﺔ", "FE94"}, {"ﺕ", "FE95"}, {"ﺖ", "FE96"},
    {"ﺗ", "FE97"}, {"ﺘ", "FE98"}, {"ﺙ", "FE99"}, {"ﺚ", "FE9A"}, {"ﺛ", "FE9B"}, {"ﺜ", "FE9C"},
    {"ﺝ", "FE9D"}, {"ﺞ", "FE9E"}, {"ﺟ", "FE9F"}, {"ﺠ", "FEA0"}, {"ﺡ", "FEA1"}, {"ﺢ", "FEA2"},
    {"ﺣ", "FEA3"}, {"ﺤ", "FEA4"}, {"ﺥ", "FEA5"}, {"ﺦ", "FEA6"}, {"ﺧ", "FEA7"}, {"ﺨ", "FEA8"},
    {"ﺩ", "FEA9"}, {"ﺪ", "FEAA"}, {"ﺫ", "FEAB"}, {"ﺬ", "FEAC"}, {"ﺭ", "FEAD"}, {"ﺮ", "FEAE"},
    {"ﺯ", "FEAF"}, {"ﺰ", "FEB0"}, {"ﺱ", "FEB1"}, {"ﺲ", "FEB2"}, {"ﺳ", "FEB3"}, {"ﺴ", "FEB4"},
    {"ﺵ", "FEB5"}, {"ﺶ", "FEB6"}, {"ﺷ", "FEB7"}, {"ﺸ", "FEB8"}, {"ﺹ", "FEB9"}, {"ﺺ", "FEBA"},
    {"ﺻ", "FEBB"}, {"ﺼ", "FEBC"}, {"ﺽ", "FEBD"}, {"ﺾ", "FEBE"}, {"ﺿ", "FEBF"}, {"ﻀ", "FEC0"},
    {"ﻁ", "FEC1"}, {"ﻂ", "FEC2"}, {"ﻃ", "FEC3"}, {"ﻄ", "FEC4"}, {"ﻅ", "FEC5"}, {"ﻆ", "FEC6"},
    {"ﻇ", "FEC7"}, {"ﻈ", "FEC8"}, {"ﻉ", "FEC9"}, {"ﻊ", "FECA"}, {"ﻋ", "FECB"}, {"ﻌ", "FECC"},
    {"ﻍ", "FECD"}, {"ﻎ", "FECE"}, {"ﻏ", "FECF"}, {"ﻐ", "FED0"}, {"ﻑ", "FED1"}, {"ﻒ", "FED2"},
    {"ﻓ", "FED3"}, {"ﻔ", "FED4"}, {"ﻕ", "FED5"}, {"ﻖ", "FED6"}, {"ﻗ", "FED7"}, {"ﻘ", "FED8"},
    {"ﻙ", "FED9"}, {"ﻚ", "FEDA"}, {"ﻛ", "FEDB"}, {"ﻜ", "FEDC"}, {"ﻝ", "FEDD"}, {"ﻞ", "FEDE"},
    {"ﻟ", "FEDF"}, {"ﻠ", "FEE0"}, {"ﻡ", "FEE1"}, {"ﻢ", "FEE2"}, {"ﻣ", "FEE3"}, {"ﻤ", "FEE4"},
    {"ﻥ", "FEE5"}, {"ﻦ", "FEE6"}, {"ﻧ", "FEE7"}, {"ﻨ", "FEE8"}, {"ﻩ", "FEE9"}, {"ﻪ", "FEEA"},
    {"ﻫ", "FEEB"}, {"ﻬ", "FEEC"}, {"ﻭ", "FEED"}, {"ﻮ", "FEEE"}, {"ﻯ", "FEEF"}, {"ﻰ", "FEF0"},
    {"ﻱ", "FEF1"}, {"ﻲ", "FEF2"}, {"ﻳ", "FEF3"}, {"ﻴ", "FEF4"}
}; //388

clsUnicode::clsUnicode() {
}

const char* clsUnicode::GetCharWithCode(const char *uCode) {
    bool ret = false;
    for (int i = 0; i < (sizeof(UList) / sizeof(Item)); i++) {
        if (strcmp(UList[i].b, uCode) == 0) {
            return UList[i].a;
        }
    }
    return NULL;
}

const char* clsUnicode::GetCodeWithChar(const char *Char, uint8_t sizeChar)
{
    bool ret = false;
    for (int i = 0; i < (sizeof(UList) / sizeof(Item)); i++) {
        if (strncmp(UList[i].a, Char, sizeChar) == 0) {
            return UList[i].b;
        }
    }
    return NULL;
}

String clsUnicode::FromUCS2(const char *uCode, int Length) {
    String ret;
    //0032 0036 0662 06F6           25٢۵
    
    const char *charOut;
    char part[ITEM_UCODE_LENGTH]={0};
    int n = 0;
    for (int i = 0; i < (Length / ITEM_CHAR_LENGTH); i++) {
        
        memcpy(part, uCode + n, ITEM_CHAR_LENGTH);
        part[ITEM_CHAR_LENGTH] = 0;
        n += ITEM_CHAR_LENGTH;
        
        charOut = clsUnicode::GetCharWithCode(part);
        if(charOut == NULL){
            //Serial.print("[");
            //Serial.print(part);
            //Serial.print("]");
            charOut = "*";
            //Serial.println("Can not found a Character!!!");
            
        }
        
        //Serial.write( (char*)&Charr, 2 );
        //Serial.println(charOut);
        
        ret += charOut;
        //ret.concat("ن");
        //ret.concat((char*)charOut, strlen(charOut));
    }
    
    
    return ret;
}

String clsUnicode::FromUCS2(String uCode){
    return FromUCS2(uCode.c_str(), uCode.length());
}

String clsUnicode::ToUCS2(const char *msg)
{
    //  126  <   , 1 bytes
    //  126  >   , 2 bytes
    //  219  >   , 3 bytes
    
    String ret;
    const char *p = msg;
    uint8_t dec = 0;
    uint8_t size = 0;
    
    while(*p != '\0')
    {
        dec = *p;
        if(dec > 219){
            size = 3;
        }else if(dec > 126){
            size = 2;
        }else if(dec < 126){
            size = 1;
        }
        
        
        const char *charOut = GetCodeWithChar(p, size);
        if(charOut != NULL)
            ret += charOut;
        
        
        p += size;
    }
    
    return ret;
}