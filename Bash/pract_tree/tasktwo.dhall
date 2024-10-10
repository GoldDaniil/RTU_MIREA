let generateGroup = λ(i : Natural) → "ИКБО-" ++ Natural/show i ++ "-20"

let groupList = [ generateGroup i | i <- List/replicate 24 1 + i ]

let student1 = { age = 19, group = "ИКБО-4-20", name = "Иванов И.И." }

let student2 = { age = 18, group = "ИКБО-5-20", name = "Петров П.П." }

let student3 = { age = 18, group = "ИКБО-5-20", name = "Сидоров С.С." }

let student4 = { age = 18, group = "ИКБО-6-20", name = "Ваше Имя" }

in  { groups = groupList
    , students = [ student1, student2, student3, student4 ]
    , subject = "Конфигурационное управление"
    }
