// Directed Simplex Type Theory grammar

grammar DiSiTT;

document : disittContents+; 

disittContents : 
    environment
  | COMMENT
  | command
  | ( WORD | SUPERSCRIPT | SUBSCRIPT | HASH | AMPERSAND | TILDE | MATH )+;

environment : BEGIN_CMD optArg* begName=envName argument* 
  disittContents+ 
  END_CMD endName=envName 
  { _localctx.begName.WORD().getText().equals(_localctx.endName.WORD().getText()) }? ;

envName : BEGIN_ARG WORD END_ARG ;

command : CMD optArg* argument* ;

argument : BEGIN_ARG disittContents+ END_ARG ;

optArg : BEGIN_OPT disittContents+ END_OPT ;

COMMENT : BEGIN_COMMENT ~( '\n' | '\r' )* [\n\r]+ ;

BEGIN_CMD : '\\begin' ;

END_CMD : '\\end';

CMD : '\\' WORD ;

BEGIN_ARG : '{';

END_ARG : '}';

BEGIN_OPT : '[';

END_OPT : ']';

fragment BEGIN_COMMENT : '%';

SUPERSCRIPT : '^';

SUBSCRIPT : '_';

TILDE : '~';

AMPERSAND : '&';

HASH : '#';

MATH : '$';

WORD : ~(' ' | '\t' | '\n' | '\r' 
  | '\\' | '%' 
  | '{'  | '}' 
  | '['  | ']' 
  | '^'  | '_' | '&' | '~' | '#' | '$' )+;
// potential: '<' | '>'
// see: http://www.aps.org/meetings/abstract/latex.cfm

WS : ( ' ' | '\t' | '\n' | '\r' )+ -> skip;
