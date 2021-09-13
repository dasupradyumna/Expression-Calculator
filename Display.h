#ifndef __display_h__
#define __display_h__

#include <string_view>

using std::string_view;

namespace Display
{
  inline constexpr string_view Start {
    "\n"
    "\n     ______________________________"
    "\n    |"
    "\n    |      Basic Calculator"
    "\n    |______________________________"
    "\n    |"
    "\n    |  (1) Evaluate Expression"
    "\n    |  (2) Exit"
    "\n    |"
  };

  inline constexpr string_view EvalExp {
    "\n"
    "\n     ______________________________"
    "\n    |"
    "\n    |      Evaluate Expression"
    "\n    |______________________________"
    "\n    |"
    "\n    |"
    "\n    |"
    "\n    |"
  };
}

#endif