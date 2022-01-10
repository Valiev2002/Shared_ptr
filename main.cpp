#include <iostream>
#include <atomic>
template <typename T>
class SharedPtr {
 private:
  T*a;
  T *count;
 public:
  SharedPtr() {a= nullptr;
    count =nullptr;}


  SharedPtr(T* ptr)
  {
    a =ptr;
    count =new T(1);
  }


  SharedPtr(const SharedPtr& r) {
    count = r.count;
    a = r.a;
  }


  SharedPtr(SharedPtr&& r) {
    a=r.a;
    count =r.count;
    delete r;
  }

  ~SharedPtr(){
    if (count) {
      if (*count == 1) {
        delete count;
        delete a;
      }
      else (*count)--;
    }
  }

  auto operator=(const SharedPtr& r) -> SharedPtr& {
    if (this != &r) {
      if (count) {
        if (*count == 1) {
          delete count;
          delete a;
        }
        else (*count)--;
      }

      a = r.a;
      count = r.count;
      (*count)++;
    }
    return *this; }
  auto operator=(SharedPtr&& r) -> SharedPtr& {
    a=r.a;
    return a ; }

  // проверяет, указывает ли указатель на объект
  operator bool() const {
    if(a==nullptr)
      return false;
    else
      return true;}
  auto operator*() const -> T& { return *a; }
  auto operator->() const -> T* { return *a; }

  auto get() -> T* {
    return a;
  }

  void reset() {
    if (a)
      *a=0;

  }

  void reset(T* ptr) {
    a=ptr;
  }

  void swap(SharedPtr& r)
  {
    if (a!= nullptr){
      a=r.a;
      count = r.count;
      count = a;
    }
  }
  // возвращает количество объектов SharedPtr,
  // которые ссылаются на тот жеуправляемый объект
  auto use_count() const -> size_t {
    if(count !=nullptr)
      return count;
    else
      return 0;
  }
};


int main() {
  // beginning
  SharedPtr<int>pointer =new int (5);
  std::cout<<"First pointer: "<<*pointer<<std::endl;
  SharedPtr<int>pointer2 = new int (7);
  std::cout<<"Second pointer: "<<*pointer2<<std::endl;
  //swap
  pointer2.swap(pointer);
  std::cout<<"After swapping"<<std::endl;
  std::cout <<"First pointer: "<<*pointer<<std::endl;
  std::cout <<"Second pointer: "<<*pointer2<<std::endl;
  //get
  int* point =new int (10);
  SharedPtr<int> point2(point);
  if(point2.get() ==point)
    std::cout <<"Pointers point to the same location: "<<*point2.get()<<std::endl;
  //reset
  SharedPtr<int>pointer_reset = new int(2);
  pointer_reset.reset();
  std::cout<<"After reset: "<<*pointer_reset<<std::endl;
  SharedPtr<int>sp = new int(2);
  //reset 2
  sp.reset(new int);
  *sp = 20;
  std::cout<<"Reset to pointer: "<<*sp<<std::endl;
}