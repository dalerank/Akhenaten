#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Скрипт для парсинга параметров домов из Pharaoh_Model_Easy.txt
и вывода их в формате houses.js
"""

import re
import sys
import codecs

# Настройка кодировки для вывода в консоль Windows
if sys.platform == 'win32':
    sys.stdout = codecs.getwriter('utf-8')(sys.stdout.buffer, 'strict')

# Названия домов по порядку (из houses.js)
HOUSE_NAMES = [
    "House 1 - Small Hut",
    "House 2 - Large Hut", 
    "House 3 - Small Shanty",
    "House 4 - Large Shanty",
    "House 5 - Small Cottage",
    "House 6 - Large Cottage",
    "House 7 - Small Homestead",
    "House 8 - Large Homestead",
    "House 9 - Small Apartment",
    "House 10 - Large Apartment",
    "House 11 - Small Residence",
    "House 12 - Medium Residence",
    "House 13 - Large Residence",
    "House 14 - Grand Residence",
    "House 15 - Small Manor",
    "House 16 - Medium Manor",
    "House 17 - Large Manor",
    "House 18 - Grand Manor",
    "House 19 - Estate",
    "House 20 - Palatial Estate"
]

# Имена параметров
PARAM_NAMES = [
    "devolve_desirability",  # a
    "evolve_desirability",   # b
    "entertainment",         # c
    "water",                 # d
    "religion",              # e
    "education",             # f
    "food",                  # g (market)
    "dentist",               # h (barber)
    "physician",             # i (bathhouse)
    "health",                # j
    "food_types",            # k (food)
    "pottery",               # l
    "linen",                 # m
    "jewelry",               # n
    "beer",                  # o
    "crime_risk",            # p (increment)
    "crime_risk_base",       # q (base)
    "prosperity",            # r
    "max_people",            # s (capacity)
    "tax_multiplier",        # t
    "malaria_risk",          # u
    "disease_risk"           # v
]

def parse_house_line(line):
    """
    Парсит строку с параметрами дома из Pharaoh_Model_Easy.txt
    Формат: House N - Name,{,val1,val2,val3,...},...
    """
    # Ищем все числа в фигурных скобках
    match = re.search(r'\{,([-\d.]+),([-\d.]+),([-\d.]+),([-\d.]+),([-\d.]+),([-\d.]+),([-\d.]+),([-\d.]+),([-\d.]+),([-\d.]+),([-\d.]+),([-\d.]+),([-\d.]+),([-\d.]+),([-\d.]+),([-\d.]+),([-\d.]+),([-\d.]+),([-\d.]+),([-\d.]+),([-\d.]+),([-\d.]+),', line)
    
    if not match:
        return None
    
    # Извлекаем все 22 параметра
    params = [match.group(i) for i in range(1, 23)]
    
    # Преобразуем в числа
    try:
        params = [float(p) if '.' in p else int(p) for p in params]
    except ValueError:
        return None
    
    return params

def format_house_model(house_num, all_params):
    """
    Форматирует параметры дома в стиле houses.js
    all_params - список из 5 элементов (по одному для каждого уровня сложности),
    каждый содержит 22 параметра
    """
    house_name = HOUSE_NAMES[house_num - 1] if house_num <= len(HOUSE_NAMES) else f"House {house_num}"
    
    output = []
    output.append(f"\n{'='*60}")
    output.append(f"{house_name}")
    output.append(f"{'='*60}\n")
    output.append("model {")
    
    # Создаем массивы из 5 значений для каждого параметра
    # all_params[0] - VeryEasy, [1] - Easy, [2] - Normal, [3] - Hard, [4] - Impossible
    
    for param_idx, param_name in enumerate(PARAM_NAMES):
        values = []
        for difficulty_params in all_params:
            if difficulty_params:
                values.append(str(difficulty_params[param_idx]))
            else:
                values.append("0")  # Значение по умолчанию, если данных нет
        
        values_str = ",".join(values)
        output.append(f"  {param_name}[{values_str}]")
    
    output.append("}\n")
    
    return "\n".join(output)

def read_houses_from_file(filename):
    """
    Читает данные домов из файла
    Возвращает список параметров для всех домов
    """
    try:
        with open(filename, 'r', encoding='utf-8') as f:
            lines = f.readlines()
    except FileNotFoundError:
        print(f"ПРЕДУПРЕЖДЕНИЕ: Файл {filename} не найден!")
        return []
    
    houses_data = []
    
    for line in lines:
        if line.startswith('House') and '{' in line:
            params = parse_house_line(line)
            if params:
                houses_data.append(params)
    
    return houses_data

def main(output_file=None):
    """Основная функция"""
    print("="*80)
    print("ПАРСИНГ ПАРАМЕТРОВ ДОМОВ ИЗ ФАЙЛОВ СЛОЖНОСТИ")
    print("="*80)
    
    # Если указан файл вывода, перенаправляем вывод
    if output_file:
        import io
        output_buffer = io.StringIO()
        original_stdout = sys.stdout
        sys.stdout = output_buffer
    
    # Файлы для чтения (по порядку сложности)
    difficulty_files = [
        'Pharaoh_Model_VeryEasy.txt',
        'Pharaoh_Model_Easy.txt',
        'Pharaoh_Model_Normal.txt',
        'Pharaoh_Model_Hard.txt',
        'Pharaoh_Model_Impossible.txt'
    ]
    
    difficulty_names = ['VeryEasy', 'Easy', 'Normal', 'Hard', 'Impossible']
    
    # Читаем данные из всех файлов
    all_difficulties = []
    for i, filename in enumerate(difficulty_files):
        print(f"\nЧитаем {difficulty_names[i]}: {filename}...")
        houses_data = read_houses_from_file(filename)
        all_difficulties.append(houses_data)
        print(f"  Найдено домов: {len(houses_data)}")
    
    # Проверяем, что все файлы содержат одинаковое количество домов
    max_houses = max(len(data) for data in all_difficulties if data)
    
    if max_houses == 0:
        print("\nОШИБКА: Ни в одном файле не найдено данных о домах!")
        return
    
    print("\n" + "="*80)
    print(f"РЕЗУЛЬТАТЫ (массивы: VeryEasy, Easy, Normal, Hard, Impossible)")
    print("="*80)
    
    # Обрабатываем каждый дом
    for house_idx in range(max_houses):
        # Собираем параметры для этого дома из всех файлов сложности
        house_params_all_difficulties = []
        
        for difficulty_data in all_difficulties:
            if house_idx < len(difficulty_data):
                house_params_all_difficulties.append(difficulty_data[house_idx])
            else:
                house_params_all_difficulties.append(None)
        
        # Форматируем и выводим
        output = format_house_model(house_idx + 1, house_params_all_difficulties)
        print(output)
    
    print("\n" + "="*80)
    print(f"Всего обработано домов: {max_houses}")
    print("="*80)

if __name__ == "__main__":
    main()

