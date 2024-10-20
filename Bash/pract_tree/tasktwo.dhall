let Prelude = https://prelude.dhall-lang.org/v20.1.0/package.dhall

let generateGroup = λ(i : Natural) → "ИКБО-" ++ Natural/show i ++ "-20"

-- баг с enumFromTo
let groupList =
      Prelude.List.map Natural Text generateGroup
        [ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 ]

let Student = { age : Natural, group : Text, name : Text }

let students : List Student =
      [ { age = 19, group = "ИКБО-4-20", name = "Иванов И.И." }
      , { age = 18, group = "ИКБО-5-20", name = "Петров П.П." }
      , { age = 18, group = "ИКБО-5-20", name = "Сидоров С.С." }
      , { age = 20, group = "ИКБО-6-20", name = "Кузнецов К.К." }
      ]

let output =
      { groups = groupList
      , students = students
      , subject = "Конфигурационное управление"
      }

in output
