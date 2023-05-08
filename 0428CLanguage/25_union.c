#include <stdio.h>
#include <stdbool.h>

void union_(); // ����ü�� �ϳ��� ������ ������� ��� ����
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

	printf("����ü ������ ������\t: %d\n", sizeof(st)); // 13�� �ƴ� 16 ---> ���� ū ũ�⸦ ������ �����(8), ���� ũ��(3)�� double�� �ȵ��Ƿ� �ٽ� 8�� ���� 16�̵�
	printf("����ü ��� c�� ������\t: %d\n", sizeof(st.c));
	printf("����ü ��� i�� ������\t: %d\n", sizeof(st.i));
	printf("����ü ��� d�� ������\t: %d\n\n", sizeof(st.d));

	printf("���Ͽ� ������ ������\t: %d\n", sizeof(uni)); // ���� ū ������ ����
	printf("���Ͽ� ��� c�� ������\t: %d\n", sizeof(uni.c));
	printf("���Ͽ� ��� i�� ������\t: %d\n", sizeof(uni.i));
	printf("���Ͽ� ��� d�� ������\t: %d\n\n", sizeof(uni.d));

	printf("0x%p\n", &st); // &st.c�� ����
	printf("0x%p\n", &st.c);
	printf("0x%p\n", &st.i);
	printf("0x%p\n\n", &st.d);

	printf("0x%p\n", &uni); // ��� ����
	printf("0x%p\n", &uni.c);
	printf("0x%p\n", &uni.i);
	printf("0x%p\n\n", &uni.d);

	uni.i = 20;
	printf("%d\n\n", uni.i);

	uni.d = 7.15; // uni.i�� ���
	printf("%d\n", uni.c);
	printf("%d\n", uni.i);
	printf("%g\n", uni.d);
}

void union_and_structures()
{
	{
		struct ptr
		{
			union // �޸� �����
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
		printf("%lf, %lf\n", loc.arr[0], loc.arr[1]); // ���� ����� ---> ���ϴ� ������� �ҷ��� �� ����
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

	union // �޸� ���� ����
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
		.po.rrn1 = "222222", // c ������ ����
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
		endianness : ��ǻ�Ͱ� �޸� �д� ��� -> ���Ͽ� ���ؼ� Ȯ�� ����

		Little Endian***
		- �����Ͱ� ������ ������ ������ ���� ���� �޸� �ּҿ� ��ġ
		- ��ǻ�Ϳ��� �Ϲ������� ���

		Big Endian
		- �����Ͱ� ������ ������ ������ ���� ū �޸� �ּҿ� ��ġ
		- ��Ʈ��ũ�� ���
	*/

	/*
		struct ������ �޸� (����)����ȭ (�ܺ�) : �����Ҵ翡�� ���� - ���۸� �ʿ�, ������ ���Ծ���
	*/
	union myUnion
	{
		int i;
		char c;
	};

	union myUnion uni;
	
	uni.i = 0x12345678; // - 4byte

	printf("i : %x\n", uni.i);
	printf("c : %x\n", uni.c); // 1byte --> 78 �� ��µ� --> Little Endian ����̶�� ����
}
