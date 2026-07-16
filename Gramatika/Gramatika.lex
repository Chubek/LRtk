Language:
     GramatikaTokens.
Definitions:
     blank = ’ ’.
     tab = ’\t’.
     newline = ’\n’.
     whitespace = blank | tab | newline.
     letter = /A-Za-z/.
     digit = /0-9/.
     escapesequence = ’\\’ ?.
     actionChar = /!’\\/ | escapesequence | newline.
Tokens:
     action = ’‘‘’ { actionChar | ’\’’ actionChar } [’\’’] ’\’\’’.
     colon = ’:’.
     comma = ’,’.
     equal = ’=’.
     field = ’(’ { whitespace } ( letter | ’_’ )
         { letter | digit | ’_’ } { whitespace } ’)’.
     period = ’.’.
     verticalBar = ’|’.
     preamble = ’Preamble’.
     terminals = ’Terminals’.
     nonterminals = ’Nonterminals’.
     start = ’Start’.
     productions = ’Productions’.
     postamble = ’Postamble’.
     language = ’Language’.
     stringT = ’"’ { /!"\\/ | ’\\"’ } ’"’.
     identifier = letter { letter | digit }.
     = whitespace { whitespace }.
     = ’#’ { ? } $.
