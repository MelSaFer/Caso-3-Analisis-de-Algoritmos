#ifndef OBSERVERPATTERN
#define OBSERVERPATTERN

#include "Path.h"

class Observer {
public:
  virtual ~Observer(){};
  virtual void update(void* element, vector<Path*> pPaths) = 0;
};

class Subject {
public:
  virtual ~Subject(){};
  virtual int getClassId() = 0;
  virtual void attach(Observer *observer) = 0;
  virtual void detach(Observer *observer) = 0;
  virtual void notify(void* element, vector<Path*> pPaths) = 0;
  
};




#endif