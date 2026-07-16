#include <iostream>
#include <list>
#include "Gramatika/Gramatika.h"
#include "Gramatika/ParseTable.h"
#include "Toolbox/List.h"

  using namespace Toolbox;

namespace Gramatika
{
    ParseTable::ParseTable(Automaton const& a) :
        automaton(&a),
        symbolTable(&a.getSymbolTable()),
        numberOfStates(a.getNumberOfStates()),
        numberOfProductions(
            a.getSymbolTable().getNumberOfProductions()),
        actionMap(numberOfStates),
        actionTable(0),
        actionTableSize(0),
        actionStates(),
        gotoMap(numberOfStates),
        gotoTable(0), gotoTableSize(0), gotoStates(),
        leftHandSideTable(numberOfProductions),
        rightHandSideTable(numberOfProductions)
    {
        makeActionMap();
        makeActionTable();
        makeGotoMap();
        makeGotoTable();
        makeProductionTables();
    }
    ParseTable::~ParseTable()
        {}
    void ParseTable::makeActionMap()
    {
        for (StateNumber i = 0; i < numberOfStates; ++i)
            actionMap[i].start = invalid;
        for (StateNumber i = 0; i < numberOfStates; ++i)
        {
            if (actionMap[i].start == invalid)
            {
                 actionStates += i;
                 uint8_t const len =
                     (*automaton)[i].getActionList().size();
                 actionMap[i].start = actionTableSize;
                 actionMap[i].count = len;
                 actionTableSize += len;
                 for (StateNumber j = i + 1;
                     j < numberOfStates; ++j)
                     if (actionMap[j].start == invalid)
                         if (List::equals (
                                    (*automaton)[i].getActionList(),
                                    (*automaton)[j].getActionList()))
                         actionMap[j] = actionMap[i];
            }
        }
    }
    void ParseTable::makeActionTable()
    {
        actionTable.resize(actionTableSize);

          uint16_t position = 0;
          for (Set::const_iterator state(actionStates.begin()), lim;
                  state != lim; ++state)
          {
              StateNumber const i = *state;
              list<ActionRecord> const& actionList =
                  (*automaton)[i].getActionList();
              for (list<ActionRecord>::const_iterator ptr(actionList.begin()),
                      lim(actionList.end()); ptr != lim; ++ptr)
              {
                  actionTable[position] = *ptr;
                  position += 1;
              }
          }
          assert(position == actionTableSize);
      }
    void ParseTable::makeGotoMap()
    {
        for (StateNumber i = 0; i < numberOfStates; ++i)
            gotoMap[i].start = invalid;
        for (StateNumber i = 0; i < numberOfStates; ++i)
        {
            if (gotoMap[i].start == invalid)
            {
                 gotoStates += i;
                 uint8_t const len =
                     (*automaton)[i].getGotoList().size();
                 gotoMap[i].start = gotoTableSize;
                 gotoMap[i].count = len;
                 gotoTableSize += len;
                 for (StateNumber j = i + 1;
                     j < numberOfStates; ++j)
                     if (gotoMap[j].start == invalid)
                         if (List::equals(
                                    (*automaton)[i].getGotoList(),
                                    (*automaton)[j].getGotoList()))
                         gotoMap[j] = gotoMap[i];
            }
        }
    }
    void ParseTable::makeGotoTable()
    {
        gotoTable.resize(gotoTableSize);

          uint16_t position = 0;
          for (Set::const_iterator state(gotoStates.begin()), null;
                  state != null; ++state)
          {
              StateNumber const i = *state;
              list<GotoRecord> const& gotoList =
                  (*automaton)[i].getGotoList();
              for (list<GotoRecord>::const_iterator ptr(gotoList.begin()),
                      lim(gotoList.end()); ptr != lim; ++ptr)
              {
                  gotoTable[position] = *ptr;
                  position += 1;
              }
          }
          assert(position == gotoTableSize);
      }
    void ParseTable::makeProductionTables()
    {
        for (SymbolNumber i = 0;
            i < symbolTable->getNumberOfSymbols(); ++i)
        {
            list<Production*> const& prodList =
                 (*symbolTable)[i].getProductionList();
            for (list<Production*>::const_iterator ptr(prodList.begin()),
                     lim(prodList.end()); ptr != lim; ++ptr)
            {
                 Production const* const prod = *ptr;
                 leftHandSideTable[prod->getNumber()] =
                     prod->getLeftHandSide()->getNumber();
                 rightHandSideTable[prod->getNumber()] =
                     prod->getLength();
            }
        }
    }
    ostream& ParseTable::putMap(ostream& s, char const* label,
        vector<MapEntry> const& map) const
    {
        s << "MapEntry const GramatikaTables::"
            << label << "[" << numberOfStates << "] =\n";
        s << "{\n";
        s << " ";
        for (StateNumber i = 0; i < numberOfStates; ++i)
        {
            s << map[i];
            if (i < numberOfStates - 1U)
                 s << ", ";
            if (i % 5 == 4)
            {
                 s << "\n";
                 s << " ";
            }
        }
        s << "\n";
        s << "};\n";
        return s;
    }
    ostream& ParseTable::putTable(ostream& s, char const* label,
        uint16_t size,
        vector<TableEntry> const& table) const
    {
        s << "TableEntry const GramatikaTables::"
            << label << "[" << size << "] =\n";
        s << "{\n";
        s << " ";
        for (uint16_t i = 0; i < size; ++i)
        {
            s << table[i];
            if (i < size - 1U)
                 s << ", ";
            if (i % 5 == 4)
            {
                 s << "\n";
                 s << " ";
            }
        }
        s << "\n";
        s << "};\n";
        return s;
    }
    ostream& ParseTable::putLeftHandSideTable(ostream& s) const
    {
        s << "SymbolNumber const GramatikaTables::leftHandSideTable["
            << numberOfProductions << "] =\n";
        s << "{\n";
        s << " ";
        for (ProductionNumber i = 0;
            i < numberOfProductions; ++i)
        {
            s << leftHandSideTable[i];
            if (i < numberOfProductions - 1U)
                 s << ", ";
            if (i % 10 == 9)
            {
                 s << "\n";
                 s << " ";
            }
        }
        s << "\n";
        s << "};\n";
        return s;
    }
    ostream& ParseTable::putRightHandSideTable(ostream& s) const
    {
        s << "ProductionIndex const GramatikaTables::rightHandSideTable["
            << numberOfProductions << "] =\n";
        s << "{\n";
        s << " ";
        for (ProductionNumber i = 0;
            i < numberOfProductions; ++i)
        {
            s << static_cast<uint16_t>(rightHandSideTable[i]);
            if (i < numberOfProductions - 1U)
                 s << ", ";
            if (i % 10 == 9)
            {
                 s << "\n";
                 s << " ";
            }
        }
        s << "\n";
        s << "};\n";
        return s;
    }
    ostream& ParseTable::put(ostream& s) const
    {
        s <<
             "#include \"gramadef.h\"\n"
             "\n"
             "namespace " << symbolTable->getLanguage() << "\n"
             "{\n";
        s << "StateNumber const GramatikaTables::numberOfStates = "
             << numberOfStates << ";\n";
        putMap(s, "actionMap", actionMap);
        putTable(s, "actionTable", actionTableSize, actionTable);
        putMap(s, "gotoMap", gotoMap);
        putTable(s, "gotoTable", gotoTableSize, gotoTable);
        s << "ProductionNumber const GramatikaTables::numberOfProductions = "
            << numberOfProductions << ";\n";
        putLeftHandSideTable(s);
        putRightHandSideTable(s);
        s << "}\n";
        return s;
    }
}
