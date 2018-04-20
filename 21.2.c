/*
Связный список - это структура данных. 
Элементы списка связаны между собой. Когда связь одна — список односвязный.
В файле представлен пример односвязного списка.
*/

#include <stdio.h>
#include <stdlib.h>

/*
 Структура описывает элемент связного списка.
 Для удобства мы определили тип node_t.
 */
typedef struct node {
    int data;           // Данные (полезная часть данных)
    struct node * next; // Указатель на следующий элемент (вспомогальная часть)
} node_t;

/*
 Структура описывает весь связный список.
 Кроме необходимого указателя на начало списка
 в структуре хранится ее размер (длина). Переменная с размером
 позволяет быстро получить его величину. Без нее пришлось бы проходить
 по всему списку, чтобы узнать число элементов. На коротких списках ok, но
 на длинных — проблема.
 Для удобства мы определили тип list_t.
 */
typedef struct list {
    node_t* head;       // Указатель на начало списка (голову)
    unsigned int size;  // Размер списка (количество элементов)
} list_t;

// Прототипы функций для работы со связным списком
list_t* create_list(void);                      // Создать список
node_t* create_node(int x, node_t* next);       // Создать элемент списка (вспомогательная)
node_t* append_list(list_t* const lst, int x);  // Добавить элемент в конец списка
node_t* prepend_list(list_t* const lst, int x); // Добавить элемент в начало списка
int pop_list(list_t * const lst);               // Извлечь первый элемент списка
void print_list(const list_t * const lst);      // Вывести список
void free_list(list_t * const lst);             // Удалить список
void copy_list(int k);                          // Копирует список (все для работы копирования)

int main(void)
{
    /*
    Создаем новый связный список.
    Храним на стеке указатель на список.
    */
    list_t* plist = create_list();
    // Добавляем в конец списка i-ое значение
    for (int i=0; i<10; ++i) {
        append_list(plist, i);
    }
    // Выводим список. Должно быть 0 1 2 3 4 5 6 7 8 9
    print_list(plist);
    // Добавляем в начало списка число 9000
    prepend_list(plist, 9000);
    /*
    Снова выводим список.
    Проверяем, что число появилось в начале списка
    Должно быть 9000 0 1 2 3 4 5 6 7 8 9
    */
    print_list(plist);
    // Забираем число из начала связного списка (это 9000)
    pop_list(plist);
    // Забираем еще раз число из начала связного списка (это теперь 0)
    pop_list(plist);
    // Забираем еще раз число из начала связного списка (это теперь 1)
    pop_list(plist);
    /*
     Снова выводим список.
     После 3-х извлечений должно быть 2 3 4 5 6 7 8 9
     */
    print_list(plist);
    copy_list(3);               //Чтоб работало копирование
    // Удаляем список
    free_list(plist);
    return 0;
}

/*
 Создать список
 Функция создает новый связный список. По факту мы создаем контейнер
 с указателем на начало списка и счетчиком элементов.
 @return list_t* — указатель на созданный связный список
 */
list_t* create_list(void)
{
    // Выделяем в heap (куча) память под новый список (на самом деле только под контейнер)
    list_t* p_new_list = (list_t*)malloc(sizeof(list_t));
    // Заполняем значениями по-умолчанию
    p_new_list->head = NULL;
    p_new_list->size = 0;
    // Возвращаем указатель на новый связный список
    return p_new_list;
}

/*
 Создать элемент списка
 Функция вспомогательная, так как самостоятельно ей пользоваться неудобно. Потому что надо вручную
 передавать указатель на следующий элемент. А затем полученный новый указатель вставлять в список.
 
 @param  int x — значение элемента
 @param  node_t* next — указатель на следующий элемент
 @return node_t* — указатель на созданный элемент
 */
node_t* create_node(int x, node_t* next)
{
    // Выделяем в heap (куча) память под новый элемент
    node_t* p_new_node = (node_t*)malloc(sizeof(node_t));
    if (p_new_node == NULL) {
        return NULL;
    }
    
    // Заполняем поля структуры в новом элементе
    p_new_node->data=x;
    p_new_node->next=next;
    
    // Возвращаем указатель на новый элемент
    return p_new_node;
}

/*
 Добавить элемент в конец списка
 
 @param  list_t* const lst — указатель на связный список (контейнер)
 @param  int x — значение элемента
 @return node_t* — указатель на добавленный элемент
 */
node_t* append_list(list_t* const lst, int x)
{
    // Создаем новый элемент. Поле next указывает в NULL, так как элемент поседний
    node_t* p_new_node = create_node(x, NULL);
    
    /*
     Чтобы записать в конец списка, мы должны дойти до его конца.
     Идем по списку
     */
    node_t* current = lst->head; // Начинаем с головы списка
    if (current != NULL)
    { //Если список не пустой
        while (current->next != NULL) {
            current = current->next;
        }
        // Здесь мы находимся на последнем элементе. На него указывает current.
        // У последнего элемента next указыает в NULL, так как за ним ничего нет.
        // Заменяем NULL на указатель на новый элемент.
        current->next = p_new_node;
    } else
    { //Если список пустой
        // Делаем головой списка новый элемент
        lst->head = p_new_node;
    }
    // Инкрементируем счетчик (длина списка)
    ++lst->size;
    
    // Возвращаем указатель на новый элемент
    return p_new_node;
}

/*
 Добавить элемент в начало списка
 
 @param  list_t* const lst — указатель на связный список (контейнер)
 @param  int x — значение элемента
 @return node_t* — указатель на добавленный элемент
 */
node_t* prepend_list(list_t* const lst, int x)
{
    // Создаем новый элемент. Поле next указывает на текущую голову,
    // так как элемент будет стоять первым в списке
    node_t* p_new_node = create_node(x, lst->head);
    if (p_new_node != NULL) {
        // Делаем головой списка новый элемент
        lst->head = p_new_node;
        // Инкрементируем счетчик (длина списка)
        ++lst->size;
    }
    
    // Возвращаем указатель на новый элемент
    return p_new_node;
}

/*
 Извлечь первый элемент списка
 Извлечение — это возврат первого элемента из списка + удаление его.
 
 @param  list_t* const lst — указатель на связный список (контейнер)
 @return int — значение первого элемента списка
 */
int pop_list(list_t * const lst)
{
    // Если список пустой, то возвращаем 0. Это наша договоренность.
    if (lst->head == NULL) {
        return 0;
    }
    // Запоминаем куда указывает элемент. Иначе данные потеряются, когда мы его удалим
    node_t* next = lst->head->next;
    // Запоминаем значение элемента. Иначе данные потеряются, когда мы его удалим
    int data = lst->head->data;
    // Освобождаем память, которую выделяли для элемента (удаляем)
    free(lst->head);
    // Новая голова — то, куда указывал первый элемент
    lst->head = next;
    // Декрементируем счетчик (длина списка)
    --lst->size;
    
    // Возвращаем сохранненое значение элемента
    return data;
}

/*
 Вывести список
 Выводим элементы связного списка один за одним через пробел
 
 @param  const list_t * const lst — указатель на связный список (контейнер)
 */
void print_list(const list_t * const lst)
{
    // Если список пустой, то ничего не делаем
    if (lst->head == NULL) {
        return;
    }
    // Идем по списку. Начинаем с головы
    node_t* current = lst->head;
    while (current != NULL) {
        // Выводим значение каждого элемента
        printf("%i ", current->data);
        current = current->next;
    }
    // Заканчиваем строку
    printf("\n");
}

/*
 Удалить список
 Освобождаем память
 
 @param  list_t * const — указатель на связный список (контейнер)
 */
void free_list(list_t * const lst)
{
    // Удаляем память элементов. Имеет смысл если список не пустой.
    if (lst->head != NULL) {
        // Идем по списку. Начинаем с головы
        node_t* current = lst->head;
        while (current != NULL) {
            // Запоминаем куда указывает элемент. Мы его удалим и данные потеряются
            node_t* next = current->next;
            // Освобождаем память, которую выделяли для элемента (удаляем)
            free(current);
            current = next;
        }
    }
    // Удаляем список (контейнер)
    free(lst);
}

// Копирование                                                                        
void copy_list(int k)
{
    list_t* plist = create_list();
    for(int j = 1; j < k; ++j)
    {
        print_list(plist);
    }
}