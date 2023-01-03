#include "utils.hpp"

void ImageLoad(std::string image_path, int index, float image[IMAGE_SIZE][IMAGE_SIZE])
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

//         PRINTING CENTER

void Info_print()
{
    std::cout << "\n The scope of this program is to detect a number in the given image(Image should be grayscaled and in 28x28 pixels.) \n \n"
              << " Programmer: Ilya.M \n\n"
              << " Contact Email: Iliya.gbm@gmail.com \n \n"
              << " Press Enter to go back.";
}

void StartMenu_print()
{
    std::cout << "\n    ||        Main Actions        ||\n\n"
              << " 1 - Explore images from dataset \n\n"
              << " 2 - Train \n\n"
              << " 3 - Test \n\n"
              << "    ||        Extra Details     ||\n\n"
              << " 4 - Info \n\n"
              << " 5 - Testing mathematical functions \n\n"
              << " 0 - Exit \n\n"
              << ">> ";
}

void ExploreMenu_print(int *Label, int *PicNum)
{
    std::cout << "\n   ||   Exploring DataSet   ||\n\n"
              << " 1 - Show Image\n\n"
              << " 2 - Label\n\n"
              << " 3 - Picture Number\n\n"
              << " 0 - Return\n\n"
              << " # Label:   " << *Label << "\n"
              << " # PicNum:  " << *PicNum << "\n\n"
              << ">> ";
}

void FunctionTesting_menu_print()
{
    std::cout << "\n   ||   Function Testing   ||\n\n"
              << " 1 - Average of 7 By 7 Marix\n\n"
              << " 2 - Std of 7 By 7 Matrix\n\n"
              << " 3 - Arry / Arry Distance Calculator\n\n"
              //   << " 4 - Arry / Matrix Distance Calculator\n\n"
              << " 0 - Return\n\n"
              << ">>  ";
}

void TrainMenu_print()
{
    std::cout << "\n   ||   Training Program   ||\n\n"
              << " 1 - Train Data Sets\n\n"
              << " 0 - Return\n\n"
              << ">>  ";
}

void TestMenu_print(int *Label, int *PicNum, float ImgFeatures[])
{
    std::cout << "\n   ||   Testing DataSet   ||\n\n"
              << " 1 - Show Image\n\n"
              << " 2 - Label\n\n"
              << " 3 - Picture Number\n\n"
              << " 4 - Test\n\n"
              << " 0 - Return\n\n"
              << " # Label:   " << *Label << "\n"
              << " # PicNum:  " << *PicNum << "\n\n";

    printf(" Image MEAN:\n ");
    for (int i = 0; i < 16; i++)
    {
        std::cout << ImgFeatures[i] << ' ';
    }
    printf("\n Image STD:\n ");
    for (int i = 0; i < 16; i++)
    {
        std::cout << ImgFeatures[i + 16] << ' ';
    }

    std::cout << "\n>> ";
}

//         MENU(S)

void ExploreMenu(float img[][IMAGE_SIZE])
{
    int Label{-1}, PicNum{-1}, filecount;
    int subaction;
    std::string image_path;

    while (1)
    {
        ClearScreen();
        ExploreMenu_print(&Label, &PicNum);
        std::cin >> subaction;
        subaction = CheckInput(subaction);
        switch (subaction)
        {
        case 1:
            if (Label == -1 || PicNum == -1)
            {
                printf("\n Please select an image first..");
                std::cin.get();
                std::cin.get();
            }
            else
            { // LOADING AND PRINTING IMAGE
                ImageLoad(image_path, PicNum, img);
                Image_print(img);

                if (PicNum < filecount)
                    ++PicNum;
            }
            break;
        case 2:
            std::cout << " Input Label (0 - 9):  ";
            std::cin.ignore(10000, '\n');
            std::cin >> Label;
            if (Label < 0 || Label > 9)
            {
                std::cout << " !! Unavailable Label !!";
                Label = -1;
                std::cin.get();
                std::cin.get();
            }
            image_path = interpolation("data\\mnist", "train", std::to_string(Label));
            filecount = file_count(image_path) - 1;
            break;
        case 3:
            if (Label == -1)
            {
                printf("\n Please Select Image Label first");
                std::cin.get();
                std::cin.get();
            }
            else
            {
                std::cout << " Input Picture Number (1 - "
                          << filecount
                          << "):  ";
                std::cin.ignore(10000, '\n');
                std::cin >> PicNum;
                if (PicNum > filecount || PicNum < 0)
                {
                    std::cout << " !! Wrong Picture Number !!";
                    PicNum = -1;
                    std::cin.get();
                    std::cin.get();
                }
            }
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

void TrainMenu(TrainSet Trainsets[], float img[][IMAGE_SIZE])
{
    int subaction;
    std::string image_path;

    while (1)
    {
        ClearScreen();
        TrainMenu_print();
        std::cin >> subaction;
        subaction = CheckInput(subaction);
        switch (subaction)
        {
        case 1:
        { // LOADING TRAIN SET

            for (int i = 0; i < 10; i++)
            {
                image_path = interpolation("data\\mnist", "train", std::to_string(i));
                Trainsets[i].Label = i;
                for (int j = 0; j < IMAGE_DATA_LIMIT; j++)
                {
                    ImageLoad(image_path, j, img);
                    BreakDown(img, Trainsets[i].imgs[j]);
                }
            }
            break;
        }
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

void TestMenu(float img[IMAGE_SIZE][IMAGE_SIZE])
{
    int subaction;
    int Label{-1}, PicNum{-1}, filecount;
    std::string image_path{""};
    float ImageFeatures[32]{0};

    while (1)
    {
        ClearScreen();
        TestMenu_print(&Label, &PicNum, ImageFeatures);
        std::cin >> subaction;
        subaction = CheckInput(subaction);
        switch (subaction)
        {
        case 1:
            if (Label == -1 || PicNum == -1)
            {
                printf("\n Please select an image first..");
                std::cin.get();
                std::cin.get();
            }
            else
            { // LOADING AND PRINTING IMAGE
                Image_print(img);
            }
            break;
        case 2:
            std::cout << " Input Label (0 - 9):  ";
            std::cin.ignore(10000, '\n');
            std::cin >> Label;
            if (Label < 0 || Label > 9)
            {
                std::cout << " !! Unavailable Label !!";
                Label = -1;
                std::cin.get();
                std::cin.get();
            }
            image_path = interpolation("data\\mnist", "train", std::to_string(Label));
            filecount = file_count(image_path) - 1;
            break;
        case 3:
            if (Label == -1)
            {
                printf("\n Please Select Image Label first");
                std::cin.get();
                std::cin.get();
            }
            else
            {
                std::cout << " Input Picture Number (1 - "
                          << filecount
                          << "):  ";
                std::cin.ignore(10000, '\n');
                std::cin >> PicNum;
                if (PicNum > filecount || PicNum < 0)
                {
                    std::cout << " !! Wrong Picture Number !!";
                    PicNum = -1;
                    std::cin.get();
                    std::cin.get();
                }
                else
                    ImageLoad(image_path, PicNum, img);
            }
            break;
        case 4:
            if (Label == -1 || PicNum == -1)
            {
                printf("\n Please select an image first..");
                std::cin.get();
                std::cin.get();
            }
            else
            {
                BreakDown(img, ImageFeatures);
            }
            break;
        case 0:
            return;
            break;
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
    float Matrix[8][7]{0}; // LAST ROW ACTS AS TEMP ARRY
    while (1)
    {
        ClearScreen();
        FunctionTesting_menu_print();
        std::cin >> subaction;
        subaction = CheckInput(subaction);
        switch (subaction)
        {
        case 1: // Mean 7by7
            ClearScreen();
            printf("\n Input 7 By 7 Matrix: \n\n");
            Matrix7squar_loader(Matrix);
            //  // std::cout << "\n Mean of matrix =  " << Matrix7squar_mean(Matrix) << "\n";
            printf("\n Mean of matrix = %.2f", Matrix7squar_mean(Matrix));
            std::cin.get();
            std::cin.get();
            break;
        case 2: // STD 7by7
            ClearScreen();
            printf("\n Input 7 By 7 Matrix: \n\n");
            Matrix7squar_loader(Matrix);
            // std::cout << Matrix7squar_std(Matrix, Matrix7squar_mean(Matrix)) << "\n";
            printf("\n STD of 7 By 7 Matrix = %.2f", Matrix7squar_std(Matrix, Matrix7squar_mean(Matrix)));
            std::cin.get();
            std::cin.get();
            break;
        case 3: // Arry - Arry Distance Calculator
            ClearScreen();
            printf("\n Input 7 elements of Array #1: ");
            Array_loader(Matrix[7], 7);
            printf("\n Input 7 elements of Array #2: ");
            Array_loader(Matrix[6], 7);
            printf("\n Distance: %.2f", DistanceCalculator(Matrix[7], Matrix[6], 7));
            std::cin.get();
            std::cin.get();
            break;
        // case 4: // Arry - Matrix Distance Calculator
        //     ClearScreen();
        //     printf("\n Input 7 elements of Array: ");
        //     Array_loader(Matrix[7], 7);
        //     printf("\n Input 7 by 7 Matrix: \n");
        //     Matrix7squar_loader(Matrix);
        //     printf("\n Distance: %.2f", MatrixDistanceCalculator());
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

//         FUNCTIONS

void Image_print(float img[][IMAGE_SIZE])
{
    for (int i = 0; i < IMAGE_SIZE; i++)
    {
        for (int j = 0; j < IMAGE_SIZE; j++)
        {
            if (img[i][j] == 0)
                std::cout << ".";
            else
            {
                std::cout << '#';
            }
        }
        std::cout << std::endl;
    }
    std::cin.get();
    std::cin.get();
}

void ClearScreen()
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

float DistanceCalculator(float ArryA[], float ArryB[], int size)
{
    float sum{0};

    for (int i = 0; i < size; i++)
    {
        sum += pow((ArryA[i] - ArryB[i]), 2);
    }

    return sum;
}

void MatrixDistanceCalculator(float ArryA[], float MatrixA[][IMAGE_SIZE], float DistanceArry[])
{
    for (int i = 0; i < IMAGE_SIZE; i++)
    {
        DistanceArry[i] = DistanceCalculator(ArryA, MatrixA[i], IMAGE_SIZE);
    }
}

void BreakDown(float SourceMatrix[IMAGE_SIZE][IMAGE_SIZE], float Values[32])
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

        Values[squarNum] = Matrix7squar_mean(LilSquar);
        Values[squarNum + 16] = Matrix7squar_std(LilSquar, Values[squarNum]);

        if (iSource >= IMAGE_SIZE)
        {
            iSource = 0;
            jSource += 7;
        }
    }
}

float Matrix7squar_mean(float Matrix[][7])
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

float Matrix7squar_std(float Matrix[][7], float Mean)
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

void Matrix7squar_loader(float Matrix[][7])
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

void Array_loader(float Arry[], int N)
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