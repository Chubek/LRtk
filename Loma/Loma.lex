Language:
     LomaTokens.
Tokens:
     atDefine = ’@define’.
     atEnd = ’@end’.
     atExample = ’@example’.
     atFile = ’@file’.
     atInclude = ’@include’.
     atLabel = ’@label’.
     atSign = ’@@’.
     atSymbol = ’@symbol’.
     atString = ’@"’ { /!"\n/ | ’\\"’ } ’"’.
     quotedString = ’"’ { /!"\n/ | ’\\"’ } ’"’.
     word = /! \t\n@/ { /! \t\n/ }.
     blank = ’ ’.
     tab = ’\t’.
     endOfLine = ’\n’.
