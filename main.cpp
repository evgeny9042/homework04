

#include <utility>
#include <iostream>
#include <vector>
#include <list>

// для печати контейнеров, кроме std::string 
template <typename T>
decltype(typename std::enable_if<!std::is_same<std::string, T>::value, void>::type(), 
  begin(std::declval<T>()), end(std::declval<T>()), void()) print_ip(T container)
{
  bool first = true;
  for ( auto val : container ) {
    if ( !first ) std::cout <<".";
    std::cout << val;
    first = false;
  }
  std::cout << std::endl;
};

// для печати std::string 
template <typename T>
decltype(typename std::enable_if<std::is_same<std::string, T>::value, void>::type(), 
  void()) print_ip(T container)
{
  std::cout << container.data();
}

// для печати чисел
template <typename T>
decltype(typename std::enable_if<!std::is_same<std::string, T>::value, void>::type(), 
  std::cout << std::declval<T>(), void()) print_ip(T value)
{
  unsigned int bytes = sizeof(T);
  unsigned char *c = (unsigned char *)(&value);
  c += bytes-1;
  bool first = true;
  for ( unsigned int i = 0; i < bytes; i++) {
    if ( !first ) std::cout << ".";
    printf("%d", *c);
    c--;
    first = false;
  }
  std::cout << std::endl;
};


int main(int argc, char const *argv[])
{
  print_ip(char(-1));
  print_ip(short(0));
  print_ip(int(2130706433));
  print_ip(long(8875824491850138409));
  print_ip(std::string("172.23.20.32"));
  print_ip(std::vector<int>{172, 23, 30, 75});
  print_ip(std::list<int>{172, 23, 40, 80});
	return 0;
}