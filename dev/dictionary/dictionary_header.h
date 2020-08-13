#define dictionaryBlockSize 20
struct DictionaryBlock {
  uint16_t blockSize;
  byte length[20];
  byte lxor[20];
  byte next[20];
}
#undef dictionaryBlockSize
