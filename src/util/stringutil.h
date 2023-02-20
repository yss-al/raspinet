
#ifndef SYS_STRINGUTIL_H
#define SYS_STRINGUTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <time.h>
#include <vector>

//using namespace std;

namespace sys {

class CStringUtil {
public:
// ��stringת��int
static int strToInt(const char *str, int d);
// ������
static int isInt(const char *str);
// ת��Сд
static char *strToLower(char *str);
// ת�ɴ�д
static char *strToUpper(char *str);
// trim
static char *trim(char *str, const char *what = " ", int mode = 3);
// hash_value
static int hashCode(const char *str);
// �õ�һ��str��hashֵ������
static int getPrimeHash(const char *str);
// ��string��delim�ָ���,�ŵ�list��
static void split(char *str, const char *delim, std::vector<char*> &list);
// urldecode
static char *urlDecode(const char *src, char *dest);
// http://murmurhash.googlepages.com/
static unsigned int murMurHash(const void *key, int len);
// ��bytesת�ɿɶ���, �� 10K 12M ��
static std::string formatByteSize(double bytes);
};
}

#endif
///////////////////END