#include <iostream>
#include <fstream.h>
#include <stdlib.h>
#include "Loma/File.h"
#include "Lexis/Lexis.h"
#include "lexistab.h"
#include "Gramatika/Gramatika.h"
#include "gramadef.h"
#include "Toolbox/PathName.h"

  using Lexis::Token;
  using Lexis::TokenStream;
  using LomaTokens::LexisTables;
  using Loma::File;
  using Loma::ParserData;
  using Loma::ItemAttributes;
  using LomaGrammar::GramatikaTables;
  using LomaGrammar::Parser;
  using Gramatika::Value;

    string const lomExtension(".lom");
    string const texExtension(".tex");

    int ProcessArgument(string argument)
    {
        PathName pathName(argument);
        string lomFile;

        if (pathName.getExtension() == lomExtension)
             lomFile = pathName;
        else
             lomFile = pathName + lomExtension;
        cerr << "Reading input file:";
        cerr << " " << lomFile;
        ifstream lomStream(lomFile.c_str());
        if (!lomStream)
        {
             cerr << " Can’t open " << lomFile << endl;
             return 3;
        }
        TokenStream<Token<LexisTables> > tin(lomStream);
        Parser<ParserData,Token<LexisTables>,ItemAttributes,GramatikaTables> parser;
        Value<Token<LexisTables>,ItemAttributes> const result = parser.parse(tin);
        File* file = result.file;
        cerr << "." << endl;
        cerr << "Writing output files:";
        string texFile = pathName.getBase() + texExtension;
        cerr << " " << texFile;
        ofstream texStream(texFile.c_str());
        if (!texStream)
        {
             cerr << " Can’t open " << texFile << endl;
             return 4;
        }
        texStream << *file;
        file->putCode(pathName.getHead(), lomFile);
        delete file;
        cerr << "." << endl;
        return 0;
    }

  int main(int argc, char* argv[])
  {
      if (argc < 2)
      {
          cerr << "Usage: loma [@]file [[@]file...]" << endl;
          return 1;
      }
      for (int i = 1; i < argc; ++i)
      {
          if (argv [i] [0] == ’@’)
          {
              string responseFileName(argv [i] + 1);

              cerr << "Reading response file:";
              cerr << " " << responseFileName << endl;
              ifstream responseFile(responseFileName.c_str());
              if (!responseFile)
              {
                  cerr << "Can’t open " << responseFileName << endl;
                  return 2;
              }
              for (;;)
              {
                  string argument;
                  responseFile >> argument;
                  if (!responseFile)
                      break;
                  int errorCode = ProcessArgument(argument);
                  if (errorCode)
                      return errorCode;
              }
          }
          else
          {
              int errorCode = ProcessArgument(argv [i]);
              if (errorCode)
                   return errorCode;
          }
      }
      return 0;
  }
