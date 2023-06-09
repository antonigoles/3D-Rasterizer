#pragma once


namespace Engine::Tests 
{
    namespace Single 
    {
        void test1();
        void test2();
    }
    
    namespace EachFrame
    {
        void test1(float deltaTime);
        void test2(float deltaTime);
    }

    

    void run_single_tests();

    void run_each_frame_tests(float deltaTime);
}