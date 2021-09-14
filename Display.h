#ifndef __display_h__
#define __display_h__

#include <string_view>

using std::string_view;

namespace Display
{
  inline constexpr string_view Start {
    "\n"
    "\n  ______________________________"
    "\n"
    "\n        Basic Calculator"
    "\n  ______________________________"
    "\n"
    "\n    [1] Evaluate Expression"
    "\n    [2] Exit"
    "\n"
    "\n"
  };

  inline constexpr string_view EvalExp {
    "\n"
    "\n  ______________________________"
    "\n"
    "\n        Evaluate Expression"
    "\n  ______________________________"
    "\n"
    "\n    \"back\"   Back to Start menu"
    "\n    \"help\"   Open Help"
    "\n    \"clear\"  Clear screen"
    "\n"
    "\n"
  };

  inline constexpr string_view Help {
    "\n"
    "\n  ______________________________"
    "\n"
    "\n      Help and Functionality"
    "\n  ______________________________"
    "\n"
    "\n    [Esc] Back"
    "\n"
    "\n    Parantheses and floating point"
    "\n    numbers are allowed."
    "\n"
    "\n    Available operators :"
    "\n"
    "\n    +  Addition"
    "\n    -  Subtraction"
    "\n    *  Multiplication"
    "\n    /  Division"
    "\n    ^  Exponentiation"
    "\n"
    "\n"
  };
}

#endif
