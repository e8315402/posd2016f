#include "..\cppunitlite\TestHarness.h"
#include "utShapes.h"

#include <string>
#include <cstdio>
#include <iostream>

int main()
{
    TestResult tr;
    TestRegistry::runAllTests(tr);

    return 0;
}

