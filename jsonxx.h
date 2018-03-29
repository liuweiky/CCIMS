#ifndef JSONXX_H
#define JSONXX_H

// -*- mode: c++; c-basic-offset: 4; -*-

// Author: Hong Jiang <hong@hjiang.net>
// Contributors:
//   Sean Middleditch <sean@middleditch.us>
//   rlyeh <https://github.com/r-lyeh>

#pragma once

#include <cstddef>
#include <cassert>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>

// jsonxx versioning: major.minor-extra where
// major = { number }
// minor = { number }
// extra = { 'a':alpha, 'b':beta, 'rc': release candidate, 'r': release, 's':stable }
#define JSONXX_MAJOR    "0"
#define JSONXX_MINOR    "22"
#define JSONXX_EXTRA    "a"
#define JSONXX_VERSION  JSONXX_MAJOR "." JSONXX_MINOR "-" JSONXX_EXTRA
#define JSONXX_XML_TAG  "<!-- generated by jsonxx " JSONXX_VERSION " -->"

#if __cplusplus > 199711L
#define JSONXX_COMPILER_HAS_CXX11 1
#elif defined(_MSC_VER) && _MSC_VER > 1700
#define JSONXX_COMPILER_HAS_CXX11 1
#else
#define JSONXX_COMPILER_HAS_CXX11 0
#endif

#ifdef _MSC_VER
// disable the C4127 warning if using VC, see http://stackoverflow.com/a/12042515
#define JSONXX_ASSERT(...) \
  do { \
    __pragma(warning(push)) __pragma(warning(disable:4127)) \
    if( jsonxx::Assertions ) \
    __pragma(warning(pop)) \
      jsonxx::assertion(__FILE__,__LINE__,#__VA_ARGS__,bool(__VA_ARGS__)); \
  __pragma(warning(push)) __pragma(warning(disable:4127)) \
  } while(0) \
  __pragma(warning(pop))
#else
#define JSONXX_ASSERT(...) do { if( jsonxx::Assertions ) \
  jsonxx::assertion(__FILE__,__LINE__,#__VA_ARGS__,bool(__VA_ARGS__)); } while(0)
#endif

namespace jsonxx {

// FIXME(hjiang): Those should really be dynamic.
// Settings
enum Settings {
  // constants
  Enabled = true,
  Disabled = false,
  Permissive = true,
  Strict = false,
  // values
  Parser = Permissive,  // permissive or strict parsing
  UnquotedKeys = Disabled, // support of unquoted keys
  Assertions = Enabled  // enabled or disabled assertions (these asserts work both in DEBUG and RELEASE builds)
};

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4127)
#endif
inline bool parser_is_strict() { return Parser == Strict; }
inline bool parser_is_permissive() { return Parser == Permissive; }
inline bool unquoted_keys_are_enabled() { return UnquotedKeys == Enabled; }
#ifdef _MSC_VER
#pragma warning(pop)
#endif

// Constants for .write() and .xml() methods
enum Format {
  JSON      = 0,     // JSON output
  JSONx     = 1,     // XML output, JSONx  format. see http://goo.gl/I3cxs
  JXML      = 2,     // XML output, JXML   format. see https://github.com/r-lyeh/JXML
  JXMLex    = 3,     // XML output, JXMLex format. see https://github.com/r-lyeh/JXMLex
  TaggedXML = 4      // XML output, tagged XML format. see https://github.com/hjiang/jsonxx/issues/12
};

// Types
typedef long double Number;
typedef bool Boolean;
typedef std::string String;
struct Null {};
class Value;
class Object;
class Array;

// Identity meta-function
template <typename T>
struct identity {
  typedef T type;
};

// Tools
bool validate( const std::string &input );
bool validate( std::istream &input );
std::string reformat( const std::string &input );
std::string reformat( std::istream &input );
std::string xml( const std::string &input, unsigned format = JSONx );
std::string xml( std::istream &input, unsigned format = JSONx );

// Detail
void assertion( const char *file, int line, const char *expression, bool result );

// A JSON Object
class Object {
 public:
  Object();
  ~Object();

  template <typename T>
  bool has(const std::string& key) const;

  // Always call has<>() first. If the key doesn't exist, consider
  // the behavior undefined.
  template <typename T>
  T& get(const std::string& key);
  template <typename T>
  const T& get(const std::string& key) const;

  template <typename T>
  const T& get(const std::string& key, const typename identity<T>::type& default_value) const;

  size_t size() const;
  bool empty() const;

  const std::map<std::string, Value*>& kv_map() const;
  std::string json() const;
  std::string xml( unsigned format = JSONx, const std::string &header = std::string(), const std::string &attrib = std::string() ) const;
  std::string write( unsigned format ) const;

  void reset();
  bool parse(std::istream &input);
  bool parse(const std::string &input);
  typedef std::map<std::string, Value*> container;
  void import( const Object &other );
  void import( const std::string &key, const Value &value );
  Object &operator<<(const Value &value);
  Object &operator<<(const Object &value);
  Object &operator=(const Object &value);
  Object(const Object &other);
  Object(const std::string &key, const Value &value);
  template<size_t N>
  Object(const char (&key)[N], const Value &value) {
    import(key,value);
  }
  template<typename T>
  Object &operator<<(const T &value);

 protected:
  static bool parse(std::istream& input, Object& object);
  container value_map_;
  std::string odd;
};

class Array {
 public:
  Array();
  ~Array();

  size_t size() const;
  bool empty() const;

  template <typename T>
  bool has(unsigned int i) const;

  template <typename T>
  T& get(unsigned int i);
  template <typename T>
  const T& get(unsigned int i) const;

  template <typename T>
  const T& get(unsigned int i, const typename identity<T>::type& default_value) const;

  const std::vector<Value*>& values() const {
    return values_;
  }
  std::string json() const;
  std::string xml( unsigned format = JSONx, const std::string &header = std::string(), const std::string &attrib = std::string() ) const;

  std::string write( unsigned format ) const { return format == JSON ? json() : xml(format); }
  void reset();
  bool parse(std::istream &input);
  bool parse(const std::string &input);
  typedef std::vector<Value*> container;
  void append(const Array &other);
  void append(const Value &value) { import(value); }
  void import(const Array &other);
  void import(const Value &value);
  Array &operator<<(const Array &other);
  Array &operator<<(const Value &value);
  Array &operator=(const Array &other);
  Array &operator=(const Value &value);
  Array(const Array &other);
  Array(const Value &value);
 protected:
  static bool parse(std::istream& input, Array& array);
  container values_;
};

// A value could be a number, an array, a string, an object, a
// boolean, or null
class Value {
 public:

  Value();
  ~Value() { reset(); }
  void reset();

  template<typename T>
  void import( const T & ) {
    reset();
    type_ = INVALID_;
    // debug
    // std::cout << "[WARN] No support for " << typeid(t).name() << std::endl;
  }
  void import( const bool &b ) {
    reset();
    type_ = BOOL_;
    bool_value_ = b;
  }
#define $number(TYPE) \
  void import( const TYPE &n ) { \
    reset(); \
    type_ = NUMBER_; \
    number_value_ = static_cast<long double>(n); \
  }
  $number( char )
  $number( int )
  $number( long )
  $number( long long )
  $number( unsigned char )
  $number( unsigned int )
  $number( unsigned long )
  $number( unsigned long long )
  $number( float )
  $number( double )
  $number( long double )
#undef $number
#if JSONXX_COMPILER_HAS_CXX11 > 0
  void import( const std::nullptr_t & ) {
    reset();
    type_ = NULL_;
  }
#endif
  void import( const Null & ) {
    reset();
    type_ = NULL_;
  }
  void import( const String &s ) {
    reset();
    type_ = STRING_;
    *( string_value_ = new String() ) = s;
  }
  void import( const Array &a ) {
    reset();
    type_ = ARRAY_;
    *( array_value_ = new Array() ) = a;
  }
  void import( const Object &o ) {
    reset();
    type_ = OBJECT_;
    *( object_value_ = new Object() ) = o;
  }
  void import( const Value &other ) {
    if (this != &other)
    switch (other.type_) {
      case NULL_:
        import( Null() );
        break;
      case BOOL_:
        import( other.bool_value_ );
        break;
      case NUMBER_:
        import( other.number_value_ );
        break;
      case STRING_:
        import( *other.string_value_ );
        break;
      case ARRAY_:
        import( *other.array_value_ );
        break;
      case OBJECT_:
        import( *other.object_value_ );
        break;
      case INVALID_:
        type_ = INVALID_;
        break;
      default:
        JSONXX_ASSERT( !"not implemented" );
    }
  }
  template<typename T>
  Value &operator <<( const T &t ) {
    import(t);
    return *this;
  }
  template<typename T>
  Value &operator =( const T &t ) {
    reset();
    import(t);
    return *this;
  }
  Value(const Value &other);
  template<typename T>
  Value( const T&t ) : type_(INVALID_) { import(t); }
  template<size_t N>
  Value( const char (&t)[N] ) : type_(INVALID_) { import( std::string(t) ); }

  bool parse(std::istream &input);
  bool parse(const std::string &input);

  template<typename T>
  bool is() const;
  template<typename T>
  T& get();
  template<typename T>
  const T& get() const;

  bool empty() const;

 public:
  enum {
    NUMBER_,
    STRING_,
    BOOL_,
    NULL_,
    ARRAY_,
    OBJECT_,
    INVALID_
  } type_;
  union {
    Number number_value_;
    String* string_value_;
    Boolean bool_value_;
    Array* array_value_;
    Object* object_value_;
  };

protected:
  static bool parse(std::istream& input, Value& value);
};

template <typename T>
bool Array::has(unsigned int i) const {
  if (i >= size()) {
    return false;
  } else {
    Value* v = values_.at(i);
    return v->is<T>();
  }
}

template <typename T>
T& Array::get(unsigned int i) {
  JSONXX_ASSERT(i < size());
  Value* v = values_.at(i);
  return v->get<T>();
}

template <typename T>
const T& Array::get(unsigned int i) const {
  JSONXX_ASSERT(i < size());
  const Value* v = values_.at(i);
  return v->get<T>();
}

template <typename T>
const T& Array::get(unsigned int i, const typename identity<T>::type& default_value) const {
  if(has<T>(i)) {
    const Value* v = values_.at(i);
    return v->get<T>();
  } else {
    return default_value;
  }
}

template <typename T>
bool Object::has(const std::string& key) const {
  container::const_iterator it(value_map_.find(key));
  return it != value_map_.end() && it->second->is<T>();
}

template <typename T>
T& Object::get(const std::string& key) {
  JSONXX_ASSERT(has<T>(key));
  return value_map_.find(key)->second->get<T>();
}

template <typename T>
const T& Object::get(const std::string& key) const {
  JSONXX_ASSERT(has<T>(key));
  return value_map_.find(key)->second->get<T>();
}

template <typename T>
const T& Object::get(const std::string& key, const typename identity<T>::type& default_value) const {
  if (has<T>(key)) {
    return value_map_.find(key)->second->get<T>();
  } else {
    return default_value;
  }
}

template<>
inline bool Value::is<Value>() const {
    return true;
}

template<>
inline bool Value::is<Null>() const {
  return type_ == NULL_;
}

template<>
inline bool Value::is<Boolean>() const {
  return type_ == BOOL_;
}

template<>
inline bool Value::is<String>() const {
  return type_ == STRING_;
}

template<>
inline bool Value::is<Number>() const {
  return type_ == NUMBER_;
}

template<>
inline bool Value::is<Array>() const {
  return type_ == ARRAY_;
}

template<>
inline bool Value::is<Object>() const {
  return type_ == OBJECT_;
}

template<>
inline Value& Value::get<Value>() {
    return *this;
}

template<>
inline const Value& Value::get<Value>() const {
    return *this;
}

template<>
inline bool& Value::get<Boolean>() {
  JSONXX_ASSERT(is<Boolean>());
  return bool_value_;
}

template<>
inline std::string& Value::get<String>() {
  JSONXX_ASSERT(is<String>());
  return *string_value_;
}

template<>
inline Number& Value::get<Number>() {
  JSONXX_ASSERT(is<Number>());
  return number_value_;
}

template<>
inline Array& Value::get<Array>() {
  JSONXX_ASSERT(is<Array>());
  return *array_value_;
}

template<>
inline Object& Value::get<Object>() {
  JSONXX_ASSERT(is<Object>());
  return *object_value_;
}

template<>
inline const Boolean& Value::get<Boolean>() const {
  JSONXX_ASSERT(is<Boolean>());
  return bool_value_;
}

template<>
inline const String& Value::get<String>() const {
  JSONXX_ASSERT(is<String>());
  return *string_value_;
}

template<>
inline const Number& Value::get<Number>() const {
  JSONXX_ASSERT(is<Number>());
  return number_value_;
}

template<>
inline const Array& Value::get<Array>() const {
  JSONXX_ASSERT(is<Array>());
  return *array_value_;
}

template<>
inline const Object& Value::get<Object>() const {
  JSONXX_ASSERT(is<Object>());
  return *object_value_;
}

template<typename T>
inline Object &Object::operator<<(const T &value) {
  return *this << Value(value), *this;
}

}  // namespace jsonxx

std::ostream& operator<<(std::ostream& stream, const jsonxx::Value& v);
std::ostream& operator<<(std::ostream& stream, const jsonxx::Object& v);
std::ostream& operator<<(std::ostream& stream, const jsonxx::Array& v);


#endif // JSONXX_H
