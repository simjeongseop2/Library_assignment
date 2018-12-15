#!/bin/bash

mkdir -p result

folder=$1
file=$2

function input_cmp() { #if v1 >= v2 && v1 <= v3 return 1 else return 0
	v1=$1 v2=$2 v3=$3
	y1=${v1:0:2} 
	y2=${v2:0:2}
	y3=${v3:0:2}
	m1=${v1:3:2} 
	m2=${v2:3:2}
	m3=${v3:3:2}
	d1=${v1:6:2} 
	d2=${v2:6:2}
	d3=${v3:6:2}
	pass=0
	if [ $y1 -gt $y2 ] 
	then
		pass=1
	elif [ $y1 -eq $y2 -a $m1 -gt $m2 ]
	then
		pass=1
	elif [ $y1 -eq $y2 -a $m1 -eq $m2 -a $d1 -gt $d2 ]
	then
		pass=1
	fi
	if [ $y1 -eq $y2 -a $m1 -eq $m2 -a $d1 -eq $d2 ]
	then
		pass=1
	fi

	if [ $pass -eq 0 ]
	then
		return 0
	fi
	if [ $y1 -lt $y3 ] 
	then
		return 1
	elif [ $y1 -eq $y3 -a $m1 -lt $m3 ]
	then
		return 1
	elif [ $y1 -eq $y3 -a $m1 -eq $m3 -a $d1 -lt $d3 ]
	then
		return 1
	fi
	if [ $y1 -eq $y3 -a $m1 -eq $m3 -a $d1 -eq $d3 ]
	then
		return 1
	fi
	return 0
}

function space_cmp() { #if v1 >= v2 && v1 <= v3 return 1 else return 0
	v1=$1 v2=$2 v3=$3
	y1=${v1:0:4} 
	y2=${v2:0:4}
	y3=${v3:0:4}
	m1=${v1:5:2} 
	m2=${v2:5:2}
	m3=${v3:5:2}
	d1=${v1:8:2} 
	d2=${v2:8:2}
	d3=${v3:8:2}
	t1=${v1:11:2}
	t2=${v2:11:2}
	t3=${v3:11:2}
	pass=0
	if [ $y1 -gt $y2 ] 
	then
		pass=1
	elif [ $y1 -eq $y2 -a $m1 -gt $m2 ]
	then
		pass=1
	elif [ $y1 -eq $y2 -a $m1 -eq $m2 -a $d1 -gt $d2 ]
	then
		pass=1
	elif [ $y1 -eq $y2 -a $m1 -eq $m2 -a $d1 -eq $d2 -a $t1 -gt $t2 ]
	then
		pass=1
	fi
	if [ $y1 -eq $y2 -a $m1 -eq $m2 -a $d1 -eq $d2 -a $t1 -eq $t2 ]
	then
		pass=1
	fi

	if [ $pass -eq 0 ]
	then
		return 0
	fi
	if [ $y1 -lt $y3 ] 
	then
		return 1
	elif [ $y1 -eq $y3 -a $m1 -lt $m3 ]
	then
		return 1
	elif [ $y1 -eq $y3 -a $m1 -eq $m3 -a $d1 -lt $d3 ]
	then
		return 1
	elif [ $y1 -eq $y3 -a $m1 -eq $m3 -a $d1 -eq $d3 -a $t1 -lt $t3 ]
	then
		return 1
	fi
	if [ $y1 -eq $y3 -a $m1 -eq $m3 -a $d1 -eq $d3 -a $t1 -eq $t3 ]
	then
		return 1
	fi
	return 0
}

if [ "$1" == "resource" ]
then
	mkdir -p ./result/resource
	if [ "$2" != "all" ]
	then
		echo "Type"$'\t'"Name" > ./result/resource/$2.dat
	fi
	while read -a line
	do
		if [ "${line[0]}" == "Book" -a "$2" == "book"  ]
		then 
			echo "Book"$'\t'${line[1]} >> ./result/resource/book.dat
		elif [ "${line[0]}" == "E-book" -a "$2" == "e-book" ]
		then
			echo "E-book"$'\t'${line[1]} >> ./result/resource/e-book.dat
		elif [ "${line[0]}" == "Magazine" -a "$2" == "magazine" ]
		then
			echo "Magazine"$'\t'${line[1]} >> ./result/resource/magazine.dat
		fi
		if [ "$2" == "all" ]
		then
			./library_statistics.sh resource book
			./library_statistics.sh resource e-book
			./library_statistics.sh resource magazine
		fi
	done < ./resource.dat
fi

if [ "$1" == "input" -o "$1" == "space" ]
then
	if [ "$1" == "input" ]
	then
		mkdir -p ./result/input
		read -r FIRSTLINE_input < input.dat
		echo $FIRSTLINE_input > new_input.dat
		read -r FIRSTLINE_space < space.dat
		echo $FIRSTLINE_space > new_space.dat
		if [ "$2" == "book" ]
		then
			while read -a line
			do
				if [ "${line[1]}" == "Book" ]
				then 
					echo ${line[@]} >> ./new_input.dat
				fi
			done < ./input.dat
		fi
		if [ "$2" == "e-book" ]
		then
			while read -a line
			do
				if [ "${line[1]}" == "E-book" ]
				then 
					echo ${line[@]} >> ./new_input.dat
				fi
			done < ./input.dat
		fi
		if [ "$2" == "magazine" ]
		then
			while read -a line
			do
				if [ "${line[1]}" == "Magazine" ]
				then 
					echo ${line[@]} >> ./new_input.dat
				fi
			done < ./input.dat
		fi
		if [ "$2" == "undergraduate" ]
		then
			while read -a line
			do
				if [ "${line[4]}" == "Undergraduate" ]
				then 
					echo ${line[@]} >> ./new_input.dat
				fi
			done < ./input.dat
		fi
		if [ "$2" == "graduate" ]
		then
			while read -a line
			do
				if [ "${line[4]}" == "Graduate" ]
				then 
					echo ${line[@]} >> ./new_input.dat
				fi
			done < ./input.dat
		fi
		if [ "$2" == "faculty" ]
		then
			while read -a line
			do
				if [ "${line[4]}" == "Faculty" ]
				then 
					echo ${line[@]} >> ./new_input.dat
				fi
			done < ./input.dat
		fi
		if [ "$2" == "date" ]
		then
			while read -a line
			do
				if [ "${line[0]}" != "Date[yy/mm/dd]" ]
				then
					input_cmp ${line[0]} $3 $4
					result=$?
					if [ $result -eq 1 ]
					then
						echo ${line[@]} >> ./new_input.dat
					fi
				fi
			done < ./input.dat
		fi
		if [ "$2" == "all" ]
		then
			./library_statistics.sh input book
			./library_statistics.sh input e-book
			./library_statistics.sh input magazine
			./library_statistics.sh input undergraduate
			./library_statistics.sh input graduate
			./library_statistics.sh input faculty
		fi
	fi
	#####space
	if [ "$1" == "space" ]
	then
		mkdir -p ./result/space
		read -r FIRSTLINE_input < input.dat
		echo $FIRSTLINE_input > new_input.dat
		read -r FIRSTLINE_space < space.dat
		echo $FIRSTLINE_space > new_space.dat
		if [ "$2" == "studyroom" ]
		then
			while read -a line
			do
				if [ "${line[1]}" == "StudyRoom" ]
				then 
					if [ "$3" == "all"  -o "${line[2]}" == "$3" ]
					then
						echo ${line[@]} >> ./new_space.dat
					fi
				fi
			done < ./space.dat
		fi
		if [ "$2" == "seat" ]
		then
			while read -a line
			do
				if [ "${line[1]}" == "Seat" ]
				then 
					if [ "$3" == "all"  -o "${line[2]}" == "$3" ]
					then
						echo ${line[@]} >> ./new_space.dat
					fi
				fi
			done < ./space.dat
		fi

		if [ "$2" == "undergraduate" ]
		then
			while read -a line
			do
				if [ "${line[4]}" == "Undergraduate" ]
				then 
					echo ${line[@]} >> ./new_space.dat
				fi
			done < ./space.dat
		fi
		if [ "$2" == "graduate" ]
		then
			while read -a line
			do
				if [ "${line[4]}" == "Graduate" ]
				then 
					echo ${line[@]} >> ./new_space.dat
				fi
			done < ./space.dat
		fi
		if [ "$2" == "faculty" ]
		then
			while read -a line
			do
				if [ "${line[4]}" == "Faculty" ]
				then 
					echo ${line[@]} >> ./new_space.dat
				fi
			done < ./space.dat
		fi
		if [ "$2" == "date" ]
		then
			while read -a line
			do
				if [ "${line[0]}" != "Date[yy/mm/dd/hh]" ]
				then
					space_cmp ${line[0]} $3 $4
					result=$?
					if [ $result -eq 1 ]
					then
						echo ${line[@]} >> ./new_space.dat
					fi
				fi
			done < ./space.dat
		fi
		if [ "$2" == "all" ]
		then
			./library_statistics.sh space studyroom all
			./library_statistics.sh space seat all
			./library_statistics.sh space undergraduate
			./library_statistics.sh space graduate
			./library_statistics.sh space faculty
		fi
	fi

	make
	./hw1 new_input.dat new_space.dat

	if [ "$2" != "all" ]
	then
		rm -f  ./result/$folder/$file.dat
		while read -a line
			do
				#echo ${#line[@]}
				count=1
				for word in ${line[@]}
				do 
					if [ $count -eq 1 -o $count -eq 2 ]
					then
						echo -n $word$'\t'  >> ./result/$folder/$file.dat
					elif [ $count -eq ${#line[@]} ]
					then
						echo $word  >> ./result/$folder/$file.dat
					else
						echo -n $word$' '  >> ./result/$folder/$file.dat
					fi
					((count++))
				done
				#echo ${line[@]} >> ./result/$folder/$file.dat

		done < ./new_output.dat
	fi
	rm -f new_input.dat
	rm -f new_space.dat
	rm -f new_output.dat
fi

if [ "$1" == "output" ]
then
	file=$2
	./hw1
	mkdir -p ./result/output
	rm -f ./result/output/$2.dat
	num=-1
	end=16
	echo "Return_code"$'\t'"Number" > ./result/output/$2.dat
	while [ $num -le $end ]
	do
		cnt=0
		while read -a line
		do
			if [ ${line[1]} == $num ]
			then
				((cnt++))
			fi
		done < ./output.dat

		echo $num$'\t'$cnt >> ./result/output/$2.dat
		((num++))
	done
fi