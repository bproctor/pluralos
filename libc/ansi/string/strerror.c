
#include <string.h>

static const char *sys_errors[] = 
{
   "no error",                            /* EOK */
   "argument list too long",              /* E2BIG */
   "permission denied",                   /* EACCES */
   "address in use",                      /* EADDRINUSE */
   "address not available",               /* EADDRNOTAVAIL */
   "address family not supported",        /* EAFNOSUPPORT */
   "resource unavailable, try again",     /* EAGAIN */
   "connection already in progress",      /* EALREADY */
   "bad file descriptor",                 /* EBADF */
   "bad message",                         /* EBADMSG */
   "device or resource busy",             /* EBUSY */
   "operation cancelled",                 /* ECANCELED */
   "no child process",                    /* ECHILD */
   "connection aborted",                  /* ECONNABORTED */
   "connection refused",                  /* ECONNREFUSED */
   "connection reset",                    /* ECONNRESET */
   "resource deadlock would occur",       /* EDEADLK */
   "destination address required",        /* EDESTADDRREQ */
   "math argument out of domain of function", /* EDOM */
   "reserved",                            /* EDQUOT */
   "file exists",                         /* EEXIST */
   "bad address",                         /* EFAULT */
   "file too large",                      /* EFBIG */
   "host unreachable",                    /* EHOSTUNREACH */
   "identifier removed",                  /* EIDRM */
   "illegal byte sequence",               /* EILSEQ */
   "operation in progress",               /* EINPROGRESS */
   "interrupted function",                /* EINTR */
   "invalid argument",                    /* EINVAL */
   "I/O error",                           /* EIO */
   "socket is connected",                 /* EISCONN */
   "is a directory",                      /* EISDIR */
   "too many levels of symbolic links",   /* ELOOP */
   "too many open files",                 /* EMFILE */
   "too many links",                      /* EMLINK */
   "message too long",                    /* EMSGSIZE */
   "reserved",                            /* EMULTIHOP */
   "name too long",                       /* ENAMETOOLONG */
   "network is down",                     /* ENETDOWN */
   "network is unreachable",              /* ENETUNREACH */
   "too many files open in system",       /* ENFILE */
   "no buffer space available",           /* ENOBUFS */
   "no message available on stream head ready queue",  /* ENODATA */
   "no such device",                      /* ENODEV */
   "no such file or directory",           /* ENOENT */
   "executable file format error",        /* ENOEXEC */
   "no locks available",                  /* ENOLCK */
   "reserved",                            /* ENOLINK */
   "no memory left",                      /* ENOMEM */
   "protocol not available",              /* ENOPROTOOPT */
   "no space left on device",             /* ENOSPC */
   "no stream resource",                  /* ENOSR */
   "not a stream",                        /* ENOSTR */
   "function not supported",              /* ENOSYS */
   "the socket is not connected",         /* ENOTCONN */
   "not a directory",                     /* ENOTDIR */
   "directory not empty",                 /* ENOTEMPTY */
   "not a socket",                        /* ENOTSOCK */
   "not supported",                       /* ENOTSUP */
   "inappropriate I/O control operation", /* ENOTTY */
   "no such device or address",           /* ENXIO */
   "operation not supported",             /* EOPNOTSUPP */
   "too large to be stored in data type", /* EOVERFLOW */
   "operation not permitted",             /* EPERM */
   "broke pipe",                          /* EPIPE */
   "protocol error",                      /* EPROTO */
   "protocol not supported",              /* EPROTONOSUPPORT */
   "socket type not supported",           /* EPROTOTYPE */
   "result to large",
   "read-only file system",
   "invalid seek",
   "no such process",
   "reserved",
   "stream ioctl() timeout",
   "connection timed out",
   "text file busy",
   "operation would block",
   "cross-device link",
};
