#include "Expression.h"

#include <algorithm>    // count, find, remove
#include <cctype>       // isdigit, tolower
#include <cmath>        // pow
#include <iostream>     // cin
#include <vector>       // vector

const std::unordered_set<char> __operators { '^', '*', '/', '+', '-' };

const std::unordered_map<char, int> Expression::__precedence {
    { '^', 3 },
    { '*', 2 }, { '/', 2 },
    { '+', 1 }, { '-', 1 },
    { '(', 0 }
};

bool __process_input( std::string& input )
{
  auto is_floating_point = [] ( char ch ) { return isdigit( ch ) || ch == '.'; };

  int mod = std::distance( input.begin(), std::find( input.begin(), input.end(), ' ' ) );
  if ( mod != input.length() )
  {
    char pre_ws { 0 };
    bool is_pre_ws { false };
    for ( int orig { mod - 1 }; ++orig < input.length(); )
      if ( input[orig] != ' ' )
      {
        if ( is_floating_point( pre_ws ) && is_floating_point( input[orig] ) ) return false;

        is_pre_ws = false;
        pre_ws = 0;
        input[mod++] = input[orig];
      }
      else if ( input[orig] == ' ' && !is_pre_ws )
      {
        pre_ws = input[orig - 1];
        is_pre_ws = true;
      }

    input.resize( mod );
  }

  return true;
}

void Expression::get()
{
  std::string raw { };
  std::getline( std::cin, raw, '\n' );
  if ( !__process_input( raw ) )
    flag = Status::Invalid;
  else if ( raw == "back" )
    flag = Status::Back;
  else if ( raw == "clear" )
    flag = Status::Clear;
  else if ( raw == "help" )
    flag = Status::Help;
  else if ( __is_valid( raw ) )
    flag = Status::Valid;
  else
    flag = Status::Invalid;
}

double Expression::value() const
{
  return __value;
}

double __operation( char op, double L, double R )
{
  switch ( op )
  {
    case '+': return L + R;
    case '-': return L - R;
    case '*': return L * R;
    case '/': return L / R;
    case '^': return pow( L, R );
  }
}

void Expression::__process_stacks( vector<char>& op_stack, vector<double>& num_stack )
{
  double R { num_stack.pop() };
  double L { num_stack.pop() };
  num_stack.push_back( __operation( op_stack.pop(), L, R ) );
}

bool Expression::__is_valid( const std::string& raw )
{
  vector<char> op_stack { };
  vector<double> num_stack { };

  int start_idx { 0 };
  bool inside_num { false };
  bool dec_point { false };
  int par_count { 0 };

  // expression cannot begin with an operator
  if ( __operators.find( raw[0] ) != __operators.end() ) return false;

  for ( int i { -1 }; ++i < raw.length(); )
  {
    auto current { raw[i] };
    auto next { raw[i + 1] };

    if ( isdigit( current ) || current == '.' )
    {
      if ( current == '.' )
      {
        if ( !dec_point )
          dec_point = true;
        else
          return false;  // multiple decimal points in a number is invalid syntax
      }

      if ( !inside_num )
      {
        inside_num = true;
        start_idx = i;
      }

      if ( inside_num && (__operators.find( next ) != __operators.end() || next == ')' || next == '\0') )
      {
        if ( i == start_idx && current == '.' ) return false; // stray decimal point is invalid syntax

        inside_num = false;
        dec_point = false;
        num_stack.push_back( std::stod( raw.substr( start_idx, i - start_idx + 1 ) ) );
      }
      else if ( inside_num && next == '(' ) return false; // digit followed by opening paranthesis is invalid syntax
    }
    else if ( current == '(' )
    {
      // opening paranthesis not followed by a digit or another opening paranthesis is invalid syntax
      if ( !isdigit( next ) && next != '.' && next != '(' ) return false;

      op_stack.push_back( current );
      ++par_count;
    }
    else if ( current == ')' )
    {
      --par_count;
      if ( par_count < 0 ) return false;  // unpaired closing paranthesis is invalid syntax
      // closing paranthesis not followed by operator or another closing paranthesis is invalid syntax
      if ( __operators.find( next ) == __operators.end() && next != ')' && next != '\0' ) return false;

      while ( op_stack.back() != '(' )
        __process_stacks( op_stack, num_stack );

      op_stack.pop_back();  // removes the corresponding opening paranthesis 
    }
    else if ( __operators.find( current ) != __operators.end() )
    {
      // operator not followed by digit or opening paranthesis is invalid syntax
      // expression cannot end with an operator
      if ( !isdigit( next ) && next != '(' && next == '\0' ) return false;

      while ( op_stack.size() != 0 && __precedence.at( current ) <= __precedence.at( op_stack.back() ) )
        __process_stacks( op_stack, num_stack );

      op_stack.push_back( current );
    }
    else
      return false; // any character other than a digit, a decimal point, an operator or parantheses is invalid syntax
  }
  if ( par_count > 0 ) return false; // unpaired opening paranthesis is invalid syntax

  while ( op_stack.size() != 0 )
    __process_stacks( op_stack, num_stack );

  __value = num_stack.pop();
  return true;
}
