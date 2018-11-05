# Library Manegement

## Class

### date

---

* variable
	* y : year
	* m : month
	* d : day
* date(int y, int m, int d)

	* 매개변수를 받아서 클래스 내의 각 변수를 초기화 한다.

### member

---

* variable
	* type : member가 상속 되었을 때, 상속 받은 클래스의 이름
	* name : 사용자의 이름
	* max_num : 최대로 빌릴 수 있는 권 수
	* max_lent : 최대로 빌릴 수 있는 기간
	* book_name : 빌린 책의 이름
	* lent_date : 책을 빌린 날짜
	* disable : 이용 불가능한 날짜. disable에 저장된 날짜 다음 날 부터 이용 가능

* member(string type, string name, int max_num, int max_lent)

	* 매개 변수를 받아서 클래스 내의 각 변수를 초기화 한다.

* is_able(date today)

	* 매개 변수로 받은 today가 이용 가능한 날짜인지 판단해 준다. 이용 가능할 경우 true, 불가능할 경우 false를 리턴한다.

### undergraduate

---

* member 클래스를 상속받는 클래스이다.

* undergraduate(string name)

	* 유저의 이름을 받아 객체를 초기화 한다. type은 Undergraduate, max_num은 1, max_lent는 14로 초기화 한다.


### resource

---

* variable
	* type : member가 상속 되었을 때, 상속 받은 클래스의 이름
	* name : resource의 이름
	* isborrowed : resource가 대출된 상태일 경우 1, 아닐경우 0을 반환
	* user : resource를 빌린 사람의 이름
	* return_date : resource가 반납 되기로 되어있는 날짜

* resource(string type, string name)

	* 매개 변수를 받아서 클래스 내의 각 변수를 초기화 한다.

### book

---

* resorce 클래스를 상속받는 클래스이다.

* book(string name)

	* 유저의 이름을 받아 객체를 초기화 한다. type은 Book으로 초기화 한다.

### library

---

* member와 resource 객체들을 관리해 주는 클래스 이다.

* variable
	* mem : member 클래스와 그 클래스를 상속받는 클래스들을 저장하는 배열이다.
	* rsc : resource 클래스와 그 클래스를 상속받는 클래스들을 저장하는 배열이다.

* library()

	* `resource.dat` 파일의 내용을 읽어들여 library 객체를 초기화 해준다. library에 있는 resource들을 업데이트 한다.

* CHARtoINT(const string& str)

	* string 형 변수에 저장되어 있는 숫자들을 int 형 숫자로 바꿔준다.

* make_date(const string& str)

	* string에 저장되어 있는 날짜를 date class에 맞게 바꿔 그 객체를 리턴해준다.

* DATEtoSTRING(date& dat)

	* date 객체에 저장되어 있는 날짜를 string에 맞게 바꿔 그 string을 리턴해 준다.

* date_plus(date today, int p)

	* today 에 저장된 날짜에서 p 만큼 지난 날을 date 클래스에 맞게 넣어준 후 그 객체를 리턴해 준다.

* date_diff(date dat1, date dat2)

	* dat1과 dat2 간의 날짜 차이를 int형 변수로 리턴해준다.

* Borrow_rsc(...)

	* member가 library에 resource를 빌리는 요청을 했을 때 그것을 처리해 주는 함수이다. member가 resource를 빌릴 수 없는 경우에는 각 상황에 맞게 문자를 출력해 준다. member가 resource를 빌리는데 성공 했을 경우, member의 book_name, lent_date와 resource의 isborrowed, user, return_date를 업데이트 한 뒤 `Success.`를 출력해 준다.

* Return_rsc(...)

	* member가 library에 resource를 반납하는 요청을 했을 떄 그것을 처리해 주는 함수이다. member의 반납이 제대로 이루어 지지 않은 경우 각 상황에 맞게 문자열을 출력해 준다. 만일 member가 resource를 반납 기한 보다 늦게 반납한 경우, member의 disable을 업데이트 하고 대출이 제한되는 날짜를 출력해 준다. 제 때에 반납한 경우 `Success`를 출력한다. 반납을 마친 뒤에는 member의 book_name, lent_date resource의 isborrowed, user, return_date를 업데이트 해준다.

* process()

	* `input.dat` 파일의 내용을 읽어들여 member의 요청을 처리한다. member가 책을 빌리는 요청을 했을 경우 Borrow_rsc 함수를, 반납하는 요청을 했을 경우 Return_rsc 함수를 호출한다.

## Building

* It is simple. just type `make`. Then the executable file, name `hw1`, is made.
* And type `./hw1` for executing.

