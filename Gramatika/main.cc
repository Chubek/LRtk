#include <iostream>
#include <fstream>
#include <string>
#include "Lexis/Lexis.h"
#include "lexistab.h"
#include "Gramatika/Gramatika.h"
#include "gramadef.h"
#include "Gramatika/Automaton.h"
#include "Gramatika/ParseTable.h"
#include "Toolbox/PathName.h"

  using Lexis::Token;
  using Lexis::TokenStream;
  using GramatikaTokens::LexisTables;
  using Gramatika::Value;
  using Gramatika::SymbolTable;
  using Gramatika::Automaton;
  using Gramatika::ParseTable;
  using Gramatika::ParserData;
  using Gramatika::ItemAttributes;
  using GramatikaGrammar::GramatikaTables;
  using GramatikaGrammar::Parser;
  using Toolbox::PathName;

  string const gtkExtension(".gtk");
  string const definitionFileName("gramadef.h");
  string const actionFileName("gramactn.cc");
  string const tableFileName("gramatbl.cc");

  int main(int argc, char* argv[])
  {
      if (argc != 2)
      {
           cerr << "Usage: gramatik file[.lom]" << endl;
           return 1;
      }
      cerr << "Reading input file:";
      PathName const argument(argv[1]);
      string gtkFile;

      if (argument.getExtension() == gtkExtension)
           gtkFile = argument;
      else
           gtkFile = argument + gtkExtension;

      cerr << " " << gtkFile;
      ifstream input(gtkFile.c_str());
      if (!input)
      {
          cerr << " Can’t open " << gtkFile << endl;
          return 1;
      }
      TokenStream<Token<LexisTables> > tin(input);
      Parser<ParserData,Token<LexisTables>,ItemAttributes,GramatikaTables> parser;
      Value<Token<LexisTables>,ItemAttributes> result = parser.parse(tin);
      SymbolTable* symbolTable = result.symbolTable;
      assert(symbolTable != 0);
      cerr << "." << endl;
      cerr << "Constructing tables:";
      // cout << *symbolTable;
      symbolTable->computeFirstSets();
      Automaton automaton(*symbolTable);
      //cout << automaton;
      ParseTable parseTable(automaton);
      cerr << "." << endl;
      cerr << "Writing output files:";
      string const actionFile = argument.getHead() + actionFileName;
      cerr << " " << actionFile;
      ofstream gramactn(actionFile.c_str());
      if (!gramactn)
      {
           cerr << " Can’t open " << actionFile << endl;
           return 1;
      }
      symbolTable->putActions(gramactn);
      string const definitionFile =
           argument.getHead() + definitionFileName;
      cerr << " " << definitionFile;
      ofstream gramadef(definitionFile.c_str());
      if (!gramadef)
      {
           cerr << " Can’t open " << definitionFile << endl;
           return 1;
      }
      symbolTable->putPreamble(gramadef);
      string const tableFile = argument.getHead() + tableFileName;
      cerr << " " << tableFile;
      ofstream gramatbl(tableFile.c_str());
      if (!gramatbl)
      {
           cerr << " Can’t open " << tableFile << endl;
           return 1;
      }
      gramatbl << parseTable;
      cerr << "." << endl;
      return 0;
  }
