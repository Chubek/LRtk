Language:
     LexisTokens.
Definitions:
     blank = ’ ’.
     tab = ’\t’.
     newline = ’\n’.
     whitespace = blank | tab | newline.
     letter = /A-Za-z/.
     octaldigit = /0-7/.
     hexdigit = /0-9A-Fa-f/.
     singleton = /ntvbrfa\\?’"\//.
     octalcode = octaldigit [ octaldigit [ octaldigit ] ].
     hexcode = ’x’ hexdigit { hexdigit }.
     escapesequence = ’\\’ ( singleton | octalcode | hexcode ).
Tokens:
     circumflex = ’^’.
     colon = ’:’.
     dollar = ’$’.
     equal = ’=’.
     leftBrace = ’{’.
     leftBracket = ’[’.
     leftParenthesis = ’(’.
     period = ’.’.
     questionMark = ’?’.
     rightBrace = ’}’.
     rightBracket = ’]’.
     rightParenthesis = ’)’.
     verticalBar = ’|’.
     stringT = ’\’’ { /!’\\/ | escapesequence } ’\’’.
     characterClass = ’/’ { /!\/\\/ | escapesequence } ’/’.
     definitions = ’Definitions’.
     tokens = ’Tokens’.
     language = ’Language’.
     identifier = letter { letter }.
     = whitespace { whitespace }.
     = ’#’ { ? } $.
