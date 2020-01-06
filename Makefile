all: output2.txt compile&run
clean:
	rm output1.txt output2.txt

compile&run: supermarket_sales.csv Final_Project_new.c
	gcc -o Final_Project_new Final_Project_new.c
	./Final_Project_new

output2.txt: supermarket_sales.csv
	cat supermarket_sales.csv | grep -i "Fashion accessories" | cut -d "," -f 10 | awk '{s+=$$1} END {printf "%0.2f", s}'> output2.txt
