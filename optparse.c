#include <stdlib.h>
#include <string.h>

#include "optparse.h"

int opt_strind(const char *s1, char c)
{
    int nPos=-1;
    char *res=strchr(s1, c);
    if(res) nPos=res-s1;
    return nPos;
}

int optparse(int argc, char * const argv[],
             optSpec *opts,
             optVal *optvals)
{
    int olen=optlen(opts);

    // generate short options
    char *optstr=(char *) malloc((3*olen+1)*sizeof(char)),
         *shortopts=(char *) malloc((olen+1)*sizeof(char));
    int ind=0;
    for(int i=0; i<olen; i++) {
        shortopts[i]=optstr[ind++]=opts[i].sname;
        int has_arg=opts[i].has_arg;
        if(has_arg!=no_argument) optstr[ind++]=':';
        if(has_arg==optional_argument) optstr[ind++]=':';
    }
    shortopts[olen]=optstr[ind]='\0';

    // generate long options
    option *longopts=\
        (option *) malloc((olen+1)*sizeof(option));
    for(int i=0; i<olen; i++) {
        longopts[i].name=opts[i].lname;
        longopts[i].has_arg=opts[i].has_arg;
        longopts[i].val=opts[i].sname;
        longopts[i].flag=NULL;
    }
    //longopts[lenopt]={NULL, 0, NULL, 0};
    //struct option temp={NULL, 0, NULL, 0};
    longopts[olen].name=NULL;
    longopts[olen].has_arg=0;
    longopts[olen].val=0;
    longopts[olen].flag=NULL;

    // initiate optVals
    for(int i=0; i<olen; i++) {
        optvals[i].set=0;
        optvals[i].val=NULL;
    }

    //opterr=0;
    int opt, longindex, optInd;
    while((opt=getopt_long(argc, argv,
                           optstr,
                           longopts,
                           &longindex))!=-1) {
        switch(opt) {
            case '?':
                return -1;
            default:
                optInd=opt_strind(shortopts,
                                  (char) opt);
                optvals[optInd].set=1;
                optvals[optInd].val=optarg;
        }
    }

    free(optstr);
    free(shortopts);
    free(longopts);
    return optind;
}