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

std::string interpolation(std::string root, std::string type, int class_name)
{
    std::string path = "";

    path.append(root);
    path.append("\\");
    path.append(type);
    path.append("\\");
    path.append(std::to_string(class_name));
    path.append("\\data.dat");

    return path;
}

int file_count(std::string path)
{
    std::ifstream in_file(path, std::ios::binary);
    in_file.seekg(0, std::ios::end);
    int file_size = in_file.tellg();

    return (file_size / IMAGE_BUFFER_SIZE) - 1;
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

void TestMenu_print(int *Label, int *PicNum, float ImgFeatures[], int *KNearest)
{
    std::cout << "\n   ||   Testing Data Set   ||\n\n"
              << " 1 - Show Image\n\n"
              << " 2 - Label\n\n"
              << " 3 - Picture Number\n\n"
              << " 4 - K Nearest\n\n"
              << " 5 - Test\n\n"
              << " 0 - Return\n\n"
              << " # Label        : " << *Label << "\n"
              << " # PicNum       : " << *PicNum << "\n"
              << " # K Nearest    : " << *KNearest << "\n"
              << "\n>> ";
}

//         MENU(S)

void ExploreMenu(float img[][IMAGE_SIZE])
{
    int Label{-1}, PicNum{-1}, filecount;
    int subaction, temp;
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
                Pause();
            }
            else
            { // LOADING AND PRINTING IMAGE
                ImageLoad(image_path, PicNum, img);
                Image_print(img);

                if (PicNum < filecount)
                    ++PicNum;
            }
            break;
        case 2: // LABEL INPUT
            std::cout << " Input Label (0 - 9):  ";
            std::cin.ignore(10000, '\n');
            std::cin >> temp;
            if (temp < 0 || temp > 9)
            {
                std::cout << "\t!! Unavailable Label !!";
                Pause();
                break;
            }
            Label = temp;
            image_path = interpolation("data\\mnist", "train", Label);
            filecount = file_count(image_path) - 1;
            PicNum = -1;
            break;
        case 3: // PICNUM INPUT
            if (Label == -1)
            {
                printf("\n Please Select Image Label first");
                Pause();
            }
            else
            {
                std::cout << " Input Picture Number (0 - "
                          << filecount
                          << "):  ";
                std::cin.ignore(10000, '\n');
                std::cin >> temp;
                if (temp > filecount || temp < 0)
                {
                    std::cout << "\t!! Wrong Picture Number !!";
                    Pause();
                }
                else
                {
                    PicNum = temp;
                }
            }
            break;
        case 0:
            return;
        default:
            if (subaction != -1)
            {
                printf("\t!!  Wrong Input  !! \n");
                Pause();
            }
            else
            {
                printf("\t!!  Wrong Input  !! \n");
                std::cin.get();
            }

            break;
        }
    }
}

void TrainMenu(TrainSet Trainsets[], float img[IMAGE_SIZE][IMAGE_SIZE], int *IsDatabaseReady)
{
    int subaction;
    int count{0}, ChosenLabel;
    std::string image_path;
    float ImageFeatures[40]{0};

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
                image_path = interpolation("data\\mnist", "train", i);
                Trainsets[i].Label = i;
                for (int j = 0; j < IMAGE_DATABASE_LIMIT; j++)
                {
                    ImageLoad(image_path, j, img);
                    BreakDown(img, Trainsets[i].imgs[j]);
                }
            }

            // OFF-SET PERSENTAGE
            CompareSets Set[DEFAULT_K];
            float DistanceHolder[IMAGE_DATABASE_LIMIT];
            int Place, LabelCounter[10]{0}, CorrectCount;

            for (int i = 0; i < 10; i++)
            {
                CorrectCount = 0;
                image_path = interpolation("data\\mnist", "test", i);
                for (int j = 0; j < ACCURACY_IMAGE; j++)
                {
                    ImageLoad(image_path, j, img);
                    BreakDown(img, ImageFeatures);

                    // RESETING COUNTERS
                    for (int k = 0; k < 10; k++)
                    {
                        LabelCounter[k] = 0;
                    }

                    for (int k = 0; k < DEFAULT_K; k++)
                    {
                        Set[k].Distance = 1000 + k;
                    }

                    for (int k = 0; k < 10; ++k)
                    {
                        MatrixDistanceCalculator(Trainsets[k].imgs, ImageFeatures, DistanceHolder);
                        for (int z = 0; z < IMAGE_DATABASE_LIMIT; z++)
                        {
                            if (DistanceHolder[z] < Set[DEFAULT_K - 1].Distance)
                            {
                                Place = DEFAULT_K - 1;
                                while (DistanceHolder[z] < Set[Place].Distance)
                                {
                                    Place--;
                                }
                                Place++;
                                ArrayCompareSetPush(Place, DEFAULT_K, Set);
                                Set[Place].Label = k;
                                Set[Place].Distance = DistanceHolder[z];
                            }
                        }
                    }

                    for (int k = 0; k < DEFAULT_K; k++)
                    {
                        LabelCounter[Set[k].Label]++;
                    }
                    int max{0}, MaxLabel;
                    for (int k = 0; k < 10; k++)
                    {
                        if (LabelCounter[k] > max)
                        {
                            max = LabelCounter[k];
                            MaxLabel = k;
                        }
                    }
                    if (MaxLabel == i)
                    {
                        CorrectCount++;
                    }
                }

                if (i % 5 == 0)
                    printf("\n");

                printf("| #%d: %.2f% |", i, (CorrectCount * 100.0 / ACCURACY_IMAGE * 1.0));
            }

            *IsDatabaseReady = 1;
            Pause();
            break;
        }
        case 0:
            return;
        default:
            if (subaction != -1)
            {
                printf("\t!!  Wrong Input  !! \n");
                Pause();
            }
            else
            {
                printf("\t!!  Wrong Input  !! \n");
                std::cin.get();
            }
            break;
        }
    }
}

void TestMenu(TrainSet Trainsets[], float img[][IMAGE_SIZE], int *IsDatabaseReady)
{
    int subaction, temp;
    int Label{-1}, PicNum{-1}, filecount, ChosenLabel{-1}, KNearest{5};
    std::string image_path{""};
    float ImageFeatures[40]{0};

    while (1)
    {
        ClearScreen();
        TestMenu_print(&Label, &PicNum, ImageFeatures, &KNearest);
        std::cin >> subaction;
        subaction = CheckInput(subaction);
        switch (subaction)
        {
        case 1:
            if (Label == -1 || PicNum == -1)
            {
                printf("\n Please select an image first..");
                Pause();
            }
            else
            { // LOADING AND PRINTING IMAGE
                Image_print(img);
            }
            break;
        case 2: // LABEL INPUT
            std::cout << " Input Label (0 - 9):  ";
            std::cin.ignore(10000, '\n');
            std::cin >> temp;
            if (temp < 0 || temp > 9)
            {
                std::cout << "\t!! Unavailable Label !!";
                Pause();
                break;
                ;
            }
            Label = temp;
            image_path = interpolation("data\\mnist", "test", Label);
            filecount = file_count(image_path);
            PicNum = -1;
            break;
        case 3: // PICNUM INPUT
            if (Label == -1)
            {
                printf("\n Please Select Image Label first");
                Pause();
            }
            else
            {
                std::cout << " Input Picture Number (0 - "
                          << filecount
                          << "):  ";
                std::cin.ignore(10000, '\n');
                std::cin >> temp;
                if (temp > filecount || temp < 0)
                {
                    std::cout << "\t!! Wrong Picture Number !!";
                    Pause();
                }
                else
                {
                    PicNum = temp;
                    ImageLoad(image_path, PicNum, img);
                }
            }
            break;
        case 4: // K FOR NN INPUT
            printf("\n Input K for KNN (1 - %d):  ", IMAGE_DATABASE_LIMIT / 10);
            std::cin >> temp;
            if (temp <= 0 || temp > IMAGE_DATABASE_LIMIT / 10)
            {
                printf("\t!! Wrong Input !!");
                Pause();
                break;
            }
            KNearest = temp;
            break;
        case 5: // TESTING STATION
            if (Label == -1 || PicNum == -1)
            {
                printf("\n Please select an image first..");
                Pause();
            }
            else if (*IsDatabaseReady == 0)
            {
                std::cout << "\n Please use the train function first..";
                Pause();
            }
            else
            {
                CompareSets Set[IMAGE_DATABASE_LIMIT / 10 + 1];
                float DistanceHolder[IMAGE_DATABASE_LIMIT];
                int Place, LabelCounter[10]{0};

                for (int i = 0; i < KNearest; i++)
                {
                    Set[i].Distance = 1000 + i;
                }

                BreakDown(img, ImageFeatures);

                for (int i = 0; i < 10; ++i)
                {
                    MatrixDistanceCalculator(Trainsets[i].imgs, ImageFeatures, DistanceHolder);
                    for (int j = 0; j < IMAGE_DATABASE_LIMIT; j++)
                    {
                        if (DistanceHolder[j] < Set[KNearest - 1].Distance)
                        {
                            Place = KNearest - 1;
                            while (DistanceHolder[j] < Set[Place].Distance)
                            {
                                Place--;
                            }
                            Place++;
                            ArrayCompareSetPush(Place, KNearest, Set);
                            Set[Place].Label = i;
                            Set[Place].Distance = DistanceHolder[j];
                        }
                    }
                }

                for (int i = 0; i < KNearest; i++)
                {
                    if (i % 7 == 0)
                    {
                        printf("\n");
                    }
                    printf("| #%d: %.2f |", Set[i].Label, Set[i].Distance);
                    LabelCounter[Set[i].Label]++;
                }
                int max{0};
                for (int k = 0; k < 10; k++)
                {
                    if (LabelCounter[k] > max)
                    {
                        max = LabelCounter[k];
                        ChosenLabel = k;
                    }
                }
                printf("\n\n");
                std::cout << " # Detected Label: " << ChosenLabel << "\t\n";
                for (int i = 0; i < 10; i++)
                {
                    printf("| #%d = %d |", i, LabelCounter[i]);
                }
                printf("\n");


                Image_print(img);
            }
            break;
        case 0:
            return;
        default:
            if (subaction != -1)
            {
                printf("\t!!  Wrong Input  !! \n");
                Pause();
            }
            else
            {
                printf("\t!!  Wrong Input  !! \n");
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
            printf("\n Mean of matrix = %.2f", Matrix7squar_mean(Matrix));
            Pause();
            break;
        case 2: // STD 7by7
            ClearScreen();
            printf("\n Input 7 By 7 Matrix: \n\n");
            Matrix7squar_loader(Matrix);
            printf("\n STD of 7 By 7 Matrix = %.2f", Matrix7squar_std(Matrix, Matrix7squar_mean(Matrix)));
            Pause();
            break;
        case 3: // Arry - Arry Distance Calculator
            ClearScreen();
            printf("\n Input 7 elements of Array #1: ");
            Array_loader(Matrix[7], 7);
            printf("\n Input 7 elements of Array #2: ");
            Array_loader(Matrix[6], 7);
            printf("\n Distance: %.2f", DistanceCalculator(Matrix[7], Matrix[6], 7));
            Pause();
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
                printf("\t!!  Wrong Input  !! \n");
                Pause();
            }
            else
            {
                printf("\t!!  Wrong Input  !! \n");
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
    Pause();
}

void ClearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Pause()
{
    std::cin.get();
    std::cin.get();
}

int CheckInput(int Input)
{
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        Input = -1;
    }
    return Input;
}

float DistanceCalculator(float ArrayA[], float ArrayB[], int size)
{
    float Distance{0};

    for (int i = 0; i < size; i++)
    {
        Distance += pow((ArrayA[i] - ArrayB[i]), 2);
    }
    return Distance;
}

void MatrixDistanceCalculator(float Matrix[][FEATURE_LIMIT], float Array[], float DistanceArry[])
{
    for (int i = 0; i < IMAGE_DATABASE_LIMIT; i++)
        DistanceArry[i] = DistanceCalculator(Matrix[i], Array, FEATURE_LIMIT) / 100.0;
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
        ++squarNum;

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

void ArrayCompareSetPush(int StartPosition, int Length, CompareSets Array[])
{
    CompareSets temp;
    for (int i = Length - 1; i > StartPosition; i--)
    {
        temp = Array[i];
        Array[i] = Array[i - 1];
        Array[i - 1] = temp;
    }
}