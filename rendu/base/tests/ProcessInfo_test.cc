#include "../includes/ProcessInfo.h"
#include <stdio.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

int main()
{
  printf("pid = %d\n", rendu::ProcessInfo::pid());
  printf("uid = %d\n", rendu::ProcessInfo::uid());
  printf("euid = %d\n", rendu::ProcessInfo::euid());
  printf("start time = %s\n", rendu::ProcessInfo::startTime().toFormattedString().c_str());
  printf("hostname = %s\n", rendu::ProcessInfo::hostname().c_str());
  printf("opened files = %d\n", rendu::ProcessInfo::openedFiles());
  printf("threads = %zd\n", rendu::ProcessInfo::threads().size());
  printf("num threads = %d\n", rendu::ProcessInfo::numThreads());
  printf("status = %s\n", rendu::ProcessInfo::procStatus().c_str());
}