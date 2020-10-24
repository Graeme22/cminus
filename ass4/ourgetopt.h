#ifndef _OURGETOPT_H_
#define _OURGETOPT_H_

int ourGetopt( int, char **, char*);

extern char *optarg;                   /* option argument if : in opts */
extern int optind;                     /* next argv index              */
extern int optopt;                     /* last option (export dubious) */

#endif
