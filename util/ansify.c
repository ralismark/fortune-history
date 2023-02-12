/*
 * ansify.c v. 0.1.0 Oct. 3, 1995
 * 
 * A trivial little program.  It checks a text file for ctl-H characters
 * (like col, for instance), and where it finds them, tries to figure out
 * if it's underlining or double-striking (bolding) or an attempt to display
 * a special character.
 * 
 * If the file contains any of that, the program modifies the string in
 * memory to turn on VT100 control sequences governing underline and 
 * bold.  v. 0.2.0 will add a configuration file which can override 
 * VT100 sequences with locally-specified control codes.  v 0.3.0 will add
 * to the configuration file specification of control codes for non-ASCII
 * characters (accented characters, primarily).
 *
 * The reason for writing this is so silly text files like the databases
 * for the fortune program can have 'real' bold and underline on VT100
 * compliant screens (which means most terminals, I think).
 * 
 * Usage: ansify [-x] [-c _config-file_] _input-file_ [_output-file_]
 * 
 *                   -x : remove backspaces, like col(1)
 *     -c _config-file_ : Read _config-file_ for control codes
 *         _input-file_ : File to examine for ^H sequences
 *        _output-file_ : File to store 'ansified' file into.
 *                        [default: _input-file.ansi_]
 *
 * Hmm.
 * Add an option to let *word* and _word_ be italicized?
 * 
 * Returns: 0 on success (files open, read, written)
 *         -1 on command-line silliness
 *        1-9 on configuration file parse error
 *         11 on file open error
 *
 * Amy A. Lewis    alewis@email.unc.edu    October, 1995
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/param.h>
#include <unistd.h>
#include <string.h>

#define MAXCTL 4		       /* length of longest control seq. */

FILE	*inp,			       /* input file */
	*outp,			       /* output file */
	*conf;			       /* configuration file */

int	remove_codes = 0,	       /* remove backspaces anyway (no) */
	verbose = 0;		       /* Verbose listings */

char	start_under[MAXCTL],	       /* strings to hold the control */
	end_under[MAXCTL],	       /* sequences to start and end */
	start_bold[MAXCTL],	       /* underlining and bold */
	end_bold[MAXCTL],
/*	spec_chars[100][MAXCTL],       / * array of accented characters */
	input_file[MAXPATHLEN],	       /* filenames */
	output_file[MAXPATHLEN],
	conf_file[MAXPATHLEN];

void usage(char *myname)
{
    fprintf(stderr, "Usage:\n\t%s [-vx] [-c _config-file_] _input-file_ [_output-file_]\n",
	    myname);
    fprintf(stderr, "\n\t-v\t\t: Show each transformed string on stderr");
    fprintf(stderr, "\n\t-x\t\t: Strip unknown ^H sequences (like col)");
    fprintf(stderr, "\n\t-c conf-file\t: Use configuration file _conf-file_");
    fprintf(stderr, "\n\tinput-file\t: Name of file to convert");
    fprintf(stderr, "\n\toutput-file\t: Name of converted file\n");
    exit(-1);
}

/*
 * getconfig:
 *   Open and read the config file.  Return success/failure
 */
int getconfig(FILE *cf)
{
    int errs, lineno;
    
    errs = lineno = 0;
    if (cf == NULL) 		       /* No config file, use defaults. */
    {				       /* Ya know, we otter use termcap/info */
	strcpy(start_under, "\033[4m");
	strcpy(end_under, "\033[0m");  /* Is the ESC[24m syntax available? */
	strcpy(start_bold, "\033[1m");
	strcpy(end_bold, "\033[0m");   /* 'Cause this means no bold+ital */
/*	for (lineno = 0; lineno < 100 ; lineno++) spec_chars[lineno][0] = '\0';*/
    }
    /* Read a line, parse it */
    
      /* Barf.  I don't understand whatever that was supposed to be. */
/*        fprintf(stderr, "Parse error in configuration file, line %d discarded.\n", lineno);
        errs++;*/
    return(errs);
}

int getargs(int argc, char *argv[])
{
    extern int optind;
    extern char *optarg;
    char ac;
    int pe;

    pe = 0;
    while ((ac = getopt(argc, argv, "c:vx")) != EOF)
        switch (ac)
	{
	 case 'v':
	    verbose = 1;
	    break;
	 case 'x':		       /* act like col(1) */
	    remove_codes = 1;
	    break;
	 case 'c':		       /* not currently implemented */
	    fprintf(stderr, "Option -c not yet implemented.  Ignored\n");
	    strcpy(conf_file, optarg);
	    pe = 1;
	    break;
	 case '?':		       /* unknown parameters */
	 default:
	    usage(argv[0]);
	}

    argv += optind;
    
    if (*argv)
    {
        strcpy(input_file, *argv);
        fprintf(stderr, "Input file: %s\n", input_file);
        if (*++argv)		       /* output file specified */
            strcpy(output_file, *argv);
	else			       /* ofile not spec., use default */
	{
	    strcpy(output_file, input_file);
	    strcat(output_file, ".ansi");
	}
	fprintf(stderr, "Output file: %s\n", output_file);
    }
    else
    {
        fprintf(stderr, "No input file name\n");
	usage(argv[0]);
    }
    /* What do we do if some yahoo wants to use the same file for input and
     * output?  A) shit; B) go blind.  No, let's just make a backup and go*/
    if (!strcmp(input_file, output_file))
    {
	fprintf(stderr, "Must use different input/output file names.\n");
	return(17);		       /* for the time being, go blind */
    }
    /* open the files */
    if ((inp = fopen(input_file, "r")) == NULL)
    {
        perror(input_file);
        return(11);
    }
    if ((outp = fopen(output_file, "w+")) == NULL)
    {
        perror(output_file);
        return(11);
    }
    if (pe)
        if ((conf = fopen(conf_file, "r")) == NULL)
	{
	    perror(conf_file);
	    /* return(11);  it isn't implemented yet; 11 when it is?  Or ignore? */
	}
        else
	{
	    /* pe = getconfig(conf); Not yet, but this is how we'll do it. */
	    pe = getconfig(NULL); /* temporarily */
	    /* if (pe) return(pe);  Quit due to parse errors. */
	}
    else getconfig(NULL);
    return(0);
}

/*
 * x_string:
 *   Transform a string according the the rules we know.  This will be
 * enhanced muchly much when we have a config file.
 */
void x_string(char *xstr, int trtp)
{
    char holder[BUFSIZ],	       /* store as we build */
         *fch, *lch;		       /* first and last ^H */
    int i;
    
    /* First, the tests to find out what it is. */
    /* All we know to start with is how long it is, but that can be useful */
    if (strlen(xstr) == 3) /* x^Hy\0 */
	if (xstr[0] == '_')	       /* single-letter underline */
	{
	    strcpy(holder, start_under);
	    strcat(holder, xstr + 2);
	    strcat(holder, end_under);
	}
	else if (xstr[0] == xstr[2])   /* single-letter bold.  Odd. */
	{
	    strcpy(holder, start_bold);
	    strcat(holder, xstr + 2);
	    strcat(holder, end_bold);
	}
	else			       /* A single accented character */
	{
	    if (remove_codes)
		strcpy(holder, xstr + 2);
	    else
	        strcpy(holder, xstr);  /* for now.  Later more complex */
	}
    else
        if (trtp == 1)	  	       /* 'long' underline or bold style */
	{
	    fch = strchr(xstr, 0x08);
	    lch = strrchr(xstr, 0x08);
	    if (strncmp(xstr, lch + 1, strlen(xstr) / 3)) /* long bold */
	    {
		strcpy(holder, start_bold);
		strcat(holder, lch + 1);
		strcat(holder, end_bold);
	    }
	    else if (xstr[0] == '_')   /* assume long underline */
	    {
		strcpy(holder, start_under);
		strcat(holder, lch + 1);
		strcat(holder, end_under);
	    }
	}
        else if (trtp == 3)	       /* 'interleaved' style */
	    if (xstr[0] == '_')	       /* assume interleaved underline */
	    {
		strcpy(holder, start_under);
		for (i = 2; i <= strlen(xstr); i += 3)
		{
		    holder[strlen(holder) + 1] = '\0';
		    holder[strlen(holder)] = xstr[i];
		}
		strcat(holder, end_under);
	    }
	    else if (xstr[0] == xstr[2])   /* assume interleaved bold */
	    {
		strcpy(holder, start_bold);
		for (i = 2; i <= strlen(xstr); i += 3)
		{
		    holder[strlen(holder) + 1] = '\0';
		    holder[strlen(holder)] = xstr[i];
		}
		strcat(holder, end_bold);
	    }
	    else		       /* assume multiple spec. chars. */
		if (remove_codes)
		    for (i = 2; i <= strlen(xstr); i += 3)
		   {
		       holder[strlen(holder) + 1] = '\0';
		       holder[strlen(holder)] = xstr[i];
		   }
		else
		    strcpy(holder, xstr);
        else			       /* bloody error, is what */
	{
	    if (verbose) fprintf(stderr, "Yuck.  \"%s\".  No change.\n", xstr);
	    strcpy(holder, xstr);
	}
    if (verbose) fprintf(stderr, "%s transformed to %s\n", xstr, holder);
    strcpy(xstr, holder);	       /* Change the source to pass it back */
}

    
    
/*
 * eval_string:
 *   This is where we do all the dirty work.
 * 
 * The parameter line, which is passed in, gets transformed.  No return
 * value, but since multiple words may be highlighted, we check for that
 * and recurse if necessary.  I suspect that this is a nasty little kludge.
 * Yow!  I wish I was a COMPUTER SCIENTIST!
 */
void eval_string(char *line, char *first)
{
    char lastpart[BUFSIZ],	       /* Holder for remainder of string */
    	 word[BUFSIZ],		       /* Holder of part to be transformed */
         *next;			       /* a spare pointer */
    int backup,			       /* point at the place to truncate */
        forward,		       /* and at end of word */
        tt;			       /* transformation type parameter */
    
    /* Start by finding the boundaries of what's to be transformed */
    /* There are two models:
     * x^Hxy^Hyz^Hz
     * xyz^H^H^Hxyz
     */
    tt = 0;
    backup = forward = 1;
    next = first + 1;
    if (*next == 0x08) 
    {
	while (*next == 0x08)
	{
	    backup++;
	    forward += 2;
	    next++;
	}
	tt = 1;
    }
    else if (next[2] == 0x08)
    {
	tt = 3;
	next = first + 3;
	while (*next == 0x08)
	{
	    forward += 3;
	    next += 3;
	}
    }			       /* Golly gee whillikers, I hope that works */
    
    /* copy the part in question, and the remainder of the string */
    strncpy(word, first - backup, backup + forward + 1);
    next = first + forward;
    strcpy(lastpart, next);
    
    /* truncate the original string. */
    next = first - backup;
    next[0] = '\0';
    
    x_string(word, tt);
    /* do the transform.  cat the transformed version to the base string */
    strcat(line, word);
    
    /* Okay, here's the tricky part.  Check the remainder of the string
     * If it doesn't have a ctlh, fine.  Cat it onto the base and return.
     * If it does, cat it anyway, reset the first pointer, and recurse */
    if (!(strchr(lastpart, 0x08))) strcat(line,lastpart);
    else
    {
	next = strchr(lastpart, 0x08);
	backup = next - lastpart + strlen(line);      /* offset to ^H */
        first = line + backup;
	strcat(line,lastpart);
	eval_string(line, first);
    }
}

int main(int argc, char *argv[])
{
    int ecode;
    char buf[BUFSIZ], *ctlh;
    
    /* read the command line*/
    ecode = getargs(argc,argv);
    if (ecode) return(ecode);	       /* This means we die on parse error */
/*  if (ecode > 9) return(ecode);         This wouldn't die for parse errors */
    
    /* Start reading */
    while (!feof(inp))
    {
	fgets(buf, sizeof buf, inp);
	if ((ctlh = strchr(buf, 0x08))) eval_string(buf, ctlh);
	fputs(buf, outp);	       /* write it out */
    }
    return(0);
}
