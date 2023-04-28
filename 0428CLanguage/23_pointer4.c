#include <stdio.h>

void pointer_and_structure();

int main()
{


	return 0;
}

void pointer_and_structure()
{
	{
		struct person
		{
			char name[256];
			int age;
			float height;
		};

		struct person p = { "홍길동",30,175.25f };
		p.height = 182.35f;

		{
			struct book
			{
				char name[256];
				float price;
			};

			struct book b1;
		}

		// struct book b2; ----> 에러 : 구조체 - 지역변수

		typedef struct
		{
			char given[256];
			char family[256];
		}names;

		typedef struct
		{
			names fullname;
			char mobile[256];
		}friendInfo;

		friendInfo myFriend[2] = {
			{{"이름", "성"}, "1545"},
			{{"이름", "성"}, "7545"}
		};

		friendInfo* bestFriend;
		bestFriend = &myFriend[0]; // 구조체는 배열과 다르게 & 생략 불가

		printf("bestFriend[0] 이름\t: %s\n", (*bestFriend).fullname.given);
		printf("bestFriend[0] 성\t: %s\n", bestFriend->fullname.family);

		bestFriend++;
		printf("bestFriend[1] 이름\t: %s\n", (*bestFriend).fullname.given);
		printf("bestFriend[1] 성\t: %s\n", bestFriend->fullname.family);
	}

	{
		typedef struct
		{
			char name[256];
			char grade[256];
			int damage;
		}weapon;

		typedef struct
		{
			char name[256];
			int hp;
			weapon* equipWeapon; // 처음부터 초기화할 필요 X --> 구조체 정의 시에는 메모리를 안잡아먹음
		}Player;

		Player p = {
			"Player",
			100,
			NULL
		};

		weapon sword = {
			"Sword",
			"Legend",
			500
		};

		weapon bow = {
			"Bow",
			"Common",
			30
		};

		p.equipWeapon = &sword;

		printf("플레이어 이름 \t\ : %s\n", p.name);
		printf("소지 무기\t : %s\n", p.equipWeapon->name); // 중간에 쓸땐 .(* 사용 불가, 그래서 -> 사용
		printf("소지 무기 등급\t : %s\n", p.equipWeapon->grade);

		p.equipWeapon = &bow;

		printf("플레이어 이름 \t\ : %s\n", p.name);
		printf("소지 무기\t : %s\n", p.equipWeapon->name);
		printf("소지 무기 등급\t : %s\n", p.equipWeapon->grade);
	}
}
