import re

class Package:
    def __init__(self, name, version, dependencies=None):
        self.name = name
        self.version = version  # версия пакета, например, "1.0.0"
        self.dependencies = dependencies if dependencies else {}  # зависимости пакета

    def __repr__(self):
        return f"{self.name} {self.version} -> {self.dependencies}"

# версии пакетов и их зависимости
packages = {
    "root": Package("root", "1.0.0", {"foo": "^1.0.0", "target": "^2.0.0"}),
    "foo_v1.0.0": Package("foo", "1.0.0", {}),
    "foo_v1.1.0": Package("foo", "1.1.0", {"left": "^1.0.0", "right": "^1.0.0"}),
    "left_v1.0.0": Package("left", "1.0.0", {"shared": ">=1.0.0"}),
    "right_v1.0.0": Package("right", "1.0.0", {"shared": "<2.0.0"}),
    "shared_v1.0.0": Package("shared", "1.0.0", {"target": "^1.0.0"}),
    "shared_v2.0.0": Package("shared", "2.0.0", {}),
    "target_v1.0.0": Package("target", "1.0.0", {}),
    "target_v2.0.0": Package("target", "2.0.0", {}),
}

# функция для парсинга зависимости вида "^1.0.0"
def parse_dependency(version_constraint):
    match = re.match(r"([<>^]=?)(\d+)\.(\d+)\.(\d+)", version_constraint)
    if match:
        operator, major, minor, patch = match.groups()
        return operator, int(major), int(minor), int(patch)
    else:
        raise ValueError(f"неправильный формат зависимости: {version_constraint}")

# функция для проверки соответствия версий
def check_version(version, operator, major, minor, patch):
    v_major, v_minor, v_patch = map(int, version.split('.'))

    if operator == "^":
        return v_major == major and (v_minor > minor or (v_minor == minor and v_patch >= patch))
    elif operator == ">=":
        return (v_major > major or (v_major == major and v_minor > minor) or
                (v_major == major and v_minor == minor and v_patch >= patch))
    elif operator == "<":
        return v_major < major or (v_major == major and v_minor < minor) or (v_major == major and v_patch < patch)
    return False

# функция для поиска подходящей версии пакета по ограничению
def get_package_by_version(packages, package_name, version_constraint):
    for key, package in packages.items():
        if package.name == package_name:
            operator, major, minor, patch = parse_dependency(version_constraint)
            if check_version(package.version, operator, major, minor, patch):
                return package
    raise KeyError(f"не удалось найти подходящую версию для {package_name} с ограничением {version_constraint}")

# функция для проверки всех зависимостей пакета
def check_dependencies(package_name, packages):
    package = packages[package_name]
    for dep_name, version_constraint in package.dependencies.items():
        dep_package = get_package_by_version(packages, dep_name, version_constraint)  # найдем зависимый пакет
        dep_key = f"{dep_package.name}_v{dep_package.version}"  # создаем ключ на основе имени и версии
        print(
            f"проверяем зависимость {package.name} -> {dep_package.name} {dep_package.version} ({version_constraint})")
        if dep_key not in packages:
            print(f"ошибка: не найден ключ {dep_key}")
            return False
        if not check_dependencies(dep_key, packages):  # рекурсивно проверим зависимости зависимого пакета
            return False
    return True

# функция для проверки всей системы пакетов
def validate_package_system(packages):
    for package_name in packages:
        try:
            if not check_dependencies(package_name, packages):
                print(f"зависимости пакета {package_name} не удовлетворены")
            else:
                print(f"все зависимости пакета {package_name} удовлетворены")
        except KeyError as e:
            print(f"ошибка: {e}")

# проверяем всю систему
validate_package_system(packages)
