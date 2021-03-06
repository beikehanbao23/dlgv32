%{
/*
 * This lex code parses a format record from an ISO 8211 file.
 * Formats have a complex syntax, so a yacc parser is used to build
 * the simplified format list.   The list is in terms of 
 * the basic data types  CHAR, INT, FLOAT, EXP_FLOAT, CHAR_BIT_STRING,
 * BITFIELD, and IGNORE.  See the ISO8211 standard for all the variations
 * possible in a format.
 *
 * $Id: FormatLexer.l,v 1.1 1998/09/14 15:04:40 bmaddox Exp bmaddox $
 *
 * We've used GNU's flex and not the standard UNIX lex on this.
 *
 * Build by:
 *  
 * % flex -B -Psio_8211_yy FormatLexer.l
 *
 * Please not that you'll have to hand edit to generated lexer to correct 
 * two problems.
 *
 * 1. #ifndef WIN32 out the #include <unistd.h>
 * 2. #define YY_NEVER_INTERACTIVE 1
 *
 */

				/* atoi() */
#include <stdlib.h>

				/* NUMBER, TYPE, CHAR, & yylval */
#include "y.tab.h"


%}


%%


[0-9]+			{ sio_8211_yylval.i_val = atoi(yytext); return NUMBER; }

[AIRSCBXairscbx]        { sio_8211_yylval.c_val = yytext[0]; return TYPE; }

[\x1e\x1f\0\n]		return 0; /* end of format field */

[(]                     return '(';
[)]                     return ')';

[,]                     { sio_8211_yylval.c_val = yytext[0]; return ','; }

.			{ sio_8211_yylval.c_val = yytext[0]; return CHAR; }



%%

/* int */
/* yylex() */
/* { */
/*   static FlexLexer* lexer = new yyFlexLexer( &format_stream, &cerr ); */
/*   return lexer->yylex(); */
/* } */
