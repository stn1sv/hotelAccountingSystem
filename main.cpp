***********************************************************************************************
*                                       ФАЙЛ MAIN.CPP                                         *
**********************************************************************************************/

#include "head.h"

int main() {
    // Указатели на первый и последний элемент списков
    hotel *head_hotel = nullptr, *tail_hotel = nullptr;
    node<room> *head_room = nullptr, *tail_room = nullptr;
    node<category> *head_category = nullptr, *tail_category = nullptr;
    node<status> *head_status = nullptr, *tail_status = nullptr;

    // id гостиницы и id статуса
    int hotel_count = 1;
    int status_count = 1;

    // Чтение входных данных
    read(head_hotel, tail_hotel, head_room, tail_room, head_category, tail_category, head_status, tail_status, hotel_count, status_count);

    // Переменные, хранящие номер операции
    int cmd = 1;
    int cmd1 = 1;
    // Переменные, необходимые для ввода
    int stars, hotel_id;
    std::string hotel_name;
    std::cout << "\nЗдравствуйте! Данный сервис предоставляет следующие возможности по работе с гостиницами:\n";
    // Пока cmd не 0
    while (cmd) {
        std::cout <<
        "\n1. Вывести список гостиниц\n" <<
        "2. Вывести список гостиниц в обратном порядке\n" <<
        "3. Вывести список гостиниц с определенным количеством звезд\n" <<
        "4. Выбрать интересующую гостиницу\n" <<
        "5. Добавить гостиницу\n" <<
        "6. Удалить гостиницу\n" <<
        "0. Выход\n" <<
        "Введите номер операции: ";
        // Ввод номера операции с проверкой
        if (!(std::cin >> cmd) || cmd < 0 || cmd > 6) {
            std::cin.clear(); // Отчистка буфера ввода
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nНомер команды должен быть целым неотрицательным числом от 0 до 6\n";
            cmd = 10;
        }
        switch (cmd) {
            case 1: // Вывод списка гостиниц
                std::cout << "\n=====================СПИСОК ВСЕХ ГОСТИНИЦ=========================\n";
                print_hotel(head_hotel, 0);
                std::cout << "\n==================================================================\n";
                break;
            case 2: // Вывод обратного списка гостиниц
                std::cout << "\n=====================СПИСОК ВСЕХ ГОСТИНИЦ=========================\n";
                print_hotel_reverse(tail_hotel);
                std::cout << "\n==================================================================\n";
                break;
            case 3: // Вывод списка гостиниц с определенным количеством звезд
                std::cout << "\nВведите количество звезд: ";
                // Ввод количества звезд с проверкой
                if (!(std::cin >> stars) || (stars < 1 || stars > 5)) {
                    std::cout << "\nКоличество звезд должно быть целым числом от 1 до 5\n";
                    std::cin.clear(); // Отчистка буфера ввода
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }
                std::cout << "\n========================СПИСОК ГОСТИНИЦ===========================\n";
                print_hotel(head_hotel, stars);
                std::cout << "\n==================================================================\n";
                break;
            case 4: // Операции с конкретной гостиницей
                std::cout << "\nВведите название интересующей гостиницы: ";
                std::cin >> hotel_name;
                hotel_id = get_hotel_id_by_name(head_hotel, hotel_name); // Получение id гостиницы по ее названию
                if (!hotel_id) {
                    std::cout << "\nГостиницы с таким названием нет в списке!\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }
                while (cmd1) {
                    std::cout << "\nЧто конкретно вас интересует?\n" <<
                              "1. Вывести все номера\n" <<
                              "2. Вывести все свободные номера\n" <<
                              "3. Подобрать номер по параметрам\n" <<
                              "4. Добавить номер\n" <<
                              "5. Добавить статус номеру\n" <<
                              "6. Удалить статус номера\n" <<
                              "7. Удалить номер\n" <<
                              "0. Вернуться в главное меню\n" <<
                              "Введите номер операции: ";
                    // Ввод номера операции с проверкой
                    if (!(std::cin >> cmd1) || cmd1 < 0 || cmd1 > 7) {
                        std::cout << "\nНомер команды должен быть целым неотрицательным числом от 0 до 7\n";
                        std::cin.clear(); // Отчистка буфера ввода
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        cmd1 = 10;
                    }
                    switch (cmd1) {
                        case 1: // Вывод списка всех номеров
                            std::cout << "\n======================СПИСОК ВСЕХ НОМЕРОВ=========================\n";
                            print_rooms_in_hotel(head_room, head_category, head_status, hotel_id, -1, -1);
                            std::cout << "\n==================================================================\n";
                            break;
                        case 2: // Вывод списка свободных номеров
                            std::cout << "\n====================СПИСОК СВОБОДНЫХ НОМЕРОВ======================\n";
                            print_rooms_in_hotel(head_room, head_category, head_status, hotel_id, -1, 0);
                            std::cout << "\n==================================================================\n";
                            break;
                        case 3: // вывод номеров, соответствующих заданным параметрам
                            print_room_by_params(head_room, head_category, head_status, hotel_id);
                            break;
                        case 4: // Добавление номера в список
                            add_room(head_room, tail_room, hotel_id);
                            break;
                        case 5: // Добавление статуса номеру
                            add_status(head_status, tail_status, head_room, head_category, hotel_id, status_count);
                            break;
                        case 6:
                            delete_status(head_status);
                            break;
                        case 7: // Удаление номера
                            delete_room(head_room, hotel_id);
                            break;
                        case 0: // Выход в главное меню
                            break;
                        default:
                            continue;
                    }
                }
                break;
            case 5: // Добавление гостиницы
                add_hotel(head_hotel, tail_hotel, hotel_count);
                break;
            case 6: // Удаление гостиницы
                delete_hotel(head_hotel, tail_hotel);
                break;
            case 0:
                return 0;
            default:
                continue;
        }
    }
    return 0;
}

/**********************************************************************************************
*                                       КОНЕЦ ФАЙЛА MAIN.CPP                                  *
**********************************************************************************************/