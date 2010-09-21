/*
 * Copyright (c) 1997, 1998, 1999, 2000, 2001, 2004, 2008, 2009, 2010
 *      Inferno Nettverk A/S, Norway.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. The above copyright notice, this list of conditions and the following
 *    disclaimer must appear in all copies of the software, derivative works
 *    or modified versions, and any portions thereof, aswell as in all
 *    supporting documentation.
 * 2. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed by
 *      Inferno Nettverk A/S, Norway.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Inferno Nettverk A/S requests users of this software to return to
 *
 *  Software Distribution Coordinator  or  sdc@inet.no
 *  Inferno Nettverk A/S
 *  Oslo Research Park
 *  Gaustadalléen 21
 *  NO-0349 Oslo
 *  Norway
 *
 * any improvements or extensions that they make and grant Inferno Nettverk A/S
 * the rights to redistribute these changes.
 *
 */

#define _NO_SUN_PRAGMA

#include "common.h"

static const char rcsid[] =
"$Id: interposition.c,v 1.130.2.3.2.4 2010/09/21 11:24:42 karls Exp $";

#if SOCKSLIBRARY_DYNAMIC

#if (defined __sun) && (defined _XPG4_2)
HAVE_PROT_BIND_0
bind(HAVE_PROT_BIND_1, HAVE_PROT_BIND_2, HAVE_PROT_BIND_3);
HAVE_PROT_CONNECT_0
connect(HAVE_PROT_CONNECT_1, HAVE_PROT_CONNECT_2, HAVE_PROT_CONNECT_3);
HAVE_PROT_LISTEN_0
listen(HAVE_PROT_LISTEN_1, HAVE_PROT_LISTEN_2);
HAVE_PROT_RECVMSG_0
recvmsg(HAVE_PROT_RECVMSG_1, HAVE_PROT_RECVMSG_2, HAVE_PROT_RECVMSG_3);
HAVE_PROT_SENDMSG_0
sendmsg(HAVE_PROT_SENDMSG_1, HAVE_PROT_SENDMSG_2, HAVE_PROT_SENDMSG_3);
HAVE_PROT_SENDTO_0
sendto(HAVE_PROT_SENDTO_1, HAVE_PROT_SENDTO_2, HAVE_PROT_SENDTO_3,
    HAVE_PROT_SENDTO_4, HAVE_PROT_SENDTO_5, HAVE_PROT_SENDTO_6);
#endif

#ifndef __USE_GNU
#define __USE_GNU /* XXX for RTLD_NEXT on Linux */
#endif /* !__USE_GNU */
#include <dlfcn.h>

#undef accept
#undef bind
#undef bindresvport
#undef connect
#undef gethostbyaddr
#undef gethostbyname
#undef gethostbyname2
#undef getaddrinfo
#undef getipnodebyname
#undef freehostent
#undef getpeername
#undef getsockname
#undef getsockopt
#undef listen
#undef read
#undef readv
#undef recv
#undef recvfrom
#undef recvmsg
#undef rresvport
#undef send
#undef sendmsg
#undef sendto
#undef write
#undef writev
#if HAVE_GSSAPI && HAVE_LINUX_GLIBC_WORKAROUND
#undef getc
#undef fgetc
#undef gets
#undef fgets
#undef putc
#undef fputc
#undef puts
#undef fputs
#undef printf
#undef vprintf
#undef fprintf
#undef vfprintf
#undef fwrite
#undef fread
#undef fflush
#undef fclose

#if HAVE__IO_GETC
#undef _IO_getc
#endif /* HAVE__IO_GETC */
#if HAVE__IO_PUTC
#undef _IO_putc
#endif /* HAVE__IO_PUTC */
#if HAVE___FPRINTF_CHK
#undef __fprintf_chk
#endif /* HAVE___FPRINTF_CHK */
#if HAVE___VFPRINTF_CHK
#undef __vfprintf_chk
#endif /* HAVE___VFPRINTF_CHK */
#endif /* HAVE_GSSAPI && HAVE_LINUX_GLIBC_WORKAROUND */

static struct libsymbol_t libsymbolv[] = {
#if SOCKS_CLIENT
{ SYMBOL_ACCEPT,               LIBRARY_ACCEPT,         NULL,   NULL, NULL },
{ SYMBOL_BIND,                 LIBRARY_BIND,           NULL,   NULL, NULL },
{ SYMBOL_BINDRESVPORT,         LIBRARY_BINDRESVPORT,   NULL,   NULL, NULL },
{ SYMBOL_CONNECT,              LIBRARY_CONNECT,        NULL,   NULL, NULL },
{ SYMBOL_GETPEERNAME,          LIBRARY_GETPEERNAME,    NULL,   NULL, NULL },
{ SYMBOL_GETSOCKNAME,          LIBRARY_GETSOCKNAME,    NULL,   NULL, NULL },
{ SYMBOL_GETSOCKOPT,           LIBRARY_GETSOCKOPT,     NULL,   NULL, NULL },
{ SYMBOL_LISTEN,               LIBRARY_LISTEN,         NULL,   NULL, NULL },
{ SYMBOL_READ,                 LIBRARY_READ,           NULL,   NULL, NULL },
{ SYMBOL_READV,                LIBRARY_READV,          NULL,   NULL, NULL },
{ SYMBOL_RECV,                 LIBRARY_RECV,           NULL,   NULL, NULL },
{ SYMBOL_RECVMSG,              LIBRARY_RECVMSG,        NULL,   NULL, NULL },
{ SYMBOL_RECVFROM,             LIBRARY_RECVFROM,       NULL,   NULL, NULL },
{ SYMBOL_RRESVPORT,            LIBRARY_RRESVPORT,      NULL,   NULL, NULL },
{ SYMBOL_SEND,                 LIBRARY_SEND,           NULL,   NULL, NULL },
{ SYMBOL_SENDMSG,              LIBRARY_SENDMSG,        NULL,   NULL, NULL },
{ SYMBOL_SENDTO,               LIBRARY_SENDTO,         NULL,   NULL, NULL },
{ SYMBOL_WRITE,                LIBRARY_WRITE,          NULL,   NULL, NULL },
{ SYMBOL_WRITEV,               LIBRARY_WRITEV,         NULL,   NULL, NULL },
#if HAVE_GETHOSTBYNAME2
{ SYMBOL_GETHOSTBYNAME2,       LIBRARY_GETHOSTBYNAME2, NULL,   NULL, NULL },
#endif /* HAVE_GETHOSTBYNAME2 */
#if HAVE_GETADDRINFO
{ SYMBOL_GETADDRINFO,          LIBRARY_GETADDRINFO,    NULL,   NULL, NULL },
#endif /* HAVE_GETADDRINFO */
#if HAVE_GETIPNODEBYNAME
{ SYMBOL_GETIPNODEBYNAME,      LIBRARY_GETIPNODEBYNAME,NULL,   NULL, NULL },
{ SYMBOL_FREEHOSTENT,          LIBRARY_FREEHOSTENT,    NULL,   NULL, NULL },
#endif /* HAVE_GETIPNODEBYNAME */

#ifdef __sun
{ SYMBOL_XNET_BIND,            LIBRARY_BIND,           NULL,   NULL, NULL },
{ SYMBOL_XNET_CONNECT,         LIBRARY_CONNECT,        NULL,   NULL, NULL },
{ SYMBOL_XNET_LISTEN,          LIBRARY_LISTEN,         NULL,   NULL, NULL },
{ SYMBOL_XNET_RECVMSG,         LIBRARY_RECVMSG,        NULL,   NULL, NULL },
{ SYMBOL_XNET_SENDMSG,         LIBRARY_SENDMSG,        NULL,   NULL, NULL },
{ SYMBOL_XNET_SENDTO,          LIBRARY_SENDTO,         NULL,   NULL, NULL },
#endif /* __sun */

#endif /* SOCKS_CLIENT */
{ SYMBOL_GETHOSTBYNAME,        LIBRARY_GETHOSTBYNAME,  NULL,   NULL, NULL },

#if SOCKS_SERVER
{ SYMBOL_GETHOSTBYADDR,        LIBRARY_GETHOSTBYADDR,  NULL,   NULL, NULL },
#endif /* SOCKS_SERVER */

#if SOCKS_CLIENT
#if HAVE_EXTRA_OSF_SYMBOLS
{ SYMBOL_EACCEPT,              LIBRARY_EACCEPT,        NULL,   NULL, NULL },
{ SYMBOL_EGETPEERNAME,         LIBRARY_EGETPEERNAME,   NULL,   NULL, NULL },
{ SYMBOL_EGETSOCKNAME,         LIBRARY_EGETSOCKNAME,   NULL,   NULL, NULL },
{ SYMBOL_EREADV,               LIBRARY_EREADV,         NULL,   NULL, NULL },
{ SYMBOL_ERECVFROM,            LIBRARY_ERECVFROM,      NULL,   NULL, NULL },
{ SYMBOL_ERECVMSG,             LIBRARY_ERECVMSG,       NULL,   NULL, NULL },
{ SYMBOL_ESENDMSG,             LIBRARY_ESENDMSG,       NULL,   NULL, NULL },
{ SYMBOL_EWRITEV,              LIBRARY_EWRITEV,        NULL,   NULL, NULL },
{ SYMBOL_NACCEPT,              LIBRARY_EACCEPT,        NULL,   NULL, NULL },
{ SYMBOL_NGETPEERNAME,         LIBRARY_NGETPEERNAME,   NULL,   NULL, NULL },
{ SYMBOL_NGETSOCKNAME,         LIBRARY_NGETSOCKNAME,   NULL,   NULL, NULL },
{ SYMBOL_NRECVFROM,            LIBRARY_NRECVFROM,      NULL,   NULL, NULL },
{ SYMBOL_NRECVMSG,             LIBRARY_NRECVMSG,       NULL,   NULL, NULL },
{ SYMBOL_NSENDMSG,             LIBRARY_NSENDMSG,       NULL,   NULL, NULL },
#endif /* HAVE_EXTRA_OSF_SYMBOLS */
#if HAVE_GSSAPI && HAVE_LINUX_GLIBC_WORKAROUND
{ SYMBOL_GETC,                 LIBRARY_GETC,           NULL,   NULL, NULL },
{ SYMBOL_FGETC,                LIBRARY_FGETC,          NULL,   NULL, NULL },
{ SYMBOL_GETS,                 LIBRARY_GETS,           NULL,   NULL, NULL },
{ SYMBOL_FGETS,                LIBRARY_FGETS,          NULL,   NULL, NULL },
{ SYMBOL_PUTC,                 LIBRARY_PUTC,           NULL,   NULL, NULL },
{ SYMBOL_FPUTC,                LIBRARY_FPUTC,          NULL,   NULL, NULL },
{ SYMBOL_PUTS,                 LIBRARY_PUTS,           NULL,   NULL, NULL },
{ SYMBOL_FPUTS,                LIBRARY_FPUTS,          NULL,   NULL, NULL },
{ SYMBOL_PRINTF,               LIBRARY_PRINTF,         NULL,   NULL, NULL },
{ SYMBOL_VPRINTF,              LIBRARY_VPRINTF,        NULL,   NULL, NULL },
{ SYMBOL_FPRINTF,              LIBRARY_FPRINTF,        NULL,   NULL, NULL },
{ SYMBOL_VFPRINTF,             LIBRARY_VFPRINTF,       NULL,   NULL, NULL },
{ SYMBOL_FWRITE,               LIBRARY_FWRITE,         NULL,   NULL, NULL },
{ SYMBOL_FREAD,                LIBRARY_FREAD,          NULL,   NULL, NULL },
{ SYMBOL_FFLUSH,               LIBRARY_FFLUSH,         NULL,   NULL, NULL },
{ SYMBOL_FCLOSE,               LIBRARY_FCLOSE,         NULL,   NULL, NULL },
#if HAVE__IO_GETC
{ SYMBOL__IO_GETC,             LIBRARY__IO_GETC,       NULL,   NULL, NULL },
#endif /* HAVE__IO_GETC */
#if HAVE__IO_PUTC
{ SYMBOL__IO_PUTC,             LIBRARY__IO_PUTC,       NULL,   NULL, NULL },
#endif /* HAVE__IO_PUTC */
#if HAVE___FPRINTF_CHK
{ SYMBOL___FPRINTF_CHK,        LIBRARY___FPRINTF_CHK,  NULL,   NULL, NULL },
#endif /* HAVE___FPRINTF_CHK */
#if HAVE___VFPRINTF_CHK
{ SYMBOL___VFPRINTF_CHK,       LIBRARY___VFPRINTF_CHK, NULL,   NULL, NULL },
#endif /* HAVE___VFPRINTF_CHK */
#endif /* HAVE_GSSAPI && HAVE_LINUX_GLIBC_WORKAROUND */
#endif /* SOCKS_CLIENT */
};

#if SOCKS_CLIENT

static void
addtolist(const char *functionname, const struct socks_id_t *id);
/*
 * Add "id" to the list of id's for which function name should resolve
 * to the native system call directly.
 */

static void
removefromlist(const char *functionname, const struct socks_id_t *id);
/*
 * Add "id" to the list of id's for which function name should resolve
 * to the native system call directly.
 */


static int
idsareequal(const struct socks_id_t *a, const struct socks_id_t *b);
/*
 * If "a" and "b" refer to the same thread/pid, return true.  Else, false.
 */


#endif /* SOCKS_CLIENT */

static struct libsymbol_t *
libsymbol(const char *symbol);
/*
 * Finds the libsymbol_t that "symbol" is defined in.
 */


void
symbolcheck(void)
{
   size_t i;

   for (i = 0; i < ELEMENTS(libsymbolv); ++i)
      symbolfunction(libsymbolv[i].symbol);
}

#if SOCKS_CLIENT

int
socks_shouldcallasnative(functionname)
   const char *functionname;
{
   struct socks_id_t myid, *fid;
   struct libsymbol_t *lib;

   lib = libsymbol(functionname);

   if ((fid = lib->dosyscall) == NULL)
      return 0;

   socks_whoami(&myid);

   for (; fid != NULL; fid = fid->next)
      if (idsareequal(&myid, fid))
         return 1;

   return 0;
}

void
socks_markasnative(functionname)
   const char *functionname;
{
   const char *function = "socks_markasnative()";
   struct socks_id_t myid;

   if (sockscf.option.debug > 1)
      slog(LOG_DEBUG, "%s: marking %s as native for current id",
      function, functionname);

   if (strcmp(functionname, "*") == 0) {
      size_t i;

      for (i = 0; i < ELEMENTS(libsymbolv); ++i)
         socks_markasnative(libsymbolv[i].symbol);

      return;
   }

   addtolist(functionname, socks_whoami(&myid));
}

void
socks_markasnormal(functionname)
   const char *functionname;
{
   const char *function = "socks_markasnormal()";
   struct socks_id_t myid;

   if (sockscf.option.debug > 1)
      slog(LOG_DEBUG, "%s: marking %s as normal for current id",
      function, functionname);

   if (strcmp(functionname, "*") == 0) {
      size_t i;

      for (i = 0; i < ELEMENTS(libsymbolv); ++i)
         socks_markasnormal(libsymbolv[i].symbol);

      return;
   }

   removefromlist(functionname, socks_whoami(&myid));
}


static int
idsareequal(a, b)
   const struct socks_id_t *a;
   const struct socks_id_t *b;
{

   switch (a->whichid) {
      case pid:
         if (a->id.pid == b->id.pid)
            return 1;
         return 0;

      case thread:
         /* pthread_equal() is more correct, but this should also work. */
         if (memcmp(&a->id.thread, &b->id.thread, sizeof(a->id.thread)) == 0)
            return 1;
         return 0;

      default:
         SERRX(a->whichid);
   }

   /* NOTREACHED */
}


static void
addtolist(functionname, id)
   const char *functionname;
   const struct socks_id_t *id;
{
   const char *function = "addtolist()";
   struct libsymbol_t *lib;
   struct socks_id_t *newid;
   addrlockopaque_t opaque;

   lib = libsymbol(functionname);
   SASSERTX(lib != NULL);

   if ((newid = malloc(sizeof(*lib->dosyscall))) == NULL)
      serr(EXIT_FAILURE, "%s: failed to malloc %lu bytes",
      function, (unsigned long)sizeof(*lib->dosyscall));
   *newid = *id;

   socks_addrlock(F_WRLCK, &opaque);

   if (lib->dosyscall == NULL) {
      lib->dosyscall       = newid;
      lib->dosyscall->next = NULL;
   }
   else {
      newid->next          = lib->dosyscall->next;
      lib->dosyscall->next = newid;
   }

   socks_addrunlock(&opaque);
}

static void
removefromlist(functionname, removeid)
   const char *functionname;
   const struct socks_id_t *removeid;
{
/*   const char *function = "removefromlist()"; */
   struct libsymbol_t *lib;
   struct socks_id_t *id, *previous;
   addrlockopaque_t opaque;

   lib = libsymbol(functionname);
   SASSERTX(lib != NULL);
   SASSERTX(lib->dosyscall != NULL);

   socks_addrlock(F_WRLCK, &opaque);

   previous = lib->dosyscall;

   if (idsareequal(lib->dosyscall, removeid)) {
      lib->dosyscall = lib->dosyscall->next;
      free(previous);
   }
   else {
      for (id = previous->next; id != NULL; previous = id, id = id->next) {
         if (idsareequal(id, removeid)) {
            previous->next = id->next;
            free(id);

            break;
         }
      }

      SASSERTX(id != NULL);
   }

   socks_addrunlock(&opaque);
}



#endif /* SOCKS_CLIENT */

void *
symbolfunction(symbol)
   const char *symbol;
{
   const char *function = "symbolfunction()";
   struct libsymbol_t *lib;

   lib = libsymbol(symbol);

   SASSERTX(lib != NULL);
   SASSERTX(lib->library != NULL);
   SASSERTX(strcmp(lib->symbol, symbol) == 0);

#if HAVE_RTLD_NEXT
   if (lib->function == NULL) {
      if ((lib->function = dlsym(RTLD_NEXT, symbol)) == NULL) {
         if (strcmp(symbol, SYMBOL_WRITE) != 0)
            serrx(EXIT_FAILURE, "%s: compile time configuration error?  "
                                "Failed to find \"%s\" using RTLD_NEXT: %s",
                                function, symbol, dlerror());
      } else {
#if 0
         if (strcmp(symbol, SYMBOL_WRITE) != 0)
            slog(LOG_DEBUG, "found symbol %s using RTLD_NEXT", lib->symbol);
#endif
      }
   }
#else /* !HAVE_RTLD_NEXT */
   if (lib->handle == NULL)
      if ((lib->handle = dlopen(lib->library, DL_LAZY)) == NULL)
         serrx(EXIT_FAILURE, "%s: compile time configuration error?  "
                             "Failed to open library \"%s\": %s",
                             function, lib->library, dlerror());

   if (lib->function == NULL)
      if ((lib->function = dlsym(lib->handle, symbol)) == NULL)
         serrx(EXIT_FAILURE, "%s: compile time configuration error?  "
                             "Failed to find \"%s\" in \"%s\": %s",
                             function, symbol, lib->library, dlerror());

#if 0
   if (strcmp(symbol, SYMBOL_WRITE) != 0)
      slog(LOG_DEBUG, "found symbol %s in library %s",
      lib->symbol, lib->library);
#endif
#endif /* !HAVE_RLTD_NEXT */

   return lib->function;
}

static struct libsymbol_t *
libsymbol(symbol)
   const char *symbol;
{
/*   const char *function = "libsymbol()"; */
   size_t i;

   for (i = 0; i < ELEMENTS(libsymbolv); ++i)
      if (strcmp(libsymbolv[i].symbol, symbol) == 0)
         return &libsymbolv[i];

   /* CONSTCOND */
   SASSERTX(0);   /* should never happen. */

   /* NOTREACHED */
   return NULL; /* please compiler. */
}

   /* the real system calls. */

#if SOCKS_CLIENT

#if !HAVE_EXTRA_OSF_SYMBOLS
HAVE_PROT_ACCEPT_0
sys_accept(s, addr, addrlen)
   HAVE_PROT_ACCEPT_1 s;
   HAVE_PROT_ACCEPT_2 addr;
   HAVE_PROT_ACCEPT_3 addrlen;
{
   int rc;
   typedef HAVE_PROT_ACCEPT_0 (*ACCEPT_FUNC_T)(HAVE_PROT_ACCEPT_1,
                                               HAVE_PROT_ACCEPT_2,
                                               HAVE_PROT_ACCEPT_3);
   ACCEPT_FUNC_T function;

   SYSCALL_START(s);
   function = (ACCEPT_FUNC_T)symbolfunction(SYMBOL_ACCEPT);
   rc = function(s, addr, addrlen);
   SYSCALL_END(s);
   return rc;
}
#endif /* !HAVE_EXTRA_OSF_SYMBOLS */

#if !HAVE_EXTRA_OSF_SYMBOLS
HAVE_PROT_BIND_0
sys_bind(s, name, namelen)
   HAVE_PROT_BIND_1 s;
   HAVE_PROT_BIND_2 name;
   HAVE_PROT_BIND_3 namelen;
{
   int rc;
   typedef HAVE_PROT_BIND_0 (*BIND_FUNC_T)(HAVE_PROT_BIND_1,
                                           HAVE_PROT_BIND_2,
                                           HAVE_PROT_BIND_3);
   BIND_FUNC_T function;

   SYSCALL_START(s);
   function = (BIND_FUNC_T)symbolfunction(SYMBOL_BIND);
   rc = function(s, name, namelen);
   SYSCALL_END(s);
   return rc;
}
#endif /* !HAVE_EXTRA_OSF_SYMBOLS */

int
sys_bindresvport(sd, sin)
   int sd;
   struct sockaddr_in *sin;
{
   int rc;
   typedef int (*BINDRESVPORT_FUNC_T)(int, struct sockaddr_in *);
   BINDRESVPORT_FUNC_T function;

   SYSCALL_START(sd);
   function = (BINDRESVPORT_FUNC_T)symbolfunction(SYMBOL_BINDRESVPORT);
   rc = function(sd, sin);
   SYSCALL_END(sd);
   return rc;
}

#if !HAVE_EXTRA_OSF_SYMBOLS
HAVE_PROT_CONNECT_0
sys_connect(s, name, namelen)
   HAVE_PROT_CONNECT_1 s;
   HAVE_PROT_CONNECT_2 name;
   HAVE_PROT_CONNECT_3 namelen;
{
   int rc;
   typedef HAVE_PROT_CONNECT_0 (*CONNECT_FUNC_T)(HAVE_PROT_CONNECT_1,
                                                 HAVE_PROT_CONNECT_2,
                                                 HAVE_PROT_CONNECT_3);
   CONNECT_FUNC_T function;

   SYSCALL_START(s);
   function = (CONNECT_FUNC_T)symbolfunction(SYMBOL_CONNECT);
   rc = function(s, name, namelen);
   SYSCALL_END(s);
   return rc;
}
#endif /* !HAVE_EXTRA_OSF_SYMBOLS */

#if !HAVE_EXTRA_OSF_SYMBOLS
HAVE_PROT_GETPEERNAME_0
sys_getpeername(s, name, namelen)
   HAVE_PROT_GETPEERNAME_1 s;
   HAVE_PROT_GETPEERNAME_2 name;
   HAVE_PROT_GETPEERNAME_3 namelen;
{
   int rc;
   typedef HAVE_PROT_GETPEERNAME_0
       (*GETPEERNAME_FUNC_T)(HAVE_PROT_GETPEERNAME_1,
                             HAVE_PROT_GETPEERNAME_2,
                             HAVE_PROT_GETPEERNAME_3);
   GETPEERNAME_FUNC_T function;

   SYSCALL_START(s);
   function = (GETPEERNAME_FUNC_T)symbolfunction(SYMBOL_GETPEERNAME);
   rc = function(s, name, namelen);
   SYSCALL_END(s);
   return rc;
}
#endif /* !HAVE_EXTRA_OSF_SYMBOLS */

#if !HAVE_EXTRA_OSF_SYMBOLS
HAVE_PROT_GETSOCKNAME_0
sys_getsockname(s, name, namelen)
   HAVE_PROT_GETSOCKNAME_1 s;
   HAVE_PROT_GETSOCKNAME_2 name;
   HAVE_PROT_GETSOCKNAME_3 namelen;
{
   int rc;
   typedef HAVE_PROT_GETSOCKNAME_0
       (*GETSOCKNAME_FUNC_T)(HAVE_PROT_GETSOCKNAME_1,
                             HAVE_PROT_GETSOCKNAME_2,
                             HAVE_PROT_GETSOCKNAME_3);
   GETSOCKNAME_FUNC_T function;

   SYSCALL_START(s);
   function = (GETSOCKNAME_FUNC_T)symbolfunction(SYMBOL_GETSOCKNAME);
   rc = function(s, name, namelen);
   SYSCALL_END(s);
   return rc;
}
#endif /* !HAVE_EXTRA_OSF_SYMBOLS */

HAVE_PROT_GETSOCKOPT_0
sys_getsockopt(s, level, optname, optval, optlen)
   HAVE_PROT_GETSOCKOPT_1 s;
   HAVE_PROT_GETSOCKOPT_2 level;
   HAVE_PROT_GETSOCKOPT_3 optname;
   HAVE_PROT_GETSOCKOPT_4 optval;
   HAVE_PROT_GETSOCKOPT_5 optlen;
{
   int rc;
   typedef HAVE_PROT_GETSOCKOPT_0
       (*GETSOCKOPT_FUNC_T)(HAVE_PROT_GETSOCKOPT_1,
                             HAVE_PROT_GETSOCKOPT_2,
                             HAVE_PROT_GETSOCKOPT_3,
                             HAVE_PROT_GETSOCKOPT_4,
                             HAVE_PROT_GETSOCKOPT_5);
   GETSOCKOPT_FUNC_T function;

   SYSCALL_START(s);
   function = (GETSOCKOPT_FUNC_T)symbolfunction(SYMBOL_GETSOCKOPT);
   rc = function(s, level, optname, optval, optlen);
   SYSCALL_END(s);
   return rc;
}

HAVE_PROT_LISTEN_0
sys_listen(s, backlog)
   HAVE_PROT_LISTEN_1 s;
   HAVE_PROT_LISTEN_2 backlog;
{
   ssize_t rc;
   typedef HAVE_PROT_LISTEN_0 (*LISTEN_FUNC_T)(HAVE_PROT_LISTEN_1,
                                           HAVE_PROT_LISTEN_2);
   LISTEN_FUNC_T function;

   SYSCALL_START(s);
   function = (LISTEN_FUNC_T)symbolfunction(SYMBOL_LISTEN);
   rc = function(s, backlog);
   SYSCALL_END(s);
   return rc;
}

HAVE_PROT_READ_0
sys_read(d, buf, nbytes)
   HAVE_PROT_READ_1 d;
   HAVE_PROT_READ_2 buf;
   HAVE_PROT_READ_3 nbytes;
{
   ssize_t rc;
   typedef HAVE_PROT_READ_0 (*READ_FUNC_T)(HAVE_PROT_READ_1,
                                           HAVE_PROT_READ_2,
                                           HAVE_PROT_READ_3);
   READ_FUNC_T function;

   SYSCALL_START(d);
   function = (READ_FUNC_T)symbolfunction(SYMBOL_READ);
   rc = function(d, buf, nbytes);
   SYSCALL_END(d);
   return rc;
}

#if !HAVE_EXTRA_OSF_SYMBOLS
HAVE_PROT_READV_0
sys_readv(d, iov, iovcnt)
   HAVE_PROT_READV_1 d;
   HAVE_PROT_READV_2 iov;
   HAVE_PROT_READV_3 iovcnt;
{
   ssize_t rc;
   typedef HAVE_PROT_READV_0 (*READV_FUNC_T)(HAVE_PROT_READV_1,
                                             HAVE_PROT_READV_2,
                                             HAVE_PROT_READV_3);
   READV_FUNC_T function;

   SYSCALL_START(d);
   function = (READV_FUNC_T)symbolfunction(SYMBOL_READV);
   rc = function(d, iov, iovcnt);
   SYSCALL_END(d);
   return rc;
}
#endif /* HAVE_EXTRA_OSF_SYMBOLS */

HAVE_PROT_RECV_0
sys_recv(s, buf, len, flags)
   HAVE_PROT_RECV_1 s;
   HAVE_PROT_RECV_2 buf;
   HAVE_PROT_RECV_3 len;
   HAVE_PROT_RECV_4 flags;
{
   ssize_t rc;
   typedef HAVE_PROT_RECV_0 (*RECV_FUNC_T)(HAVE_PROT_RECV_1,
                                           HAVE_PROT_RECV_2,
                                           HAVE_PROT_RECV_3,
                                           HAVE_PROT_RECV_4);
   RECV_FUNC_T function;

   SYSCALL_START(s);
   function = (RECV_FUNC_T)symbolfunction(SYMBOL_RECV);
   rc = function(s, buf, len, flags);
   SYSCALL_END(s);
   return rc;
}

#if !HAVE_EXTRA_OSF_SYMBOLS
HAVE_PROT_RECVFROM_0
sys_recvfrom(s, buf, len, flags, from, fromlen)
   HAVE_PROT_RECVFROM_1 s;
   HAVE_PROT_RECVFROM_2 buf;
   HAVE_PROT_RECVFROM_3 len;
   HAVE_PROT_RECVFROM_4 flags;
   HAVE_PROT_RECVFROM_5 from;
   HAVE_PROT_RECVFROM_6 fromlen;
{
   int rc;
   typedef HAVE_PROT_RECVFROM_0 (*RECVFROM_FUNC_T)(HAVE_PROT_RECVFROM_1,
                                                   HAVE_PROT_RECVFROM_2,
                                                   HAVE_PROT_RECVFROM_3,
                                                   HAVE_PROT_RECVFROM_4,
                                                   HAVE_PROT_RECVFROM_5,
                                                   HAVE_PROT_RECVFROM_6);
   RECVFROM_FUNC_T function;

   SYSCALL_START(s);
   function = (RECVFROM_FUNC_T)symbolfunction(SYMBOL_RECVFROM);
   rc = function(s, buf, len, flags, from, fromlen);
   SYSCALL_END(s);
   return rc;
}
#endif /* HAVE_EXTRA_OSF_SYMBOLS */

#if !HAVE_EXTRA_OSF_SYMBOLS
HAVE_PROT_RECVMSG_0
sys_recvmsg(s, msg, flags)
   HAVE_PROT_RECVMSG_1 s;
   HAVE_PROT_RECVMSG_2 msg;
   HAVE_PROT_RECVMSG_3 flags;
{
   ssize_t rc;
   typedef HAVE_PROT_RECVMSG_0 (*RECVMSG_FUNC_T)(HAVE_PROT_RECVMSG_1,
                                                 HAVE_PROT_RECVMSG_2,
                                                 HAVE_PROT_RECVMSG_3);
   RECVMSG_FUNC_T function;

   SYSCALL_START(s);
   function = (RECVMSG_FUNC_T)symbolfunction(SYMBOL_RECVMSG);
   rc = function(s, msg, flags);
   SYSCALL_END(s);
   return rc;
}
#endif /* HAVE_EXTRA_OSF_SYMBOLS */

int
sys_rresvport(port)
   int *port;
{
   typedef int (*RRESVPORT_FUNC_T)(int *);
   RRESVPORT_FUNC_T function;

   function = (RRESVPORT_FUNC_T)symbolfunction(SYMBOL_RRESVPORT);
   return function(port);
}

HAVE_PROT_SEND_0
sys_send(s, msg, len, flags)
   HAVE_PROT_SEND_1 s;
   HAVE_PROT_SEND_2 msg;
   HAVE_PROT_SEND_3 len;
   HAVE_PROT_SEND_4 flags;
{
   ssize_t rc;
   typedef HAVE_PROT_SEND_0 (*SEND_FUNC_T)(HAVE_PROT_SEND_1,
                                           HAVE_PROT_SEND_2,
                                           HAVE_PROT_SEND_3,
                                           HAVE_PROT_SEND_4);
   SEND_FUNC_T function;

   SYSCALL_START(s);
   function = (SEND_FUNC_T)symbolfunction(SYMBOL_SEND);
   rc = function(s, msg, len, flags);
   SYSCALL_END(s);
   return rc;
}

#if !HAVE_EXTRA_OSF_SYMBOLS
HAVE_PROT_SENDMSG_0
sys_sendmsg(s, msg, flags)
   HAVE_PROT_SENDMSG_1 s;
   HAVE_PROT_SENDMSG_2 msg;
   HAVE_PROT_SENDMSG_3 flags;
{
   ssize_t rc;
   typedef HAVE_PROT_SENDMSG_0 (*SENDMSG_FUNC_T)(HAVE_PROT_SENDMSG_1,
                                                 HAVE_PROT_SENDMSG_2,
                                                 HAVE_PROT_SENDMSG_3);
   SENDMSG_FUNC_T function;

   SYSCALL_START(s);
   function = (SENDMSG_FUNC_T)symbolfunction(SYMBOL_SENDMSG);
   rc = function(s, msg, flags);
   SYSCALL_END(s);
   return rc;
}
#endif /* HAVE_EXTRA_OSF_SYMBOLS */

#if !HAVE_EXTRA_OSF_SYMBOLS
HAVE_PROT_SENDTO_0
sys_sendto(s, msg, len, flags, to, tolen)
   HAVE_PROT_SENDTO_1 s;
   HAVE_PROT_SENDTO_2 msg;
   HAVE_PROT_SENDTO_3 len;
   HAVE_PROT_SENDTO_4 flags;
   HAVE_PROT_SENDTO_5 to;
   HAVE_PROT_SENDTO_6 tolen;
{
   ssize_t rc;
   typedef HAVE_PROT_SENDTO_0 (*SENDTO_FUNC_T)(HAVE_PROT_SENDTO_1,
                                               HAVE_PROT_SENDTO_2,
                                               HAVE_PROT_SENDTO_3,
                                               HAVE_PROT_SENDTO_4,
                                               HAVE_PROT_SENDTO_5,
                                               HAVE_PROT_SENDTO_6);
   SENDTO_FUNC_T function;

   SYSCALL_START(s);
   function = (SENDTO_FUNC_T)symbolfunction(SYMBOL_SENDTO);
   rc = function(s, msg, len, flags, to, tolen);
   SYSCALL_END(s);
   return rc;
}
#endif /* !HAVE_EXTRA_OSF_SYMBOLS */

HAVE_PROT_WRITE_0
sys_write(d, buf, nbytes)
   HAVE_PROT_WRITE_1 d;
   HAVE_PROT_WRITE_2 buf;
   HAVE_PROT_WRITE_3 nbytes;
{
   ssize_t rc;
   typedef HAVE_PROT_WRITE_0 (*WRITE_FUNC_T)(HAVE_PROT_WRITE_1,
                                             HAVE_PROT_WRITE_2,
                                             HAVE_PROT_WRITE_3);
   WRITE_FUNC_T function;

   SYSCALL_START(d);
   function = (WRITE_FUNC_T)symbolfunction(SYMBOL_WRITE);
   rc = function(d, buf, nbytes);
   SYSCALL_END(d);
   return rc;
}

#if DEBUG
/*
 * used for debugging, go direct to write(2), no SYSCALL_START() etc.
 */

HAVE_PROT_WRITE_0 syssys_write(HAVE_PROT_WRITE_1 d, HAVE_PROT_WRITE_2 buf,
                                HAVE_PROT_WRITE_3 nbytes);
HAVE_PROT_WRITE_0
syssys_write(d, buf, nbytes)
   HAVE_PROT_WRITE_1 d;
   HAVE_PROT_WRITE_2 buf;
   HAVE_PROT_WRITE_3 nbytes;
{
   typedef HAVE_PROT_WRITE_0 (*WRITE_FUNC_T)(HAVE_PROT_WRITE_1,
                                             HAVE_PROT_WRITE_2,
                                             HAVE_PROT_WRITE_3);
   WRITE_FUNC_T function;

   function = (WRITE_FUNC_T)symbolfunction(SYMBOL_WRITE);
   return function(d, buf, nbytes);
}
#endif /* DEBUG */

#if !HAVE_EXTRA_OSF_SYMBOLS
HAVE_PROT_WRITEV_0
sys_writev(d, iov, iovcnt)
   HAVE_PROT_WRITEV_1 d;
   HAVE_PROT_WRITEV_2 iov;
   HAVE_PROT_WRITEV_3 iovcnt;
{
   ssize_t rc;
   typedef HAVE_PROT_WRITEV_0 (*WRITEV_FUNC_T)(HAVE_PROT_WRITEV_1,
                                               HAVE_PROT_WRITEV_2,
                                               HAVE_PROT_WRITEV_3);
   WRITEV_FUNC_T function;

   SYSCALL_START(d);
   function = (WRITEV_FUNC_T)symbolfunction(SYMBOL_WRITEV);
   rc = function(d, iov, iovcnt);
   SYSCALL_END(d);
   return rc;
}
#endif /* HAVE_EXTRA_OSF_SYMBOLS */

#if HAVE_GSSAPI && HAVE_LINUX_GLIBC_WORKAROUND
HAVE_PROT_GETC_0
sys_getc(stream)
   HAVE_PROT_GETC_1 stream;
{
   const int d = fileno(stream);
   HAVE_PROT_GETC_0 rc;
   typedef HAVE_PROT_GETC_0 (*GETC_FUNC_T)(HAVE_PROT_GETC_1);
   GETC_FUNC_T function;

   SYSCALL_START(d);
   function = (GETC_FUNC_T)symbolfunction(SYMBOL_GETC);
   rc = function(stream);
   SYSCALL_END(d);
   return rc;
}

HAVE_PROT_FGETC_0
sys_fgetc(stream)
   HAVE_PROT_FGETC_1 stream;
{
   const int d = fileno(stream);
   HAVE_PROT_FGETC_0 rc;
   typedef HAVE_PROT_FGETC_0 (*FGETC_FUNC_T)(HAVE_PROT_FGETC_1);
   FGETC_FUNC_T function;

   SYSCALL_START(d);
   function = (FGETC_FUNC_T)symbolfunction(SYMBOL_FGETC);
   rc = function(stream);
   SYSCALL_END(d);

   return rc;
}

HAVE_PROT_GETS_0
sys_gets(buf)
   HAVE_PROT_GETS_1 buf;
{
   const int d = fileno(stdin);
   HAVE_PROT_GETS_0 rv;
   typedef HAVE_PROT_GETS_0(*GETS_FUNC_T)(HAVE_PROT_GETS_1);
   GETS_FUNC_T function;

   SYSCALL_START(d);
   function = (GETS_FUNC_T)symbolfunction(SYMBOL_GETS);
   rv = function(buf);
   SYSCALL_END(d);
   return rv;
}

HAVE_PROT_FGETS_0
sys_fgets(buf, size, stream)
   HAVE_PROT_FGETS_1 buf;
   HAVE_PROT_FGETS_2 size;
   HAVE_PROT_FGETS_3 stream;
{
   const int d = fileno(stream);
   HAVE_PROT_FGETS_0 rc;
   typedef HAVE_PROT_FGETS_0(*FGETS_FUNC_T)(HAVE_PROT_FGETS_1,
                                            HAVE_PROT_FGETS_2,
                                            HAVE_PROT_FGETS_3);
   FGETS_FUNC_T function;

   SYSCALL_START(d);
   function = (FGETS_FUNC_T)symbolfunction(SYMBOL_FGETS);
   rc = function(buf, size, stream);
   SYSCALL_END(d);
   return rc;
}

HAVE_PROT_PUTC_0
sys_putc(c, stream)
   HAVE_PROT_PUTC_1 c;
   HAVE_PROT_PUTC_2 stream;
{
   const int d = fileno(stream);
   HAVE_PROT_PUTC_0 rc;
   typedef HAVE_PROT_PUTC_0(*PUTC_FUNC_T)(HAVE_PROT_PUTC_1, HAVE_PROT_PUTC_2);
   PUTC_FUNC_T function;

   SYSCALL_START(d);
   function = (PUTC_FUNC_T)symbolfunction(SYMBOL_PUTC);
   rc = function(c, stream);
   SYSCALL_END(d);
   return rc;
}

HAVE_PROT_FPUTC_0
sys_fputc(c, stream)
   HAVE_PROT_FPUTC_1 c;
   HAVE_PROT_FPUTC_2 stream;
{
   const int d = fileno(stream);
   HAVE_PROT_FPUTC_0 rc;
   typedef HAVE_PROT_FPUTC_0 (*FPUTC_FUNC_T)(HAVE_PROT_FPUTC_1,
                                             HAVE_PROT_FPUTC_2);
   FPUTC_FUNC_T function;

   SYSCALL_START(d);
   function = (FPUTC_FUNC_T)symbolfunction(SYMBOL_FPUTC);
   rc = function(c, stream);
   SYSCALL_END(d);
   return rc;
}

HAVE_PROT_PUTS_0
sys_puts(buf)
   HAVE_PROT_PUTS_1 buf;
{
   const int d = fileno(stdout);
   HAVE_PROT_PUTS_0 rc;
   typedef HAVE_PROT_PUTS_0 (*PUTS_FUNC_T)(HAVE_PROT_PUTS_1);
   PUTS_FUNC_T function;

   SYSCALL_START(d);
   function = (PUTS_FUNC_T)symbolfunction(SYMBOL_PUTS);
   rc = function(buf);
   SYSCALL_END(d);
   return rc;
}

HAVE_PROT_FPUTS_0
sys_fputs(buf, stream)
   HAVE_PROT_FPUTS_1 buf;
   HAVE_PROT_FPUTS_2 stream;
{
   const int d = fileno(stream);
   HAVE_PROT_FPUTS_0 rc;
   typedef HAVE_PROT_FPUTS_0 (*FPUTS_FUNC_T)(HAVE_PROT_FPUTS_1,
                                             HAVE_PROT_FPUTS_2);
   FPUTS_FUNC_T function;

   SYSCALL_START(d);
   function = (FPUTS_FUNC_T)symbolfunction(SYMBOL_FPUTS);
   rc = function(buf, stream);
   SYSCALL_END(d);
   return rc;
}

HAVE_PROT_FFLUSH_0
sys_fflush(stream)
   HAVE_PROT_FFLUSH_1 stream;
{
   HAVE_PROT_FFLUSH_0 rc;
   typedef HAVE_PROT_FFLUSH_0 (*FFLUSH_FUNC_T)(HAVE_PROT_FFLUSH_1);
   FFLUSH_FUNC_T function;

   if (stream != NULL)
      SYSCALL_START(fileno(stream));

   function = (FFLUSH_FUNC_T)symbolfunction(SYMBOL_FFLUSH);
   rc = function(stream);

   if (stream != NULL)
      SYSCALL_END(fileno(stream));

   return rc;
}

HAVE_PROT_FCLOSE_0
sys_fclose(stream)
   HAVE_PROT_FCLOSE_1 stream;
{
   const int d = fileno(stream);
   HAVE_PROT_FCLOSE_0 rc;
   typedef HAVE_PROT_FCLOSE_0 (*FCLOSE_FUNC_T)(HAVE_PROT_FCLOSE_1);
   FCLOSE_FUNC_T function;

   SYSCALL_START(d);
   function = (FCLOSE_FUNC_T)symbolfunction(SYMBOL_FCLOSE);
   rc = function(stream);
   SYSCALL_END(d);
   return rc;
}

HAVE_PROT_PRINTF_0
sys_printf(HAVE_PROT_PRINTF_1 format, ...)
{
   va_list ap;
   HAVE_PROT_FPRINTF_0 rc;

   va_start(ap, format);
   rc = sys_vprintf(format, ap);
   va_end(ap);
   return rc;
}

HAVE_PROT_VPRINTF_0
sys_vprintf(format, ap)
   HAVE_PROT_VPRINTF_1 format;
   HAVE_PROT_VPRINTF_2 ap;
{
   const int d = fileno(stdout);
   HAVE_PROT_VFPRINTF_0 rc;
   typedef HAVE_PROT_VPRINTF_0 (*VPRINTF_FUNC_T)(HAVE_PROT_VPRINTF_1,
                                                 HAVE_PROT_VPRINTF_2);
   VPRINTF_FUNC_T function;

   SYSCALL_START(d);
   function = (VPRINTF_FUNC_T)symbolfunction(SYMBOL_VPRINTF);
   rc = function(format, ap);
   SYSCALL_END(d);

   return rc;
}

HAVE_PROT_FPRINTF_0
sys_fprintf(HAVE_PROT_FPRINTF_1 stream, HAVE_PROT_FPRINTF_2 format, ...)
{
   va_list ap;
   HAVE_PROT_FPRINTF_0 rc;

   va_start(ap, format);
   rc = sys_vfprintf(stream, format, ap);
   va_end(ap);
   return rc;
}

HAVE_PROT_VFPRINTF_0
sys_vfprintf(stream, format, ap)
   HAVE_PROT_VFPRINTF_1 stream;
   HAVE_PROT_VFPRINTF_2 format;
   HAVE_PROT_VFPRINTF_3 ap;
{
   HAVE_PROT_VFPRINTF_0 rc;
   int d = fileno(stream);
   typedef HAVE_PROT_VFPRINTF_0 (*VFPRINTF_FUNC_T)(HAVE_PROT_VFPRINTF_1,
                                                   HAVE_PROT_VFPRINTF_2,
                                                   HAVE_PROT_VFPRINTF_3);
   VFPRINTF_FUNC_T function;

   SYSCALL_START(d);
   function = (VFPRINTF_FUNC_T)symbolfunction(SYMBOL_VFPRINTF);
   rc = function(stream, format, ap);
   SYSCALL_END(d);
   return rc;
}

HAVE_PROT_FWRITE_0
sys_fwrite(ptr, size, nmb, stream)
   HAVE_PROT_FWRITE_1 ptr;
   HAVE_PROT_FWRITE_2 size;
   HAVE_PROT_FWRITE_3 nmb;
   HAVE_PROT_FWRITE_4 stream;
{
   const int d = fileno(stream);
   HAVE_PROT_FWRITE_0 rc;
   typedef HAVE_PROT_FWRITE_0 (*FWRITE_FUNC_T)(HAVE_PROT_FWRITE_1,
                                               HAVE_PROT_FWRITE_2,
                                               HAVE_PROT_FWRITE_3,
                                               HAVE_PROT_FWRITE_4);
   FWRITE_FUNC_T function;

   SYSCALL_START(d);
   function = (FWRITE_FUNC_T)symbolfunction(SYMBOL_FWRITE);
   rc = function(ptr, size, nmb, stream);
   SYSCALL_END(d);
   return rc;
}

HAVE_PROT_FREAD_0
sys_fread(ptr, size, nmb, stream)
   HAVE_PROT_FREAD_1 ptr;
   HAVE_PROT_FREAD_2 size;
   HAVE_PROT_FREAD_3 nmb;
   HAVE_PROT_FREAD_4 stream;
{
   const int d = fileno(stream);
   HAVE_PROT_FREAD_0 rc;
   typedef HAVE_PROT_FREAD_0 (*FREAD_FUNC_T)(HAVE_PROT_FREAD_1,
                                             HAVE_PROT_FREAD_2,
                                             HAVE_PROT_FREAD_3,
                                             HAVE_PROT_FREAD_4);
   FREAD_FUNC_T function;

   SYSCALL_START(d);
   function = (FREAD_FUNC_T)symbolfunction(SYMBOL_FREAD);
   rc = function(ptr, size, nmb, stream);
   SYSCALL_END(d);

   return rc;
}
#endif /* HAVE_GSSAPI && HAVE_LINUX_GLIBC_WORKAROUND */

   /*
    * the interpositioned functions.
    */

#if !HAVE_EXTRA_OSF_SYMBOLS
HAVE_PROT_ACCEPT_0
accept(s, addr, addrlen)
   HAVE_PROT_ACCEPT_1 s;
   HAVE_PROT_ACCEPT_2 addr;
   HAVE_PROT_ACCEPT_3 addrlen;
{
   if (ISSYSCALL(s, SYMBOL_ACCEPT))
      return sys_accept(s, addr, addrlen);
   return Raccept(s, addr, (socklen_t *)addrlen);
}
#endif /* HAVE_EXTRA_OSF_SYMBOLS */

#if !HAVE_EXTRA_OSF_SYMBOLS
HAVE_PROT_BIND_0
bind(s, name, namelen)
   HAVE_PROT_BIND_1 s;
   HAVE_PROT_BIND_2 name;
   HAVE_PROT_BIND_3 namelen;
{
   if (ISSYSCALL(s, SYMBOL_BIND))
      return sys_bind(s, name, namelen);
   return Rbind(s, name, namelen);
}
#endif /* !HAVE_EXTRA_OSF_SYMBOLS */

int
bindresvport(sd, sin)
   int sd;
   struct sockaddr_in *sin;
{
   if (ISSYSCALL(sd, SYMBOL_BINDRESVPORT))
      return sys_bindresvport(sd, sin);
   return Rbindresvport(sd, sin);
}

#if !HAVE_EXTRA_OSF_SYMBOLS
HAVE_PROT_CONNECT_0
connect(s, name, namelen)
   HAVE_PROT_CONNECT_1 s;
   HAVE_PROT_CONNECT_2 name;
   HAVE_PROT_CONNECT_3 namelen;
{
   if (ISSYSCALL(s, SYMBOL_CONNECT))
      return sys_connect(s, name, namelen);
   return Rconnect(s, name, namelen);
}
#endif /* HAVE_EXTRA_OSF_SYMBOLS */

#if !HAVE_EXTRA_OSF_SYMBOLS
HAVE_PROT_GETPEERNAME_0
getpeername(s, name, namelen)
   HAVE_PROT_GETPEERNAME_1 s;
   HAVE_PROT_GETPEERNAME_2 name;
   HAVE_PROT_GETPEERNAME_3 namelen;
{
   if (ISSYSCALL(s, SYMBOL_GETPEERNAME))
      return sys_getpeername(s, name, namelen);
   return Rgetpeername(s, name, namelen);
}
#endif /* HAVE_EXTRA_OSF_SYMBOLS */

#if !HAVE_EXTRA_OSF_SYMBOLS
HAVE_PROT_GETSOCKNAME_0
getsockname(s, name, namelen)
   HAVE_PROT_GETSOCKNAME_1 s;
   HAVE_PROT_GETSOCKNAME_2 name;
   HAVE_PROT_GETSOCKNAME_3 namelen;
{
   if (ISSYSCALL(s, SYMBOL_GETSOCKNAME))
      return sys_getsockname(s, name, namelen);
   return Rgetsockname(s, name, namelen);
}
#endif /* HAVE_EXTRA_OSF_SYMBOLS */

HAVE_PROT_GETSOCKOPT_0
getsockopt(s, level, optname, optval, optlen)
   HAVE_PROT_GETSOCKOPT_1 s;
   HAVE_PROT_GETSOCKOPT_2 level;
   HAVE_PROT_GETSOCKOPT_3 optname;
   HAVE_PROT_GETSOCKOPT_4 optval;
   HAVE_PROT_GETSOCKOPT_5 optlen;
{
   if (ISSYSCALL(s, SYMBOL_GETSOCKNAME))
      return sys_getsockopt(s, level, optname, optval, optlen);
   return Rgetsockopt(s, level, optname, optval, optlen);
}

HAVE_PROT_LISTEN_0
listen(s, backlog)
   HAVE_PROT_LISTEN_1 s;
   HAVE_PROT_LISTEN_2 backlog;
{
   if (ISSYSCALL(s, SYMBOL_LISTEN))
      return sys_listen(s, backlog);
   return Rlisten(s, backlog);
}

HAVE_PROT_READ_0
read(d, buf, nbytes)
   HAVE_PROT_READ_1 d;
   HAVE_PROT_READ_2 buf;
   HAVE_PROT_READ_3 nbytes;
{
   if (ISSYSCALL(d, SYMBOL_READ))
      return sys_read(d, buf, nbytes);
   return Rread(d, buf, nbytes);
}

#if !HAVE_EXTRA_OSF_SYMBOLS
HAVE_PROT_READV_0
readv(d, iov, iovcnt)
   HAVE_PROT_READV_1 d;
   HAVE_PROT_READV_2 iov;
   HAVE_PROT_READV_3 iovcnt;
{
   if (ISSYSCALL(d, SYMBOL_READV))
      return sys_readv(d, iov, iovcnt);
   return Rreadv(d, iov, iovcnt);
}
#endif /* HAVE_EXTRA_OSF_SYMBOLS */

HAVE_PROT_RECV_0
recv(s, msg, len, flags)
   HAVE_PROT_RECV_1 s;
   HAVE_PROT_RECV_2 msg;
   HAVE_PROT_RECV_3 len;
   HAVE_PROT_RECV_4 flags;
{
   if (ISSYSCALL(s, SYMBOL_RECV))
      return sys_recv(s, msg, len, flags);
   return Rrecv(s, msg, len, flags);
}

#if !HAVE_EXTRA_OSF_SYMBOLS
HAVE_PROT_RECVFROM_0
recvfrom(s, buf, len, flags, from, fromlen)
   HAVE_PROT_RECVFROM_1 s;
   HAVE_PROT_RECVFROM_2 buf;
   HAVE_PROT_RECVFROM_3 len;
   HAVE_PROT_RECVFROM_4 flags;
   HAVE_PROT_RECVFROM_5 from;
   HAVE_PROT_RECVFROM_6 fromlen;
{
   if (ISSYSCALL(s, SYMBOL_RECVFROM))
      return sys_recvfrom(s, buf, len, flags, from, fromlen);
   return Rrecvfrom(s, buf, len, flags, from, fromlen);
}
#endif /* HAVE_EXTRA_OSF_SYMBOLS */

#if !HAVE_EXTRA_OSF_SYMBOLS
HAVE_PROT_RECVMSG_0
recvmsg(s, msg, flags)
   HAVE_PROT_RECVMSG_1 s;
   HAVE_PROT_RECVMSG_2 msg;
   HAVE_PROT_RECVMSG_3 flags;
{
   if (ISSYSCALL(s, SYMBOL_RECVMSG))
      return sys_recvmsg(s, msg, flags);
   return Rrecvmsg(s, msg, flags);
}
#endif /* HAVE_EXTRA_OSF_SYMBOLS */

int
rresvport(port)
   int *port;
{
   return Rrresvport(port);
}

HAVE_PROT_WRITE_0
write(d, buf, nbytes)
   HAVE_PROT_WRITE_1 d;
   HAVE_PROT_WRITE_2 buf;
   HAVE_PROT_WRITE_3 nbytes;
{
   if (ISSYSCALL(d, SYMBOL_WRITE))
      return sys_write(d, buf, nbytes);
   return Rwrite(d, buf, nbytes);
}

#if !HAVE_EXTRA_OSF_SYMBOLS
HAVE_PROT_WRITEV_0
writev(d, iov, iovcnt)
   HAVE_PROT_WRITEV_1 d;
   HAVE_PROT_WRITEV_2 iov;
   HAVE_PROT_WRITEV_3 iovcnt;
{
   if (ISSYSCALL(d, SYMBOL_WRITEV))
      return sys_writev(d, iov, iovcnt);
   return Rwritev(d, iov, iovcnt);
}
#endif /* HAVE_EXTRA_OSF_SYMBOLS */

HAVE_PROT_SEND_0
send(s, msg, len, flags)
   HAVE_PROT_SEND_1 s;
   HAVE_PROT_SEND_2 msg;
   HAVE_PROT_SEND_3 len;
   HAVE_PROT_SEND_4 flags;
{
   if (ISSYSCALL(s, SYMBOL_SEND))
      return sys_send(s, msg, len, flags);
   return Rsend(s, msg, len, flags);
}

#if !HAVE_EXTRA_OSF_SYMBOLS
HAVE_PROT_SENDMSG_0
sendmsg(s, msg, flags)
   HAVE_PROT_SENDMSG_1 s;
   HAVE_PROT_SENDMSG_2 msg;
   HAVE_PROT_SENDMSG_3 flags;
{
   if (ISSYSCALL(s, SYMBOL_SENDMSG))
      return sys_sendmsg(s, msg, flags);
   return Rsendmsg(s, msg, flags);
}
#endif /* HAVE_EXTRA_OSF_SYMBOLS */

#if !HAVE_EXTRA_OSF_SYMBOLS
HAVE_PROT_SENDTO_0
sendto(s, msg, len, flags, to, tolen)
   HAVE_PROT_SENDTO_1 s;
   HAVE_PROT_SENDTO_2 msg;
   HAVE_PROT_SENDTO_3 len;
   HAVE_PROT_SENDTO_4 flags;
   HAVE_PROT_SENDTO_5 to;
   HAVE_PROT_SENDTO_6 tolen;
{
   if (ISSYSCALL(s, SYMBOL_SENDTO))
      return sys_sendto(s, msg, len, flags, to, tolen);
   return Rsendto(s, msg, len, flags, to, tolen);
}
#endif /* !HAVE_EXTRA_OSF_SYMBOLS */

#ifdef __sun
/* __xnet_foo variants of some functions exist on Solaris if _XPG4_2 is set */

HAVE_PROT_BIND_0
sys_xnet_bind(s, name, namelen)
   HAVE_PROT_BIND_1 s;
   HAVE_PROT_BIND_2 name;
   HAVE_PROT_BIND_3 namelen;
{
   int rc;
   typedef HAVE_PROT_BIND_0 (*BIND_FUNC_T)(HAVE_PROT_BIND_1,
                                           HAVE_PROT_BIND_2,
                                           HAVE_PROT_BIND_3);
   BIND_FUNC_T function;

   SYSCALL_START(s);
   function = (BIND_FUNC_T)symbolfunction(SYMBOL_XNET_BIND);
   rc = function(s, name, namelen);
   SYSCALL_END(s);
   return rc;
}

HAVE_PROT_BIND_0
__xnet_bind(s, name, namelen)
   HAVE_PROT_BIND_1 s;
   HAVE_PROT_BIND_2 name;
   HAVE_PROT_BIND_3 namelen;
{
   if (ISSYSCALL(s, SYMBOL_XNET_BIND))
      return sys_xnet_bind(s, name, namelen);
   return Rbind(s, name, namelen);
}

HAVE_PROT_CONNECT_0
sys_xnet_connect(s, name, namelen)
   HAVE_PROT_CONNECT_1 s;
   HAVE_PROT_CONNECT_2 name;
   HAVE_PROT_CONNECT_3 namelen;
{
   int rc;
   typedef HAVE_PROT_CONNECT_0 (*CONNECT_FUNC_T)(HAVE_PROT_CONNECT_1,
                                                 HAVE_PROT_CONNECT_2,
                                                 HAVE_PROT_CONNECT_3);
   CONNECT_FUNC_T function;

   SYSCALL_START(s);
   function = (CONNECT_FUNC_T)symbolfunction(SYMBOL_XNET_CONNECT);
   rc = function(s, name, namelen);
   SYSCALL_END(s);
   return rc;
}

HAVE_PROT_CONNECT_0
__xnet_connect(s, name, namelen)
   HAVE_PROT_CONNECT_1 s;
   HAVE_PROT_CONNECT_2 name;
   HAVE_PROT_CONNECT_3 namelen;
{
   if (ISSYSCALL(s, SYMBOL_XNET_CONNECT))
      return sys_xnet_connect(s, name, namelen);
   return Rconnect(s, name, namelen);
}

HAVE_PROT_LISTEN_0
sys_xnet_listen(s, backlog)
   HAVE_PROT_LISTEN_1 s;
   HAVE_PROT_LISTEN_2 backlog;
{
   ssize_t rc;
   typedef HAVE_PROT_LISTEN_0 (*LISTEN_FUNC_T)(HAVE_PROT_LISTEN_1,
                                           HAVE_PROT_LISTEN_2);
   LISTEN_FUNC_T function;

   SYSCALL_START(s);
   function = (LISTEN_FUNC_T)symbolfunction(SYMBOL_XNET_LISTEN);
   rc = function(s, backlog);
   SYSCALL_END(s);
   return rc;
}

HAVE_PROT_LISTEN_0
__xnet_listen(s, backlog)
   HAVE_PROT_LISTEN_1 s;
   HAVE_PROT_LISTEN_2 backlog;
{
   if (ISSYSCALL(s, SYMBOL_XNET_LISTEN))
      return sys_xnet_listen(s, backlog);
   return Rlisten(s, backlog);
}

HAVE_PROT_RECVMSG_0
sys_xnet_recvmsg(s, msg, flags)
   HAVE_PROT_RECVMSG_1 s;
   HAVE_PROT_RECVMSG_2 msg;
   HAVE_PROT_RECVMSG_3 flags;
{
   ssize_t rc;
   typedef HAVE_PROT_RECVMSG_0 (*RECVMSG_FUNC_T)(HAVE_PROT_RECVMSG_1,
                                                 HAVE_PROT_RECVMSG_2,
                                                 HAVE_PROT_RECVMSG_3);
   RECVMSG_FUNC_T function;

   SYSCALL_START(s);
   function = (RECVMSG_FUNC_T)symbolfunction(SYMBOL_XNET_RECVMSG);
   rc = function(s, msg, flags);
   SYSCALL_END(s);
   return rc;
}

HAVE_PROT_RECVMSG_0
__xnet_recvmsg(s, msg, flags)
   HAVE_PROT_RECVMSG_1 s;
   HAVE_PROT_RECVMSG_2 msg;
   HAVE_PROT_RECVMSG_3 flags;
{
   if (ISSYSCALL(s, SYMBOL_XNET_RECVMSG))
      return sys_xnet_recvmsg(s, msg, flags);
   return Rrecvmsg(s, msg, flags);
}

HAVE_PROT_SENDMSG_0
sys_xnet_sendmsg(s, msg, flags)
   HAVE_PROT_SENDMSG_1 s;
   HAVE_PROT_SENDMSG_2 msg;
   HAVE_PROT_SENDMSG_3 flags;
{
   ssize_t rc;
   typedef HAVE_PROT_SENDMSG_0 (*SENDMSG_FUNC_T)(HAVE_PROT_SENDMSG_1,
                                                 HAVE_PROT_SENDMSG_2,
                                                 HAVE_PROT_SENDMSG_3);
   SENDMSG_FUNC_T function;

   SYSCALL_START(s);
   function = (SENDMSG_FUNC_T)symbolfunction(SYMBOL_XNET_SENDMSG);
   rc = function(s, msg, flags);
   SYSCALL_END(s);
   return rc;
}

HAVE_PROT_SENDMSG_0
__xnet_sendmsg(s, msg, flags)
   HAVE_PROT_SENDMSG_1 s;
   HAVE_PROT_SENDMSG_2 msg;
   HAVE_PROT_SENDMSG_3 flags;
{
   if (ISSYSCALL(s, SYMBOL_XNET_SENDMSG))
      return sys_xnet_sendmsg(s, msg, flags);
   return Rsendmsg(s, msg, flags);
}

HAVE_PROT_SENDTO_0
sys_xnet_sendto(s, msg, len, flags, to, tolen)
   HAVE_PROT_SENDTO_1 s;
   HAVE_PROT_SENDTO_2 msg;
   HAVE_PROT_SENDTO_3 len;
   HAVE_PROT_SENDTO_4 flags;
   HAVE_PROT_SENDTO_5 to;
   HAVE_PROT_SENDTO_6 tolen;
{
   ssize_t rc;
   typedef HAVE_PROT_SENDTO_0 (*SENDTO_FUNC_T)(HAVE_PROT_SENDTO_1,
                                               HAVE_PROT_SENDTO_2,
                                               HAVE_PROT_SENDTO_3,
                                               HAVE_PROT_SENDTO_4,
                                               HAVE_PROT_SENDTO_5,
                                               HAVE_PROT_SENDTO_6);
   SENDTO_FUNC_T function;

   SYSCALL_START(s);
   function = (SENDTO_FUNC_T)symbolfunction(SYMBOL_XNET_SENDTO);
   rc = function(s, msg, len, flags, to, tolen);
   SYSCALL_END(s);
   return rc;
}

HAVE_PROT_SENDTO_0
__xnet_sendto(s, msg, len, flags, to, tolen)
   HAVE_PROT_SENDTO_1 s;
   HAVE_PROT_SENDTO_2 msg;
   HAVE_PROT_SENDTO_3 len;
   HAVE_PROT_SENDTO_4 flags;
   HAVE_PROT_SENDTO_5 to;
   HAVE_PROT_SENDTO_6 tolen;
{
   if (ISSYSCALL(s, SYMBOL_XNET_SENDTO))
      return sys_xnet_sendto(s, msg, len, flags, to, tolen);
   return Rsendto(s, msg, len, flags, to, tolen);
}

#endif /* __sun */

#ifdef __FreeBSD__
HAVE_PROT_ACCEPT_0
_accept(s, addr, addrlen)
   HAVE_PROT_ACCEPT_1 s;
   HAVE_PROT_ACCEPT_2 addr;
   HAVE_PROT_ACCEPT_3 addrlen;
{
   if (ISSYSCALL(s, SYMBOL_ACCEPT))
      return sys_accept(s, addr, addrlen);
   return Raccept(s, addr, (socklen_t *)addrlen);
}

HAVE_PROT_BIND_0
_bind(s, name, namelen)
   HAVE_PROT_BIND_1 s;
   HAVE_PROT_BIND_2 name;
   HAVE_PROT_BIND_3 namelen;
{
   if (ISSYSCALL(s, SYMBOL_BIND))
      return sys_bind(s, name, namelen);
   return Rbind(s, name, namelen);
}

HAVE_PROT_CONNECT_0
_connect(s, name, namelen)
   HAVE_PROT_CONNECT_1 s;
   HAVE_PROT_CONNECT_2 name;
   HAVE_PROT_CONNECT_3 namelen;
{
   if (ISSYSCALL(s, SYMBOL_CONNECT))
      return sys_connect(s, name, namelen);
   return Rconnect(s, name, namelen);
}

HAVE_PROT_GETPEERNAME_0
_getpeername(s, name, namelen)
   HAVE_PROT_GETPEERNAME_1 s;
   HAVE_PROT_GETPEERNAME_2 name;
   HAVE_PROT_GETPEERNAME_3 namelen;
{
   if (ISSYSCALL(s, SYMBOL_GETPEERNAME))
      return sys_getpeername(s, name, namelen);
   return Rgetpeername(s, name, namelen);
}

HAVE_PROT_GETSOCKNAME_0
_getsockname(s, name, namelen)
   HAVE_PROT_GETSOCKNAME_1 s;
   HAVE_PROT_GETSOCKNAME_2 name;
   HAVE_PROT_GETSOCKNAME_3 namelen;
{
   if (ISSYSCALL(s, SYMBOL_GETSOCKNAME))
      return sys_getsockname(s, name, namelen);
   return Rgetsockname(s, name, namelen);
}

HAVE_PROT_LISTEN_0
_listen(s, backlog)
   HAVE_PROT_LISTEN_1 s;
   HAVE_PROT_LISTEN_2 backlog;
{
   if (ISSYSCALL(s, SYMBOL_LISTEN))
      return sys_listen(s, backlog);
   return Rlisten(s, backlog);
}

HAVE_PROT_READ_0
_read(d, buf, nbytes)
   HAVE_PROT_READ_1 d;
   HAVE_PROT_READ_2 buf;
   HAVE_PROT_READ_3 nbytes;
{
   if (ISSYSCALL(d, SYMBOL_READ))
      return sys_read(d, buf, nbytes);
   return Rread(d, buf, nbytes);
}

HAVE_PROT_READV_0
_readv(d, iov, iovcnt)
   HAVE_PROT_READV_1 d;
   HAVE_PROT_READV_2 iov;
   HAVE_PROT_READV_3 iovcnt;
{
   if (ISSYSCALL(d, SYMBOL_READV))
      return sys_readv(d, iov, iovcnt);
   return Rreadv(d, iov, iovcnt);
}

HAVE_PROT_RECV_0
_recv(s, msg, len, flags)
   HAVE_PROT_RECV_1 s;
   HAVE_PROT_RECV_2 msg;
   HAVE_PROT_RECV_3 len;
   HAVE_PROT_RECV_4 flags;
{
   if (ISSYSCALL(s, SYMBOL_RECV))
      return sys_recv(s, msg, len, flags);
   return Rrecv(s, msg, len, flags);
}

HAVE_PROT_RECVFROM_0
_recvfrom(s, buf, len, flags, from, fromlen)
   HAVE_PROT_RECVFROM_1 s;
   HAVE_PROT_RECVFROM_2 buf;
   HAVE_PROT_RECVFROM_3 len;
   HAVE_PROT_RECVFROM_4 flags;
   HAVE_PROT_RECVFROM_5 from;
   HAVE_PROT_RECVFROM_6 fromlen;
{
   if (ISSYSCALL(s, SYMBOL_RECVFROM))
      return sys_recvfrom(s, buf, len, flags, from, fromlen);
   return Rrecvfrom(s, buf, len, flags, from, fromlen);
}

HAVE_PROT_RECVMSG_0
_recvmsg(s, msg, flags)
   HAVE_PROT_RECVMSG_1 s;
   HAVE_PROT_RECVMSG_2 msg;
   HAVE_PROT_RECVMSG_3 flags;
{
   if (ISSYSCALL(s, SYMBOL_RECVMSG))
      return sys_recvmsg(s, msg, flags);
   return Rrecvmsg(s, msg, flags);
}

HAVE_PROT_WRITE_0
_write(d, buf, nbytes)
   HAVE_PROT_WRITE_1 d;
   HAVE_PROT_WRITE_2 buf;
   HAVE_PROT_WRITE_3 nbytes;
{
   if (ISSYSCALL(d, SYMBOL_WRITE))
      return sys_write(d, buf, nbytes);
   return Rwrite(d, buf, nbytes);
}

HAVE_PROT_WRITEV_0
_writev(d, iov, iovcnt)
   HAVE_PROT_WRITEV_1 d;
   HAVE_PROT_WRITEV_2 iov;
   HAVE_PROT_WRITEV_3 iovcnt;
{
   if (ISSYSCALL(d, SYMBOL_WRITEV))
      return sys_writev(d, iov, iovcnt);
   return Rwritev(d, iov, iovcnt);
}

HAVE_PROT_SEND_0
_send(s, msg, len, flags)
   HAVE_PROT_SEND_1 s;
   HAVE_PROT_SEND_2 msg;
   HAVE_PROT_SEND_3 len;
   HAVE_PROT_SEND_4 flags;
{
   if (ISSYSCALL(s, SYMBOL_SEND))
      return sys_send(s, msg, len, flags);
   return Rsend(s, msg, len, flags);
}

HAVE_PROT_SENDMSG_0
_sendmsg(s, msg, flags)
   HAVE_PROT_SENDMSG_1 s;
   HAVE_PROT_SENDMSG_2 msg;
   HAVE_PROT_SENDMSG_3 flags;
{
   if (ISSYSCALL(s, SYMBOL_SENDMSG))
      return sys_sendmsg(s, msg, flags);
   return Rsendmsg(s, msg, flags);
}

HAVE_PROT_SENDTO_0
_sendto(s, msg, len, flags, to, tolen)
   HAVE_PROT_SENDTO_1 s;
   HAVE_PROT_SENDTO_2 msg;
   HAVE_PROT_SENDTO_3 len;
   HAVE_PROT_SENDTO_4 flags;
   HAVE_PROT_SENDTO_5 to;
   HAVE_PROT_SENDTO_6 tolen;
{
   if (ISSYSCALL(s, SYMBOL_SENDTO))
      return sys_sendto(s, msg, len, flags, to, tolen);
   return Rsendto(s, msg, len, flags, to, tolen);
}
#endif /* __FreeBSD__ */

#endif /* SOCKS_CLIENT */

#if SOCKS_SERVER

struct hostent *
sys_gethostbyaddr(addr, len, af)
   const char *addr;
   socklen_t len;
   int af;
{
   typedef struct hostent *(*GETHOSTBYADDR_FUNC_T)(const char *, int, int);
   GETHOSTBYADDR_FUNC_T function;

   function = (GETHOSTBYADDR_FUNC_T)symbolfunction(SYMBOL_GETHOSTBYADDR);
   return function(addr, len, af);
}

HAVE_PROT_GETHOSTBYADDR_0
gethostbyaddr(addr, len, af)
   HAVE_PROT_GETHOSTBYADDR_1 addr;
   HAVE_PROT_GETHOSTBYADDR_2 len;
   HAVE_PROT_GETHOSTBYADDR_3 af;
{

   if (socks_shouldcallasnative(SYMBOL_GETHOSTBYADDR))
      return sys_gethostbyaddr(addr, len, af);
   return cgethostbyaddr(addr, len, af);
}

#endif /* SOCKS_SERVER */

struct hostent *
sys_gethostbyname(name)
   const char *name;
{
   typedef struct hostent *(*GETHOSTBYNAME_FUNC_T)(const char *);
   GETHOSTBYNAME_FUNC_T function;

   function = (GETHOSTBYNAME_FUNC_T)symbolfunction(SYMBOL_GETHOSTBYNAME);
   return function(name);
}

struct hostent *
gethostbyname(name)
   const char *name;
{
#if SOCKS_SERVER
   return cgethostbyname(name);
#else
   if (socks_shouldcallasnative(SYMBOL_GETHOSTBYNAME))
      return sys_gethostbyname(name);
   return Rgethostbyname(name);
#endif /* SOCKS_SERVER */
}

#if SOCKS_CLIENT

struct hostent *
sys_gethostbyname2(name, af)
   const char *name;
   int af;
{
   typedef struct hostent *(*GETHOSTBYNAME2_FUNC_T)(const char *, int);
   GETHOSTBYNAME2_FUNC_T function;

   function = (GETHOSTBYNAME2_FUNC_T)symbolfunction(SYMBOL_GETHOSTBYNAME2);
   return function(name, af);
}

struct hostent *
gethostbyname2(name, af)
   const char *name;
   int af;
{
   if (socks_shouldcallasnative(SYMBOL_GETHOSTBYNAME2))
      return sys_gethostbyname2(name, af);
   return Rgethostbyname2(name, af);
}

#if HAVE_GETADDRINFO

int
sys_getaddrinfo(nodename, servname, hints, res)
   const char *nodename;
   const char *servname;
   const struct addrinfo *hints;
   struct addrinfo **res;
{
   typedef int (*GETADDRINFO_FUNC_T)(const char *, const char *,
                 const struct addrinfo *,
                 struct addrinfo **);
   GETADDRINFO_FUNC_T function;

   function = (GETADDRINFO_FUNC_T)symbolfunction(SYMBOL_GETADDRINFO);
   return function(nodename, servname, hints, res);
}

int
getaddrinfo(nodename, servname, hints, res)
   const char *nodename;
   const char *servname;
   const struct addrinfo *hints;
   struct addrinfo **res;
{
   if (socks_shouldcallasnative(SYMBOL_GETADDRINFO))
      return sys_getaddrinfo(nodename, servname, hints, res);
   return Rgetaddrinfo(nodename, servname, hints, res);
}

#endif /* HAVE_GETADDRINFO */

#if HAVE_GETIPNODEBYNAME

struct hostent *
sys_getipnodebyname(name, af, flags, error_num)
   const char *name;
   int af;
   int flags;
   int *error_num;
{
   typedef struct hostent *(*GETIPNODEBYNAME_FUNC_T)(const char *, int, int,
                                                     int *);
   GETIPNODEBYNAME_FUNC_T function;

   function = (GETIPNODEBYNAME_FUNC_T)symbolfunction(SYMBOL_GETIPNODEBYNAME);
   return function(name, af, flags, error_num);
}

struct hostent *
getipnodebyname(name, af, flags, error_num)
   const char *name;
   int af;
   int flags;
   int *error_num;
{

   if (socks_shouldcallasnative(SYMBOL_GETIPNODEBYNAME))
      return sys_getipnodebyname(name, af, flags, error_num);
   return Rgetipnodebyname(name, af, flags, error_num);
}

void
sys_freehostent(ptr)
        struct hostent *ptr;
{
        typedef struct hostent *(*FREEHOSTENT_FUNC_T)(struct hostent *);

   FREEHOSTENT_FUNC_T function;

   function = (FREEHOSTENT_FUNC_T)symbolfunction(SYMBOL_FREEHOSTENT);
   function(ptr);
}

void
freehostent(ptr)
        struct hostent *ptr;
{

   if (socks_shouldcallasnative(SYMBOL_FREEHOSTENT))
      sys_freehostent(ptr);
   else
      Rfreehostent(ptr);
}

#endif /* HAVE_GETIPNODEBYNAME */

#if HAVE_GSSAPI && HAVE_LINUX_GLIBC_WORKAROUND
HAVE_PROT_GETC_0
#ifdef getc
#undef getc
#endif /* getc */
getc(stream)
   HAVE_PROT_GETC_1 stream;
{
   const int d = fileno(stream);

   if (!sockscf.state.havegssapisockets || ISSYSCALL(d, SYMBOL_GETC))
      return sys_getc(stream);
   return Rfgetc(stream);
}

#if HAVE__IO_GETC
HAVE_PROT__IO_GETC_0
_IO_getc(stream)
   HAVE_PROT__IO_GETC_1 stream;
{
   const int d = fileno(stream);

   if (!sockscf.state.havegssapisockets || ISSYSCALL(d, SYMBOL__IO_GETC))
      return sys_getc(stream);
   return Rfgetc(stream);
}
#endif /* HAVE__IO_GETC */

HAVE_PROT_FGETC_0
fgetc(stream)
   HAVE_PROT_FGETC_1 stream;
{
   const int d = fileno(stream);

   if (!sockscf.state.havegssapisockets || ISSYSCALL(d, SYMBOL_FGETC))
      return sys_getc(stream);
   return Rfgetc(stream);
}

HAVE_PROT_GETS_0
gets(buf)
   HAVE_PROT_GETS_1 buf;
{
   const int d = fileno(stdin);

   if (!sockscf.state.havegssapisockets || ISSYSCALL(d, SYMBOL_GETS))
      return sys_gets(buf);
   return Rgets(buf);
}

HAVE_PROT_FGETS_0
fgets(buf, size, stream)
   HAVE_PROT_FGETS_1 buf;
   HAVE_PROT_FGETS_2 size;
   HAVE_PROT_FGETS_3 stream;
{
   const int d = fileno(stream);

   if (!sockscf.state.havegssapisockets || ISSYSCALL(d, SYMBOL_FGETS))
      return sys_fgets(buf, size, stream);
   return Rfgets(buf, size, stream);
}

HAVE_PROT_PUTC_0
putc(c, stream)
   HAVE_PROT_PUTC_1 c;
   HAVE_PROT_PUTC_2 stream;
{
   const int d = fileno(stream);

   if (!sockscf.state.havegssapisockets || ISSYSCALL(d, SYMBOL_PUTC))
      return sys_putc(c, stream);
   return Rfputc(c, stream);
}

#if HAVE__IO_PUTC
HAVE_PROT__IO_PUTC_0
_IO_putc(c, stream)
   HAVE_PROT__IO_PUTC_1 c;
   HAVE_PROT__IO_PUTC_2 stream;
{
   const int d = fileno(stream);

   if (!sockscf.state.havegssapisockets || ISSYSCALL(d, SYMBOL__IO_PUTC))
      return sys_putc(c, stream);
   return Rfputc(c, stream);
}
#endif /* HAVE__IO_PUTC */

HAVE_PROT_FPUTC_0
fputc(c, stream)
   HAVE_PROT_FPUTC_1 c;
   HAVE_PROT_FPUTC_2 stream;
{
   const int d = fileno(stream);

   if (!sockscf.state.havegssapisockets || ISSYSCALL(d, SYMBOL_FPUTC))
      return sys_fputc(c, stream);
   return Rfputc(c, stream);
}

HAVE_PROT_PUTS_0
puts(buf)
   HAVE_PROT_PUTS_1 buf;
{
   const int d = fileno(stdout);

   if (!sockscf.state.havegssapisockets || ISSYSCALL(d, SYMBOL_PUTS))
      return sys_puts(buf);
   return Rfputs(buf, stdout);
}

HAVE_PROT_FPUTS_0
fputs(buf, stream)
   HAVE_PROT_FPUTS_1 buf;
   HAVE_PROT_FPUTS_2 stream;
{
   const int d = fileno(stream);

   if (!sockscf.state.havegssapisockets || ISSYSCALL(d, SYMBOL_FPUTS))
      return sys_fputs(buf, stream);
   return Rfputs(buf, stream);
}

HAVE_PROT_FFLUSH_0
fflush(stream)
   HAVE_PROT_FFLUSH_1 stream;
{

   if (!sockscf.state.havegssapisockets
   || (stream != NULL && ISSYSCALL(fileno(stream), SYMBOL_FFLUSH)))
      return sys_fflush(stream);
   return Rfflush(stream);
}

HAVE_PROT_FCLOSE_0
fclose(stream)
   HAVE_PROT_FCLOSE_1 stream;
{
   const int d = fileno(stream);

   if (!sockscf.state.havegssapisockets || ISSYSCALL(d, SYMBOL_FCLOSE))
      return sys_fclose(stream);
   return Rfclose(stream);
}

HAVE_PROT_PRINTF_0
printf(HAVE_PROT_PRINTF_1 format, ...)
{
   const int d = fileno(stdout);
   va_list ap;
   int rc;

   va_start(ap, format);

   if (!sockscf.state.havegssapisockets || ISSYSCALL(d, SYMBOL_PRINTF)) {
      rc = sys_vprintf(format, ap);
      va_end(ap);
      return rc;
   }

   rc = Rvfprintf(stdout, format, ap);
   va_end(ap);

   return rc;
}

HAVE_PROT_FPRINTF_0
fprintf(HAVE_PROT_FPRINTF_1 stream, HAVE_PROT_FPRINTF_2 format, ...)
{
   const int d = fileno(stream);
   va_list ap;
   int rc;

   va_start(ap, format);

   if (!sockscf.state.havegssapisockets || ISSYSCALL(d, SYMBOL_FPRINTF)) {
      rc = sys_vfprintf(stream, format, ap);
      va_end(ap);
      return rc;
   }

   rc = Rvfprintf(stream, format, ap);
   va_end(ap);
   return rc;
}

#if HAVE___FPRINTF_CHK
HAVE_PROT_FPRINTF_0
__fprintf_chk(HAVE_PROT_FPRINTF_1 stream, int dummy, HAVE_PROT_FPRINTF_2 format, ...)
{
   const int d = fileno(stream);
   va_list ap;
   int rc;

   va_start(ap, format);

   if (!sockscf.state.havegssapisockets || ISSYSCALL(d, SYMBOL___FPRINTF_CHK)) {
      rc = sys_vfprintf(stream, format, ap);
      va_end(ap);
      return rc;
   }

   rc = Rvfprintf(stream, format, ap);
   va_end(ap);
   return rc;
}
#endif /* HAVE___FPRINTF_CHK */

HAVE_PROT_VPRINTF_0
vprintf(format, ap)
   HAVE_PROT_VPRINTF_1 format;
   HAVE_PROT_VPRINTF_2 ap;
{
   const int d = fileno(stdout);

   if (!sockscf.state.havegssapisockets || ISSYSCALL(d, SYMBOL_VPRINTF))
      return sys_vprintf(format, ap);
   return Rvfprintf(stdout, format, ap);
}

HAVE_PROT_VFPRINTF_0
vfprintf(stream, format, ap)
   HAVE_PROT_VFPRINTF_1 stream;
   HAVE_PROT_VFPRINTF_2 format;
   HAVE_PROT_VFPRINTF_3 ap;
{
   const int d = fileno(stream);

   if (!sockscf.state.havegssapisockets || ISSYSCALL(d, SYMBOL_VFPRINTF))
      return sys_vfprintf(stream, format, ap);
   return Rvfprintf(stream, format, ap);
}

#if HAVE___VFPRINTF_CHK
HAVE_PROT_VFPRINTF_0
__vfprintf_chk(stream, dummy, format, ap)
   HAVE_PROT_VFPRINTF_1 stream;
   int                  dummy;
   HAVE_PROT_VFPRINTF_2 format;
   HAVE_PROT_VFPRINTF_3 ap;
{
   const int d = fileno(stream);

   if (!sockscf.state.havegssapisockets || ISSYSCALL(d, SYMBOL___VFPRINTF_CHK))
      return sys_vfprintf(stream, format, ap);
   return Rvfprintf(stream, format, ap);
}
#endif /* HAVE___VFPRINTF_CHK */

HAVE_PROT_FWRITE_0
fwrite(ptr, size, nmb, stream)
   HAVE_PROT_FWRITE_1 ptr;
   HAVE_PROT_FWRITE_2 size;
   HAVE_PROT_FWRITE_3 nmb;
   HAVE_PROT_FWRITE_4 stream;
{
   const int d = fileno(stream);

   if (!sockscf.state.havegssapisockets || ISSYSCALL(d, SYMBOL_FWRITE))
      return sys_fwrite(ptr, size, nmb, stream);
   return Rfwrite(ptr, size, nmb, stream);
}

HAVE_PROT_FREAD_0
fread(ptr, size, nmb, stream)
   HAVE_PROT_FREAD_1 ptr;
   HAVE_PROT_FREAD_2 size;
   HAVE_PROT_FREAD_3 nmb;
   HAVE_PROT_FREAD_4 stream;
{
   const int d = fileno(stream);

   if (!sockscf.state.havegssapisockets || ISSYSCALL(d, SYMBOL_FREAD))
      return sys_fread(ptr, size, nmb, stream);
   return Rfread(ptr, size, nmb, stream);
}
#endif /* HAVE_GSSAPI && HAVE_LINUX_GLIBC_WORKAROUND */
#endif /* SOCKS_CLIENT */
#endif /* SOCKSLIBRARY_DYNAMIC */
