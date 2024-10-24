//这段代码是一个简单的 C++ 单元测试，使用了 CppUnit 测试框架
#include <iostream>
#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

//继承自 CppUnit 的 TestCase 类的新测试类 Test，其中包含了一个测试方法 testHelloWorld()。
class Test : public CPPUNIT_NS::TestCase
{
  //CPPUNIT_TEST_SUITE(Test); 和 CPPUNIT_TEST_SUITE_END(); 宏用于声明要执行的测试方法。
  CPPUNIT_TEST_SUITE(Test);
  //CPPUNIT_TEST(testHelloWorld); 宏注册了 testHelloWorld 方法作为单元测试。
  CPPUNIT_TEST(testHelloWorld);
  CPPUNIT_TEST_SUITE_END();

public:
 //setUp() 和 tearDown() 方法在每个测试之前和之后运行，分别用于测试环境的初始化和清理
 void setUp(void) {}
 void tearDown(void) {}
protected:
 //testHelloWorld() 使用系统调用来执行编译好的 hello 程序，并将输出重定向到 nul（Unix/Linux 系统上应该是 /dev/null），意味着忽略了程序的标准输出和标准错误输出。
 void testHelloWorld(void) {
 system("./hello >nul 2>nul");
 }
};
//CPPUNIT_TEST_SUITE_REGISTRATION(Test); 宏将 Test 类中的测试添加到全局测试注册表中，以便可以自动运行。
CPPUNIT_TEST_SUITE_REGISTRATION(Test);

int main()

{
  //创建了一个 TestResult 对象，作为测试事件（如测试开始/结束、断言失败等）的控制器。
  CPPUNIT_NS::TestResult controller;

  //创建了一个 TestResultCollector 对象，用于收集测试结果。
  CPPUNIT_NS::TestResultCollector result;
  controller.addListener(&result);
  //创建了一个 BriefTestProgressListener 对象，监听测试进度并提供实时反馈。
  CPPUNIT_NS::BriefTestProgressListener progress;

  //controller.addListener(&result) 和 controller.addListener(&progress) 分别将结果收集器和进度监听器添加到控制器上。
  controller.addListener(&progress);

  //创建了一个 TestRunner 对象，并从全局测试注册表中获取所有测试，然后执行它们。
  CPPUNIT_NS::TestRunner runner;
  runner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
  runner.run(controller);
  
  //根据测试是否成功（通过了所有断言），返回相应的退出代码（成功为 0，失败为 1）
  return result.wasSuccessful() ? 0 : 1;
}
