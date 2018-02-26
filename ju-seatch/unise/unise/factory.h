// Usage:
//     class BaseClass {  // base class
//       ...
//     };
//     REGISTER_FACTORY(BaseClass);
//     #define REGISTER_BASECLASS(name) REGISTER_CLASS(BaseClass, name)
//
//     class Sub1 : public BaseClass {
//       ...
//     };
//     REGISTER_BASE(Sub1);
//     class Sub2 : public BaseClass {
//       ...
//     };
//     REGISTER_BASE(Sub2);
//
// Note that REGISTER_BASE(sub1) should be put in cc file instead of h file,
// to avoid multi-declaration error when compile.
//
// Then you could get a new object of the sub class by:
//    Base *obj = BaseClassFactory::get_instance("Sub1");
// or get a get_singleton object of the sub class by:
//    Base* obj = BaseClassFactory::get_singleton("Sub1");
//
// This is convenient when you need decide the class at runtime or by flag:
//    string name = "Sub1";
//    if (...)
//      name = "Sub2";
//    Base *obj = BaseClassFactory::get_instance(name);
//
// If there should be only one instance in the program by desgin,
// get_uniq_instance could be used:
//    Base *obj = BaseClassFactory::get_uniq_instance();

#ifndef UNISE_FACTORY_H_
#define UNISE_FACTORY_H_

#include <map>
#include <string>
#include "unise/singleton.h"

namespace unise
{

/// @brief Like boost any but no type check on any_cast
class Any
{
public:
    Any() : _var_ptr(NULL) {}

    template<typename T>
    Any(const T &value) : _var_ptr(new Type<T>(value)) {}

    Any(const Any &other) : _var_ptr(other._var_ptr ? other._var_ptr->clone() : NULL) {}

    ~Any() {
        delete _var_ptr;
    }

    template<typename T>
    T *any_cast() {
        return _var_ptr ? &static_cast<Type<T> *>(_var_ptr)->_var : NULL;
    }

private:
    /// @brief Interface class to hold all types
    class Typeless
    {
    public:
        virtual ~Typeless() {}
        virtual Typeless *clone() const = 0;
    };

    /// @brief Type calss template to hold a specific type
    template<typename T>
    class Type : public Typeless
    {
    public:
        explicit Type(const T &value) : _var(value) {}
        virtual Typeless *clone() const {
            return new Type(_var);
        }
        T _var;             ///< The real variable of a specific type
    };
    Typeless *_var_ptr;     ///< Typeless variable pointer
};

/// @brief Concrete object factory `interface`
struct ConcreteFactory {
    typedef Any(*FactoryIntf)();
    FactoryIntf  get_instance;      ///< Function pointer to get instance
    FactoryIntf  get_singleton;     ///< Function pointer to get singleton
};

/// @note The use of a POD struct instead of an overridable class interface
/// makes map destruction safer and easier.
typedef std::map<std::string, ConcreteFactory> FactoryMap;
typedef std::map<std::string, FactoryMap> BaseClassMap;

/// @brief The use of a function instead of a global variable makes
/// construction safer. Because we are using __attribute__((constructor)).
BaseClassMap& g_factory_map();
}  // namespace unise

/// @brief Define an abstract factory for base_class, which uses
/// the global concrete object factory map to produce objects.
#define REGISTER_FACTORY(base_class) \
    class base_class ## Factory { \
        typedef ::unise::Any Any; \
        typedef ::unise::FactoryMap FactoryMap; \
    public: \
        static base_class *get_instance(const ::std::string &name) { \
            FactoryMap &map = ::unise::g_factory_map()[#base_class]; \
            FactoryMap::iterator iter = map.find(name); \
            if (iter == map.end()) { \
                return NULL; \
            } \
            Any object = iter->second.get_instance(); \
            return *(object.any_cast<base_class*>()); \
        } \
        static base_class* get_singleton(const ::std::string& name) { \
            FactoryMap& map = ::unise::g_factory_map()[#base_class]; \
            FactoryMap::iterator iter = map.find(name); \
            if (iter == map.end()) { \
                return NULL; \
            }\
            Any object = iter->second.get_singleton(); \
            return *(object.any_cast<base_class*>()); \
        } \
        static const ::std::string get_uniq_instance_name() { \
            FactoryMap &map = ::unise::g_factory_map()[#base_class]; \
            if (map.empty() || map.size() != 1) { \
                return ""; \
            } \
            return map.begin()->first; \
        } \
        static base_class *get_uniq_instance() { \
            FactoryMap &map = ::unise::g_factory_map()[#base_class]; \
            if (map.empty() || map.size() != 1) { \
                return NULL; \
            } \
            Any object = map.begin()->second.get_instance(); \
            return *(object.any_cast<base_class*>()); \
        } \
        static bool is_valid(const ::std::string &name) { \
            FactoryMap &map = ::unise::g_factory_map()[#base_class]; \
            return map.find(name) != map.end(); \
        } \
    }; \
 
/// @brief Define a concrete object factory for sub_calss, and register it to
/// the base_class entry in global object factory map, on application
/// start.
#define REGISTER_CLASS(base_class, sub_class) \
    namespace { \
    ::unise::Any sub_class##get_instance() { \
        return ::unise::Any(new sub_class()); \
    } \
    ::unise::Any sub_class##get_singleton() { \
        return ::unise::Any(::unise::Singleton<sub_class>::get()); \
    } \
    __attribute__((constructor)) void register_factory_##sub_class() { \
        ::unise::FactoryMap &map = ::unise::g_factory_map()[#base_class]; \
        if (map.find(#sub_class) == map.end()) { \
            ::unise::ConcreteFactory factory = {&sub_class##get_instance, \
                                                 &sub_class##get_singleton}; \
            map[#sub_class] = factory; \
        } \
    } \
    }

#endif
