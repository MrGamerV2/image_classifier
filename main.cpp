// Author: Ilya.M
// Contact: Iliya.gbm@gmail.com

#include "utils\\utils.hpp"
#include "utils\\timer.hpp"

int main()
{
    Timer timer;
    std::string ImagePath1{"NULL"}, ImagePath2{"NULL"};

    float img[IMAGE_SIZE][IMAGE_SIZE];
    float ValuesPic1[32]{0}, ValuesPic2[32]{0};
    int action;
    while (1)
    {
        // system("color B0");
        clear_screen();
        start_menu_print();
        std::cin >> action;
        action = CheckInput(action);
        switch (action)
        {
        case 1:
            explore_menu(&ImagePath1, &ImagePath2);
            break;
        case 2:
            train_menu(ValuesPic1, ValuesPic2, img);
            break;
        case 3:
            test_menu();
            break;
        case 4:
            clear_screen();
            info_print();
            std::cin.get();
            std::cin.ignore(10000, '\n');
            break;
        case 5:
            FunctionTesting_menu();
            break;
        case 0:
            return 0;
        default:
            if (action != -1)
            {
                //  // std::cout << "!!  Wrong Input  !! \n";
                printf("!!  Wrong Input  !! \n");
                std::cin.get();
                std::cin.get();
            }
            else
            {
                //  // std::cout << "!!  Wrong Input  !! \n";
                printf("!!  Wrong Input  !! \n");
                std::cin.get();
            }

            break;
        }
    }

    return 0;
}