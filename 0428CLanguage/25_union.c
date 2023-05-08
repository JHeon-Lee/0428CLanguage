#include <stdio.h>
#include <stdbool.h>

void union_(); // 공용체는 하나의 공간을 멤버들이 모두 공유
void union_and_structures();
void union_and_structures2();
void endianness();

int main()
{
	union_();

	union_and_structures();

	union_and_structures2();

	endianness();

	return 0;
}

void union_()
{
	struct myStruct
	{
		char c;
		int i;
		double d;
	};

	union myUnion
	{
		char c;
		int i;
		double d;
	};

	struct myStruct st;
	union myUnion uni;

	printf("구조체 공간의 사이즈\t: %d\n", sizeof(st)); // 13이 아닌 16 ---> 가장 큰 크기를 단위로 만들고(8), 남은 크기(3)에 double이 안들어가므로 다시 8을 만들어서 16이됨
	printf("구조체 멤버 c의 사이즈\t: %d\n", sizeof(st.c));
	printf("구조체 멤버 i의 사이즈\t: %d\n", sizeof(st.i));
	printf("구조체 멤버 d의 사이즈\t: %d\n\n", sizeof(st.d));

	printf("유니온 공간의 사이즈\t: %d\n", sizeof(uni)); // 가장 큰 사이즈 기준
	printf("유니온 멤버 c의 사이즈\t: %d\n", sizeof(uni.c));
	printf("유니온 멤버 i의 사이즈\t: %d\n", sizeof(uni.i));
	printf("유니온 멤버 d의 사이즈\t: %d\n\n", sizeof(uni.d));

	printf("0x%p\n", &st); // &st.c와 같다
	printf("0x%p\n", &st.c);
	printf("0x%p\n", &st.i);
	printf("0x%p\n\n", &st.d);

	printf("0x%p\n", &uni); // 모두 같다
	printf("0x%p\n", &uni.c);
	printf("0x%p\n", &uni.i);
	printf("0x%p\n\n", &uni.d);

	uni.i = 20;
	printf("%d\n\n", uni.i);

	uni.d = 7.15; // uni.i를 덮어씀
	printf("%d\n", uni.c);
	printf("%d\n", uni.i);
	printf("%g\n", uni.d);
}

void union_and_structures()
{
	{
		struct ptr
		{
			union // 메모리 절약됨
			{
				int* ip;
				float* fp;
			};
			bool isInt;
		};
		struct ptr ptr;

		int i = 100;
		float f = 200.0f;

		ptr.ip = &i;
		ptr.isInt = true;

		if ((ptr.isInt == true))
		{
			printf("ptr is int : %d\n", *ptr.ip);
		}
		else
		{
			printf("ptr is float : %f\n", *ptr.fp);
		}

		ptr.fp = &f;
		ptr.isInt = false;

		if ((ptr.isInt == true))
		{
			printf("ptr is int : %d\n", *ptr.ip);
		}
		else
		{
			printf("ptr is float : %f\n", *ptr.fp);
		}
	}
	{
		struct Location
		{
			union
			{
				struct { double x; double y; };
				struct { double arr[2]; };
			};
		};

		struct Location loc = { 1.1, 1.2 };

		printf("%lf, %lf\n", loc.x, loc.y);
		printf("%lf, %lf\n", loc.arr[0], loc.arr[1]); // 같은 결과값 ---> 원하는 방식으로 불러올 수 있음
	}
}

#define PERSONAL 0
#define COMPANY 1

typedef struct
{
	char rrn1[7];
	char rrn2[8];
}personalOwner;

typedef struct
{
	char crn1[4];
	char crn2[3];
	char crn3[6];
}companyOwner;

typedef struct
{
	char model[15];
	int status;

	union // 메모리 절약 가능
	{
		personalOwner po;
		companyOwner co;
	};
}carData;

void printCar(carData data)
{
	if (data.status == PERSONAL)
	{
		printf("personal owner = %s-%s\n", data.po.rrn1, data.po.rrn2);
	}
	else if (data.status == COMPANY)
	{
		printf("company owner = %s-%s-%s\n", data.co.crn1, data.co.crn2, data.co.crn3);
	}
}

void union_and_structures2()
{
	carData myCar = {
		"Avante",
		PERSONAL,
		.po.rrn1 = "222222", // c 에서만 가능
		.po.rrn2 = "1111111"
	};

	carData companyCar = {
		"Avante",
		COMPANY,
		.co.crn1 = "111",
		.co.crn2 = "22",
		.co.crn3 = "33333"
	};

	printCar(myCar);
	printCar(companyCar);
}

void endianness()
{
	/*
		endianness : 컴퓨터가 메모리 읽는 방식 -> 유니온 통해서 확인 가능

		Little Endian***
		- 데이터가 끝나는 마지막 단위가 가장 작은 메모리 주소에 위치
		- 컴퓨터에서 일반적으로 사용

		Big Endian
		- 데이터가 끝나는 마지막 단위가 가장 큰 메모리 주소에 위치
		- 네트워크에 사용
	*/

	/*
		struct 에서의 메모리 (내부)단편화 (외부) : 동적할당에서 생김 - 구글링 필요, 면접에 나왔었음
	*/
	union myUnion
	{
		int i;
		char c;
	};

	union myUnion uni;
	
	uni.i = 0x12345678; // - 4byte

	printf("i : %x\n", uni.i);
	printf("c : %x\n", uni.c); // 1byte --> 78 만 출력됨 --> Little Endian 방식이라는 증거
}
