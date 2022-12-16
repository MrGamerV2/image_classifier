// Author: Ilya.M
// Contact: Iliya.gbm@gmail.com

#include "utils\\utils.hpp"
#include "utils\\timer.hpp"

int main()
{
    Timer timer;

    std::string image_path = interpolation("data\\mnist", "train", "7");
    float img[IMAGE_SIZE][IMAGE_SIZE];

    load_image(image_path, 100, img);

    for (int i = 0; i < IMAGE_SIZE; i++)
    {
        for (int j = 0; j < IMAGE_SIZE; j++)
        {
            std::cout << img[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // system("pause");


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
            clear_screen();
            explore_menu();
            continue;
            break;
        case 2:
            clear_screen();
            train_menu();
            continue;
            break;
        case 3:
            clear_screen();
            test_menu();
            continue;
            break;
        case 4:
            clear_screen();
            info_print();
            std::cin.get();
            std::cin.ignore(10000, '\n');
            continue;
            break;
        case 0:
            return 0;
        default:
            if (action != -1)
            {
                std::cout << "!!  Wrong Input  !! \n";
                std::cin.get();
                std::cin.get();
            }
            else
            {
                std::cout << "!!  Wrong Input  !! \n";
                std::cin.get();
            }

            break;
        }
    }

    return 0;
}