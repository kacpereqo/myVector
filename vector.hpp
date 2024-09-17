

#include <iterator>
#include <memory>
#include <version>

template <class T, class Allocator> class Vector {
public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using difference_type = std::ptrdiff_t;
  using size_type = std::size_t;
  using allocator_type = Allocator;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;
  using iterator = T *;
  using const_iterator = const T *;

#if defined(POST_CXX11)
  using const_pointer = std::allocator_traits<Allocator>::const_pointer;
  using pointer = std::allocator_traits<Allocator>::pointer;
#else
  using pointer = typename Allocator::pointer;
  using const_pointer = typename Allocator::const_pointer;
#endif

  // Member functions

  Vector();
  ~Vector();

  Vector &operator=(const Vector &other);
  void assign(size_type count, const T &value);

#if defined(POST_CXX23)
  void assign_range();
#endif

  allocator_type get_allocator() const;

  // Element access

  reference at(size_type pos);
  const_reference at(size_type pos) const;

  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;

  reference front();
  const_reference front() const;

  reference back();
  const_reference back() const;

  T *data() noexcept;
  const T *data() const noexcept;

  // Iterators

  iterator begin() noexcept;
  const_iterator begin() const noexcept;

  iterator end() noexcept;
  const_iterator end() const noexcept;

  reverse_iterator rbegin() noexcept;
  const_reverse_iterator rbegin() const noexcept;

  reverse_iterator rend() noexcept;
  const_reverse_iterator rend() const noexcept;

  // Capacity

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  void reserve(size_type new_cap);
  size_type capacity() const noexcept;
  void shrink_to_fit();

  // Modifiers

  void clear() noexcept;

  iterator insert(const_iterator pos, const T &value);
  iterator insert(const_iterator pos, T &&value);
  iterator insert(const_iterator pos, size_type count, const T &value);

  template <class InputIt>
  iterator insert(const_iterator pos, InputIt first, InputIt last);
  iterator insert(const_iterator pos, std::initializer_list<T> ilist);

#if defined(POST_CXX23)

  template <container - compatibile - range<T> R>
  iterator insert(const_iterator pos, R &&range);
#endif

  template <class... Args> iterator emplace(const_iterator pos, Args &&...args);

  iterator erase(const_iterator pos);
  iterator erase(const_iterator first, const_iterator last);

  void push_back(const T &value);
  void push_back(T &&value);

  template <class... Args> void emplace_back(Args &&...args);

  void pop_back();

  void resize(size_type count);
  void resize(size_type count, const T &value);

  void swap(Vector &other);

  // Non-member functions

  friend bool operator==(const Vector &lhs, const Vector &rhs);
  friend bool operator!=(const Vector &lhs, const Vector &rhs);
  friend bool operator<(const Vector &lhs, const Vector &rhs);
  friend bool operator<=(const Vector &lhs, const Vector &rhs);
  friend bool operator>(const Vector &lhs, const Vector &rhs);
  friend bool operator>=(const Vector &lhs, const Vector &rhs);
#if defined(POST_CXX20)
  friend bool operator<=>(const Vector &lhs, const Vector &rhs);
#endif
};

template <class T, class Allocator>
void swap(Vector<T, Allocator> &lhs, Vector<T, Allocator> &rhs);

template <class T, class Allocator, class U>
size_t erase_if(Vector<T, Allocator> &c, const U &value);
