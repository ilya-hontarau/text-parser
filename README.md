# solution-of-testing-problem
Для компиляции необходим компилятор  с поддержкой C++17 и с флагом компиляции /std:c++17.

how to run:
run programm exe with this flags

1)index folder

	-i [folder_path] [-r]
	-r -recursive searching(none recursiving is setting by default)
	NOTE: programm asks for printing information indexing folder
	
2)search word in indexing folder

	[folder_path] -s
	NOTE: you should index file before searching
	
3)index and search 

	-i [folder_path] -s "word" [-r]
	-r - recursive searching(none recursiving is setting by default)

Условия задачи. 
Есть фолдер с текстовыми файлами в формате UTF-8. Файлы могут быть на английском и русском языках. 
Необходимо разработать компонент с двумя интерфейсами: 
-	Indexer 
-	Searcher 
 
Требования к Indexer 
Indexer должен отпроцессить все файлы из заданного фолдера. 
Для каждого файла Indexer должен: 
-	Разбить текст на предложения 
-	Разбить каждое предложение на слова считая, что слово это буквы подряд или цифры подряд - 	Для каждого слова сохранить статистику:  
o имя файла,  o номер предложения o смещение слова в предложении 
Indexer должен построить статистику по словам для всех файлов из фолдера. 
Indexer должен иметь возможность сохранять статистику на диск и затем загружать ее без повторного процессинга папки. 
 
Например, 
Файл “Example.txt” содержит текст “Minsk is the capital and largest city of Belarus. The population in January 2018 was 1982444.” 

Sent#0: “Minsk is the capital and largest city of Belarus.” 

Sent#1: “The population in January 2018 was 1982444.” 

Word: “Minsk”: {“Example.txt”, (Sent#0, offset = 0)} 

Word: “is”: {“Example.txt”, (Sent#0, offset = 6)} 

Word: “the”: {“Example.txt”, ((Sent#0, offset = 9), (Sent#1, offset = 0))} 

Требования к Searcher 
 
Searcher должен обеспечивать эффективный поиск статистики по слову. 
 
Например, 
Для запроса “Minsk” (смотри выше) результат должен быть такой:  
-  	“Minsk”:  
o	File “Example.txt” 
▪	(Sent#0, offset = 0) 

Запрос “the”: 

o	File “Example.txt” 

	▪	(Sent#0, offset = 9) 
	▪	(Sent#1, offset = 0) 
