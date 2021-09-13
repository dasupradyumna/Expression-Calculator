#include "Expression.h"

#include <algorithm>
#include <iostream>

void process( std::string& input )
{
  for ( auto& ch : input ) ch = tolower( ch );

  auto new_length { input.length() - std::count( input.begin(), input.end(), ' ' ) };
  std::remove( input.begin(), input.end(), ' ' );
  input.resize( new_length );
}

void Expression::get()
{
  std::getline( std::cin, __raw_data, '\n' );
  process( __raw_data );

  if ( __raw_data == "back" )
    flag = Status::Back;
  else if ( __raw_data == "clear" )
    flag = Status::Clear;
  else if ( isValid() )
    flag = Status::Valid;
  else
    flag = Status::Invalid;
}

double Expression::evaluate()
{
  return 0.0;
}

bool Expression::isValid() const
{
  return false;
}
