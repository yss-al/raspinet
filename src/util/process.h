
#ifndef SYS_PROCESS_H
#define SYS_PROCESS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <log.h>

namespace sys {

class CProcess {

public:
// ��һ��daemon
static int startDaemon(const char *szPidFile, const char *szLogFile);
// �����ǲ��Ǵ���
static int existPid(const char *szPidFile);
// дPID�ļ�
static void writePidFile(const char *szPidFile);
};
}
#endif
