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

		struct person p = { "ȫ�浿",30,175.25f };
		p.height = 182.35f;

		{
			struct book
			{
				char name[256];
				float price;
			};

			struct book b1;
		}

		// struct book b2; ----> ���� : ����ü - ��������

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
			{{"�̸�", "��"}, "1545"},
			{{"�̸�", "��"}, "7545"}
		};

		friendInfo* bestFriend;
		bestFriend = &myFriend[0]; // ����ü�� �迭�� �ٸ��� & ���� �Ұ�

		printf("bestFriend[0] �̸�\t: %s\n", (*bestFriend).fullname.given);
		printf("bestFriend[0] ��\t: %s\n", bestFriend->fullname.family);

		bestFriend++;
		printf("bestFriend[1] �̸�\t: %s\n", (*bestFriend).fullname.given);
		printf("bestFriend[1] ��\t: %s\n", bestFriend->fullname.family);
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
			weapon* equipWeapon; // ó������ �ʱ�ȭ�� �ʿ� X --> ����ü ���� �ÿ��� �޸𸮸� ����Ƹ���
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

		printf("�÷��̾� �̸� \t\ : %s\n", p.name);
		printf("���� ����\t : %s\n", p.equipWeapon->name); // �߰��� ���� .(* ��� �Ұ�, �׷��� -> ���
		printf("���� ���� ���\t : %s\n", p.equipWeapon->grade);

		p.equipWeapon = &bow;

		printf("�÷��̾� �̸� \t\ : %s\n", p.name);
		printf("���� ����\t : %s\n", p.equipWeapon->name);
		printf("���� ���� ���\t : %s\n", p.equipWeapon->grade);
	}
}
