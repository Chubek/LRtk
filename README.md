# Reconstructed source — Lexis & Gramatika (and Toolbox / Loma)

These 82 files were reconstructed by *tangling* the literate C++ source in
`../lex-and-parse-with-cpp.pdf` (Bruno R. Preiss, *Lexical Analysis and Parsing
using C++*, 2004). They are **not** hand-transcribed: they were produced by
`../tangle.py`, which parses every code chunk in the book and expands the
`File:` root chunks.

## How the book is structured (CWEB / Loma literate style)

Code lives in named chunks. In the PDF the angle-bracket delimiters ⟨…⟩ are
rendered by `pdftotext` as the ASCII letters **`h` … `i`**. Each chunk is
*defined* at one paragraph ¶N:

```
hchunk name i N ≡              (¶N may also be printed on the left)
   1  body line
   2  body line
This code is used in ¶M.
```

A chunk may be defined *incrementally* across several paragraphs (e.g. ¶58…¶64);
those bodies concatenate. A *reference* inside a body is a whole line:

```
hchunk name i <paragraphs>
```

where `<paragraphs>` is a single number (`55`), an en-dash range (`58–64`), or a
comma list (`158,164–172`). **The paragraph spec disambiguates chunks**: the same
name (`State class declaration`) is defined at both ¶55 (Lexis) and ¶486
(Gramatika) for two unrelated classes, so resolution is by *paragraph number*,
not by name. The final source files are the chunks whose name begins with
`File: ` — the roots of the tangle tree.

## Layout

| Part       | Dir         | Files | Contents                                                |
|------------|-------------|-------|---------------------------------------------------------|
| I  Lexis   | `Lexis/`    | 19    | Lexer generator (NFA→DFA→CompressedDFA) + main          |
| II Gramatika | `Gramatika/` | 29  | LR parser generator (Symbol…ParseTable, Parser) + main  |
| III Toolbox | `Toolbox/`  | 19    | Shared utilities (Set, Stack, HashTable, …) used by both|
| IV Loma    | `Loma/`     | 15    | The literate-programming tool that wrote this very book |

## File types

* `*.h` / `*.cc` — C++ source (76 files).
* `*.gtk` — Gramatika grammar specification (each generator's own input grammar).
* `*.lex` — Lexis token specification.

The `.gtk` / `.lex` files are the BNF-like specifications of the generators'
own input languages, *not* C++.

## Caveats

* The code follows the book's idiosyncratic formatting (e.g. `public:`/`protected:`
  labels share a line with their declaration; some inline bodies are indented).
  This is faithful to the source, not a formatting bug.
* The text is **as compilable as the book makes it**. It depends on generated
  tab headers (e.g. `lexistab.h`), the `Lexis::`/`Gramatika::` namespaces built
  by the generators, and the author's original build setup, so it will not
  compile standalone without those generated inputs.
* The book's prose "List of Files" index (pp. 373+) under-lists the Gramatika
  part; the authoritative set is the 82 `File:` chunks, all of which are
  reproduced here (verified 1:1, zero unresolved references).

Regenerate with `python3 tangle.py` from the parent directory.
