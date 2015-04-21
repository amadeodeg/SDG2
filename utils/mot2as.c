/*
 * Motorola to AT&T/GNU ASsembler syntax convertor
 */
#ifndef lint
static char rcsid[] = "$Id: mot2as.c,v 1.1 2003/05/16 03:51:38 short Exp $";
#endif

static char helptext[] =
  "Motorola to AT&T/GNU ASsembler syntax convertor\n"
	"Version: %s\n"
	"Written in 1999 by Jan Kratochvil for Princip, a.s.\n"
	" - released under GPL version 2 license, see http://www.gnu.org for details\n"
	"\n"
  "for compilation of foo.s use the following command:\n"
  "./mot2as <foo.s|as --bitwise-or --register-prefix-optional -o foo.o\n"
  "\n";

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

typedef unsigned char muchar;

enum fatality { WARN,ERR,FATAL };

#ifndef LINE_MAX
#define LINE_MAX 16384
#endif

char buf[LINE_MAX];
unsigned lino=0;
char waserror;

static void Log(enum fatality fat,const char *fmt,...) __attribute__((format(printf,2,3)));
static void Log(enum fatality fat,const char *fmt,...)
{
  va_list ap;
  va_start(ap,fmt);
  fprintf(stderr,"mot2as: %u: ",lino);
  switch (fat) {
  case WARN : fputs("Warning: ",stderr); break;
  case ERR  : fputs("Error  : ",stderr); waserror=1; break;
  case FATAL: fputs("Fatal  : ",stderr); break;
  default   : assert(0);
  }
  vfprintf(stderr,fmt,ap);
  va_end(ap);
  fputs("!\n",stderr);
  if (fat==FATAL) exit(EXIT_FAILURE);
}

int main(int argc,char **argv)
{
  char fld,defbyte,*s;

  if (argc!=1) {
    fprintf(stderr,helptext,rcsid);
    return(EXIT_FAILURE);
  }
  while (lino++,fgets(buf,sizeof(buf),stdin)) {
    if (!(s=strchr(buf,'\n')))
      Log(ERR,"Line too long (>%lu), cut",sizeof(buf)-2);
    else {
      assert(!s[1]);
      *s='\0';
    }
    fld=0;
    defbyte=0;
    if (buf[0]=='l' && buf[1]=='b') buf[0]='L';
    else if (buf[0]=='L') buf[0]='l';
    for (s=buf;*s;s++)
      switch (*s) {
      case ' ':
      case '\t': {
	char *s2=s,eq=0;
	skip:
	fld++;
	while (s[1]==' ' || s[1]=='\t') s++;
	*s2='\0';
	if (fld==1
	    && !strncasecmp(s+1,"equ",3)
	    && (s[1+3]==' ' || s[1+3]=='\t'))
	  {
	    fputs("\t.equ\t",stdout);
	    fputs(buf,stdout); putchar(',');
	    s+=4;
	    eq=1;
	    goto skip;
	  }
	if (fld==1) fputs(buf,stdout);
	if (s2>buf && fld==1) putchar(':'); //label
	if (!eq) putchar('\t');
	defbyte |= (fld==1
		    && !strncasecmp(s+1,"dc.b",4)
		    && (s[1+4]==' ' || s[1+4]=='\t'));
	if (fld==1
	    && !strncasecmp(s+1,"opt",3)
	    && (s[1+3]==' ' || s[1+3]=='\t'))
	  putchar('|');
	break; }
      case ';': //comment
#ifdef PASS_THRU_COMMENTS
	putchar('|');
	fputs(s+1,stdout);
#endif //PASS_THRU_COMMENTS
	s+=strlen(s)-1;
	fld=1;
	break;
      case '"':
	do {
	  if (s[0]=='\\' && s[1]) putchar(*s++);
	  putchar(*s++);
	} while (*s && *s!='"');
	putchar(*s);
	break;
      case '\'': { //string
	char *d,*str;
	for (str = d = ++s; *s; *d++=*s++) {
	  if (s[0]=='\'') {
	    if (s[1]=='\'') s++;
	    else break;
	  }
	}
	if (!*s) {
	  Log(ERR,"String ('...) not terminated on this line");
	  s--;
	}
	if (!defbyte) {
	  if (d-str!=1 && d-str!=2 && d-str!=4)
	    Log(ERR,
		"String ('...') in NOT-defbyte instruction "
		"is not of length 1, 2 or 4");
	  else {
	    fputs("0x",stdout);
	    while (str<d) printf("%02X",(muchar)*str++);
	  }
	  break;
	}
	while (str<d) {
	  printf("%u",(muchar)*str++);
	  if (str<d) putchar(',');
	}
	break; }
      case '$':
	fputs("0x",stdout);
	break;
      case '%':
	fputs("0b",stdout);
	break;
      case 'l':
	if (s>buf
	    && !isalnum(s[-1])
	    && s[-1]!='_'
	    && s[1]=='b'
	    && s[2]!='_')
	  *s='L';
	goto out;
      case 'L':
	if (s>buf
	    && !isalnum(s[-1])
	    && s[-1]!='_')
	  *s='l';
	goto out;
      case '!':
	*s='|';
	/* FALLTHRU */
      default:
      out:
	if (fld) putchar(*s);
      }
    if (!fld && *buf) {
      fputs(buf,stdout); putchar(':');
    }
    putchar('\n');
  }
  return(waserror);
}
