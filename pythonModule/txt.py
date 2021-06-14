def open_txt_file(name_of_file : str) -> None:
    global file
    file = open(name_of_file, 'wt')

def write_data_to_file(timestamp: int, values: list) -> None:
    try:
        data = '{}, {}, {}, {}, {}\n'.format(timestamp, values[0], values[1], values[2], values[3])
        file.write(data)
    except:
        print('Input/Output error with data: {}.'.format(data))

def close_txt_file() -> None:
    file.close()