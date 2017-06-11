/**
 * @file punctuators.cpp
 * Manages the table of punctutators.
 *
 * @author  Ben Gardner
 * @license GPL v2+
 */
#include "punctuators.h"
#include "prototypes.h"
#include <algorithm>

/**
 *
 *   The file "punctuator_table.h" was generated by punc.py from this file.
 *   If you change one of the below symbol tables, re-run punc.py.
 *   $ python scripts/punc.py > src/punctuator_table.h
 *
 *   NOTE: the tables below do not need to be sorted.
 */


// 6-char symbols
static const chunk_tag_t symbols6[] =
{
   { R"_(??(??))_", CT_TSQUARE, LANG_C | LANG_CPP | FLAG_DIG }, // trigraph []
   { R"_(??!??!)_", CT_BOOL,    LANG_C | LANG_CPP | FLAG_DIG }, // trigraph ||
   { R"_(??=??=)_", CT_PP,      LANG_C | LANG_CPP | FLAG_DIG }, // trigraph ##
};

/* 5-char symbols */
static const chunk_tag_t symbols5[] =
{
   { R"_(??!=)_", CT_ASSIGN, LANG_C | LANG_CPP | FLAG_DIG }, // trigraph |=
   { R"_(??'=)_", CT_ASSIGN, LANG_C | LANG_CPP | FLAG_DIG }, // trigraph ^=
   { R"_(??=@)_", CT_POUND,  LANG_C | LANG_CPP | FLAG_DIG }, // trigraph #@ MS extension
};

/* 4-char symbols */
static const chunk_tag_t symbols4[] =
{
   { "!<>=",      CT_COMPARE, LANG_D                         },
   { ">>>=",      CT_ASSIGN,  LANG_D | LANG_JAVA | LANG_PAWN },
   { R"_(<::>)_", CT_TSQUARE, LANG_C | LANG_CPP | FLAG_DIG   }, // digraph []
   { R"_(%:%:)_", CT_PP,      LANG_C | LANG_CPP | FLAG_DIG   }, // digraph ##
};

// 3-char symbols
static const chunk_tag_t symbols3[] =
{
   { "!<=",      CT_COMPARE,      LANG_D                                             },
   { "!<>",      CT_COMPARE,      LANG_D                                             },
   { "!==",      CT_COMPARE,      LANG_D | LANG_ECMA                                 },
   { "!>=",      CT_COMPARE,      LANG_D                                             },
   { "->*",      CT_MEMBER,       LANG_C | LANG_CPP | LANG_D                         },
   { "...",      CT_ELLIPSIS,     LANG_C | LANG_CPP | LANG_D | LANG_PAWN | LANG_JAVA },
   { "<<=",      CT_ASSIGN,       LANG_ALL                                           },
   { "<>=",      CT_COMPARE,      LANG_D                                             },
   { "===",      CT_COMPARE,      LANG_D | LANG_ECMA                                 },
   { ">>=",      CT_ASSIGN,       LANG_ALL                                           },
   { ">>>",      CT_ARITH,        LANG_D | LANG_JAVA | LANG_PAWN | LANG_ECMA         },
   { "->*",      CT_MEMBER,       LANG_C | LANG_CPP | LANG_D                         },
   { "%:@",      CT_POUND,        LANG_C | LANG_CPP | LANG_OC                        }, // digraph  #@ MS extension
   { R"_(??=)_", CT_POUND,        LANG_C | LANG_CPP | FLAG_DIG                       }, // trigraph #
   { R"_(??()_", CT_SQUARE_OPEN,  LANG_C | LANG_CPP | FLAG_DIG                       }, // trigraph [
   { R"_(??))_", CT_SQUARE_CLOSE, LANG_C | LANG_CPP | FLAG_DIG                       }, // trigraph ]
   { R"_(??')_", CT_CARET,        LANG_C | LANG_CPP | FLAG_DIG                       }, // trigraph ^
   { R"_(??<)_", CT_BRACE_OPEN,   LANG_C | LANG_CPP | FLAG_DIG                       }, // trigraph {
   { R"_(??>)_", CT_BRACE_CLOSE,  LANG_C | LANG_CPP | FLAG_DIG                       }, // trigraph }
   { R"_(??-)_", CT_INV,          LANG_C | LANG_CPP | FLAG_DIG                       }, // trigraph ~
   { R"_(??!)_", CT_ARITH,        LANG_C | LANG_CPP | FLAG_DIG                       }, // trigraph |
};
// { R"_(??/)_", CT_UNKNOWN,      LANG_C | LANG_CPP | FLAG_DIG                       }, // trigraph '\'

// 2-char symbols
static const chunk_tag_t symbols2[] =
{
   { "!<",      CT_COMPARE,      LANG_D                                           },
   { "!=",      CT_COMPARE,      LANG_ALL                                         },
   { "!>",      CT_COMPARE,      LANG_D                                           },
   { "!~",      CT_COMPARE,      LANG_D                                           },
   { "##",      CT_PP,           LANG_C | LANG_CPP | LANG_OC                      },
   { "#@",      CT_POUND,        LANG_C | LANG_CPP | LANG_OC                      },           // MS extension
   { "%=",      CT_ASSIGN,       LANG_ALL                                         },
   { "&&",      CT_BOOL,         LANG_ALL                                         },
   { "&=",      CT_ASSIGN,       LANG_ALL                                         },
   { "*=",      CT_ASSIGN,       LANG_ALL                                         },
   { "++",      CT_INCDEC_AFTER, LANG_ALL                                         },
   { "+=",      CT_ASSIGN,       LANG_ALL                                         },
   { "--",      CT_INCDEC_AFTER, LANG_ALL                                         },
   { "-=",      CT_ASSIGN,       LANG_ALL                                         },
   { "->",      CT_MEMBER,       LANG_ALLC                                        },
   { ".*",      CT_MEMBER,       LANG_C | LANG_CPP | LANG_D                       },
   { "..",      CT_RANGE,        LANG_D                                           },
   { "?.",      CT_NULLCOND,     LANG_CS                                          },           // null conditional operator
   { "/=",      CT_ASSIGN,       LANG_ALL                                         },
   { "::",      CT_DC_MEMBER,    LANG_C | LANG_CPP | LANG_CS | LANG_D | LANG_VALA },
   { "<<",      CT_ARITH,        LANG_ALL                                         },
   { "<=",      CT_COMPARE,      LANG_ALL                                         },
   { "<>",      CT_COMPARE,      LANG_D                                           },
   { "==",      CT_COMPARE,      LANG_ALL                                         },
   { ">=",      CT_COMPARE,      LANG_ALL                                         },
   { ">>",      CT_ARITH,        LANG_ALL                                         },
   { "[]",      CT_TSQUARE,      LANG_ALL                                         },
   { "^=",      CT_ASSIGN,       LANG_ALL                                         },
   { "|=",      CT_ASSIGN,       LANG_ALL                                         },
   { "||",      CT_BOOL,         LANG_ALL                                         },
   { "~=",      CT_COMPARE,      LANG_D                                           },
   { "~~",      CT_COMPARE,      LANG_D                                           },
   { "=>",      CT_LAMBDA,       LANG_VALA | LANG_CS | LANG_D                     },
   { "??",      CT_COMPARE,      LANG_CS | LANG_VALA                              },
   { R"_(<%)_", CT_BRACE_OPEN,   LANG_C | LANG_CPP | FLAG_DIG                     },           // digraph {
   { R"_(%>)_", CT_BRACE_CLOSE,  LANG_C | LANG_CPP | FLAG_DIG                     },           // digraph }
   { R"_(<:)_", CT_SQUARE_OPEN,  LANG_C | LANG_CPP | FLAG_DIG                     },           // digraph [
   { R"_(:>)_", CT_SQUARE_CLOSE, LANG_C | LANG_CPP | FLAG_DIG                     },           // digraph ]
   { R"_(%:)_", CT_POUND,        LANG_C | LANG_CPP | FLAG_DIG                     },           // digraph #
};

// 1-char symbols
static const chunk_tag_t symbols1[] =
{
   { "!", CT_NOT,          LANG_ALL                            },
   { "#", CT_POUND,        LANG_ALL & ~(LANG_JAVA | LANG_ECMA) },
   { "$", CT_COMPARE,      LANG_D                              },
   { "%", CT_ARITH,        LANG_ALL                            },
   { "&", CT_AMP,          LANG_ALL                            },
   { "(", CT_PAREN_OPEN,   LANG_ALL                            },
   { ")", CT_PAREN_CLOSE,  LANG_ALL                            },
   { "*", CT_STAR,         LANG_ALL                            },
   { "+", CT_PLUS,         LANG_ALL                            },
   { ",", CT_COMMA,        LANG_ALL                            },
   { "-", CT_MINUS,        LANG_ALL                            },
   { ".", CT_DOT,          LANG_ALL                            },
   { "/", CT_ARITH,        LANG_ALL                            },
   { ":", CT_COLON,        LANG_ALL                            },
   { ";", CT_SEMICOLON,    LANG_ALL                            },
   { "<", CT_ANGLE_OPEN,   LANG_ALL                            },
   { "=", CT_ASSIGN,       LANG_ALL                            },
   { ">", CT_ANGLE_CLOSE,  LANG_ALL                            },
   { "@", CT_OC_AT,        LANG_OC                             },
   { "?", CT_QUESTION,     LANG_ALL                            },
   { "[", CT_SQUARE_OPEN,  LANG_ALL                            },
   { "]", CT_SQUARE_CLOSE, LANG_ALL                            },
   { "^", CT_CARET,        LANG_ALL                            },
   { "{", CT_BRACE_OPEN,   LANG_ALL                            },
   { "|", CT_ARITH,        LANG_ALL                            },
   { "}", CT_BRACE_CLOSE,  LANG_ALL                            },
   { "~", CT_INV,          LANG_ALL                            },
};

// must be positioned here, after all symbolsX[], because punc_table uses them
#include "punctuator_table.h"


const chunk_tag_t *find_punctuator(const char *str, int lang_flags)
{
   if (str == nullptr || str[0] == '\0')
   {
      return(nullptr);
   }

   const auto binary_find =
      [](const lookup_entry_t *first, const lookup_entry_t *last, const char &value)
      {
         const auto tmp = std::lower_bound(first, last, value,
                                           lookup_entry_t::comperator());

         return((value == tmp->ch) ? tmp : nullptr);
      };

   const chunk_tag_t *match  = nullptr;
   const auto        *parent = punc_table; //!< graph in table form, initially point at first entry
   auto              ch_idx  = int {};

   while (ch_idx < 6 && str[ch_idx] != '\0') //!< symbols6: max punc len = 6
   {
      // search for next parent node in all current child nodes
      parent = binary_find(parent, next(parent, parent->left_in_group), str[ch_idx]);
      if (parent == nullptr)
      {
         break; // no nodes found with the searched char
      }

      if (parent->tag != nullptr
          && (parent->tag->lang_flags & lang_flags) != 0  // punctuator lang and processing lang match
          && ((parent->tag->lang_flags & FLAG_DIG) == 0   // punctuator is not a di/tri-graph
              || cpd.settings[UO_enable_digraphs].b))     // or di/tri-graph processing is enabled
      {
         match = parent->tag;
      }

      if (parent->next_idx == 0)
      {
         break;                               // no child nodes, leaf reached
      }
      parent = &punc_table[parent->next_idx]; // point at the first child node
      ch_idx++;
      continue;
   }
   return(match);
} // find_punctuator
