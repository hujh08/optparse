wrapper of getopt_long to parse options

# valid options specification
only give a list of struct--optSpec, which contains fileds: longname(lname), shortname(sname), has_arg

# result
- return an integer,  which is the index of first not-option arguments in argv
- a list of set, val pair, which is stored in a struct--optVal, corresponding to specified options respectively

# example
<pre><code>
int main(int argc, char *argv[])
{
    optSpec opts[]={
        {"help", 'h', no_argument},
        {"name", 'n', required_argument},
        {"opt", 'o', optional_argument},
        {NULL, 0, 0},
    };

    optVal optvals[optlen(opts)];

    printf("begin to parse opt\n");
    int opti=optparse(argc, argv, opts, optvals);
    if(opti==-1) {
        //perror("error to parse option");
        exit(EXIT_FAILURE);
    }
}
</code></pre>