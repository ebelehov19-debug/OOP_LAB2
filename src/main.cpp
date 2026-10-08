#include "string.h"
#include <exception>
#include <iostream>
#include <limits>
#include <utility>

int main()
{
    String first;
    String second;
    int choice = -1;

    while (true)
    {
        std::cout << "\n1. Ввести первую строку\n"
                  << "2. Ввести вторую строку\n"
                  << "3. Вывести обе строки\n"
                  << "4. Добавить символ к первой строке\n"
                  << "5. Добавить текст к первой строке\n"
                  << "6. Добавить вторую строку к первой\n"
                  << "7. Найти подстроку в первой строке\n"
                  << "8. Перенести первую строку по словам\n"
                  << "9. Показать длину, ёмкость и пустоту строк\n"
                  << "10. Скопировать первую строку во вторую\n"
                  << "11. Переместить первую строку во вторую\n"
                  << "12. Обменять строки\n"
                  << "0. Выход\n"
                  << "Выберите операцию: ";

        if (!(std::cin >> choice))
        {
            if (std::cin.eof() || std::cin.bad())
            {
                return 0;
            }

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка ввода! Введите целый номер операции.\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        try
        {
            String input;

            if (choice == 1 || choice == 2 || choice == 4 || choice == 5 || choice == 7)
            {
                std::cout << (choice == 4 ? "Введите символ: " : "Введите текст: ");
                char c;

                while (std::cin.get(c) && c != '\n')
                {
                    input.push_back(c);
                }

                if (std::cin.bad() || (std::cin.eof() && input.empty()))
                {
                    return 0;
                }
            }

            switch (choice)
            {
                case 0:
                    return 0;

                case 1:
                    first = std::move(input);
                    break;

                case 2:
                    second = std::move(input);
                    break;

                case 3:
                {
                    std::cout << "Первая строка: ";
                    first.print(std::cout);
                    std::cout << "\nВторая строка: ";
                    second.print(std::cout);
                    std::cout << '\n';
                    break;
                }

                case 4:
                {
                    if (input.size() != 1)
                    {
                        std::cout << "Введите один символ: латинскую букву, цифру или знак.\n";
                        break;
                    }

                    first.push_back(input.c_str()[0]);
                    break;
                }

                case 5:
                    first.append(input.c_str());
                    break;

                case 6:
                    first.append(second);
                    break;

                case 7:
                {
                    const std::size_t position = first.find(input);
                    if (position == String::npos)
                    {
                        std::cout << "Подстрока не найдена.\n";
                    }
                    else
                    {
                        std::cout << "Позиция: " << position << '\n';
                    }
                    break;
                }

                case 8:
                {
                    int width = 0;
                    std::cout << "Ширина строки: ";
                    if (!(std::cin >> width))
                    {
                        if (std::cin.eof() || std::cin.bad())
                        {
                            return 0;
                        }

                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Ошибка ввода! Введите целую ширину.\n";
                        break;
                    }

                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    if (width <= 0)
                    {
                        std::cout << "Ширина должна быть положительным целым числом.\n";
                        break;
                    }

                    const String wrapped = first.wrap(static_cast<std::size_t>(width));
                    std::cout << "Результат переноса:\n";
                    wrapped.print(std::cout);
                    std::cout << '\n';
                    break;
                }

                case 9:
                {
                    std::cout << "Первая строка: длина = " << first.size()
                              << ", ёмкость = " << first.capacity()
                              << ", пустая = " << (first.empty() ? "да" : "нет")
                              << "\nВторая строка: длина = " << second.size()
                              << ", ёмкость = " << second.capacity()
                              << ", пустая = " << (second.empty() ? "да" : "нет") << '\n';
                    break;
                }

                case 10:
                    second = first;
                    std::cout << "Первая строка скопирована во вторую.\n";
                    break;

                case 11:
                    second = std::move(first);
                    std::cout << "Первая строка перемещена во вторую. Первая строка теперь пустая.\n";
                    break;

                case 12:
                    first = second;
                    std::cout << "Строки обменены.\n";
                    break;

                default:
                    std::cout << "Неизвестная операция. Выберите номер от 0 до 12.\n";
                    break;
            }
        }
        catch (const std::exception& error)
        {
            std::cout << "Ошибка: " << error.what() << '\n';
        }
    }
}
