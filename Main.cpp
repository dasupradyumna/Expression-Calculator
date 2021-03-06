#include "Display.h"
#include "Expression.h"

#include <conio.h>      // _getch, _kbhit
#include <cstdlib>      // system
#include <iostream>     // cin, cout

// escape key is 27 from _getch
// TODO : use windows.h for handling keyboard events

enum class ProgramState
{
  Start,
  EvaluateExpression,
  Exit,
  Help
};

inline
void flushConioBuffer()
{
  while ( _kbhit() ) _getch();  // to flush the input buffer before user input
}

inline
void clearScreen()
{
  system( "cls" );
}

ProgramState Start()
{
  flushConioBuffer();
  int choice { _getch() };  //////// remove temp variable `choice`
  switch ( choice )
  {
    case '1': return ProgramState::EvaluateExpression;
    case '2': return ProgramState::Exit;
    default: return ProgramState::Start;
  }
}

ProgramState EvalExp()
{
  Expression Input { };
  while ( true )
  {
    std::cout << Expression::new_line;
    Input.get();

    switch ( Input.flag )
    {
      case Expression::Status::Valid:
        std::cout << "      = " << Input.value() << "\n\n";
        break;
      case Expression::Status::Invalid:
        std::cout << Expression::invalid;
        break;
      case Expression::Status::Help:
        return ProgramState::Help;
      case Expression::Status::Clear:
        clearScreen();
        std::cout << Display::EvalExp;
        break;
      case Expression::Status::Back:
        return ProgramState::Start;
    }
  }
}

ProgramState Help()
{
  flushConioBuffer();
  int choice { _getch() };
  if ( choice == 27 )
    return ProgramState::EvaluateExpression;
  else
    return ProgramState::Help;
}

int main()
{
  auto state { ProgramState::Start };
  while ( state != ProgramState::Exit )
    switch ( state )
    {
      case ProgramState::Start:
        clearScreen();
        std::cout << Display::Start;
        state = Start();
        break;
      case ProgramState::EvaluateExpression:
        clearScreen();
        std::cout << Display::EvalExp;
        state = EvalExp();
        break;
      case ProgramState::Help:
        clearScreen();
        std::cout << Display::Help;
        state = Help();
        break;
    }

  clearScreen();
  return 0;
}
