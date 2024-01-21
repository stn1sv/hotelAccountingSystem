/**********************************************************************************************
*                                       ФАЙЛ HEADER.H                                         *
**********************************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>

//================================ОБЪЯВЛЕНИЕ СТРУКТУР========================================//

// Элемент двусвязного кольцевого списка
struct hotel {
    std::string name; // Название
    int number_of_stars; // Количество звезд
    int id_hotel; // Список комнат
    hotel *prev, *next; // Указатели на предыдущий и следующий элементы
};

// Элемент односвязного линейного списка
template<typename T>
struct node {
    T data;
    node *next; // Указатель на следующий элемент
};

struct room {
    int number; // Номер
    int id; // Id гостиницы, к которой относится номер
    int id_category; // Id категории, к которой относится номер
    int id_status; // Id статусов, которыми обладает номер (их может быть несколько на разные даты)
};

struct category {
    std::string category_name; // Категория номера (эконом/стандарт/люкс)
    int capacity; // Вместительность
    int id; // Id категории
};

struct status {
    std::string status_name; // Статус номера (свободен/бронь/занят)
    int number_of_guests; // Количество гостей
    std::string arrival_date; // Дата прибытия
    std::string release_date; // Дата освобождения
    int id; // Id статуса
};


//===============================ШАБЛОННЫЕ ФУНКЦИИ===========================================//

// Шаблонная функция добавления элемента в односвязный линейный список
template<typename T>
void add(node<T> *&head, node<T> *&tail, T data) {
    node<T>* new_node = new node<T>(); // Выделение памяти под новый элемент
    new_node->data = data;
    new_node->next = nullptr; // Так как элемент добавляется в конец, его указатель на следующий элемент равен null

    if (head == nullptr) { // Если список пуст
        head = new_node; // Первый и последний элементы равны новому
        tail = new_node;
    } else {
        tail->next = new_node; // Следующий за последним равен новому
        tail = new_node;
    }
}

// Шаблонная функция проверки на повторяющийся элемент
template<typename T>
bool check(node<T> *&head, int id, int number) {
    node<T>* temp = head;
    for (; temp != nullptr; temp = temp->next) {
        if (temp->data.id == id && temp->data.number == number) return true;
    }
    return false;
}

// Функция для чтения файлов
void read(
        hotel *&head_hotel, hotel *&tail_hotel, // Список отелей
        node<room> *&head_room, node<room> *&tail_room, // Список номеров
        node<category> *&head_category, node<category> *&tail_category, // Список категорий
        node<status> *&head_status, node<status> *&tail_status, // Список статусов
        int &hotel_count,
        int &status_count
);

//===============================ФУНКЦИИ ДЛЯ РАБОТЫ С НОМЕРАМИ===============================//
// Функция добавления номера в список
void add_room(node<room> *&head_room, // Список номеров
              node<room> *&tail_room,
              int hotel_id // id гостиницы, к которой относится номер
);
// Функция удаления номера из списка
void delete_room(node<room> *&head_room, // Список номеров
                 int hotel_id // id гостиницы, к которой относится номер
);
void remove(node<room> *&head_room, // Список номеров
            int hotel_id, // id гостиницы, к которой относится номер
            int number // Номер
);
// Функция добавления статуса номеру
void add_status(node<status> *&head_status, // Список статусов
                node<status> *&tail_status,
                node<room> *&head_room,
                node<category> *&head_category,
                int hotel_id, // id гостиницы, к которой относится номер
                int &status_count
);
// Функция печати номеров в гостинице
void print_rooms_in_hotel(node<room> *&head_room, // Список номеров
                          node<category> *&head_category, // Список категорий
                          node<status> *&head_status, // Список статусов
                          int hotel_id, // id гостиницы, к которой относится номер
                          int cat, // Категория номера
                          int stat // Статус номера
);
// Функция печати номеров с заданными параметрами в гостинице
void print_room_by_params(node<room> *&head_room, // Список номеров
              node<category> *&head_category, // Список категорий
              node<status> *&head_status, // Список статусов
              int hotel_id // id гостиницы, к которой относится номер
);

//============================ФУНКЦИИ ДЛЯ РАБОТЫ С ГОСТИНИЦАМИ===============================//
// Функция добавления гостиницы в список
void add(hotel *&head, // Список гостиниц
               hotel *&tail,
               std::string name, // Название гостиницы
               int number_of_stars, // Количество звезд
               int id_hotel // id гостиницы
);
void add_hotel(hotel *&head, // Список гостиниц
               hotel *&tail,
               int &hotel_count
);
// Функция удаления гостиницы из списка
void delete_hotel(hotel *&head, // список гостиниц
                  hotel *&tail
);
void remove(hotel *&head, // Список гостиниц
            hotel *&tail,
            std::string name // Название гостиницы
);
// Функция печати списка гостиниц
void print_hotel(hotel *&head, // Список гостиниц
                 int stars // Количество звезд
);
// Функция печати обратного списка гостиниц
void print_hotel_reverse(hotel *&tail // Список гостиниц
);
// Функция поиска id гостиницы по ее названию
int get_hotel_id_by_name(hotel *&head, // Список гостиниц
                         std::string hotel_name // Название гостиницы
);
void delete_status(node<status> *&head);
/**********************************************************************************************
*                                    КОНЕЦ ФАЙЛА HEADER.H                                     *
**********************************************************************************************/