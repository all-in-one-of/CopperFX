/*
 * Mantra ASCII .IFD file format grammer.
 */

grammar IFD;

import BSON; /* binary json lexer grammar */

file: line*;

line: version | declare | setenv | start | end | property | detail | image | geomerty | time | bgeo | raytrace | quit | COMMENT;

bgeo
   : BGEO_START .*? ~'ray_end' //{_input->LA(1)!='ray_end'}?
   ;

setenv
   : 'setenv' VAR_NAME '=' VALUE
   ;

version
   : 'ray_version' VEX_VERSION
   ;

declare
   : 'ray_declare' OBJECT TYPE VAR_NAME VALUE
   ;

start
   : 'ray_start' OBJECT
   ;

end
   : 'ray_end'
   ;

detail
   : 'ray_detail' ('-T' | (('-v' VALUE) | ('-V' VALUE VALUE)))? OBJNAME  ( 'stdin' | STRING )
   ;

property
   : 'ray_property' OBJECT VAR_NAME VALUE?
   ;

image
   : 'ray_image' VALUE VALUE?
   ;

geomerty
   : 'ray_geometry' VALUE
   ;

time
   : 'ray_time' VALUE
   ;

raytrace
   : 'ray_raytrace'
   ;

quit
   : 'ray_quit'
   ;

COMMENT
   : '#' ~( '\r' | '\n' )*
   ;

OBJNAME
   : '/' NO_QUOTED ('/' NO_QUOTED)?
   ;

TYPE
   : 'float' | 'bool' | 'int' | 'vector2' | 'vector3' | 'vector4' | 'matrix3' | 'matrix4' | 'string'
   ;

OBJECT
   : 'global' | 'material' | 'geo' | 'geomerty' | 'segment' | 'camera' | 'light' | 'fog' | 'object' | 'instance' | 'plane' | 'image' | 'renderer'
   ;

VEX_VERSION
   : 'VEX' INT ('.' INT)*
   ;

VAR_NAME
   : VALID_ID_START VALID_ID_CHAR*
   ;

VALUE
   : INTEGER | NUMBER | STRING
   ;

INTEGER
   : INT
   ;

NUMBER
   : '-'? INT '.' [0-9] + EXP? | '-'? INT EXP | '-'? INT
   ;

STRING
   : QUOTED | NO_QUOTED
   ;

NO_QUOTED
   : ~(' ' | '\'' | '"' | '\t' | '\r' | '\n' | '\u007f')+  // ignore bjson magic number
   ;

QUOTED
   : '"' (NO_QUOTED | ' ')* '"'
   ;

CHARS
   : LETTER+
   ;

BGEO_START
   : '\u007f' VALID_BGEO
   ;

fragment VALID_BGEO
   : 'NSJb'
   ;

fragment VALID_ID_START
   : LETTER | '_'
   ;

fragment VALID_ID_CHAR
   : VALID_ID_START | ('0' .. '9') | '-' | '+' | ':' | '.'
   ;

fragment LETTER
   : [a-zA-Z$_]
   ;

fragment INT
   : '0' | [1-9] [0-9]*
   ;

fragment EXP
   : [Ee] [+\-]? INT
   ;

WS: [ \n\t\r]+
   -> skip;