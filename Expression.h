#ifndef __expression_h__
#define __expression_h__

#include <string>           // getline, stod, string
#include <string_view>      // string_view
#include <unordered_map>
#include <unordered_set>

class Expression
{
  template<typename T>
  class vector : public std::vector<T>
  {
    using std::vector<T>::vector;

  public:
    T pop()
    {
      T last { this->back() };
      this->pop_back();
      return last;
    }
  };

  double __value { };
  static const std::unordered_set<char> __separators;
  static const std::unordered_map<char, int> __precedence;

  bool __is_valid( const std::string& raw );
  void __process_stacks( vector<char>& op_stack, vector<double>& num_stack );

public:
  enum class Status
  {
    Valid,
    Invalid,
    Help,
    Clear,
    Back
  };
  Status flag { };

  static constexpr std::string_view new_line { "    >>> " };
  static constexpr std::string_view invalid { "    !!! Expression entered is invalid.\n\n" };

  Expression() = default;
  void get();
  double value() const;
};

#endif
