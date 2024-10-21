import java.util.*

fun main() {
    val scanner = Scanner(System.`in`)
    var exit = false

    while (!exit) {
        println("выберите задание (введите номер задания от 1 до 3) или 'exit' для выхода:")
        println("1 - задача 1")
        println("2 - задача 2")
        println("3 - задача 3")

        val input = scanner.nextLine()

        when (input) {
            "1" -> task1()
            "2" -> task2()
            "3" -> task3()
            "exit" -> {
                exit = true
                println("выход")
            }
            else -> println("ошибка-  введи снова!")
        }
    }
}

fun task1() {
    println("введите значения a, b, m и n (разделенные пробелом):")
    val (a, b, m, n) = readLine()!!.split(" ").map { it.toDouble() }

    if ((m <= a && n <= b) || (m <= b && n <= a)) {
        println("YES")
    } else {
        println("NO")
    }
}

fun task2() {
    println("введите строку ДНК:")
    val dna = readLine()!!

    val countA = dna.count { it == 'A' }
    val countT = dna.count { it == 'T' }
    val countG = dna.count { it == 'G' }
    val countC = dna.count { it == 'C' }

    println("$countA $countT $countG $countC")
}

fun task3() {
    println("введите строку для подсчета гласных:")
    val input = readLine()!!
    val result = countVowels(input)
    println("количество гласных: $result")
}

fun countVowels(str: String): Int {
    val vowels = "aeiouAEIOU"
    return str.count { it in vowels }
}
