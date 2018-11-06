
/*  A Bison parser, made from formatparser.y with Bison version GNU Bison version 1.24
  */

#define YYBISON 1  /* Identify Bison output.  */

#define yyparse sio_8211_yyparse
#define yylex sio_8211_yylex
#define yyerror sio_8211_yyerror
#define yylval sio_8211_yylval
#define yychar sio_8211_yychar
#define yydebug sio_8211_yydebug
#define yynerrs sio_8211_yynerrs
#define	NUMBER	258
#define	TYPE	259
#define	CHAR	260

#line 1 "formatparser.y"


  /*
   * $Id: formatparser_tab.c,v 1.1 1998/09/14 15:04:41 bmaddox Exp bmaddox $
   *
   */

#include <ctype.h>		/* toupper() */

#include <iostream>

#include <map>

/*
	FormatParser.y

	build parser by:

	% bison -p sio_8211_yy FormatParser.y


*/


#ifdef WIN32
#pragma warning( once : 4786 )
#endif

#include <string>
#include <iostream>

#ifndef INCLUDED_SIO8211FIELDFORMAT_H
#include "io/sio_8211FieldFormat.h"
#endif

#ifndef INCLUDED_SIO_CONVERTER_H
#include "io/sio_Converter.h"
#endif

#ifndef INCLUDED_SIO_8211CONVERTER_H
#include "io/sio_8211Converter.h"
#endif

/* buffer containing current subfield format string */

extern const char * sio_8211_subfield_format_buffer;



/* cursor into a subfield format to be set by the format string */

extern sio_8211FieldFormat::iterator current_sio_8211Subfield;



/* hints for finding the _right_ converter for a given binary subfield -- should
   be set by sio_8211MakeFieldFormat() */

extern map<string, sio_8211Converter*> const* sio_8211_binary_converter_hints;

extern "C" { int sio_8211_yywrap() { return 1; } }

void yyerror(const char* s);

int yylex();

void setConverter( sio_8211SubfieldFormat& sf );

void setType( char t, sio_8211SubfieldFormat& sf );


#line 74 "formatparser.y"
typedef union {
  int  i_val;
  char c_val;
} YYSTYPE;

#ifndef YYLTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YYLTYPE yyltype
#endif

#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		28
#define	YYFLAG		-32768
#define	YYNTBASE	9

#define YYTRANSLATE(x) ((unsigned)(x) <= 260 ? yytranslate[x] : 15)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     7,
     8,     2,     2,     6,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     6,    10,    13,    18,    20,    24,    28,    32,    34,
    36,    38,    41
};

static const short yyrhs[] = {     7,
     7,    12,     8,     8,     0,     7,    12,     8,     0,     3,
    14,     0,     3,     7,    10,     8,     0,    14,     0,     7,
     3,     8,     0,     7,    13,     8,     0,    12,     6,    10,
     0,    10,     0,     6,     0,     5,     0,     4,    11,     0,
     4,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
    88,    89,    93,   133,   134,   137,   138,   141,   142,   145,
   146,   149,   154
};

static const char * const yytname[] = {   "$","error","$undefined.","NUMBER",
"TYPE","CHAR","','","'('","')'","format","n_base","descriptor","n_base_list",
"delimiter","base",""
};
#endif

static const short yyr1[] = {     0,
     9,     9,    10,    10,    10,    11,    11,    12,    12,    13,
    13,    14,    14
};

static const short yyr2[] = {     0,
     5,     3,     2,     4,     1,     3,     3,     3,     1,     1,
     1,     2,     1
};

static const short yydefact[] = {     0,
     0,     0,    13,     0,     9,     0,     5,     0,     3,     0,
    12,     0,     0,     2,     0,     0,    11,    10,     0,     0,
     8,     4,     6,     7,     1,     0,     0,     0
};

static const short yydefgoto[] = {    26,
     5,    11,     6,    19,     7
};

static const short yypact[] = {     1,
    -1,    -3,    10,    12,-32768,     5,-32768,    12,-32768,     4,
-32768,     6,    12,-32768,    11,    13,-32768,-32768,    14,    15,
-32768,-32768,-32768,-32768,-32768,    18,    20,-32768
};

static const short yypgoto[] = {-32768,
    -8,-32768,    21,-32768,    22
};


#define	YYLAST		25


static const short yytable[] = {    15,
     3,     2,     3,     8,    21,     4,    16,     1,    17,    18,
    13,    13,    14,    20,     2,     3,    10,    27,    22,    28,
    23,    24,    25,     9,    12
};

static const short yycheck[] = {     8,
     4,     3,     4,     7,    13,     7,     3,     7,     5,     6,
     6,     6,     8,     8,     3,     4,     7,     0,     8,     0,
     8,     8,     8,     2,     4
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *_alloca (unsigned int);
};
#else /* not __cplusplus */
void *_alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

#include <malloc.h>

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(FROM,TO,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (from, to, count)
     char *from;
     char *to;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *from, char *to, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 192 "bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#else
#define YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#endif

int
yyparse(YYPARSE_PARAM)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) _alloca (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) _alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) _alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 1:
#line 88 "formatparser.y"
{  ;
    break;}
case 2:
#line 89 "formatparser.y"
{  ;
    break;}
case 3:
#line 94 "formatparser.y"
{ 
			// save an iterator for the first subfield
		   sio_8211FieldFormat::iterator first_sio_8211Subfield =
		      current_sio_8211Subfield;

		   current_sio_8211Subfield++;	// skip the current subfield; it
										// already has the proper value


				// now the remaining N - 1 subfields need
				// to get the _same_ data and semantic
				// type as the first subfield; so,
				// iterate through the next N - 1
				// subfields, setting their type to that of the first subfield

		   for ( int i = 1; i < yyvsp[-1].i_val; i++ )
		   {  // assign the state of the first subfield format to the current one
			  current_sio_8211Subfield->setFormat( first_sio_8211Subfield->getFormat() );

			  switch ( current_sio_8211Subfield->getFormat() )
			  {
			  case sio_8211SubfieldFormat::fixed :
				current_sio_8211Subfield->setLength( first_sio_8211Subfield->getLength() );
				break;
			  case sio_8211SubfieldFormat::variable :
				current_sio_8211Subfield->setDelimiter( first_sio_8211Subfield->getDelimiter() );
				break;
			  }

			  // we set the type last so that the length can be properly resized in the case
			  // of binary subfields

				current_sio_8211Subfield->setType( first_sio_8211Subfield->getType() );
				setConverter( *current_sio_8211Subfield );

		      current_sio_8211Subfield++;
		   }

		;
    break;}
case 4:
#line 133 "formatparser.y"
{  ;
    break;}
case 5:
#line 134 "formatparser.y"
{ current_sio_8211Subfield++; ;
    break;}
case 6:
#line 137 "formatparser.y"
{ current_sio_8211Subfield->setLength( yyvsp[-1].i_val ); ;
    break;}
case 7:
#line 138 "formatparser.y"
{ current_sio_8211Subfield->setDelimiter( yyvsp[-1].c_val ); ;
    break;}
case 12:
#line 150 "formatparser.y"
{ 
			setType( yyvsp[-1].c_val, *current_sio_8211Subfield ); 
			setConverter( *current_sio_8211Subfield ); 
		;
    break;}
case 13:
#line 155 "formatparser.y"
{ 
			setType( yyvsp[0].c_val, *current_sio_8211Subfield ); 
			setConverter( *current_sio_8211Subfield ); 
		;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 487 "bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);

	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 161 "formatparser.y"


char* format_buffer;

void
yyerror(const char* s)
{
  perror(s);
}



/* converters for use by setConverter */

static sio_8211Converter_A  _A_converter;
static sio_8211Converter_I  _I_converter;
static sio_8211Converter_R  _R_converter;
static sio_8211Converter_S  _S_converter;

void 
setConverter( sio_8211SubfieldFormat& sf )
{

  switch ( sf.getType() )
  {
  case sio_8211SubfieldFormat::A : sf.setConverter( & _A_converter ); break;

  case sio_8211SubfieldFormat::I : sf.setConverter( & _I_converter ); break;

  case sio_8211SubfieldFormat::R : sf.setConverter( & _R_converter ); break;

  case sio_8211SubfieldFormat::S : sf.setConverter( & _S_converter ); break;

  case sio_8211SubfieldFormat::C : /* sf.setConverter( & _C_converter ); */ break;

  case sio_8211SubfieldFormat::B :
  {
						/* if binary converters are supplied, find one
						   that matches the subfield label and bind it
						   to the current subfield format -- if either of
						   those conditions fail, the converter function will
						   be null for that subfield format. */

	if ( 0 != sio_8211_binary_converter_hints )
	{
		map<string, sio_8211Converter*>::const_iterator converter_itr = 
			sio_8211_binary_converter_hints->find( sf.getLabel() );

//		cerr << "looking for " << sf.getLabel() << "'s converter\n";

		if ( converter_itr != sio_8211_binary_converter_hints->end() )
		{
			sf.setConverter( (*converter_itr).second );
//			cerr << "converter for " << sf.getLabel() << " found." <<
//				  "  Set to " << hex << (*converter_itr).second << dec << ".\n";
		}
		else
		{
//			cerr << "converter for " << sf.getLabel() << " not found.\n";
		}

	}
	else
	{
//		cerr << __FILE__ << ":\tno binary converter hints\n";
	}

	break;
  }

  case sio_8211SubfieldFormat::X : /* sf.setConverter( & _X_converter ); */ break;

  default :  break;

  }

  return;

} /* setConverter() */




void
setType( char t, sio_8211SubfieldFormat& sf )
{
  char type = toupper(t);	/* upcase just in case */

  switch (type)
  {
  case 'A': sf.setType( sio_8211SubfieldFormat::A ); break;

  case 'I': sf.setType( sio_8211SubfieldFormat::I ); break;

  case 'R': sf.setType( sio_8211SubfieldFormat::R ); break;

  case 'S': sf.setType( sio_8211SubfieldFormat::S ); break;

  case 'C': sf.setType( sio_8211SubfieldFormat::C ); break;

  case 'B': sf.setType( sio_8211SubfieldFormat::B ); break;

  case 'X': sf.setType( sio_8211SubfieldFormat::X ); break;

  default:  return;

  }

} /* setType() */



#ifdef FOR_SLIGHTY_BENT_TESTING_PURPOSES
int
main()
{
  string parse_string;

  cout << "--> ";

  cin >> parse_string;

  cout << "you entered: " << parse_string << "\n";

  format_stream << parse_string << ends;

  yyparse();

  exit(0);

}

#endif