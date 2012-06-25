/* $Header: C:\\UTILS\\CVS\\ROOT/programs\\lang\\thue/thue.c,v 1.4 2000/09/02 16:46:29 John Colagioia Exp $
 *
 * Recent Changes:
 *
 * $Log: thue.c,v $
 * Revision 1.5  2010/12/18           Chris Pressey
 * Fix off-by-one error in sort routine, reported by
 * Nathan Thern.  Fix another off-by-one error in
 * random number generation.  Modernize: use rand()
 * and rename getline() to avoid name conflict.
 *
 * Revision 1.4  2000/09/02 16:46:29  John Colagioia
 * Trivial bugfix.
 *
 * Revision 1.2  2000/02/29 21:51:24  John Colagioia
 *
 * Just added some basic header info in the comments.
 *
 *
 */

/* For want of a nail,
    the shoe was lost.
   For want of a shoe,
    the horse was lost.
   For want of a horse,
    the knight was lost.
   For want of a knight,
    the battle was lost.
   So it was a kingdom was lost,
    all for the want of a nail.
	-- George Herbert, Jacula Prudentum
	   (Colloqual Adaptation)
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define	SEP	"::="

	char	* get_line	(FILE * infile);

struct rule
	{
	 char	lhs[64];
	 char	rhs[64];
	} rulebase[128];

int	ruleidx = 0,
	debug = 0;
char	*dataspace,
	*tempspace;

int main (int argc, char *argv[])
{
 char	*line,
	*c,
	*tmp,
	*target[64],
	 tempstr[64];
 int	 state,
	 flagstate,
	 i, j, k,
	 order,
	 temp,
	 rnum[64];
 FILE	*infile;

 srand(time(0));
 dataspace = malloc(16384);
 tempspace = malloc(16384);
 if (dataspace == NULL || tempspace == NULL) {
	fprintf (stderr, "Could not allocate sufficient working memory\n");
	exit(1);
 }
 target[0] = dataspace;
 memset (rulebase, 0, sizeof (rulebase));
 memset (dataspace, 0, sizeof (dataspace));
 if (argc > 1)
	infile = fopen (argv[1], "r");
 else
	infile = stdin;
 if (infile == NULL)
	return (-1);

 order = 0;
 if (argc > 2)
    switch (argv[2][0])
	{
	 case 'r':	/* Right-to-Left Processing */
		order = 2;
		break;
	 case 'l':	/* Left-to-Right */
		order = 1;
		break;
	 case 'd':
		debug = 1;
		break;
	}

 /* Get input file */
 state = 0;
 while (!feof (infile))
	{
	 line = get_line (infile);
	 if (state == 0)
		{
		 if (line != NULL && !strlen (line))
			continue;
		 c = strstr (line, SEP);
		 if (c == NULL)
			fprintf (stderr, "Malformed production: \"%s\"!\n", line);
		 else if (c == line)
			state = 1;
		 else	{
			 flagstate = 0;
			 for (tmp=line;tmp!=c;tmp++)
				if (!isspace (*tmp))
					 flagstate = 1;
			 if (flagstate)
				{
				 *c = '\000';
				 c += strlen (SEP);
				 strcpy (rulebase[ruleidx].lhs, line);
				 strcpy (rulebase[ruleidx].rhs, c);
				 ++ruleidx;
				}
			 else	state = 1;
			}
		}
	 else if (line != NULL)
			strcat (dataspace, line);
	}

 if (debug)
	printf ("Initial:  \"%s\"\n", dataspace);

 /* Apply rules */
 state = 1;
 while (state)
	{
	 /* Get all valid LHSs */
	 j = 1;
	 k = 0;
	 c = dataspace;
	 for (i=0;i<ruleidx;i++)
	    do
		{
		 k = j;
		 target[k] = strstr (c, rulebase[i].lhs);
		 rnum[k] = i;
		 if (target[k] != NULL)
			{
			 ++j;
			 c = target[k] + 1;
			}
		 else
			c = dataspace;
		}
	    while (target[k]);

	 if (j == 1)
		{
		 state = 0;
		 continue;
		}

	 /* Sort the LHS list - Just a bubble sort */
	 for (i=1;i<j;i++)
	    for (k=1;k<i;k++)
		if (target[i] < target[k])
			{
			 c = target[i];		temp = rnum[i];
			 target[i] = target[k];	rnum[i] = rnum[k];
			 target[k] = c;		rnum[k] = temp;
			}

	 /* Choose rule to apply */
	 switch (order)
		{
		 case 2:
			i = j - 1;
			break;
		 case 1:
			i = 1;
			break;
		 default:
			i = rand() % (j - 1) + 1;
			break;
		}
	 line = target[i];
	 temp = rnum[i];
	 c = line + strlen (rulebase[temp].lhs);
	 *line = '\000';

	 /* Check for I/O */
	 i = rulebase[temp].rhs[0] == '~';
	 if (i)
		{
		 puts (&rulebase[temp].rhs[1]);
		 memset (tempstr, 0, sizeof (tempstr));
		}
	 else
		{
 		 i = !strcmp (rulebase[temp].rhs, ":::");
		 if (i)
                     {
			fgets (tempstr, sizeof (tempstr), stdin);
                        tempstr[strlen (tempstr) - 1] = '\0';
                     }
		}

	 /* Apply the rule */
	 sprintf (tempspace, "%s%s%s", dataspace, i?tempstr:rulebase[temp].rhs, c);
	 strcpy (dataspace, tempspace);
	 if (debug)
		puts (dataspace);
	}

 if (debug)
	printf ("Final:  \"%s\"\n", dataspace);
 return (0);
}

char * get_line (FILE * infile)
{
 static	char	 buffer[256];
	char	*s;

 memset (buffer, 0, sizeof (buffer));
 /* Get next line from file */
 s = fgets (buffer, sizeof (buffer), infile);
 if (s == NULL)
	return (NULL);
 buffer[strlen (buffer) - 1] = '\0';
 /* Return pointer to string */
 return (buffer);
}
