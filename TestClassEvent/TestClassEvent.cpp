#include <iostream>
#include "ClassEvent.h"

class TestClass1
{
public:
    void TestPrint(std::string _str)
    {
        std::cout << "Event1 Print : " << _str << std::endl;
    }
};

class TestClass2
{
public:
    void TestPrint(std::string _str)
    {
        std::cout << "Event2 Print : " << _str << std::endl;
    }
};

int main()
{
    TestClass1 _testClass1;
    TestClass2 _testClass2;

    // Event Instance Case 1
    ClassEvent<void(std::string)> _testEvent1;
    // Set Event Case 1
    (_testEvent1 = (&TestClass1::TestPrint)) = (&_testClass1);
    
    //Event Instance Case 2
    ClassEvent<std::function<void(std::string)>> _testEvent2;
    // Set Event Case 2
    _testEvent2.SetEvent(&_testClass2, &TestClass2::TestPrint);

    std::string _inStr = "";
    while (true)
    {
        std::cin >> _inStr;
        // Call Event1
        _testEvent1(_inStr);
        // Call Event2
        _testEvent2(_inStr);

        if (_inStr == "exit")
        {
            break;
        }
    }
    return 0;
}
