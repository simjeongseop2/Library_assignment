# Library Manegement

## Class

### date

---

* 날짜를 년, 월, 일, 시간으로 구분하여 저장해 주는 클래스이다.

* variable
	* y : year
	* m : month
	* d : day
	* t : second

* date(int y, int m, int d)

	* 매개변수를 받아서 클래스 내의 각 변수를 초기화 한다.

* date(int y, int m, int d, int t)

	* 매개변수를 받아서 클래스 내의 각 변수를 초기화 한다. 시간 변수를 추가로 받았을 때 호출된다.

### member

---

* library 이용자의 정보를 저장하는 클래스이다.

* variable
	* type : member가 상속 되었을 때, 상속 받은 클래스의 이름
	* name : 사용자의 이름
	* max_num : 최대로 빌릴 수 있는 권 수
	* max_lent : 최대로 빌릴 수 있는 기간
	* book_name : 빌린 책의 이름
	* lent_date : 책을 빌린 날짜
	* disable : 이용 불가능한 날짜. disable에 저장된 날짜 다음 날 부터 이용 가능
	* max_capacity : 최대로 빌릴 수 있는 E-book의 용량
	* now_capacity : 현재 보유하고 있는 E-book의 용량

* member(string type, string name, int max_num, int max_lent)

	* 매개 변수를 받아서 클래스 내의 각 변수를 초기화 한다.

* is_able(date today)

	* 매개 변수로 받은 today가 이용 가능한 날짜인지 판단해 준다. 이용 가능할 경우 true, 불가능할 경우 false를 리턴한다.

### undergraduate

---

* member 클래스를 상속 받는 클래스이다.

* undergraduate(string name)

	* 유저의 이름을 받아 객체를 초기화 한다. type은 Undergraduate, max_num은 1, max_lent는 14로 초기화 한다. max_capacity를 100으로 초기화한다.

### graduate

---

* member 클래스를 상속 받는 클래스이다.

* graduate(string name)

	* 유저의 이름을 받아 객체를 초기화 한다. type은 Graduate, max_num은 5, max_lent는 30으로 초기화 하고, max_capacity를 500으로 초기화 한다.

### faculty

---

* member클래스를 상속 받는 클래스이다.

* faculty(string name)

	* 유저의 이름을 받아 객체를 초기화 한다. type은 Faculty, max_num은 10, max_lent는 30으로 초기화 하고, max_capacity를 1000으로 초기화 한다.


### resource

---

* library에 보관되는 resource의 정보를 저장하는 클래스이다.

* variable
	* type : member가 상속 되었을 때, 상속 받은 클래스의 이름
	* name : resource의 이름
	* isborrowed : resource가 대출된 상태일 경우 1, 아닐경우 0을 반환
	* user : resource를 빌린 사람의 이름
	* return_date : resource가 반납 되기로 되어있는 날짜
	* capacity : resource의 용량을 나타내는 변수. e_book class에 사용된다.

* resource(string type, string name)

	* 매개 변수를 받아서 클래스 내의 각 변수를 초기화 한다.

* bool isSame(string rsc_name, date now, date m_date)
	
	* resource의 이름을 받아 객체의 이름과 같은지 판단한 후, 같으면 true, 다르면 false를 리턴한다.

* bool already_borrow(member* m, date m_date)

	* resource가 이미 다른 멤버가 빌린 상태인지 아닌지를 판단하여 리턴해준다.

*  bool return_isborrowed(date m_date)
	
	* resource의 isborrowed의 상태를 리턴한다.

* void borrow_rsc(...)
	
	* resource를 빌리는 연산을 구현한 함수이다. 빌리는 member의 포인터를 받아 book_name과 lent_date를 추가해 준 후 resource의 변수들을 업데이트 한다.

* void update(date now)
	
	* magazine 과 e_book class에 사용되는 함수이다. 멤버의 요청이 들어온 날짜를 받아, 해당 날짜에 맞게 객체의 변수들을 업데이트 해준다.


* bool matching_user(...)

	* member가 해당 resource를 빌리고 있는 상태인지를 판단해 true 또는 false를 리턴해 준다.

* void return_rsc(...)

	* resource를 반납하는 연산을 구현한 함수이다. 반납하는 member의 포인터를 받아 book_name과 lent_date를 제거해 준 후 resource의 변수들을 업데이트 한다.

* date find_return_date(date m_date, string origin_name)

	* resource가 

### book

---

* resource 클래스를 상속받는 클래스이다.

* book(string name)

	* 책의 이름을 받아 객체를 초기화 한다. type은 Book으로 초기화 한다.

### magazine

---

* resource 클래스를 상속받는 클래스이다. 객체 내에서 배열을 통해 월간호 별로 잡지들을 관리하며, 1년 이 지난 잡지들은 자동으로 폐기처리 된다.

* variable

	* date_arr : date 객체를 저장하기 위한 배열이다. magazine 클래스 내의 월간호들을 나타내는데 사용된다.

	* mem_arr : member 객체와 그 클래스를 상속받는 객체들을 저장하는 배열이다. 각 월간호 들을 빌린 멤버들을 저장하는데 사용된다.

* magazine(string name)
	
	* magazine의 이름을 받아 객체를 초기화 한다. type은 Magazine으로 최화 한다.

* bool check_publication(date a, date b)

	* 두 date 객체를 받아 서로 같은 연도와 월을 가지고 있다면 true, 아니면 false를 리턴한다. 같은 월간호 인지를 판단하는데 사용된다.

### e_book

---

* resource 클래스를 상속받는 클래스이다. 용량만 된다면 다수의 멤버가 하나의 e_book을 빌릴 수 있으며, 반납일이 지난 e_book은 자동으로 반납처리 된다.

* variable

	* mem_arr : member 객체와 그 클래스를 상속받는 객체들을 저장하는 배열이다. e_book을 빌린 멤버들을 저장하는데 사용된다.

	* ret_date_arr : date 객체들을 저장하는 배열이다. 각 멤버별 e_book이 반납되는 날짜들을 저장하는데 사용된다.

* e_book(string n)

	* e_book의 이름을 받아 객체를 초기화 한다. type은 E-book으로 하고, 이름에 같이 들어 있던 capacity를 잘라내어 e_book의 capacity를 초기화 해준다.

### library

---

* member와 resource 객체들 그리고 space 객체들을 관리해 주는 클래스 이다. member와 resource, space에 관련된 요청은 이 클래스를 통해서 처리된다.

* variable
	* mem : member 객체와 그 클래스를 상속받는 객체들을 저장하는 배열이다.
	* rsc : resource 객체와 그 클래스를 상속받는 객체들을 저장하는 배열이다.
	* spc : space 객체와 그 클래스를 상속받는 객체들을 저장하는 배열이다.

* library()

	* `resource.dat` 파일의 내용을 읽어들여 library 객체를 초기화 해준다. library에 있는 resource들을 업데이트 한다. 그리고 spc배열에 10개의 study_room 객체와 3개의 seat 객체들을 동적할당 한다

* CHARtoINT(const string& str)

	* string 형 변수에 저장되어 있는 숫자들을 int 형 숫자로 바꿔준다.

* INTtoSTRING(int n)
	* 2자리의 정수 n을 받아 char형 배열로 바꿔 그 배열의 주소값을 리턴해 준다.

* make_date(const string& str)

	* string에 저장되어 있는 날짜를 date class에 맞게 바꿔 그 객체를 리턴해준다.

* make_space_date(const string& str)
	
	* string에 저장되어 있는 날짜를 date class에 맞게 바꿔 그 객체를 리턴해준다. space.dat에서 시간과 함께 들어오는 날짜를 처리해 주기 위한 함수이다.



* DATEtoSTRING(date& dat)

	* date 객체에 저장되어 있는 날짜를 string에 맞게 바꿔 그 string을 리턴해 준다.

* date_plus(date today, int p)

	* today 에 저장된 날짜에서 p 만큼 지난 날을 date 클래스에 맞게 넣어준 후 그 객체를 리턴해 준다.

* date_diff(date dat1, date dat2)

	* dat1과 dat2 간의 날짜 차이를 int형 변수로 리턴해준다.

* Borrow_rsc(...)

	* member가 library에 resource를 빌리는 요청을 했을 때 그것을 처리해 주는 함수이다. 다음 각 상황에 맞게 문자를 출력해 준 후 resource를 해당 날짜, 요청에 맞게 업데이트 해준다.
		* 빌리려는 책이 존재 하지 않는 경우 :  Non exist resource.
		* max_num을 넘게 빌리려는 경우 : Exceeds your possible number of borrow...
		* 이미 빌린 책을 또 빌리려는 경우 : You already borrowed this book at...
		* 다른 멤버기 이미 책을 빌린 경우 : Other member already borrowed this book...
		* 연체로 인해 대여가 제한된 상태에서 빌리려는 경우 : Restricted member until...
		* E-book의 경우, max_capacity를 넘게 빌리려는 경우 : Exceeds your storage capacity.
		* 빌리고 있는 책의 반납일이 지난 상태에서 또 빌리려는 경우 : Previously borrowed books are overdue, so borrow is limited.
		* 이 외의 경우 : Success.

* Return_rsc(...)

	* member가 library에 resource를 반납하려는 요청을 했을 때 그것을 처리해 주는 함수이다. 다음 각 상황에 맞게 문자를 출력해 준 후 resource를 해당 날짜, 요청에 맞게 업데이트 해준다.
		* 빌리려는 책이 존재 하지 않는 경우 :  Non exist resource.
		* 빌리지 않은 책을 반납하려는 경우 : You did not borrow this book.
		* 반납일이 지난 상태에서 반납하려는 경우 : Delayed return. You'll be restricted until...
		* 이 외의 경우 : Success.

* Borrow_spc(...)
	* member가 library에 space를 빌리는 요청을 했을 때 그것을 처리해 주는 함수이다. 다음 각 상황에 맞게 문자를 출력해 준 후 space를 해당 날짜, 요청에 맞게 업데이트 해준다.
		* 유효하지 않은 id일 경우 : Invalid space id.
		* 이용 시간이 아닌 경우 : This space is not available now. Available from...
		* 이미 같은 종류의 space를 빌린 경우 : You already borrowed this kind of space.
		* 멤버별 최대 이용 좌석을 초과한 요청을 할 경우 : Exceed available number.
		* 멤버별 최대 이용 시간을 초과한 요청을 할 경우 : Exceed available time.
		* 남은 자리가 없는 경우 : There is no remain space. This space is available after...
		* 이 외의 경우 : Success.
		
* REC_spc(...)
	* member가 library에 space를 반납, empty, comback 요청을 했을 때 그것을 처리해 주는 함수이다. 다음 각 상황에 맞게 문자를 출력해 준 후 space를 해당 날짜, 요청에 맞게 업데이트 해준다.
		* 유효하지 않은 id일 경우 : Invalid space id.
		* 빌리지 않은 자리를 반납하려는 경우 : You did not borrow this space.
		* 이 외의 경우 : Success.

* ThrowFunc(...)

	* space에 대한 요청에 대해서 예외 상황을 처리해 주는 함수이다. 다음 각 상황에 맞게 예외 문구를 출력해준다.
		* 10/01/01 이전의 날짜가 들어온 경우 : Date out of range
		* 존재하지 않는 space type일 경우 : Non-exist space type
		* 존재하지 않는 operation일 경우 : Non-exist operation
		* 존재하지 않는 member type일 경우 : Non-exist member type
		* 멤버이름에 숫자가 포함된 경우 : Member name with numbers
		* 음수의 시간이 들어온 경우 : Negative time

* process()

	* `input.dat` 파일과 `space.dat` 파일의 내용을 읽어들여 member의 요청을 처리한 후 그 결과를 `output.dat`에 출력한다. 출력 결과는 예시 파일에 맞췄다. 두 파일을 동시에 읽어 들이면서 날짜가 빠른 순으로 출력한다. 날짜가 같을 경우에는 `input.dat`의 요청을 먼저 처리한 뒤 `space.dat`의 요청을 처리한다. `space.dat`의 요청의 경우, ThrowFunc을 통해 예외 상황을 처리한다.

### space

---

* 도서관 내의 멤버들이 사용할 수 있는 공간에 대한 정보를 나타내는 클래스이다.

* variable
	* max_num : space의 전체 좌석 갯수.
	* max_time : member가 빌릴 수 있는 최대 시간.
	* num : 현재 예약되어 있는 좌석 갯수.
	* empty_num : 현재 사용할 수 있는 좌석 갯수.
	* open_time : space를 사용 가능한 시작 시간.
	* close_time : space의 마감 시간.
	* user_info : space를 예약한 멤버의 정보를 담고 있는 구조체 변수이다. 멤버의 이름, 빌린 좌석 갯수, 예약 종료 시간, 자리를 비웠는지 여부를 나타낸다.

* space(int mn, int mt, int ot, int ct)
	* 매개변수를 받아서 space의 max_num, max_time, open_time, close_time을 초기화 한다.

* isThereUser(string name)
	* space 내에 name의 이름을 가진 member가 좌석을 빌린 상황이면 true를 리턴하고, 아니면 false를 리턴한다.

* borrow_space(string name, int n, date dat, int borrow_time)
	* member의 좌석 예약을 처리해 주는 함수이다.

* return_space(string name)
	* member의 좌석 반납을 처리해 주는 함수이다.

* empty_space(string name, date dat)
	* 좌석을 빌린 member가 자리를 비우는 상황을 처리해 주는 함수이다.

* comback_space(string name)
	* 자리를 비운 멤버가 다시 돌아오는 상황을 처리해 주는 함수이다.

### study_room

---

* space 클래스를 상속받는 클래스이다. 도서관 내의 스터디룸을 나타낸다.

* study_room()
	* study_room 클래스를 초기화 해준다. 좌석 갯수는 50개 이고, 최대 신청 가능 시간은 3시간, 오픈 시간과 마감 시간은 각각 9시, 18시로 초기화 한다.

* update(date d)
	* date 클래스를 받아 해당 시간으로 study_room 내의 좌석 정보를 업데이트 해준다. 좌석 예약 시간이 지난 멤버들을 반납 처리 한다.

* return_available_time(int t, int n)
	* 이미 study_room을 누가 사용하고 있는 상황에서 다음 번에 예약이 가능한 시간을 리턴 해준다.

### seat

---

* space 클래스를 상속받는 클래스이다. 도서관 내의 열람실의 좌석을 나타낸다.

* seat(int ot, int ct)
	* 열람실의 오픈 시간과 마감 시간을 매개변수로 받아 각각 초기화 해준다. 좌석 갯수는 50개, 최대로 빌릴 수 있는 시간은 3시간으로 초기화 한다.

* update(date d)
	* date 클래스를 받아 해당 시간으로 seat 내의 좌석 정보를 업데이트 해준다. 좌석 예약 시간이 지난 멤버들과 자리를 비운 후 1시간 이상 돌아오지 않은 멤버들을 반납처리 해준다.

* return_available_time(int t, int n)
	* 예약 시간과 인원을 받아 예약 가능한 시간을 리턴해 준다.

## Building

* It is simple. just type `make`. Then the executable file, name `hw1`, is made.
* And type `./hw1` for executing
