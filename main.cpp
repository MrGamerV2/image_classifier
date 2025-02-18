// Author: Ilya.M
// Contact: Iliya.gbm@gmail.com

#include "utils\\utils.hpp"

int main()
{
    // Timer timer;

    float img[IMAGE_SIZE][IMAGE_SIZE];
    TrainSet Trainsets[10];
    int action;
    bool IsDatabaseReady{false}, IsDataTypeNum{true};
    
    while (1)
    {
        // system("color 0B");
        ClearScreen();
        StartMenu_print();
        std::cin >> action;
        action = CheckInput(action);
        switch (action)
        {
        case 1:
            ExploreMenu(img, &IsDataTypeNum);
            break;
        case 2:
            TrainMenu(Trainsets, img, &IsDatabaseReady, &IsDataTypeNum);
            break;
        case 3:
            TestMenu(Trainsets, img, &IsDatabaseReady, &IsDataTypeNum);
            break;
        case 4:
            ClearScreen();
            Info_print();
            std::cin.get();
            std::cin.ignore(10000, '\n');
            break;
        case 5:
            FunctionTesting_menu();
            break;
        case 6:
            Options(&IsDataTypeNum, &IsDatabaseReady);
            break;
        case 0:
            return 0;
        default:
            if (action != -1)
            {
                printf("!!  Wrong Input  !! \n");
                Pause();
            }
            else
            {
                printf("!!  Wrong Input  !! \n");
                std::cin.get();
            }
            break;
        }
    }
    return 0;
}
