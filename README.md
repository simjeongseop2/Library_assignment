# Library Manegement

## Class

### date

---

* 날짜를 년, 월, 일, 시간으로 구분하여 저장해 주는 클래스이다.

* variable
	* y : year
	* m : month
	* d : day
	* y : second

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

* library에 보관되는 resource의 정보를 저장하는 클래스이다.

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

* resource 클래스를 상속받는 클래스이다.

* book(string name)

	* 책의 이름을 받아 객체를 초기화 한다. type은 Book으로 초기화 한다.

### library

---

* member와 resource 객체들을 관리해 주는 클래스 이다. member와 resource에 관련된 요청은 이 클래스를 통해서 처리된다.

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

	* member가 library에 resource를 빌리는 요청을 했을 때 그것을 처리해 주는 함수이다. member가 resource를 빌릴 수 없는 경우에는 각 상황에 맞게 문자를 출력해 준다. member가 resource를 빌리는데 성공 했을 경우, member의 book_name, lent_date와 resource의 isborrowed, user, return_date를 업데이트 한 뒤 `Success.`를 출력해 준다.

* Return_rsc(...)

	* member가 library에 resource를 반납하는 요청을 했을 때  그것을 처리해 주는 함수이다. member의 반납이 제대로 이루어 지지 않은 경우 각 상황에 맞게 문자열을 출력해 준다. 만일 member가 resource를 반납 기한 보다 늦게 반납한 경우, member의 disable을 업데이트 하고 대출이 제한되는 날짜를 출력해 준다. 제 때에 반납한 경우 `Success.`를 출력한다. 반납을 마친 뒤에는 member의 book_name, lent_date resource의 isborrowed, user, return_date를 업데이트 해준다.

* Borrow_spc(...)
	* member가 library에 space를 빌리는 요청을 했을 때 그것을 처리해 주는 함수이다. 빌리려는 space의 넘버가 범위를 벗어나거나, space를 이용할 수 없는 시간에 요청을 했을 경우 각 상황에 맞게 문자열을 출력해 준다. 만일 요청을한 멤버가 이미 같은 종류의 space를 빌리고 있는 상황이면 빌릴 수 없다는 문자를 출력해 주고, member가 요청 가능한 최대 멤버 수와 최대 시간을 초과하는 경우에도 그 경우 맞게 문자열을 출력한다. 현재 다른 멤버들이 사용하고 있어서 좌석을 예약할 수 없는 경우에는 예약 가능한 시간을 출력해 준다. 이외의 경우에는 member에게 그 space를 빌려주는 요청을 한 뒤, 성공했다는 문자열을 출력한다.

* REC_spc(...)
	* member가 library에 space를 반납, 자리비움, 혹은 다시 자리로 돌아오느 요청을 했을 때 그것을 처리해 주는 함수이다. 만일 member가 요청한 space의 넘버가 범위를 벗어나거나, 현재 빌리고 있지 않은 space에 대하여 위의 요청을 할 경우 상황에 맞는 문자열을 출력해 준다. 이 외의 경우에는 반납, 자리비움, 다시 돌아옴 요청에 대하여 각각 space에 return_space, empty_space, comback_space 함수를 호출하여 요청을 처리 한 뒤에 성공했다는 문자열을 출력한다.

* process()

	* `input.dat` 파일과 `space.dat` 파일의 내용을 읽어들여 member의 요청을 처리한 후 그 결과를 `output.dat`에 출력한다. 출력 결과는 예시 파일에 맞췄다. 두 파일을 동시에 읽어 들이면서 날짜가 빠른 순으로 출력한다. 날짜가 같을 경우에는 `input.dat`의 요청을 먼저 처리한 뒤 `space.dat`의 요청을 처리한다.

### space

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

* space 클래스를 상속받는 클래스이다. 도서관 내의 스터디룸을 나타낸다.

* study_room()
	* study_room 클래스를 초기화 해준다. 좌석 갯수는 50개 이고, 최대 신청 가능 시간은 3시간, 오픈 시간과 마감 시간은 각각 9시, 18시로 초기화 한다.

* update(date d)
	* date 클래스를 받아 해당 시간으로 study_room 내의 좌석 정보를 업데이트 해준다. 좌석 예약 시간이 지난 멤버들을 반납 처리 한다.

* return_available_time(int t, int n)
	* 이미 study_room을 누가 사용하고 있는 상황에서 다음 번에 예약이 가능한 시간을 리턴 해준다.

### seat

* space 클래스를 상속받는 클래스이다. 도서관 내의 열람실의 좌석을 나타낸다.

* seat(int ot, int ct)
	* 열람실의 오픈 시간과 마감 시간을 매개변수로 받아 각각 초기화 해준다. 좌석 갯수는 50개, undergraduate member의 경우 최대로 빌릴 수 있는 시간은 3시간으로 초기화 한다.

* update(date d)
	* date 클래스를 받아 해당 시간으로 seat 내의 좌석 정보를 업데이트 해준다. 좌석 예약 시간이 지난 멤버들과 자리를 비운 후 1시간 이상 돌아오지 않은 멤버들을 반납처리 해준다.

* return_available_time(int t, int n)
	* 예약 시간과 인원을 받아 예약 가능한 시간을 리턴해 준다.

## Building

* It is simple. just type `make`. Then the executable file, name `hw1`, is made.
* And type `./hw1` for executing
