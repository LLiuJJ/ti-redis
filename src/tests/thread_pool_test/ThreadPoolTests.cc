#include <tiredis/ThreadPool.h>
#include <gtest/gtest.h>
#include <iostream>

void funHelloA() {
    for (int i = 0; i < 5; i ++){
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "have fun from A " << i << std::endl;
    }
}

void funHelloB() {
    for (int i = 0; i < 5; i ++){
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "have fun from B " << i << std::endl;
    }
}

TEST(ThreadPoolTests, ExecuteTask)
{
    ThreadPool::Instance().ExecuteTask(funHelloA);
    ThreadPool::Instance().ExecuteTask(funHelloB);
}
