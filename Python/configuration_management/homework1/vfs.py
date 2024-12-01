import zipfile
import os

class VFS:
    def __init__(self, zip_path):
        self.zip_path = zip_path
        self.zip_file = zipfile.ZipFile(zip_path, 'a')#'a' для добавления файлов

    def file_exists(self, path):
        try:
            all_files = self.zip_file.namelist()#существует ли файл в архиве
            return path in all_files
        except Exception as e:
            raise Exception(f"err checking file existence: {str(e)}")

    def list_dir(self, path):
        try:
            all_files = self.zip_file.namelist()#список всех файлов в архиве
            normalized_path = path.lstrip('/')#убираем начальный "/"

            if normalized_path and not normalized_path.endswith('/'):
                normalized_path += '/'#чек путь заканчивается "/"?

            contents = set()
            for file in all_files:
                if file.startswith(normalized_path):#файл в каталоге?
                    relative_path = file[len(normalized_path):].lstrip('/')
                    first_part = relative_path.split('/')[0]
                    if first_part:
                        contents.add(first_part)#уникальные файлы/папки в результат

            return sorted(contents)
        except Exception as e:
            raise Exception(f"err reading directory '{path}': {str(e)}")

    def read_file(self, path):
        try:
            with self.zip_file.open(path) as f:
                return f.read().decode('utf-8')
        except KeyError:
            raise KeyError(f"there is no file named '{path}' in the archive")
        except Exception as e:
            raise Exception(f"err reading file '{path}': {str(e)}")

    def directory_exists(self, path):
        normalized_path = path.lstrip('/')
        if not normalized_path.endswith('/'):
            normalized_path += '/'
        return any(file.startswith(normalized_path) for file in self.zip_file.namelist())

    def write_file(self, path, content):
        try:
            with self.zip_file.open(path, 'w') as f:#открываем архив для записи
                f.write(content.encode('utf-8'))
        except Exception as e:
            raise Exception(f"err writing file '{path}': {str(e)}")

    def delete_file(self, path):
        try:
            all_files = self.zip_file.namelist()#удалить файл - пересоздаем архив без удаленного файла
            if path not in all_files:
                raise FileNotFoundError(f"{path} not found in archive")

            new_zip_path = self.zip_path + ".temp"
            with zipfile.ZipFile(new_zip_path, 'w') as new_zip:
                for file in all_files:
                    if file != path:
                        new_zip.writestr(file, self.zip_file.read(file))

            os.rename(new_zip_path, self.zip_path)#замена старый архив новым
        except Exception as e:
            raise Exception(f"err deleting file '{path}': {str(e)}")

    def close(self):
        self.zip_file.close()
