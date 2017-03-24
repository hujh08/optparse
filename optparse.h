#include <getopt.h>

// structure used to specify an option
typedef struct
{
    const char *lname; // long name
    char sname; // short name
    int has_arg;
} optSpec;

// structure to store parsing result
typedef struct
{
    int set;
    char *val;
} optVal;

typedef struct option option;

// main function to parse options
extern int optparse(int , char * const [], optSpec *, optVal *);

// like strlen
extern int optlen(optSpec *);