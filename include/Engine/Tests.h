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
        void test1();
    }

    

    void run_single_tests();

    void run_each_frame_tests();
}