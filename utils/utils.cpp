#include "utils.hpp"

void load_image(std::string image_path, int index, float image[IMAGE_SIZE][IMAGE_SIZE])
{
    // cv::Mat matrix = cv::imread(image_path, cv::IMREAD_GRAYSCALE);
    // cv::Mat converted_matrix;
    // matrix.convertTo(converted_matrix, CV_32F, 1. / 255., 0);
    // cv::MatConstIterator_<double> iter = converted_matrix.begin<double>(), end = converted_matrix.end<double>();

    // int counter = 0;
    // for (; iter != end; ++iter)
    // {
    //     image[counter / 28][counter % 28] = *iter;
    //     counter++;
    // }
    char buffer[IMAGE_BUFFER_SIZE];
    std::fstream file_stream(image_path, std::ios::in | std::ios::binary);
    file_stream.seekg(IMAGE_BUFFER_SIZE * sizeof(char) * index, std::ios::beg);
    file_stream.read(buffer, IMAGE_BUFFER_SIZE * sizeof(char));

    for (int i = 0; i < IMAGE_SIZE; i++)
    {
        for (int j = 0; j < IMAGE_SIZE; j++)
            image[i][j] = (int)(unsigned char)buffer[j + i * IMAGE_SIZE];
    }
}

std::string interpolation(std::string root, std::string type, std::string class_name)
{
    std::string path = "";

    path.append(root);
    path.append("\\");
    path.append(type);
    path.append("\\");
    path.append(class_name);
    path.append("\\data.dat");

    return path;
}

int file_count(std::string path)
{
    std::ifstream in_file(path, std::ios::binary);
    in_file.seekg(0, std::ios::end);
    int file_size = in_file.tellg();

    return file_size / IMAGE_BUFFER_SIZE;
}

//         My Functions

void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int CheckInput(int opt)
{
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        opt = -1;
    }
    return opt;
}

void start_menu_print()
{
    std::cout << "\n    ||        Main Actions      ||\n\n"
              << " 1 - Explore images from dataset \n\n"
              << " 2 - Train \n\n"
              << " 3 - Test \n\n"
              << "    ||        Extra Details     ||\n\n"
              << " 4 - Info \n\n"
              << " 5 - Testing mathematical functions \n\n"
              << " 0 - Exit \n\n"
              << ">> ";
}

void info_print()
{
    std::cout << "\n The scope of this program is to detect a number in the given image(Image should be grayscaled and in 28x28 pixels.) \n \n"
              << " Programmer: Ilya.M \n\n"
              << " Contact Email: Iliya.gbm@gmail.com \n \n"
              << " Press Enter to go back.";
}

void explore_menu_print(std::string *imgP1, std::string *imgP2)
{
    std::cout << "\n Image Path #1:   " << *imgP1 << "\n"
              << " Image Path #2:   " << *imgP2 << "\n\n"
              << " 1 - Image Path #1\n\n"
              << " 2 - Image Path #2\n\n"
              << " 3 - Reset Image Path\n\n"
              << " 0 - Return\n\n"
              << ">> ";
}

void FunctionTesting_menu_print()
{
    std::cout << "\n 1 - Average of 7 By 7 Marix\n\n"
              << " 2 - Std of 7 By 7 Matrix\n\n"
              << " 3 - Arry / Arry Distance Calculator\n\n"
            //   << " 4 - Arry / Matrix Distance Calculator\n\n"
              << " 0 - Return\n\n"
              << ">>  ";
}

void train_menu_print(float ValueP1[32], float ValueP2[32])
{
    std::cout << "\n 1 - Store Values (Pic1).\n\n"
              << " 2 - Store Values (Pic2)\n\n"
              << " 0 - Return\n\n"
              << "\n Values #1: ";

    std::cout << "\n Means:\n ";
    for (int i = 0; i < 16; i++) // MEANs pic 1
    {
        std::cout << ValueP1[i] << " ";
    }
    std::cout << "\n Stds:\n ";
    for (int i = 16; i < 32; i++) // STDs pic 1
    {
        std::cout << ValueP1[i] << " ";
    }

    std::cout << "\n\n Values #2: ";

    std::cout << "\n Means:\n ";
    for (int i = 0; i < 16; i++) // MEANs pic 2
    {
        std::cout << ValueP2[i] << " ";
    }
    std::cout << "\n Stds:\n ";
    for (int i = 16; i < 32; i++) // STDs pic 2
    {
        std::cout << ValueP2[i] << " ";
    }

    printf("\n\n>> ");
}

void explore_menu(std::string *imgP1, std::string *imgP2)
{
    int subaction;
    while (1)
    {
        clear_screen();
        explore_menu_print(&*imgP1, &*imgP2);
        //  // std::cin >> subaction;
        scanf("%d", &subaction);
        subaction = CheckInput(subaction);
        switch (subaction)
        {
        case 1:
            clear_screen();
            std::cout << " Input Image path:\n\n"
                      << ">>  ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, *imgP1);
            break;
        case 2:
            clear_screen();
            std::cout << " Input Image path:\n\n"
                      << ">>  ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, *imgP2);
            break;
        case 3:
            *imgP1 = "NULL";
            *imgP2 = "NULL";
            break;
        case 0:
            return;
        default:
            if (subaction != -1)
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
}

void train_menu(float ValuesPic1[32], float ValuesPic2[32], float img[][IMAGE_SIZE])
{
    int subaction;

    while (1)
    {
        clear_screen();
        train_menu_print(ValuesPic1, ValuesPic2);
        //  // std::cin >> subaction;
        scanf("%d", &subaction);
        subaction = CheckInput(subaction);
        switch (subaction)
        {
        case 1:
        { // LOADING TRAIN SET ( PIC #1 )
            std::string image_path = interpolation("data\\mnist", "train", "7");

            load_image(image_path, 100, img);

            for (int i = 0; i < IMAGE_SIZE; i++)
            {
                for (int j = 0; j < IMAGE_SIZE; j++)
                {
                    if (img[i][j] == 0)
                        std::cout << " ";
                    else
                    {
                        std::cout << '*';
                    }
                }
                std::cout << std::endl;
            }
            std::cin.get();
            std::cin.get();

        } // STORING VALUES INTO ARRY_#1
            Break_Down(img, ValuesPic1);
            break;
        case 2:
        { // LOADING TEST SET ( PIC #2 )
            std::string image_path = interpolation("data\\mnist", "test", "7");

            load_image(image_path, 100, img);

            for (int i = 0; i < IMAGE_SIZE; i++)
            {
                for (int j = 0; j < IMAGE_SIZE; j++)
                {
                    if (img[i][j] == 0)
                        std::cout << " ";
                    else
                    {
                        std::cout << '*';
                    }
                }
                std::cout << std::endl;
            }
            std::cin.get();
            std::cin.get();

        } // STORING VALUES INTO ARRY_#2
            Break_Down(img, ValuesPic2);
            break;
        case 0:
            return;
        default:
            if (subaction != -1)
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
}

void test_menu_print()
{
    std::cout << " Test function Incomplete\n\n"
              << " 0 - Return\n"
              << ">>  ";
}

void test_menu()
{
    int subaction;
    while (1)
    {
        clear_screen();
        test_menu_print();
        //  // std::cin >> subaction;
        scanf("%d", &subaction);
        subaction = CheckInput(subaction);
        switch (subaction)
        {
        case 0:
            return;
        default:
            if (subaction != -1)
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
}

void FunctionTesting_menu()
{
    int subaction;
    float Matrix[8][7]{0};  // LAST ROW ACTS AS TEMP ARRY
    while (1)
    {
        clear_screen();
        FunctionTesting_menu_print();
        //  // std::cin >> subaction;
        scanf("%d", &subaction);
        subaction = CheckInput(subaction);
        switch (subaction)
        {
        case 1: // Mean 7by7
            clear_screen();
            printf("\n Input 7 By 7 Matrix: \n\n");
            Input_7By7Matrix(Matrix);
            //  // std::cout << "\n Mean of matrix =  " << Mean_Matrix7by7(Matrix) << "\n";
            printf("\n Mean of matrix = %.2f", Mean_Matrix7by7(Matrix));
            std::cin.get();
            std::cin.get();
            break;
        case 2: // STD 7by7
            clear_screen();
            printf("\n Input 7 By 7 Matrix: \n\n");
            Input_7By7Matrix(Matrix);
            // std::cout << Std_Matrix7by7(Matrix, Mean_Matrix7by7(Matrix)) << "\n";
            printf("\n STD of 7 By 7 Matrix = %.2f", Std_Matrix7by7(Matrix, Mean_Matrix7by7(Matrix)));
            std::cin.get();
            std::cin.get();
            break;
        case 3: // Arry - Arry Distance Calculator
            clear_screen();
            printf("\n Input 7 elements of Array #1: ");
            Input_Arry(Matrix[7], 7);
            printf("\n Input 7 elements of Array #2: ");
            Input_Arry(Matrix[6], 7);
            printf("\n Distance: %.2f", Distance_Cal(Matrix[7], Matrix[6], 7));
            std::cin.get();
            std::cin.get();
            break;
        // case 4: // Arry - Matrix Distance Calculator
        //     clear_screen();
        //     printf("\n Input 7 elements of Array: ");
        //     Input_Arry(Matrix[7], 7);
        //     printf("\n Input 7 by 7 Matrix: \n");
        //     Input_7By7Matrix(Matrix);
        //     printf("\n Distance: %.2f", DistanceForMatrix_Cal());
        //     break;
        case 0:
            return;
        default:
            if (subaction != -1)
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
}

float Distance_Cal(float ArryA[], float ArryB[], int size)
{
    float sum{0};

    for (int i = 0; i < size; i++)
    {
        sum += pow((ArryA[i] - ArryB[i]), 2);
    }

    return sum;
}

void DistanceForMatrix_Cal(float ArryA[], float MatrixA[][IMAGE_SIZE], float DistanceArry[])
{
    for (int i = 0; i < IMAGE_SIZE; i++)
    {
        DistanceArry[i] = Distance_Cal(ArryA, MatrixA[i], IMAGE_SIZE);
    }
}

void Break_Down(float SourceMatrix[IMAGE_SIZE][IMAGE_SIZE], float Values[32])
{
    float LilSquar[7][7];
    int iSource{0}, jSource{0}, squarNum{0};

    while (squarNum < 16)
    {
        for (int i = 0; i < 7; i++)
        {
            { // FILLING LITTLE SQUAR (7by7)
                for (int j = 0; j < 7; j++)
                {
                    LilSquar[i][j] = SourceMatrix[iSource][jSource];
                    jSource++;
                }
            }
            iSource++;
            jSource -= 7;
        }
        squarNum++;

        Values[squarNum] = Mean_Matrix7by7(LilSquar);
        Values[squarNum + 16] = Std_Matrix7by7(LilSquar, Values[squarNum]);

        if (iSource >= IMAGE_SIZE)
        {
            iSource = 0;
            jSource += 7;
        }
    }
}

float Mean_Matrix7by7(float Matrix[][7])
{
    float sum{0};

    { // SUMING ALL THE ELEMENTS
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                sum += Matrix[i][j];
            }
        }
    }

    return (sum / 49.0);
}

float Std_Matrix7by7(float Matrix[][7], float Mean)
{
    float sum{0};

    { // SUMING ALL THE ELEMENTS
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                sum += pow((Matrix[i][j] - Mean), 2);
            }
        }
    }

    return sqrt(sum / 49);
}

void Input_7By7Matrix(float Matrix[][7])
{
    for (int i = 0; i < 7; i++)
    {
        printf("Row %d :  ", i + 1);
        for (int j = 0; j < 7; j++)
        {
            //  // std::cin >> Matrix[i][j];
            scanf("%f", &Matrix[i][j]);

            { // INCASE OF ACCIDENTAL INPUT
                if (std::cin.fail())
                {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    return;
                }
            }
        }
    }
}

void Input_Arry(float Arry[], int N)
{
    for (int i = 0; i < N; i++)
    {
        scanf("%f", &Arry[i]);
    }

    { // INCASE OF ACCIDENTAL INPUT
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            return;
        }
    }
}