#ifndef OBSERVERPATTERN
#define OBSERVERPATTERN

class Observer {
public:
  virtual ~Observer(){};
  virtual void update(void* pElement) = 0;
};

class Subject {
public:
  virtual ~Subject(){};
  virtual int getClassId() = 0;
  virtual void attach(Observer *observer) = 0;
  virtual void detach(Observer *observer) = 0;
  virtual void notify(void* element) = 0;
  
};

#endif