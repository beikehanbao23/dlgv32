%{

  /*
   * $Id: FormatParser.y,v 1.1 1998/09/14 15:04:40 bmaddox Exp bmaddox $
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

%}


%union {
  int  i_val;
  char c_val;
}

%token <i_val> NUMBER
%token <c_val> TYPE
%token <c_val> CHAR ','
%type <c_val> delimiter
%left '('


%%

format  :       '(' '(' n_base_list ')' ')' {  }
        |       '(' n_base_list ')' {  }
        ;


n_base  :       NUMBER base 
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

		   for ( int i = 1; i < $1; i++ )
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

		}
        |       NUMBER '(' n_base ')' {  }
        |       base { current_sio_8211Subfield++; }
        ;

descriptor :  '(' NUMBER ')' { current_sio_8211Subfield->setLength( $2 ); }
           |  '(' delimiter ')'{ current_sio_8211Subfield->setDelimiter( $2 ); }
           ;

n_base_list :       n_base_list ',' n_base
            |       n_base
            ;

delimiter   : ','
            | CHAR
            ;

base    :       TYPE descriptor 
		{ 
			setType( $1, *current_sio_8211Subfield ); 
			setConverter( *current_sio_8211Subfield ); 
		}
        |       TYPE 
		{ 
			setType( $1, *current_sio_8211Subfield ); 
			setConverter( *current_sio_8211Subfield ); 
		}
        ;

%%

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
