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
    std::cout << " Choose an action: \n \n"
              << "    ||        Main Actions      ||\n\n"
              << " 1 - Explore images from dataset \n\n"
              << " 2 - Train \n\n"
              << " 3 - Test \n\n"
              << "    ||        Extra Details     ||\n\n"
              << " 4 - Info \n\n"
              << " 0 - Exit \n\n"
              << ">>  ";
}

void info_print()
{
    std::cout << " The scope of this program is to detect a number in the given image(Image should be grayscaled and in 28x28 pixels.) \n \n"
              << " Programmer: Ilya.M \n"
              << " Contact Email: Iliya.gbm@gmail.com \n \n"
              << " Press Enter to go back.";
}

void explore_menu_print()
{
    std::cout << " Explore function Incomplete\n\n"
              << " 0 - Return\n\n"
              << ">>  ";
}

void explore_menu()
{
    int subaction;
    while (1)
    {
        clear_screen();
        explore_menu_print();
        std::cin >> subaction;
        subaction = CheckInput(subaction);
        switch (subaction)
        {
        case 0:
            return;
        default:
            if (subaction != -1)
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
}

void train_menu_print()
{
    std::cout << " Train function Incomplete\n\n"
              << " 0 - Return\n"
              << ">>  ";
}
void train_menu()
{
    int subaction;
    while (1)
    {
        clear_screen();
        train_menu_print();
        std::cin >> subaction;
        subaction = CheckInput(subaction);
        switch (subaction)
        {
        case 0:
            return;
        default:
            if (subaction != -1)
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
        std::cin >> subaction;
        subaction = CheckInput(subaction);
        switch (subaction)
        {
        case 0:
            return;
        default:
            if (subaction != -1)
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
}

float Distance_Cal(float ArryA[], float ArryB[]) //--
{
    float sum{0};

    for (int i = 0; i < IMAGE_SIZE; i++)
    {
        sum += (ArryA[i] - ArryB[i]) * (ArryA[i] - ArryB[i]);
    }

    return sum;
}

void DistanceForMatrix_Cal(float ArryA[], float MatrixA[][IMAGE_SIZE], float DistanceArry[])
{
    for (int i = 0; i < IMAGE_SIZE; i++)
    {
        DistanceArry[i] = Distance_Cal(ArryA, MatrixA[i]);
    }
}

void Break_Down(float SourceMatrix[IMAGE_SIZE][IMAGE_SIZE], float Values[32])
{
    float LilSquar[2][2];
    int iSource{0}, jSource{0};

    while (jSource <= IMAGE_SIZE)
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                LilSquar[i][j] = SourceMatrix[iSource][jSource];
                jSource++;
            }
            iSource++;
            jSource -= 2;
        }
    }
}