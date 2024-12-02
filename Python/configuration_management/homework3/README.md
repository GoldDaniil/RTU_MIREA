# конфигурационный трансформатор
## описание
проект предназначен для проверки синтаксиса и преобразования текстовых конфигурационных файлов в стандартный формат. он обрабатывает входные данные, такие как массивы, строки, числа, XML-теги и комментарии, и преобразует их в унифицированный вид с учетом заданных синтаксических правил

## особенности
- **поддержка синтаксиса:**
  - валидация имен, чисел, строк, массивов и XML-тего.
- **работа с XML:** 
  - поддержка вложенных тегов с проверкой соответствия открывающих и закрывающих тегов
- **массивы:** 
  - обработка массивов, содержащих числа и строки, например `'(1 "text")'`
- **константы:**
  - объявление и использование констант в формате `def name value;` и `$name$`
- **выходной формат:**
  - унифицированное представление строк, массивов, чисел и XML-тегов

## реализация
<img width="771" alt="Screenshot 2024-12-02 at 10 21 09" src="https://github.com/user-attachments/assets/907308ee-3178-4050-afb7-525375b37fb8">
<img width="771" alt="Screenshot 2024-12-02 at 10 21 06" src="https://github.com/user-attachments/assets/b42a5336-d9e2-4853-8630-1e97376c3092">
<img width="771" alt="Screenshot 2024-12-02 at 10 20 52" src="https://github.com/user-attachments/assets/07703a89-affe-4c19-aab1-e31449b595d8">

<img width="771" alt="Screenshot 2024-12-02 at 10 20 58" src="https://github.com/user-attachments/assets/d2905e36-3788-443c-ab9a-cfc844f2eead">


## пример работы
### входные данные:
```text
* Это однострочный комментарий
<config>
    <setting>enabled</setting>
    <value>42</value>
    <array>'( 1 2 3 4 "text" )'</array>
</config>
name_1
42
"string_value"
end
```
### выходные данные:

выходной текст:

* Это однострочный комментарий
config:
  setting: enabled
  value: 42
array:   1   2   3   4   "text"  
name: name_1
number: 42
[[string_value]]

<img width="730" alt="Screenshot 2024-12-02 at 10 26 36" src="https://github.com/user-attachments/assets/84001ed4-4fd9-4943-b38f-69d92957c2d2">


