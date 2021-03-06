/*
   Copyright (C) CFEngine AS

   This file is part of CFEngine 3 - written and maintained by CFEngine AS.

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; version 3.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA

  To the extent this program is licensed as part of the Enterprise
  versions of CFEngine, the applicable Commerical Open Source License
  (COSL) may apply to this file if you as a licensee so wish it. See
  included file COSL.txt.
*/

#ifndef CFENGINE_PLATFORM_H
#define CFENGINE_PLATFORM_H

/*
 * Platform-specific definitions and declarations.
 *
 * This header has to be included first in order to define apropriate macros for
 * including system headers (such as _FILE_OFFSET_BITS).
 */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#define _GNU_SOURCE 1

#ifdef _WIN32
# define MAX_FILENAME 227
# define WINVER 0x501
#if defined(__CYGWIN__)
# undef FD_SETSIZE
#endif
# define FD_SETSIZE 512         // increase select(2) FD limit from 64
#else
# define MAX_FILENAME 254
#endif

#ifdef __MINGW32__
# include <winsock2.h>
# include <windows.h>
# include <accctrl.h>
# include <aclapi.h>
# include <psapi.h>
# include <wchar.h>
# include <sddl.h>
# include <tlhelp32.h>
# include <iphlpapi.h>
# include <ws2tcpip.h>
# include <objbase.h>           // for disphelper
#endif

#include <stdio.h>
#include <math.h>

#ifndef _GETOPT_H
# include "../libcompat/getopt.h"
#endif

#ifdef HAVE_STDLIB_H
# include <stdlib.h>
#endif
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#ifdef HAVE_UNAME
# include <sys/utsname.h>
#else
# define _SYS_NMLN       257

struct utsname
{
    char sysname[_SYS_NMLN];
    char nodename[_SYS_NMLN];
    char release[_SYS_NMLN];
    char version[_SYS_NMLN];
    char machine[_SYS_NMLN];
};

#endif

#include <sys/types.h>
#include <sys/stat.h>

#ifdef HAVE_STDINT_H
# include <stdint.h>
#endif

#ifdef HAVE_INTTYPES_H
# include <inttypes.h>
#endif

#ifdef HAVE_SYS_SYSTEMINFO_H
# include <sys/systeminfo.h>
#endif

#ifdef HAVE_SYS_PARAM_H
# include <sys/param.h>
#endif

#ifdef HAVE_SYS_MOUNT_H
# include <sys/mount.h>
#endif

#ifdef HAVE_SYS_WAIT_H
# include <sys/wait.h>
#endif
#ifndef WEXITSTATUS
# define WEXITSTATUS(s) ((unsigned)(s) >> 8)
#endif
#ifndef WIFEXITED
# define WIFEXITED(s) (((s) & 255) == 0)
#endif
#ifndef WIFSIGNALED
# define WIFSIGNALED(s) ((s) & 0)       /* Can't use for BSD */
#endif
#ifndef WTERMSIG
# define WTERMSIG(s) ((s) & 0)
#endif

#include "bool.h"

#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/rand.h>
#include <openssl/bn.h>
#include <errno.h>

#ifdef HAVE_PCRE_H
# include <pcre.h>
#endif

#ifdef HAVE_PCRE_PCRE_H
# include <pcre/pcre.h>
#endif

#ifdef HAVE_DIRENT_H
# include <dirent.h>
#else
# define dirent direct
# if HAVE_SYS_NDIR_H
#  include <sys/ndir.h>
# endif
# if HAVE_SYS_DIR_H
#  include <sys/dir.h>
# endif
# if HAVE_NDIR_H
#  include <ndir.h>
# endif
#endif

#include <signal.h>

#ifdef __MINGW32__
# define LOG_LOCAL0      (16<<3)
# define LOG_LOCAL1      (17<<3)
# define LOG_LOCAL2      (18<<3)
# define LOG_LOCAL3      (19<<3)
# define LOG_LOCAL4      (20<<3)
# define LOG_LOCAL5      (21<<3)
# define LOG_LOCAL6      (22<<3)
# define LOG_LOCAL7      (23<<3)
# define LOG_USER        (1<<3)
# define LOG_DAEMON      (3<<3)

#else /* !__MINGW32__ */
# include <syslog.h>
#endif

#ifdef _AIX
# ifndef ps2
#  include <sys/statfs.h>
# endif

# include <sys/systemcfg.h>
#endif

#ifdef __sun
# include <sys/statvfs.h>
# undef nfstype

#include <sys/mkdev.h>

#ifndef timersub
# define timersub(a, b, result)                             \
    do                                                      \
    {                                                       \
           (result)->tv_sec = (a)->tv_sec - (b)->tv_sec;    \
           (result)->tv_usec = (a)->tv_usec - (b)->tv_usec; \
           if ((result)->tv_usec < 0)                       \
           {                                                \
               --(result)->tv_sec;                          \
               (result)->tv_usec += 1000000;                \
           }                                                \
    } while (0)
#endif

#endif

#if !HAVE_DECL_DIRFD
int dirfd(DIR *dirp);
#endif

/* strndup is defined as a macro on many systems */
#if !HAVE_DECL_STRNDUP
# ifndef strndup
char *strndup(const char *s, size_t n);
# endif
#endif

#if !HAVE_DECL_STRNLEN
size_t strnlen(const char *str, size_t maxlen);
#endif

#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif

#if !HAVE_DECL_STRLCPY
size_t strlcpy(char *destination, const char *source, size_t size);
#endif

#if !HAVE_DECL_STRLCAT
size_t strlcat(char *destination, const char *source, size_t size);
#endif

#if !HAVE_DECL_STRSEP
char *strsep(char **stringp, const char *delim);
#endif

#ifdef __APPLE__
# include <sys/malloc.h>
# include <sys/paths.h>
#endif

#ifdef HAVE_SYS_MALLOC_H
# ifdef __APPLE__
#  include <sys/malloc.h>
#  include <sys/paths.h>
# endif
#else
# ifdef HAVE_MALLOC_H
#  ifndef __OpenBSD__
#   ifdef __FreeBSD__
#    include <stdlib.h>
#   else
#    include <malloc.h>
#   endif
#  endif
# endif
#endif

#include <fcntl.h>

#ifdef HAVE_VFS_H
# include <sys/vfs.h>
#endif

#ifdef __hpux
# include <sys/dirent.h>
#endif

#ifdef HAVE_UTIME_H
# include <utime.h>             /* use utime not utimes for portability */
#elif TIME_WITH_SYS_TIME
# include <sys/time.h>
# include <time.h>
#elif HAVE_SYS_TIME_H
# include <sys/time.h>
#elif ! defined(AOS)
# include <time.h>
#endif

#ifdef HAVE_TIME_H
# include <time.h>
#endif

#ifdef HAVE_SYS_TIME_H
# include <sys/time.h>
#endif

#ifndef __MINGW32__
# include <pwd.h>
# include <grp.h>
#endif

#ifdef HAVE_SYS_SOCKIO_H
# include <sys/sockio.h>
#endif

#ifndef __MINGW32__
# include <sys/socket.h>
# include <sys/ioctl.h>
# include <net/if.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <netinet/tcp.h>
# include <arpa/inet.h>
# include <netdb.h>
# if !defined __linux__ && !defined _WIN32
#  include <sys/protosw.h>
#  undef sgi
#  include <net/route.h>
# endif
#endif

#ifdef __linux__
# ifdef __GLIBC__
#  include <net/route.h>
#  include <netinet/in.h>
#  include <netinet/ip.h>
# else
#  include <linux/route.h>
#  include <linux/in.h>
#  include <linux/ip.h>
# endif
#endif

#ifndef CLOCK_REALTIME
# define CLOCK_REALTIME 1
#endif

#ifndef HAVE_CLOCKID_T
typedef int clockid_t;
#endif

#ifndef HAVE_SOCKLEN_T
typedef int socklen_t;
#endif

# define __USE_GNU 1

# include <pthread.h>
# ifndef _SC_THREAD_STACK_MIN
#  define _SC_THREAD_STACK_MIN PTHREAD_STACK_MIN
# endif

# ifndef PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP
#  define PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP PTHREAD_MUTEX_INITIALIZER
# endif

# if !HAVE_DECL_PTHREAD_ATTR_SETSTACKSIZE
int pthread_attr_setstacksize(pthread_attr_t *attr, size_t stacksize);
# endif

#ifdef HAVE_SCHED_H
# include <sched.h>
#endif

#ifdef WITH_SELINUX
# include <selinux/selinux.h>
#endif

#ifndef MIN
# define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#ifndef MAX
# define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifndef INADDR_NONE
# define INADDR_NONE ((unsigned long int) 0xffffffff)
#endif
#ifndef HAVE_SETEGID
int setegid(gid_t gid);
#endif
#if !HAVE_DECL_UNAME
int uname(struct utsname *buf);
#endif
#if !HAVE_DECL_GETUID
uid_t getuid(void);
#endif
#if !HAVE_DECL_GETGID
gid_t getgid(void);
#endif
#if !HAVE_DECL_DRAND48
double drand48(void);
#endif
#if !HAVE_DECL_SRAND48
void srand48(long seed);
#endif
#if !HAVE_DECL_CLOCK_GETTIME
int clock_gettime(clockid_t clock_id, struct timespec *tp);
#endif
#if !HAVE_DECL_REALPATH
char *realpath(const char *path, char *resolved_path);
#endif
#if !HAVE_DECL_LSTAT
int lstat(const char *file_name, struct stat *buf);
#endif
#if !HAVE_DECL_SLEEP
unsigned int sleep(unsigned int seconds);
#endif
#if !HAVE_DECL_CHOWN
int chown(const char *path, uid_t owner, gid_t group);
#endif
#if !HAVE_DECL_FCHMOD
int fchmod(int fd, mode_t mode);
#endif

#if !HAVE_DECL_GETNETGRENT
int getnetgrent(char **host, char **user, char **domain);
#endif

#if !HAVE_DECL_SETNETGRENT
int setnetgrent(const char *netgroup);
#endif

#if !HAVE_DECL_ENDNETGRENT
int endnetgrent(void);
#endif

#if !HAVE_DECL_STRSTR
char *strstr(const char *haystack, const char *needle);
#endif
#if !HAVE_DECL_STRCASESTR
char *strcasestr(const char *haystack, const char *needle);
#endif
#if !HAVE_DECL_STRCASECMP
int strcasecmp(const char *s1, const char *s2);
#endif
#if !HAVE_DECL_STRNCASECMP
int strncasecmp(const char *s1, const char *s2, size_t n);
#endif
#if !HAVE_DECL_STRSIGNAL
char *strsignal(int sig);
#endif
#if !HAVE_DECL_STRDUP
char *strdup(const char *str);
#endif
#if !HAVE_DECL_MEMDUP
void *memdup(const void *mem, size_t size);
#endif
#if !HAVE_DECL_STRERROR
char *strerror(int err);
#endif
#if !HAVE_DECL_UNSETENV
int unsetenv(const char *name);
#endif
#ifndef HAVE_SETEUID
int seteuid(uid_t euid);
#endif
#ifndef HAVE_SETEUID
int setegid(gid_t egid);
#endif
#if !HAVE_DECL_SETLINEBUF
void setlinebuf(FILE *stream);
#endif
#if HAVE_STDARG_H
# include <stdarg.h>
# if !HAVE_VSNPRINTF
int rpl_vsnprintf(char *, size_t, const char *, va_list);
# endif
# if !HAVE_SNPRINTF
int rpl_snprintf(char *, size_t, const char *, ...);
# endif
# if !HAVE_VASPRINTF
int rpl_vasprintf(char **, const char *, va_list);
# endif
# if !HAVE_ASPRINTF
int rpl_asprintf(char **, const char *, ...);
# endif
#endif /* HAVE_STDARG_H */
#if !defined(isfinite)
# define isfinite(x) finite(x)
#endif
#if !HAVE_DECL_GMTIME_R
struct tm *gmtime_r(const time_t *timep, struct tm *result);
#endif
#if !HAVE_DECL_LOCALTIME_R
struct tm *localtime_r(const time_t *timep, struct tm *result);
#endif
#if !HAVE_DECL_CHMOD
int chmod(const char *path, mode_t mode);
#endif
#if !HAVE_DECL_ALARM
unsigned int alarm(unsigned int seconds);
#endif
#if !HAVE_DECL_MKDTEMP
char *mkdtemp(char *template);
#endif
#if !HAVE_DECL_STRRSTR
char *strrstr(const char *haystack, const char *needle);
#endif
#if !HAVE_DECL_INET_NTOP
const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
#endif
#if !HAVE_DECL_INET_PTON
int inet_pton(int af, const char *src, void *dst);
#endif
#if !HAVE_DECL_GETADDRINFO
int getaddrinfo(const char *node, const char *service,
                const struct addrinfo *hints, struct addrinfo **res);
void freeaddrinfo(struct addrinfo *res);
int getnameinfo(const struct sockaddr *sa, socklen_t salen,
                char *node, socklen_t nodelen,
                char *service, socklen_t servicelen, int flags);
const char *gai_strerror(int errcode);
#endif
#if !HAVE_STRUCT_SOCKADDR_STORAGE
    #ifdef AF_INET6
        #define sockaddr_storage sockaddr_in6
    #else
        #define sockaddr_storage sockaddr
    #endif
#endif
#ifndef AF_INET6
    /* if the platform doesn't have it, it's useless, but define it as -1
     * since we need it in our code... */
    #define AF_INET6 -1
#endif
#ifndef AI_NUMERICSERV
    /* Not portable to MinGW so don't use it. */
    #define AI_NUMERICSERV -1
#endif

#if !defined(HAVE_MKDIR_PROPER)
int rpl_mkdir(const char *pathname, mode_t mode);
#endif

#if !defined(HAVE_STAT_PROPER)
int rpl_stat(const char *path, struct stat *buf);
#define _stat64(name, st) rpl_stat(name, st)
#endif

#if !defined(HAVE_RENAME_PROPER)
int rpl_rename(const char *oldpath, const char *newpath);
#endif

#if !defined(HAVE_CTIME_PROPER)
char *rpl_ctime(const time_t *t);
#endif

#ifndef NGROUPS
# define NGROUPS 20
#endif

/*******************************************************************/
/*  Windows                                                        */
/*******************************************************************/

#ifdef __MINGW32__
# define MAXHOSTNAMELEN 256     // always adequate: http://msdn.microsoft.com/en-us/library/ms738527(VS.85).aspx

// as seen in in_addr struct in winsock.h
typedef u_long in_addr_t;

// shold be in winnt.h, but is not in current MinGW version
# ifndef VER_SUITE_WH_SERVER
#  define VER_SUITE_WH_SERVER 0x00008000
# endif

/* Dummy signals, can be set to anything below 23 but
 * 2, 4, 8, 11, 15, 21, 22 which are taken.
 * Calling signal() with anything from below causes SIG_ERR
 * to be returned.                                         */

# define SIGALRM 1
# define SIGHUP 3
# define SIGTRAP 5
# define SIGKILL 6
# define SIGPIPE 7
# define SIGCONT 9
# define SIGSTOP 10
# define SIGQUIT 12
# define SIGCHLD 13
# define SIGUSR1 14
# define SIGUSR2 16
# define SIGBUS 17

# if !defined( _TIMESPEC_DEFINED) && !defined(HAVE_STRUCT_TIMESPEC)
#  define HAVE_STRUCT_TIMESPEC 1
struct timespec
{
    long tv_sec;
    long tv_nsec;
};
# endif/* NOT _TIMESPEC_DEFINED */

#endif /* __MINGW32__ */

#ifndef ERESTARTSYS
# define ERESTARTSYS EINTR
#endif

#ifndef EOPNOTSUPP
# define EOPNOTSUPP EINVAL
#endif

#ifndef ENOTSUPP
# define ENOTSUPP EINVAL
#endif

/*******************************************************************/
/* Copy file defines                                               */
/*******************************************************************/

            /* Based heavily on cp.c in GNU-fileutils */

#ifndef DEV_BSIZE
# ifdef BSIZE
#  define DEV_BSIZE BSIZE
# else/* !BSIZE */
#  define DEV_BSIZE 4096
# endif/* !BSIZE */
#endif /* !DEV_BSIZE */

/* Extract or fake data from a `struct stat'.
   ST_BLKSIZE: Optimal I/O blocksize for the file, in bytes.
   ST_NBLOCKS: Number of 512-byte blocks in the file
   (including indirect blocks). */

#define SMALL_BLOCK_BUF_SIZE 512

#ifndef HAVE_ST_BLOCKS
# define ST_BLKSIZE(statbuf) DEV_BSIZE
# if defined(_POSIX_SOURCE) || !defined(BSIZE)  /* fileblocks.c uses BSIZE.  */
#  define ST_NBLOCKS(statbuf) (((statbuf).st_size + 512 - 1) / 512)
# else/* !_POSIX_SOURCE && BSIZE */
#  define ST_NBLOCKS(statbuf) (st_blocks ((statbuf).st_size))
# endif/* !_POSIX_SOURCE && BSIZE */
#else /* HAVE_ST_BLOCKS */
/* Some systems, like Sequents, return st_blksize of 0 on pipes. */
# define ST_BLKSIZE(statbuf) ((statbuf).st_blksize > 0 \
                               ? (statbuf).st_blksize : DEV_BSIZE)
# if defined(__hpux)
/* HP-UX counts st_blocks in 1024-byte units.
   This loses when mixing HP-UX and BSD filesystems with NFS.  */
#  define ST_NBLOCKS(statbuf) ((statbuf).st_blocks * 2)
# else/* !hpux */
#  if defined(_AIX) && defined(_I386)
/* AIX PS/2 counts st_blocks in 4K units.  */
#   define ST_NBLOCKS(statbuf) ((statbuf).st_blocks * 8)
#  else
      /* not AIX PS/2 */
#   define ST_NBLOCKS(statbuf) ((statbuf).st_blocks)
#  endif
       /* not AIX PS/2 */
# endif/* !hpux */
#endif /* HAVE_ST_BLOCKS */

#ifndef SEEK_CUR
# define SEEK_CUR 1
#endif

/*******************************************************************/
/* Ultrix/BSD don't have all these from sys/stat.h                 */
/*******************************************************************/

#ifndef S_IFBLK
# define S_IFBLK 0060000
#endif
#ifndef S_IFCHR
# define S_IFCHR 0020000
#endif
#ifndef S_IFDIR
# define S_IFDIR 0040000
#endif
#ifndef S_IFIFO
# define S_IFIFO 0010000
#endif
#ifndef S_IFREG
# define S_IFREG 0100000
#endif
#ifndef S_IFLNK
# define S_IFLNK 0120000
#endif
#ifndef S_IFSOCK
# define S_IFSOCK 0140000
#endif
#ifndef S_IFMT
# define S_IFMT  00170000
#endif

#ifndef S_ISREG
# define S_ISREG(m)      (((m) & S_IFMT) == S_IFREG)
#endif
#ifndef S_ISDIR
# define S_ISDIR(m)      (((m) & S_IFMT) == S_IFDIR)
#endif
#ifndef S_ISLNK
# define S_ISLNK(m)      (((m) & S_IFMT) == S_IFLNK)
#endif
#ifndef S_ISFIFO
# define S_ISFIFO(m)     (((m) & S_IFMT) == S_IFIFO)
#endif
#ifndef S_ISCHR
# define S_ISCHR(m)      (((m) & S_IFMT) == S_IFCHR)
#endif
#ifndef S_ISBLK
# define S_ISBLK(m)      (((m) & S_IFMT) == S_IFBLK)
#endif
#ifndef S_ISSOCK
# define S_ISSOCK(m)     (((m) & S_IFMT) == S_IFSOCK)
#endif

#ifndef S_IRUSR
# define S_IRWXU 00700
# define S_IRUSR 00400
# define S_IWUSR 00200
# define S_IXUSR 00100

# define S_IRWXG 00070
# define S_IRGRP 00040
# define S_IWGRP 00020
# define S_IXGRP 00010

# define S_IRWXO 00007
# define S_IROTH 00004
# define S_IWOTH 00002
# define S_IXOTH 00001
#endif

/* Too bad we don't have FD_CLOEXEC -- but we can fake it */
#ifndef FD_CLOEXEC
# define FD_CLOEXEC 0
#endif

/* kill(2) on OS X returns ETIMEDOUT instead of ESRCH */
#ifndef ETIMEDOUT
# define ETIMEDOUT ESRCH
#endif

/********************************************************************/
/* *BSD chflags stuff -                                             */
/********************************************************************/

#if !defined UF_NODUMP
# define UF_NODUMP 0
#endif
#if !defined UF_IMMUTABLE
# define UF_IMMUTABLE 0
#endif
#if !defined UF_APPEND
# define UF_APPEND 0
#endif
#if !defined UF_OPAQUE
# define UF_OPAQUE 0
#endif
#if !defined UF_NOUNLINK
# define UF_NOUNLINK 0
#endif
#if !defined SF_ARCHIVED
# define SF_ARCHIVED 0
#endif
#if !defined SF_IMMUTABLE
# define SF_IMMUTABLE 0
#endif
#if !defined SF_APPEND
# define SF_APPEND 0
#endif
#if !defined SF_NOUNLINK
# define SF_NOUNLINK 0
#endif
#define CHFLAGS_MASK  ( UF_NODUMP | UF_IMMUTABLE | UF_APPEND | UF_OPAQUE | UF_NOUNLINK | SF_ARCHIVED | SF_IMMUTABLE | SF_APPEND | SF_NOUNLINK )

/* For cygwin32 */

#if !defined O_BINARY
# define O_BINARY 0
#endif

#if defined(__MINGW32__)
/* _mkdir(3) */
#include <direct.h>
#endif

#include "config.post.h"

#endif
