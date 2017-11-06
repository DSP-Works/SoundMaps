#ifndef SINGLETON_H
#define SINGLETON_H

#include <QtGlobal>
#include <QScopedPointer>
#include "call_once.h"

template <class T>
class Singleton
{
private:
  typedef T* (*CreateInstanceFunction)();
public:
  static T* instance(CreateInstanceFunction create);
private:
  static void init();

  Singleton();
  ~Singleton();
  Q_DISABLE_COPY(Singleton)
  static QBasicAtomicPointer<T* (void)> create;
  static QBasicAtomicInt flag;
  static QBasicAtomicPointer<void> tptr;
  bool inited;
};

template <class T>
T* Singleton<T>::instance(CreateInstanceFunction create)
{
  Singleton::create.store(create);
  qCallOnce(init, flag);
  return (T*)tptr.load();
}

template <class T>
void Singleton<T>::init()
{
  static Singleton singleton;
  if (singleton.inited) {
    CreateInstanceFunction createFunction = (CreateInstanceFunction)Singleton::create.load();
    tptr.store(createFunction());
  }
}

template <class T>
Singleton<T>::Singleton() {
  inited = true;
};

template <class T>
Singleton<T>::~Singleton() {
  T* createdTptr = (T*)tptr.fetchAndStoreOrdered(nullptr);
  if (createdTptr) {
    delete createdTptr;
  }
  create.store(nullptr);
}

template<class T> QBasicAtomicPointer<T* (void)> Singleton<T>::create = Q_BASIC_ATOMIC_INITIALIZER(nullptr);
template<class T> QBasicAtomicInt Singleton<T>::flag = Q_BASIC_ATOMIC_INITIALIZER(CallOnce::CO_Request);
template<class T> QBasicAtomicPointer<void> Singleton<T>::tptr = Q_BASIC_ATOMIC_INITIALIZER(nullptr);


#define ENABLE_SINGLETONE(Class) \
    static Class* createInstance() { return new Class(); } \
    Class* singletone() { return Singleton<Class>::instance(Class::createInstance); }


#define ENABLE_QML_SINGLETONE(Class) \
    static Class* createInstance() { return new Class(); } \
    Class* qmlSingleton(QQmlEngine* engine, QJSEngine *scriptEngine) { \
        Q_UNUSED(engine) \
        Q_UNUSED(scriptEngine) \
        return Singleton<Class>::instance(Class::createInstance); }


#define SINGLETON_CREATOR(Class)  static Class* createInstance() { return new Class(); }
#define SINGLETON_INSTANCE(Class) Singleton<Class>::instance(Class::createInstance)

#endif // SINGLETON_H