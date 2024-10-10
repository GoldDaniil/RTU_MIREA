let generateGroup = λ(i : Natural) → "ИКБО-" ++ Natural/show i ++ "-20"

let numbers = [ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 ]

let groupList = List/map Natural Text generateGroup numbers

let student1 = { age = 19, group = "ИКБО-4-20", name = "Иванов И.И." }

let student2 = { age = 18, group = "ИКБО-5-20", name = "Петров П.П." }

let student3 = { age = 18, group = "ИКБО-5-20", name = "Сидоров С.С." }

let student4 = { age = 18, group = "ИКБО-6-20", name = "Ваше Имя" }

in  { groups = groupList
    , students = [ student1, student2, student3, student4 ]
    , subject = "Конфигурационное управление"
    }
