#include "unise/factory.h"

namespace unise
{

BaseClassMap& g_factory_map()
{
    static BaseClassMap factory_map;
    return factory_map;
}

}  // namespace unise
