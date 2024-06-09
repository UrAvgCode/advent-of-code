# fetch advent of code inputs

import os
import requests
from datetime import datetime


def get_advent_of_code_input(year, day, session_cookie):
    url = f'https://adventofcode.com/{year}/day/{day}/input'
    cookies = {'session': session_cookie}
    response = requests.get(url, cookies=cookies)
    if response.status_code == 200:
        return response.text.rstrip()
    else:
        response.raise_for_status()


def save_input_to_file(directory, filename, data):
    os.makedirs(directory, exist_ok=True)
    file_path = os.path.join(directory, filename)
    with open(file_path, 'w') as file:
        file.write(data)


def fetch_advent_of_code_input(year, day, session_cookie):
    directory = f'../input/{year}/day_{day:02d}'
    filename = 'input.txt'
    file_path = os.path.join(directory, filename)

    if not os.path.exists(file_path):
        try:
            input_data = get_advent_of_code_input(year, day, session_cookie)
            save_input_to_file(directory, filename, input_data)
            print(f'input for day {day:02d} saved successfully')
        except requests.HTTPError as e:
            print(f'failed to fetch input for {year}-12-{day:02d}: {e}')
    else:
        print(f'file {file_path} already exists -> skipping')


def fetch_all_inputs():
    with open('session_cookie', 'r') as file:
        session_cookie = file.read().strip()

    current_date = datetime.now()
    if datetime.month == 12:
        end_year = current_date.year
        end_day = min(current_date.day, 25)
    else:
        end_year = current_date.year - 1
        end_day = 25

    start_year = 2020
    for year in range(start_year, end_year + 1):
        print(f'\nfetching inputs for {year}')
        for day in range(1, end_day + 1):
            fetch_advent_of_code_input(year, day, session_cookie)


if __name__ == '__main__':
    fetch_all_inputs()
