/**********************************************************************************************
*                                       ФАЙЛ FUNC.CPP                                         *
**********************************************************************************************/

#include "head.h"

// Функция для чтения файлов
void read(
        hotel *&head_hotel, hotel *&tail_hotel, // Список отелей
        node<room> *&head_room, node<room> *&tail_room, // Список номеров
        node<category> *&head_category, node<category> *&tail_category, // Список категорий
        node<status> *&head_status, node<status> *&tail_status, // Список статусов
        int &hotel_count,
        int &status_count
) {
    // Файлы входных данных
    std::fstream hotels;
    std::fstream rooms;
    std::fstream categories;
    std::fstream statuses;

    // Открытие и чтение файла
    hotels.open("hotels.txt");
    if (!hotels.is_open()) {
        std::cout << "Ошибка: не удалось открыть файл hotels.txt\n";
    }
    hotel h; // Вспомогательный элемент типа гостиница
    while (hotels >> h.name >> h.number_of_stars >> h.id_hotel) {
        add(head_hotel, tail_hotel, h.name, h.number_of_stars, h.id_hotel);
        hotel_count++;
    }

    // Открытие и чтение файла
    rooms.open("rooms.txt");
    if (!rooms.is_open()) {
        std::cout << "Ошибка: не удалось открыть файл rooms.txt\n";
    }
    room r; // Вспомогательный элемент типа комната
    while (rooms >> r.number >> r.id >> r.id_category >> r.id_status) {
        add(head_room, tail_room, r);
    }

    // Открытие и чтение файла
    categories.open("categories.txt");
    if (!categories.is_open()) {
        std::cout << "Ошибка: не удалось открыть файл categories.txt\n";
    }
    category c;
    while (categories >> c.category_name >> c.capacity >> c.id) {
        add(head_category, tail_category, c);
    }

    // Открытие и чтение файла
    statuses.open("statuses.txt");
    if (!statuses.is_open()) {
        std::cout << "Ошибка: не удалось открыть файл statuses.txt\n";
    }
    status s;
    while (statuses >> s.status_name >> s.number_of_guests >> s.arrival_date >> s.release_date >> s.id) {
        add(head_status, tail_status, s);
        status_count++;
    }
}


//===============================ФУНКЦИИ ДЛЯ РАБОТЫ С НОМЕРАМИ===============================//

// Функция добавления номера в список
void add_room(node<room> *&head_room, // Список номеров
              node<room> *&tail_room,
              int hotel_id // id гостиницы, к которой относится номер
) {
    int number_of_guest;
    room room;
    std::string category;
    std::cout << "\nВведите номер: ";
    if (!(std::cin >> room.number) || (room.number < 1 || room.number > 1000)) {
        std::cout << "\nНомер должен быть целым числом от 1 до 1000\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    if (check(head_room, hotel_id, room.number)) {
        std::cout << "\nТакой номер уже существует в выбранной гостинице\n";
        return;
    }
    while(true) {
        std::cout << "\nВведите категорию номера (эконом/стандарт/люкс): ";
        std::cin >> category;
        std::cout << "\nВведите вместительность номера (эконом - 1,2) (стандарт - 2,3) (люкс - 3,4,5): ";
        if (!(std::cin >> number_of_guest)) {
            std::cout << "\nВместительность должна быть целым числом\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (category == "эконом") {
            if (number_of_guest < 1 || number_of_guest > 2) {
                std::cout << "\nВместительность для категории <<эконом>> должна быть от 1 до 2 человек\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            room.id_category = number_of_guest;
            break;
        }
        if (category == "стандарт") {
            if (number_of_guest < 2 || number_of_guest > 3) {
                std::cout << "\nВместительность для категории <<стандарт>> должна быть от 2 до 3 человек\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            room.id_category = number_of_guest + 1;
            break;
        }
        if (category == "люкс") {
            if (number_of_guest < 3 || number_of_guest > 5) {
                std::cout << "\nВместительность для категории <<люкс>> должна быть от 3 до 5 человек\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            room.id_category = number_of_guest + 2;
            break;
        }
        std::cout << "\nНекорректная категория номера\n";
    }
    room.id = hotel_id;
    room.id_status = 0;
    add(head_room, tail_room, room);
    std::cout << "\nНомер успешно добавлен в гостиницу\n";
}

// Функция удаления номера из списка
void delete_room(node<room> *&head_room, // Список номеров
                 int hotel_id // id гостиницы, к которой относится номер
) {
    int number;
    std::cout << "\nВведите номер, который хотите удалить из гостиницы: ";
    if (!(std::cin >> number) || (number < 1 || number > 1000)) {
        std::cout << "\nНомер должен быть целым числом от 1 до 1000\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    remove(head_room, hotel_id, number);
}

void remove(node<room> *&head_room, // Список номеров
            int hotel_id, // id гостиницы, к которой относится номер
            int number // Номер
) {
    node<room>* temp = head_room;
    node<room>* prev = nullptr;
    if (temp == nullptr) {
        std::cout << "\nСписок номеров пуст\n";
        return;
    }
    // Если удаляемый элемент - первый
    if (temp->data.number == number && temp->data.id == hotel_id) {
        head_room = temp->next;
        delete temp;
        return;
    }
    // Идем до конца списка
    while (temp != nullptr) {
        if (temp->data.number == number && temp->data.id == hotel_id) break;
        prev = temp;
        temp = temp->next;
    }
    // Если не нашли такой элемент
    if (temp == nullptr) {
        std::cout << "\nТакого номера нет в списке\n";
        return;
    } else {
        std::cout << "\nНомер успешно удален из гостиницы\n";
    }
    prev->next = temp->next;
    delete temp;
}

// Функция добавления статуса номеру
void add_status(node<status> *&head_status,
                node<status> *&tail_status,
                node<room> *&head_room,
                node<category> *&head_category,
                int hotel_id,
                int &status_count
) {
    node<room> *temp_room = head_room;
    node<status> *temp_status = head_status;
    node<category> *temp_category = head_category;
    int number;
    status status;
    std::cout << "\nВведите номер, которму хотите добавить статус: ";
    if (!(std::cin >> number) || (number < 1 || number > 1000)) {
        std::cout << "\nНомер должен быть целым числом от 1 до 1000\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    while (temp_room != nullptr) {
        if (temp_room->data.number == number && temp_room->data.id == hotel_id) {
            temp_status = head_status;
            temp_category = head_category;
            while (temp_status != nullptr) {
                if (temp_status->data.id == temp_room->data.id_status) {
                    break;
                }
                temp_status = temp_status->next;
            }
            while (temp_category != nullptr) {
                if (temp_category->data.id == temp_room->data.id_category) {
                    break;
                }
                temp_category = temp_category->next;
            }
            break;
        }
        temp_room = temp_room->next;
    }
    if (temp_room == nullptr) {
        std::cout << "\nТакого номера нет в списке\n";
        return;
    }
    std::cout << "\nНомер: " << temp_room->data.number <<
    "\nКатегория: " << temp_category->data.category_name <<
    "\nВместительность: " << temp_category->data.capacity << "\n";
    while (true) {
        std::cout << "\nВведите статус номера (бронь/занят): ";
        std::cin >> status.status_name;
        if (!(status.status_name == "бронь" || status.status_name == "занят")) {
            std::cout << "\nНекорректный статус номера\n";
            continue;
        }
        break;
    }
    while (true) {
        std::cout << "Введите количество гостей: ";
        if (!(std::cin >> status.number_of_guests)) {
            std::cout << "\nКоличество гостей должно быть целым числом\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (status.number_of_guests < 1 || status.number_of_guests > temp_category->data.capacity) {
            std::cout << "\nКоличество гостей не соответствует вместительности номера\n";
            continue;
        }
        break;
    }
    while (true) {
        std::cout << "\nВведите дату заезда в формате год-месяц-день: ";
        std::cin >> status.arrival_date;
        std::cout << "Введите дату выезда в формате год-месяц-день: ";
        std::cin >> status.release_date;
        if (!("2023-12-01" < status.arrival_date && status.arrival_date < "2024-12-01" && "2023-12-01" < status.release_date && status.release_date < "2024-12-01")) {
            std::cout << "\nНеверный формат даты\n";
            continue;
        }
        if (status.release_date < status.arrival_date) {
            std::cout << "\nДата выезда не может быть меньше даты заезда\n";
            continue;
        }
        break;
    }
    if (!temp_room->data.id_status) {
        status.id = status_count;
        temp_room->data.id_status = status.id;
        status_count++;
    }
    status.id = temp_room->data.id_status;
    temp_status = head_status;
    while (temp_status != nullptr) {
        if (temp_status->data.id == status.id) {
            if ((status.arrival_date >= temp_status->data.arrival_date && status.arrival_date < temp_status->data.release_date) ||
                    (status.release_date <= temp_status->data.release_date && status.release_date > temp_status->data.arrival_date)) {
                std::cout << "\nНомер уже занят на данные даты\n";
                return;
            }
        }
        temp_status = temp_status->next;
    }
    add(head_status, tail_status, status);
    std::cout << "\nСтатус номера успешно добавлен\n";
}

// Функция печати номеров с заданными параметрами в гостинице
void print_room_by_params(node<room> *&head_room, // Список номеров
                          node<category> *&head_category, // Список категорий
                          node<status> *&head_status, // Список статусов
                          int hotel_id // id гостиницы, к которой относится номер
) {
    int cat, capacity;
    std::string category;
    while(true) {
        std::cout << "\nВведите категорию номера (эконом/стандарт/люкс): ";
        std::cin >> category;
        std::cout << "\nВведите вместительность номера (эконом - 1,2) (стандарт - 2,3) (люкс - 3,4,5): ";
        if (!(std::cin >> capacity)) {
            std::cout << "\nВместительность должна быть целым числом\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (category == "эконом") {
            if (capacity < 1 || capacity > 2) {
                std::cout << "\nВместительность для категории <<эконом>> должна быть от 1 до 2 человек\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            cat = capacity;
            break;
        }
        if (category == "стандарт") {
            if (capacity < 2 || capacity > 3) {
                std::cout << "\nВместительность для категории <<стандарт>> должна быть от 2 до 3 человек\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            cat = capacity + 1;
            break;
        }
        if (category == "люкс") {
            if (capacity < 3 || capacity > 5) {
                std::cout << "\nВместительность для категории <<люкс>> должна быть от 3 до 5 человек\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            cat = capacity + 2;
            break;
        }
        std::cout << "\nНекорректная категория номера\n";
    }
    std::cout << "\n======================СПИСОК НОМЕРОВ==============================\n";
    print_rooms_in_hotel(head_room, head_category, head_status, hotel_id, cat, -1);
    std::cout << "\n==================================================================\n";
}

// Функция печати номеров в гостинице
void print_rooms_in_hotel(node<room> *&head_room, // Список номеров
                          node<category> *&head_category, // Список категорий
                          node<status> *&head_status, // Список статусов
                          int hotel_id, // id гостиницы, к которой относится номер
                          int cat, // Категория номера
                          int stat // Статус номера
) {
    node<room> *temp_room = head_room;
    if (temp_room == nullptr) {
        std::cout << "\nВ отеле нет номеров\n";
        return;
    }
    // Цикл по списку номеров
    for (; temp_room != nullptr; temp_room = temp_room->next) {

        // Если id комнаты не равно id отеля, то пропускаем итерацию цикла
        if (temp_room->data.id != hotel_id) continue;

        // Если переданная категория не -1, => необходимо проверить категорию номера
        if (cat != -1) {
            // Если категория номера не равна переданной категории, то пропускаем итерацию цикла
            if (temp_room->data.id_category != cat) continue;
        }

        // Если переданный статус не -1, => необходимо проверить статус номера
        if (stat != -1) {
            // Если статус номера не равен переданному статусу, то пропускаем итерацию цикла
            if (temp_room->data.id_status != stat) continue;
        }
        std::cout << "\nНомер комнаты: " << temp_room->data.number << "\n";
        node<category> *temp_category = head_category;
        // Цикл по списку категорий
        for (; temp_category != nullptr; temp_category = temp_category->next) {
            // Если id категории такое же, как указанное в комнате
            if (temp_category->data.id == temp_room->data.id_category) {
                std::cout << "Категория: " << temp_category->data.category_name << "\n"
                          << "Вместительность: " << temp_category->data.capacity << "\n";
            }
        }
        // Если статус не ноль
        if (temp_room->data.id_status) {
            node<status> *temp_status = head_status;
            // Цикл по списку статусов
            for (; temp_status != nullptr; temp_status = temp_status->next) {
                if (temp_room->data.id_status) {
                    if (temp_status->data.id == temp_room->data.id_status) {
                        std::cout << "Статус: " << temp_status->data.status_name << "\n"
                                  << "Количество гостей: " << temp_status->data.number_of_guests << "\n"
                                  << "Дата заезда: " << temp_status->data.arrival_date << "\n"
                                  << "Дата выезда: " << temp_status->data.release_date << "\n";
                    }
                }
            }
        } else { // Если статус ноль
            std::cout << "Статус: свободен\n";
        }
    }
}

//============================ФУНКЦИИ ДЛЯ РАБОТЫ С ГОСТИНИЦАМИ===============================//

// Функция добавления гостиницы в список
void add_hotel(hotel *&head, // Список гостиниц
               hotel *&tail,
               int &hotel_count
) {
    std::string name;
    int stars;
    std::cout << "Введите название гостиницы: ";
    std::cin >> name;
    if (get_hotel_id_by_name(head, name)) {
        std::cout << "\nГостиница с таким названием уже существует\n";
        return;
    }
    std::cout << "\nВведите количество звезд: ";
    // Ввод количества звезд с проверкой
    if (!(std::cin >> stars) || (stars < 1 || stars > 5)) {
        std::cout << "\nКоличество звезд должно быть целым числом от 1 до 5\n";
        std::cin.clear(); // Отчистка буфера ввода
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    add(head, tail, name, stars, hotel_count);
    std::cout << "\nГостиница успешно добавлена\n";
    hotel_count++;
}

void add(hotel *&head, // Список гостиниц
               hotel *&tail,
               std::string name, // Название гостиницы
               int number_of_stars, // Количество звезд
               int id_hotel // id гостиницы
) {
    hotel* temp = new hotel;
    if (head == nullptr){
        head = temp;
        temp->prev = nullptr;
        temp->next = temp;
    } else{
        tail->next = temp;
        temp->prev = tail;
        head->prev = temp;
    }
    temp->name = name;
    temp->number_of_stars = number_of_stars;
    temp->id_hotel = id_hotel;
    temp->next = head;
    tail = temp;
}

// Функция удаления гостиницы из списка
void delete_hotel(hotel *&head, // Список гостиниц
                  hotel *&tail
) {
    std::string name;
    std::cout << "\nВведите название гостиницы, которую хотите удалить: ";
    std::cin >> name;
    remove(head, tail, name);
}


void remove(hotel *&head, // Список гостиниц
            hotel *&tail,
            std::string name // Название гостиницы
) {
    bool flag = true;
    hotel *temp = head;
    // Если список пуст
    if (head == nullptr) {
        std::cout << "\nСписок гостиниц пуст\n";
        return;
    }
    // Цикл до конца списка
    do {
        // Если название текущего отеля совпадает с названием отеля, который необходимо удалить
        if (temp->name == name) {
            flag = false;
            if (temp == head) { // Если это первый элемент
                head = head->next;
                tail->next = head;
                head->prev = tail;
            } else if (temp == tail) { // Если это последний элемент
                tail = tail->prev;
                tail->next = head;
                head->prev = tail;
            } else { // Если элемент в середине списка
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
            // Удаление элемента
            delete temp;
            return;
        }
        temp = temp->next;
    } while (temp != head);
    if (flag) {
        std::cout << "\nГостиницы с таким названием нет в списке\n";
        return;
    } else {
        std::cout << "\nГостиница успешно удалена\n";
        return;
    }
}

void delete_status(node<status> *&head) {
    int id;
    bool flag = true;
    std::cout << "\nВведите id статуса, который хотите удалить: ";

    node<status> *temp_status = head;
    while (temp_status != nullptr) {
        if (temp_status->data.id == id) {
            flag = false;
            break;
        }
        temp_status = temp_status->next;
    }
    if (flag) {
        std::cout << "\nСтатуса с таким id нет в списке\n";
        return;
    }
    std::cout << "Статус успешно удален\n";
}
// Функция печати списка гостиниц
void print_hotel(hotel *&head, // Список гостиниц
                 int stars // Количество звезд
) {
    hotel *temp = head;
    if (temp == nullptr) {
        std::cout << "\nСписок гостиниц пуст\n";
        return;
    }
    do {
        if (stars) {
            if (temp->number_of_stars != stars) {
                temp = temp->next;
                continue;
            }
        }
        std::cout << "\nНазвание: " << temp->name << "\n" <<
                  "Количество звезд: ";
        for (int i = 0; i < temp->number_of_stars; i++) {
            std::cout << "*";
        }
        std::cout << "\n";
        temp = temp->next;
    } while (temp != head);
}

// Функция печати обратного списка гостиниц
void print_hotel_reverse(hotel *&tail // Список гостиниц
) {
    hotel *temp = tail;
    if (temp == nullptr) {
        std::cout << "\nСписок гостиниц пуст\n";
        return;
    }
    do {
        std::cout << "\nНазвание: " << temp->name << "\n" <<
                  "Количество звезд: ";
        for (int i = 0; i < temp->number_of_stars; i++) {
            std::cout << "*";
        }
        std::cout << "\n";
        temp = temp->prev;
    } while (temp != tail);
}

// Функция поиска id гостиницы по ее названию
int get_hotel_id_by_name(hotel *&head, // Список гостиниц
                         std::string hotel_name // Название гостиницы
) {
    int id = 0;
    hotel *temp = head;
    if (temp == nullptr) {
        std::cout << "\nСписок гостиниц пуст\n";
        return 0;
    }
    do {
        if (temp->name == hotel_name) id = temp->id_hotel;
        temp = temp->next;
    } while (temp != head);
    return id;
}

/**********************************************************************************************
*                                       КОНЕЦ ФАЙЛА FUNC.CPP                                  *
**********************************************************************************************/