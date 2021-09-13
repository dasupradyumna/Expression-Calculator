#ifndef __expression_h__
#define __expression_h__

#include <string>
#include <string_view>

class Expression
{
  std::string __raw_data {};

public:
  enum class Status
  {
    Valid,
    Invalid,
    Clear,
    Back
  };
  Status flag {};

  static constexpr std::string_view new_line { "    >>> " };
  static constexpr std::string_view invalid { "    !!! Expression entered is invalid.\n\n" };

  Expression() = default;
  void get();
  bool isValid() const;
  double evaluate();
};

#endif
