// Rnd project Randomize_stdout_1.go
package main

import (
	"bufio"
	"fmt"
	"log"
	"math/rand"
	"os"
	"strconv"
	"strings"
	"time"
)

func main() {
	fmt.Println("Генератор случайных чисел в диапазоне от 1 до 100", "\n", "Введите желаемое количеcтво чисел ниже:")
	reader := bufio.NewReader(os.Stdin)
	input, err := reader.ReadString('\n')
	if err != nil {
		fmt.Println("Ошибка ввода bufio.NewReader")
		log.Fatal(err)
	}
	input = strings.TrimSpace(input)
	ncount, err := strconv.Atoi(input)
	if err != nil {
		fmt.Println("Ошибка ввода:", input, "- не целое число!")
		log.Fatal(err)
	}

	seconds := time.Now().Unix()
	rand.Seed(seconds + int64(ncount))
	for x := 0; x < ncount; x++ {
		answer := rand.Intn(100) + 1

		fmt.Println(answer)
	}
	fmt.Println("Готово!")
}
