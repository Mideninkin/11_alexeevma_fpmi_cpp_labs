#include <iostream>
#include "vector_impl.h"

std::ostream& operator<<(std::ostream& outstr, const Vector& vector)
{
    outstr << "[";
    for (size_t k = 0; k < vector.Size(); k++)
    {
    outstr << vector[k];
        if (k < vector.Size() - 1)
        {
            outstr << ", ";
        }
    }
    outstr << "]";
    return outstr;
}
