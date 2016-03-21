#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#ifdef ITSC
    extern "C" {
#endif
#include "uthreads.h"
#ifdef ITSC
    }
#endif


#include <iostream>

void f (void)
{
    int tid = uthread_get_tid();
    int i = 1;
    while(1)
    {
        std::cout << "in func f" << std::endl;
        if(i == uthread_get_quantums(tid))
        {
            std::cout << "f" << tid << " Quanta:" <<  i << std::endl;
            if (i == 5)
            {
                std::cout << "f END" << std::endl;
                uthread_terminate(tid);
            }
            i++;
        }

    }
}

void g (void)
{
    int tid = uthread_get_tid();
    int i = 1;
    while(1)
    {
        std::cout << "in func g" << std::endl;
        if(i == uthread_get_quantums(tid))
        {
            std::cout << "g" << tid << " Quanta:" <<  i << std::endl;
            if (i == 5)
            {
                std::cout << "g END" << std::endl;
                uthread_terminate(tid);
            }
            i++;
        }

    }
}


int main(void)
{
    try
    {
        uthread_init(100);
        int tid = uthread_get_tid();
        int i = 1;
        std::cout << "Thread:m Number:(0) " << tid << std::endl;
        std::cout << "Init Quantum num is: " << uthread_get_total_quantums() << std::endl;
        while(1)
        {
//            std::cout << "i = " << i << std::endl; // todo dbg
            if(i == uthread_get_quantums(tid))
            {
                std::cout << "m" << tid << " Quanta:" <<  i << std::endl;
                if (i == 3)
                {
                    std::cout << "m spawns f at (1) " << uthread_spawn(f) << std::endl;
                    std::cout << "m spawns g at (2) " << uthread_spawn(g) << std::endl;
                }
                if (i == 10)
                {
                    std::cout << "Total Quantums: " << uthread_get_total_quantums() << std::endl;
                    uthread_terminate(tid);
                }
                i++;
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cout << "Catched The Following Excpetion: \n" << e.what() << std::endl;
    }

}

#pragma clang diagnostic pop