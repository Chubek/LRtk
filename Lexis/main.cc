#include <iostream>
#include <fstream>
#include <string>
#include "Lexis/Lexis.h"
#include "Lexis/CompressedDFA.h"
#include "Lexis/NFA.h"
#include "Lexis/DFA.h"
#include "Lexis/ParserData.h"
#include "Lexis/ItemAttributes.h"
#include "lexistab.h"
#include "Gramatika/Gramatika.h"
#include "gramadef.h"
#include "Toolbox/PathName.h"

  using Lexis::NFA;
  using Lexis::DFA;
  using Lexis::CompressedDFA;
  using Lexis::Token;
  using Lexis::TokenStream;
  using Lexis::ParserData;
  using Lexis::ItemAttributes;
  using LexisTokens::LexisTables;
  using LexisGrammar::GramatikaTables;
  using LexisGrammar::Parser;
  using Gramatika::Value;
  using Toolbox::PathName;

  string const lexExtension(".lex");
  string const tokenFileName("lexistab.h");
  string const tableFileName("lexistab.cc");

  int main(int argc, char* argv[])
  {
      if (argc != 2)
      {
           cerr << "Usage: lexis file[.lex]" << endl;
           return 1;
      }
      cerr << "Reading input file:";
      PathName argument(argv[1]);
      string lexFile;

      if (argument.getExtension() == lexExtension)
           lexFile = argument;
      else
           lexFile = argument + lexExtension;

      cerr << " " << lexFile;
      ifstream input(lexFile.c_str());
      if (!input)
      {
          cerr << "Can’t open " << lexFile << endl;
          return 1;
      }
      TokenStream<Token<LexisTables> > tin(input);
      Parser<ParserData,Token<LexisTables>,ItemAttributes,GramatikaTables> parser;
      Value<Token<LexisTables>,ItemAttributes> const result = parser.parse(tin);
      cerr << "." << endl;
      NFA* nfa = result.nfa;
      if (nfa == 0)
           cerr << "Null automaton." << endl;
      else
      {
           cerr << "Computing tables:";
           //cout << *nfa;
           DFA dfa(*nfa);
           delete nfa;
           //cout << dfa;
           dfa.minimize();
           //cout << dfa;
           CompressedDFA cdfa(dfa);
           cerr << "." << endl;
           cerr << "Writing output files:";
           string const tokenFile = argument.getHead() + tokenFileName;

           cerr << " " << tokenFile;
           ofstream lexisdef(tokenFile.c_str());
           if (!lexisdef)
           {
               cerr << "Can’t open " << tokenFile << endl;
               return 1;
           }
           cdfa.putTokens(lexisdef);
           string const tableFile = argument.getHead() + tableFileName;

           cerr << " " << tableFile;
           ofstream lexistbl(tableFile.c_str());
           if (!lexistbl)
           {
               cerr << "Can’t open " << tableFile << endl;
               return 1;
           }
           cdfa.putTables(lexistbl);
           cerr << "." << endl;
      }
      return 0;
  }
