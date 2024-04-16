# Исследование оптимизаций кода на примере хэш-таблицы

## Введение

Данный проект состоит из двух частей:
1. Исследовать заселенность хэш-таблицы для определленного набора хэш-функций.
2. Оптимизировать несколько участков кода с наименьшим числом строк кода.

## Скачивание и установка проекта

Для установки программы используются утилиты `make` и `git`.

```CMAKE
    git clone git@github.com:EntryFrager/HashTable.git
    cd HashTable
    make
    ./HashTable.exe
```

## Немного про хэш-таблицы

Хеш-таблица — структура данных, реализующая интерфейс ассоциативного массива, а именно, она позволяет хранить пары (ключ, значение) и выполнять три операции: операцию добавления новой пары, операцию удаления и операцию поиска пары по ключу.

Существуют два основных варианта хеш-таблиц: с открытой адресацией и списками. Хеш-таблица является массивом, элементы которого есть пары (хеш-таблица с открытой адресацией) или списки пар (хеш-таблица со списками).

Выполнение операции в хеш-таблице начинается с вычисления хеш-функции от ключа. Получающееся хеш-значение играет роль индекса в массиве. Затем выполняемая операция (добавление, удаление или поиск) перенаправляется объекту, который хранится в соответствующей ячейке массива.

Ситуация, когда для различных ключей получается одно и то же хеш-значение, называется коллизией. Такие события не так уж и редки — например, при вставке в хеш-таблицу размером 365 ячеек всего лишь 23 элементов вероятность коллизии уже превысит 50% (если каждый элемент может равновероятно попасть в любую ячейку) — см. парадокс дней рождения. Поэтому механизм разрешения коллизий — важная составляющая любой хеш-таблицы.


> [!NOTE]
>
> Более подробно про хэш-таблицы вы можете прочитать [здесь](https://ru.wikipedia.org/wiki/%D0%A5%D0%B5%D1%88-%D1%82%D0%B0%D0%B1%D0%BB%D0%B8%D1%86%D0%B0).

## Статистические данные для хэш-таблиц

Пусть $Index[m]$ – хеш-таблица с $m$ позициями, в которую занесено $n$ пар (key,
value). Отношение $\alpha = \frac {n} {m}$ называется коэффициентом заполнения хеш-таблицы.

Коэффициент заполнения $\alpha$ позволяет судить о качестве хеш-функции:
пусть $M = \frac {1} {m} \Sigma_ {i = 0} ^ {m} |*Index[i]|$– средняя длина списков; если `hash(key)` – «хорошая» хеш-функция, то дисперсия $D = \frac {1} {m} \Sigma_ {i = 0} ^ {m - 1} (|M - *Index[i]|) ^ 2 \leq \alpha$


> [!NOTE]
>
> Данная информация взята с этого [сайта](http://algcourse.cs.msu.su/wp-content/uploads/2010/12/Lect13.pdf).

## Первая часть работы

Для исследования заселенности хэш-таблицы были взяты хэш-функции, которые в качестве хэша возрващали:

1. Ноль
2. ASCII код первой буквы слова
3. Длину слова
4. Сумму всех ASCII кодов букв(контрольная сумма)
5. Частное контрольной суммы и длины слова
6. Для пустой строки - `0`,
7.
8. Хэш-функция - `crc32`

Для заполнения хэш-таблицы был взят текст Евгения Онегина на английском языке, из которого были удалены все знаки препинания и который был разбит на отдельные слова. Всего слов было `14379`, уникальных из них `3473`.

Ниже преведены графики, отоброжающие зависимость количества коллизий от номера ячейки.

### 1. Функция, возврающая ноль

![overlfow](./graphics/1_table.png)

Все наши слова попали в первую ячейку. На графике это показано соответствующей пикой в нуле. Данное распределение является крайне неэффективным.

### 2. Функция, возврающая ASCII код первой буквы слова

![overlfow](./graphics/2_table.png)

Из графика видно, что наши слова распределились между ячейками от `65` до `122`.

### 3. Функция, возврающая длину слова

![overlfow](./graphics/3_table.png)

Из графика видим пику в самом начале.

### 4. Функция, возврающая контрольную сумму

![overlfow](./graphics/4_table.png)

Данное распределение лучше всех остальных, но все также непригодно для использования, так как из графика четко видны две пики и неравномерное распределение.

### 5. Функция, возврающая частное контрольной суммы и длины слова

![overlfow](./graphics/5_table.png)

На графике видна одна пика. В данном распределении все слова расположились около ячейки с номером `100`.

### 6. Функция, возврающая длину слова

![overlfow](./graphics/6_table.png)

На графике видны пики в начале и конце.

### 7. Функция, возврающая длину слова

![overlfow](./graphics/7_table.png)

Видны две пики в начале графика. Данная функция выдает лучшее распределение, нежели функция с циклическим сдвигом битов влево. Но данное распределения все еще является не допустимой к применению.

### 8. Хэш функция - `crc32`

![overlfow](./graphics/8_table.png)

На графике видны две пики. Среди всех хэш функций данная выдает самое лучшее распределение, но все равно не допустима к применению.

### Load фактор и дисперсия хэш-функций

Load фактор для всех функций был одинаковым и его значение было равно `7.2`.

| Номер хэш-функции | Дисперсия |
|-------------------|-----------|
| 1                 | 103274    |
| 2                 | 4060      |
| 3                 | 15764     |
| 4                 | 544       |
| 5                 | 6441      |
| 6                 | 557       |
| 7                 | 410       |
| 8                 | 396       |

## Вторая часть работы