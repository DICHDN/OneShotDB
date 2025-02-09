## Задание 2

В дополнение к классам-заместителям VeryHeavyDatabase, реализованным на лекции, реализуйте класс

    class OneShotDB : VeryHeavyDatabase {

    explicit OneShotDB (VeryHeavyDatabase* real_object, size_t shots=1) : ...
    }


Он должен возвращать данные по ключу из реального объекта то количество раз, которое указано в конструкторе. Исчерпав лимит получения данных, метод GetData всегда возвращает строку error. 

Пример использования:

    auto real_db = VeryHeavyDatabase();
    auto limit_db = OneShotDB(std::addressof(real_db), 2);
    std::cout << limit_db.GetData("key") << std::endl;
    std::cout << limit_db.GetData("key") << std::endl;
    std::cout << limit_db.GetData("key") << std::endl;

Output:

    >>> value
    >>> value
    >>> error