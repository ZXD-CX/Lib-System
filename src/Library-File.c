#define _CRT_SECURE_NO_WARNINGS
#if 1
#include <stdio.h>
#include<windows.h>
#include<conio.h>
#include<string.h>
#include<time.h>

#define BOOK_NUM 200    //图书信息最大数量
#define READER_NUM 200  //读者信息最大数量
//图书信息输出宏
#define BOOK_DATA astBook[i].iNum,astBook[i].acName,astBook[i].acAuthor,astBook[i].acPress,astBook[i].iAmount
//读者信息输出宏
#define READER_DATA astReader[i].iNum,astReader[i].acName,astReader[i].acSex,astReader[i].iMax,astReader[i].iAmount
#define LEN_BOOK sizeof(struct Book) //单条图书信息字节长度
#define LEN_READER sizeof(struct Reader) //单条读者信息字节长度

//图书结构体
struct Book {
	int iNum;
	char acName[15];  //图书名称
	char acAuthor[15];//图书作者
	char acPress[15]; //图书出版社
	int iAmount;      //图书库存量
};

//读者结构体
struct Reader {
	int iNum;        //读者编号
	char acName[15]; //读者姓名
	char acSex[4];   //读者性别
	int iMax;        //读者最大可借阅数量
	int iAmount;     //读者当前可借阅数量
	int BookId[15];  //读者已经借阅图书列表
	time_t borrowTime[15];//已借图书的借阅时间
};

//定义两个全局结构体数组记录所有图书信息和所有的读者信息
struct Book astBook[BOOK_NUM];
struct  Reader astReader[READER_NUM];


//系统主菜单
void ShowMainMenu()  
{
	system("cls");  //清屏函数
	printf("\n\n\n\n");
	printf("\t\t\t\t********************欢迎进入*********************\n");
	printf("\t\t\t\t********************图书管理系统*****************\n");
	printf("\t\t\t\t********************主菜单***********************\n");
	printf("\t\t\t\t********************1.图书管理*******************\n");
	printf("\t\t\t\t********************2.读者管理*******************\n");
	printf("\t\t\t\t********************3.借书还书登记***************\n");
	printf("\t\t\t\t********************4.读者借阅详情***************\n");
	printf("\t\t\t\t********************5.帮助手册*******************\n");
	printf("\t\t\t\t********************0.退出系统*******************\n");
	printf("\n");
	printf("\t\t\t请选择(0-5):");
}

//图书管理子菜单
void ShowBookMenu()  
{
	system("cls");  //清屏函数
	printf("\n\n\n\n");
	printf("\t\t\t\t********************欢迎进入*************************\n");
	printf("\t\t\t\t********************图书管理系统*********************\n");
	printf("\t\t\t\t********************子菜单***************************\n");
	printf("\t\t\t\t********************1.显示图书信息*******************\n");
	printf("\t\t\t\t********************2.新增图书信息*******************\n");
	printf("\t\t\t\t********************3.查找图书信息*******************\n");
	printf("\t\t\t\t********************4.删除图书信息*******************\n");
	printf("\t\t\t\t********************5.修改图书信息*******************\n");
	printf("\t\t\t\t********************0.返回主菜单*********************\n");
	printf("\n");
	printf("\t\t\t请选择(0-5):");
}

//图书修改子菜单
void ShowModifyBookMenu() {  
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t\t\t***************************请选择修改方式***************************\n");
	printf("\t\t\t\t***************************1.编号***********************************\n");
	printf("\t\t\t\t***************************2.书名***********************************\n");
	printf("\t\t\t\t***************************3.作者***********************************\n");
	printf("\t\t\t\t***************************4.出版社*********************************\n");
	printf("\t\t\t\t***************************5.库存量*********************************\n");
	printf("\n");
	printf("\t\t\t请输入要修改的信息(1-5):");
}

//读者管理子菜单
void ShowReaderMenu() {
	system("cls");  //清屏函数
	printf("\n\n\n\n");
	printf("\t\t\t\t********************欢迎进入*************************\n");
	printf("\t\t\t\t********************读者管理系统*********************\n");
	printf("\t\t\t\t********************子菜单***************************\n");
	printf("\t\t\t\t********************1.显示读者信息*******************\n");
	printf("\t\t\t\t********************2.新增读者信息*******************\n");
	printf("\t\t\t\t********************3.查找读者信息*******************\n");
	printf("\t\t\t\t********************4.删除读者信息*******************\n");
	printf("\t\t\t\t********************5.修改读者信息*******************\n");
	printf("\t\t\t\t********************0.返回主菜单*********************\n");
	printf("\n");
	printf("\t\t\t请选择(0-5):");
}

//读者修改子菜单
void ShowModifyReaderMenu() { 
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t\t\t***************************请选择修改方式***************************\n");
	printf("\t\t\t\t***************************1.编号***********************************\n");
	printf("\t\t\t\t***************************2.姓名***********************************\n");
	printf("\t\t\t\t***************************3.性别***********************************\n");
	printf("\t\t\t\t***************************4.最大可借阅数***************************\n");
	printf("\t\t\t\t***************************4.当前借阅数***************************\n");
	printf("\n");
	printf("\t\t\t请输入要修改的信息(1-4):");
}

//借书还书子菜单
void ShowBorrowReturnMenu() {
	system("cls");  //清屏函数
	printf("\n\n\n\n");
	printf("\t\t\t\t********************欢迎进入*************************\n");
	printf("\t\t\t\t********************借书还书*************************\n");
	printf("\t\t\t\t********************子菜单***************************\n");
	printf("\t\t\t\t********************1.借书登记***********************\n");
	printf("\t\t\t\t********************2.还书登记***********************\n");
	printf("\t\t\t\t********************0.返回主菜单*********************\n");
	printf("\n");
	printf("\t\t\t请选择(0-2):");
}

//图书查询方式子菜单
void ShowBookSearchMenu() {
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t\t\t********************图书查询方式*********************\n");
	printf("\t\t\t\t********************1.按编号精准查询*****************\n");
	printf("\t\t\t\t********************2.按名称模糊查询*****************\n");
	printf("\t\t\t\t********************0.退出***************************\n");
	printf("\n");
	printf("\t\t\t请选择查询方式(0-2):");
}

//帮助手册菜单
void ShowHelpMenu() {
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t\t\t********************系统帮助*********************\n");
	printf("\t\t\t\t1. 图书管理：可增删改查图书信息\n");
	printf("\t\t\t\t2. 读者管理：可增删改查读者信息\n");
	printf("\t\t\t\t3. 借还书：支持图书借阅/归还登记\n");
	printf("\t\t\t\t4. 借阅详情：查询读者已借图书+借阅时间\n");
	printf("\t\t\t\t*************************************************\n");
}

//图书管理

//读取图书文件数据到全局数组astBook
int ReadBookFile(const char* pcMode) {  //读文件
	int iBookRecord = 0;
	FILE* pfBook;  //文件指针
	pfBook = fopen("book.txt", pcMode);
	if (pfBook == NULL)return -1;
	while (!feof(pfBook)) {  //文件末尾停止
		if (fread(&astBook[iBookRecord], LEN_BOOK, 1, pfBook)) {
			iBookRecord++;
		}
	}
	fclose(pfBook);
	return iBookRecord;
}

//显示所有图示信息
void ShowBook() {  //显示图书信息
	system("cls");
	int i, iBookReacord;
	iBookReacord = ReadBookFile("rb"); //接收返回值(读取成功条数)
	if (iBookReacord == -1) {
		printf("该文件打开失败，请先增加图书信息!\n");
	}
	else if (iBookReacord == 0) {
		printf("文件中没有图书信息!\n");
	}
	else {
		printf("\t\t---------------------------------图书信息------------------------------------\n");
		printf("\n");
		printf("\t\t   %-16s%-16s%-16s%-16s%-16s\n", "编号", "书名", "作者", "出版社", "库存量");
		printf("\t\t-----------------------------------------------------------------------------\n");
		for (i = 0; i < iBookReacord; ++i) {
			printf("\t\t   %-16d%-16s%-16s%-16s%-16d\n", BOOK_DATA);
		}
		printf("\n");
		printf("\t\t-----------------------------------------------------------------------------\n");
		printf("\n\n");
	}
}

//添加图书信息
void AddBook() {  
	FILE* pfBook;  //文件指针
	int iBookReacord, iFlagExit, i;  
	//iFlagExit：编号重复标记
	char cFlag; //继续添加标记
	iBookReacord = ReadBookFile("ab+"); //ab+追加的方式打开或新建二进制文件
	//接收成功读取的条数
	if (iBookReacord == -1) {
		printf("文件打开失败!\n");
		return;
	}
	else if (iBookReacord == 0) {
		printf("没有图书记录!\n");
	}
	else {
		ShowBook(); //记录不为0,显示
	}
	printf("请选择是否输入信息(y/n):");
	cFlag = getchar();
	getchar(); //吸收换行符
	if (cFlag == 'n')return;
	pfBook = fopen("book.txt", "ab+"); //追加模式打开文件
	if (pfBook == NULL) {
		printf("文件打开失败!\n");
		return;
	}
	//循环录入图书信息
	while (cFlag == 'y') {
		//循环录入
		printf("录入数据!\n");
		if (iBookReacord >= BOOK_NUM) {
			printf("记录已满!\n");
			fclose(pfBook);
			return;
		}
		//录入图书编号，保证图书编号不能重复
		do {
			printf("请输入图书编号:");
			iFlagExit = 0;
			scanf("%d", &astBook[iBookReacord].iNum);
			getchar();
			for (i = 0; i < iBookReacord; ++i) {
				//编号不能等于自己(无意义修改)和别人
				if (astBook[i].iNum == astBook[iBookReacord].iNum) {
					iFlagExit = 1;
					printf("该图书编号已经存在!请重新输入!\n");
					break;
				}
			}
		} while (iFlagExit == 1); //重复重新输入

		printf("请输入图书名称:");
		scanf("%s", astBook[iBookReacord].acName);
		getchar();

		printf("请输入图书作者:");
		scanf("%s", astBook[iBookReacord].acAuthor);
		getchar();

		printf("请输入图书出版社:");
		scanf("%s", astBook[iBookReacord].acPress);
		getchar();

		printf("请输入图书库存量:");
		scanf("%d", &astBook[iBookReacord].iAmount);
		getchar();

		//保存信息

		if (fwrite(&astBook[iBookReacord], LEN_BOOK, 1, pfBook) != 1) {
			printf("无法保存该信息!\n");
			return;
		}
		else {
			printf("%d号图书信息已经保存!\n", astBook[iBookReacord].iNum);
		}
		//判断是否继续添加
		printf("继续录入信息吗?(y/n)\n");
		cFlag = getchar();
		getchar();
	}
	//关闭文件
	fclose(pfBook);
	printf("添加图书执行完毕!\n");
}

//查找图书信息
int SearchBook() {  
	int iBookNum, iBookRecord, iBookId, i,choice;
	//iBookNum 输入的目标图书编号
	//choice 输入查询方式编号
	//iBookId 返回值，返回目标图书下标，未找到返回-1，文件异常返回-2/-3
	char keyName[15]; //存储名称查询关键词
	iBookRecord = ReadBookFile("rb"); //接收成功读取的条数
	if (iBookRecord == -1) {
		printf("文件打开失败!\n");
		printf("按任意键返回子菜单");
		_getch();
		return -2;
	}
	else if (iBookRecord == 0) {
		printf("没有图书记录!\n");
		printf("按任意键返回子菜单");
		_getch();
		return -3;
	}
	//选择查询方式
	ShowBookSearchMenu();
	scanf("%d", &choice);
	getchar();
	if (choice == 1) {
		printf("请输入图书编号:");
		scanf("%d", &iBookNum);
		getchar();
		for (i = 0; i < iBookRecord; ++i) {
			if (iBookNum == astBook[i].iNum) {
				iBookId = i;
				printf("\t%d号图书信息如下:\n", iBookNum);
				printf("\t\t---------------------------------查询结果------------------------------------\n");
				printf("\t\t   %-16s%-16s%-16s%-16s%-16s\n", "编号", "书名", "作者", "出版社", "库存量");
				printf("\t\t-----------------------------------------------------------------------------\n");
				printf("\t\t   %-16d%-16s%-16s%-16s%-16d\n", BOOK_DATA);
				printf("\t\t-----------------------------------------------------------------------------\n");
				break;
			}
		}
		if (i == iBookRecord) {
			printf("找不到%d号图书信息!\n", iBookNum);
			iBookId = -1;
		}
	}
	//按名称模糊查询
	else if (choice == 2) {
		printf("请输入图书名称关键词（支持模糊匹配）:");
		scanf("%s", keyName);
		getchar();
		printf("\n");
		printf("\t\t---------------------------------查询结果------------------------------------\n");
		printf("\t\t   %-16s%-16s%-16s%-16s%-16s\n", "编号", "书名", "作者", "出版社", "库存量");
		printf("\t\t-----------------------------------------------------------------------------\n");

		int findCount = 0;
		// 遍历图书数组，用strstr实现模糊匹配
		for (i = 0; i < iBookRecord; i++) {
			if (strstr(astBook[i].acName, keyName) != NULL) {
				printf("\t\t   %-16d%-16s%-16s%-16s%-16d\n", BOOK_DATA);	
				findCount++;
				iBookId = i; // 记录最后一个匹配的图书下标
			}
		}
		if (findCount == 0) {
			printf("\t\t未找到包含「%s」的图书！\n", keyName);
			iBookId = -1;
		}
	}
	else if(choice == 0){
		printf("已取消查询操作，返回上一级菜单\n");
		return -1; // 返回-1表示查询被取消	
	}
	else {
		printf("输入有误! 仅支持0-2选项!\n");
		iBookId = -4;
	}
	return iBookId;
}

//删除图书信息
void DeleteBook() {  
	FILE* pfBook;
	int iBookId, iBookRecord, i;
	//iBookId 返回值，返回目标图书下标
	char cFlag;
	//cFlag 确认是否删除
	iBookId = SearchBook();
	if (iBookId == -1) {
		printf("没有该图书!");
		return;
	}
	iBookRecord = ReadBookFile("rb"); //接收成功读取的条数
	printf("已经找到该图书，是否删除? (y/n)\n");
	cFlag = getchar();
	getchar();
	//要删除的图书编号
	int index = astBook[iBookId].iNum;
	if (cFlag == 'n')
		return;
	else if (cFlag == 'y') {
		//覆盖删除
		for (i = iBookId; i + 1 < iBookRecord; ++i) {
			astBook[i] = astBook[i + 1];
		}
		//记录数-1
		iBookRecord--;
	}

	//保存
	pfBook = fopen("book.txt", "wb");
	if (pfBook != NULL) {
		for (i = 0; i < iBookRecord; ++i) {
			if (fwrite(&astBook[i], LEN_BOOK, 1, pfBook) != 1) {
				printf("无法保存该信息!\n");
				return;
			}
		}
		fclose(pfBook);
		printf("%d号图书已经删除!\n", index);
	}
}

// 保存修改后的单条图书信息到文件
void SaveBookFile(int iBookId) { 
	FILE* pfBook;
	pfBook = fopen("book.txt", "rb+"); //读+写
	if (pfBook != NULL) {
		// 定位到要修改的图书位置  SEEK_SET:文件开头
		fseek(pfBook, iBookId * LEN_BOOK, SEEK_SET);
		if (fwrite(&astBook[iBookId], LEN_BOOK, 1, pfBook) != 1) {
			printf("无法保存该信息!\n");
		}
	}
	fclose(pfBook);
}

//修改图书信息
void ModifyBook() {  
	int iBookId, iBookRecord, iFlagExist, iltem, iNum, i;
	//iFlagExist 判断编号是否重复
	//iltem 选择修改方式
	iBookId = SearchBook();
	if (iBookId == -1) {
		printf("没有该图书!");
		return;
	}
	//读取图书记录
	iBookRecord = ReadBookFile("rb");
	//展示修改子菜单
	ShowModifyBookMenu();
	scanf("%d", &iltem);
	getchar();
	switch (iltem) {
	case 1:
		do {
			printf("\t\t\t请输入图书编号:");
			iFlagExist = 0;
			scanf("%d", &iNum);
			getchar();
			for (i = 0; i < iBookRecord; ++i) {
				if (iNum == astBook[i].iNum) {  //|| iNum == astBook[iBookId].iNum 加上一样,代码冗余
					iFlagExist = 1;
					printf("\t\t\t该编号已经存在，请重新输入!\n");
					break;
				}
			}
		} while (iFlagExist == 1);
		astBook[iBookId].iNum = iNum;
		break;
	case 2:
		printf("\t\t\t请输入图书名称:");
		scanf("%s", astBook[iBookId].acName);
		getchar();
		break;
	case 3:
		printf("\t\t\t请输入图书作者:");
		scanf("%s", astBook[iBookId].acAuthor);
		getchar();
		break;
	case 4:
		printf("\t\t\t请输入图书出版社:");
		scanf("%s", astBook[iBookId].acPress);
		getchar();
		break;
	case 5:
		printf("\t\t\t请输入图书库存量:");
		scanf("%d", &astBook[iBookId].iAmount);
		getchar();
		break;
	}

	// 保存
	SaveBookFile(iBookId);
	printf("\t\t\t图书信息已经修改成功!\n");
}

//图书管理总入口
void ManageBook() {  
	int iltem;
	ShowBookMenu();
	scanf("%d", &iltem);
	getchar();
	while (iltem) {
		switch (iltem) {
		case 1:
			ShowBook(); //显示图书信息
			break;
		case 2:
			AddBook(); //新增图书信息
			break;
		case 3:
			SearchBook(); //查找图书信息
			break;
		case 4:
			DeleteBook(); //删除图书信息
			break;
		case 5:
			ModifyBook();// 修改图书信息
			break;
		default:
			printf("\t\t请输入正确的数字(0-5)!\n");
		}
		printf("按任意键返回子菜单\n");
		_getch();  //从键盘上获取一个字符但不执行
		ShowBookMenu();
		scanf("%d", &iltem);
		getchar();
	}
} 

//读者管理

// 读取读者文件信息到全局数组astReader
int ReadReaderFile(const char* foMode) {   
	int iReaderReadcord = 0;
	FILE* pfReader;
	pfReader = fopen("reader.txt", foMode);
	if (pfReader == NULL)return -1;
	while (!feof(pfReader)) {
		if (fread(&astReader[iReaderReadcord], LEN_READER, 1, pfReader)) {
			iReaderReadcord++;
		}
	}
	fclose(pfReader);
	return iReaderReadcord;
}

//显示所有读者信息
void ShowReader() {  
	system("cls");
	int i, iReaderReacord;
	iReaderReacord = ReadReaderFile("rb");
	if (iReaderReacord == -1) {
		printf("该文件打开失败，请先增加读者信息!\n");
	}
	else if (iReaderReacord == 0) {
		printf("文件中没有读者信息!\n");
	}
	else {
		printf("\t\t-------------------------------------读者信息------------------------------------\n");
		printf("\n");
		printf("\t\t   %-16s%-16s%-16s%-16s%-16s\n", "编号", "姓名", "性别", "最大借阅量", "当前可借阅量");
		printf("\t\t---------------------------------------------------------------------------------\n");
		for (i = 0; i < iReaderReacord; ++i) {
			printf("\t\t   %-16d%-16s%-16s%-16d%-16d\n", READER_DATA);
		}
		printf("\n");
		printf("\t\t---------------------------------------------------------------------------------\n");
		printf("\n\n");
	}
}

//新增读者信息
void AddReader() {  
	FILE* pfReader;
	int iReaderReacord, iFlagExit, i;
	char cFlag;
	//system("cls");
	iReaderReacord = ReadReaderFile("ab+"); //ab+追加的方式打开或新建二进制文件
	if (iReaderReacord == -1) {
		printf("文件打开失败!\n");
		return;
	}
	else if (iReaderReacord == 0) {
		printf("没有读者记录!\n");
	}
	else {
		ShowReader(); //记录不为0,显示
	}
	//循环录入读者信息
	printf("请选择是否输入信息(y/n):");
	cFlag = getchar();
	getchar();
	if (cFlag == 'n')return;
	pfReader = fopen("reader.txt", "ab+");
	if (pfReader == NULL) {
		printf("文件打开失败!\n");
		return;
	}
	while (cFlag == 'y') {
		//循环录入
		printf("录入数据!\n");
		if (iReaderReacord >= READER_NUM) {
			printf("记录已满!\n");
			fclose(pfReader);
			return;
		}
		//录入读者编号，保证图书编号不能重复
		do {
			printf("请输入读者编号:");
			iFlagExit = 0;
			scanf("%d", &astReader[iReaderReacord].iNum);
			getchar();
			for (i = 0; i < iReaderReacord; ++i) {
				if (astReader[i].iNum == astReader[iReaderReacord].iNum) {
					iFlagExit = 1;
					printf("该读者编号已经存在!请重新输入!\n");
					break;
				}
			}
		} while (iFlagExit == 1);

		printf("请输入读者姓名:");
		scanf("%s", astReader[iReaderReacord].acName);

		getchar();

		printf("请输入读者性别:");
		scanf("%s", astReader[iReaderReacord].acSex);
		getchar();
		//strcmp和输入比较，性别只能为男/女
		while (strcmp(astReader[iReaderReacord].acSex, "男") != 0
			&& strcmp(astReader[iReaderReacord].acSex, "女") != 0) {
			printf("输入错误！只能输入“男”或“女”\n");
			printf("请重新输入读者性别（男/女）:");
			scanf("%s", astReader[iReaderReacord].acSex);
			getchar();
		}
		printf("请输入读者最大可借阅数量(5--15本):");
		scanf("%d", &astReader[iReaderReacord].iMax);
		getchar();

		// 校验最大可借阅数范围
		while (astReader[iReaderReacord].iMax < 5 || astReader[iReaderReacord].iMax > 15) {
			printf("最大可借阅数范围为5-15，请重新输入:");
			scanf("%d", &astReader[iReaderReacord].iMax);
			getchar();
		}
		// 强制当前可借阅数=最大可借阅数（新读者无借阅）
		astReader[iReaderReacord].iAmount = astReader[iReaderReacord].iMax;
		printf("新读者当前可借阅数自动设为: %d\n", astReader[iReaderReacord].iAmount);

		//写入信息

		if (fwrite(&astReader[iReaderReacord], LEN_READER, 1, pfReader) != 1) {
			printf("无法保存该信息!\n");
			return;
		}
		else {
			printf("%d号读者信息已经保存!\n", astReader[iReaderReacord].iNum);
			iReaderReacord++;
		}

		printf("继续录入信息吗?(y/n)\n");
		cFlag = getchar();
		getchar();
	}
	fclose(pfReader);
	printf("添加读者执行完毕!\n");
}

//查找读者信息
int SearchReader() {  
	int iReaderNum, iReaderRecord, iReaderId, i;
	system("cls");
	iReaderRecord = ReadReaderFile("rb");
	if (iReaderRecord == -1) {
		printf("文件打开失败!\n");
		printf("按任意键返回子菜单");
		_getch();
		return -2;
	}
	else if (iReaderRecord == 0) {
		printf("没有读者记录!\n");
		printf("按任意键返回子菜单");
		_getch();
		return -3;
	}
	//记录查找程序
	printf("请输入读者编号:");
	scanf("%d", &iReaderNum);
	getchar();
	for (i = 0; i < iReaderRecord; ++i) {
		if (iReaderNum == astReader[i].iNum) {
			iReaderId = i;
			printf("\t%d号读者信息如下:\n", iReaderNum);
			printf("\t\t-------------------------------------读者信息------------------------------------\n");
			printf("\t\t   %-16s%-16s%-16s%-16s%-16s\n", "编号", "姓名", "性别", "最大借阅量", "当前可借阅量");
			printf("\t\t---------------------------------------------------------------------------------\n");
			printf("\t\t   %-16d%-16s%-16s%-16d%-16d\n", READER_DATA);
			printf("\t\t---------------------------------------------------------------------------------\n");
			break;
		}
	}
	if (i == iReaderRecord) {
		printf("找不到%d号读者信息!\n", iReaderNum);
		iReaderId = -1;
	}
	return iReaderId;
}

//读者借阅详情查询
void SearchReaderBorrowInfo() {
	system("cls");
	int iReaderCount = ReadReaderFile("rb");
	if (iReaderCount == -1) return;

	// 输入要查询的读者编号
	int searchReaderNum;
	printf("请输入要查询的读者编号：");
	scanf("%d", &searchReaderNum);
	getchar();

	// 查找对应读者
	int findReaderIdx = -1;
	for (int i = 0; i < iReaderCount; i++) {
		if (astReader[i].iNum == searchReaderNum) {
			findReaderIdx = i;
			break;
		}
	}
	if (findReaderIdx == -1) {
		printf("未找到编号为%d的读者！\n", searchReaderNum);
		return;
	}

	// 计算已借图书数量
	int borrowCount = astReader[findReaderIdx].iMax - astReader[findReaderIdx].iAmount;

	// 打印读者借阅详情
	printf("\t\t---------------------------------借阅详情------------------------------------\n");
	printf("\t\t   %-16s%-16s%-16s\n", "编号", "姓名", "当前可借阅量");
	printf("\t\t-----------------------------------------------------------------------------\n");
	printf("\t\t   %-16d%-16s%-16d\n", astReader[findReaderIdx].iNum, astReader[findReaderIdx].acName, astReader[findReaderIdx].iAmount);
	printf("\t\t-----------------------------------------------------------------------------\n");

	if (borrowCount == 0) {
		printf("\t\t该读者暂无已借图书！\n");
	}
	else {
		printf("\t\t已借图书列表：\n");
		printf("\t\t%-16s%-16s\n", "图书编号", "借阅时间");
		printf("\t\t-----------------------------------------------------------------------------\n");
		// 遍历已借图书，打印编号+借阅时间
		for (int j = 0; j < borrowCount; j++) {
			// 将时间戳转换为YYYY-MM-DD格式
			char timeStr[20];
			strftime(timeStr, sizeof(timeStr), "%Y-%m-%d", localtime(&astReader[findReaderIdx].borrowTime[j]));
			printf("\t\t%-16d%-16s\n", astReader[findReaderIdx].BookId[j], timeStr);
		}
	}
	printf("\t\t-----------------------------------------------------------------------------\n");
}

//删除读者信息
void DeleteReader() {  
	FILE* pfReader;
	int iReaderId, iReaderRecord, i;
	char cFlag;

	system("cls");
	iReaderId = SearchReader();
	if (iReaderId == -1)
		return;

	iReaderRecord = ReadReaderFile("rb");
	printf("已经找到该读者，是否删除? (y/n):");
	cFlag = getchar();
	getchar();

	int index = astReader[iReaderId].iNum;
	if (cFlag == 'n')
		return;
	else if (cFlag == 'y') {
		for (i = iReaderId; i + 1 < iReaderRecord; ++i) {
			astReader[i] = astReader[i + 1];
		}
		iReaderRecord--;
	}

	//保存
	pfReader = fopen("reader.txt", "wb");
	if (pfReader != NULL) {
		for (i = 0; i < iReaderRecord; ++i) {
			if (fwrite(&astReader[i], LEN_READER, 1, pfReader) != 1) {
				printf("无法保存该信息!\n");
				return;
			}
		}
		fclose(pfReader);
		printf("%d号读者已经删除!\n", index);
	}
}

//保存修改后的读者信息到文件
void SaveReaderFile(int iReaderId) { 
	FILE* pfReader;
	pfReader = fopen("reader.txt", "rb+");
	if (pfReader != NULL) {
		fseek(pfReader, iReaderId * LEN_READER, SEEK_SET);
		if (fwrite(&astReader[iReaderId], LEN_READER, 1, pfReader) != 1) {
			printf("无法保存该信息!\n");
		}
	}
	fclose(pfReader);
}

//修改读者信息
void ModifyReader() {  //修改读者信息
	int iReaderId, iReaderRecord, iBorrow, iFlagExist, iltem, iNum, iMax,i;
	//iBorrow 已经借阅的数量
	system("cls");
	iReaderId = SearchReader();
	if (iReaderId == -1)return;

	iReaderRecord = ReadReaderFile("rb");

	//system("cls");
	ShowModifyReaderMenu();
	scanf("%d", &iltem);
	getchar();
	switch (iltem) {
	case 1:
		do {
			printf("\t\t\t请输入读者编号:");
			iFlagExist = 0;
			scanf("%d", &iNum);
			getchar();
			for (i = 0; i < iReaderRecord; ++i) {
				if (iNum == astReader[i].iNum) {
					iFlagExist = 1;
					printf("\t\t\t该读者编号已经存在，请重新输入!\n");
					break;
				}
			}
		} while (iFlagExist == 1);
		astReader[iReaderId].iNum = iNum;
		break;
	case 2:
		printf("\t\t\t请输入读者姓名:");
		scanf("%s", astReader[iReaderId].acName);
		getchar();
		break;
	case 3:
		printf("\t\t\t请输入读者性别: 男/女:");
		scanf("%s", astReader[iReaderId].acSex);
		while (strcmp(astReader[iReaderId].acSex, "男") != 0
			&& strcmp(astReader[iReaderId].acSex, "女") != 0) {
			printf("\t\t\t只能输入男或女!请重新输入!\n");
			printf("\t\t\t请输入读者性别：男/女:");
			scanf("%s", astReader[iReaderId].acSex);
		}
		break;
	case 4:
		// case 4: 修改读者最大可借阅数量逻辑
		iBorrow = astReader[iReaderId].iMax - astReader[iReaderId].iAmount;
		// 已借阅的图书数量 = 最大可借阅数量 - 当前剩余可借阅数量
		printf("请输入读者最大可借阅的数量(范围为5-15):");
		while (scanf("%d", &iMax) == 1)
		{
			getchar(); // 吸收输入缓冲区的换行符，避免后续输入异常
			if (iMax >= 5 && iMax <= 15)
			{
				// 若当前已借阅数量超过新设置的最大可借阅数，不允许修改
				if (iBorrow > iMax)
				{
					printf("该读者目前图书借阅数量大于该数目,需要先还书后修改!\n");
					return;
				}
				else
				{
					// 更新最大可借阅数和剩余可借阅数
					astReader[iReaderId].iMax = iMax;
					astReader[iReaderId].iAmount = iMax - iBorrow;
					// 对新增的可借阅位置，图书ID置0（初始化空位置）
					for (i = iBorrow; i < iMax; i++)
					{
						astReader[iReaderId].BookId[i] = 0;
					}
					break; // 输入合法，退出循环
				}
			}
			// 输入数值超出范围，提示重新输入
			printf("错误,读者最大可借阅数范围为5-15,请重新输入\n");
		}
		break;

		// 保存修改后的读者信息到文件
		SaveReaderFile(iReaderId);
		printf("读者信息已经修改成功!\n");
	}

	// 保存
	SaveReaderFile(iReaderId);
	printf("\t\t\t读者信息已经修改成功!\n");
}

//读者管理总入口
void ManageReader() { 
	int iltem;
	ShowReaderMenu();
	scanf("%d", &iltem);
	getchar();
	while (iltem) {
		switch (iltem) {
		case 1:
			ShowReader(); //显示读者信息
			break;
		case 2:
			AddReader(); //新增读者信息
			break;
		case 3:
			SearchReader(); //查找读者信息
			break;
		case 4:
			DeleteReader(); //删除读者信息
			break;
		case 5:
			ModifyReader();// 修改读者信息
			break;
		default:
			printf("\t\t请输入正确的数字(0-5)!\n");
		}
		printf("按任意键返回子菜单\n");
		_getch();  //从键盘上获取一个字符但不执行
		ShowReaderMenu();
		scanf("%d", &iltem);
		getchar();
	}
}  

//借书还书

//图书借阅功能
void BorrowBook() { 
	//读者编号是否存在
	//图书编号是否存在(库存量够不够)
	system("cls");
	int iBookId, iReaderId, iBorrow, i;
	char Confirm;
	iReaderId = SearchReader();
	if (iReaderId == -1) {
		printf("该读者不存在!请输入正确读者编号!\n");
		return;
	}
	//查询读者借阅数
	iBorrow = astReader[iReaderId].iMax - astReader[iReaderId].iAmount;
	if (iBorrow == 0) {
		printf("该读者没有借阅任何书籍!\n");
	}
	else {
		printf("该读者当前所借阅的图书为: ");
		//显示已借图书
		for (i = 0; i < iBorrow; ++i) {
			printf("%d\t", astReader[iReaderId].BookId[i]);
		}
		printf("\n\n");
	}
	if (astReader[iReaderId].iAmount == 0) {
		printf("该读者当前可借阅的书籍数量为0，不能继续借书!\n");
		return;
	}
	printf("\t按任意键输入要借阅的图书信息!\n");
	_getch();
	iBookId = SearchBook();
	// 根据不同的返回值，输出不同的提示
	if (iBookId == -4) {
		return;
	}
	else if (iBookId == -1) {
		printf("没有该图书！\n");
		return;
	}
	else if (iBookId == -2) {
		printf("文件读取失败！\n");
		return;
	}
	else if (iBookId == -3) {
		printf("无图书记录！\n");
		return;
	}
	if (astBook[iBookId].iAmount == 0) {
		printf("该图书库存量为0!图书不可借阅!\n");
	}
	//借书确认
	printf("\n是否确认借阅该图书？(y/n):");
	Confirm = getchar();
	getchar();
	if (Confirm == 'n') {
		printf("已取消借阅操作!\n");
		return;
	}
	else if (Confirm == 'y') {
		//执行借书
		astReader[iReaderId].BookId[iBorrow] = astBook[iBookId].iNum;
		//记录当前时间
		astReader[iReaderId].borrowTime[iBorrow] = time(NULL);
		//图书的库存量--
		astBook[iBookId].iAmount--;
		//读者当前可借阅量--
		astReader[iReaderId].iAmount--;
		SaveBookFile(iBookId);
		SaveReaderFile(iReaderId);
		printf("借书成功!\n");
	}
}

//图书归还功能
void ReturnBook() {
	//读者是否存在
	//图书是否存在
	//图书列表没有这本书
	system("cls");
	int iBookId, iReaderId, iBorrow, i, j;

	iReaderId = SearchReader();
	if (iReaderId == -1) {
		printf("没有该读者!\n");
		return;
	}
	//计算当前借阅数
	iBorrow = astReader[iReaderId].iMax - astReader[iReaderId].iAmount;
	if (iBorrow == 0) {
		printf("该读者没有借阅任何书，无需归还!\n");
		return;
	}
	else {
		printf("该读者当前所借阅的书籍为: ");
		//显示已借图书
		for (i = 0; i < iBorrow; ++i) {
			printf("%d\t", astReader[iReaderId].BookId[i]);
		}
		printf("\n\n");
	}

	printf("\t按任意键输入要归还的图书信息!\n");
	_getch();

	iBookId = SearchBook();
	if (iBookId == -1) {
		printf("没有该书籍!\n");
		return;
	}
	//找到读者了，也找到书
	//借阅列表里面有没有这本书
	for (i = 0; i < iBorrow; ++i) {
		if (astReader[iReaderId].BookId[i] == astBook[iBookId].iNum) {
			//还书
			for (j = i; j < iBorrow; ++j) {
				astReader[iReaderId].BookId[j] = astReader[iReaderId].BookId[j + 1];
				//时间同步前移
				astReader[iReaderId].borrowTime[j] = astReader[iReaderId].borrowTime[j + 1];
			}
			//最后一个位置置为0
			astReader[iReaderId].BookId[iBorrow - 1] = 0;
			astReader[iReaderId].borrowTime[iBorrow - 1] = 0;
			//图书库存量++
			astBook[iBookId].iAmount++;
			//读者当前可借阅数++
			astReader[iReaderId].iAmount++;
			break;
		}
	}
	if (i == iBorrow) {
		printf("该读者没有借阅这本书，无需归还!\n");
		return;
	}
	//保存
	SaveBookFile(iBookId);
	SaveReaderFile(iReaderId);
	printf("还书成功!\n");
	//显示归还后的已借图书
	printf("该读者当前所借阅的图书为: ");
	//已归还一本，遍历长度-1
	for (i = 0; i < iBorrow; ++i) {
		printf("%d\t", astReader[iReaderId].BookId[i]);
	}
}

//借书还书管理总入口
void BorrowReturnManger() {  
	ShowBorrowReturnMenu();  //借书还书子菜单
	int iltem;
	scanf("%d", &iltem);
	getchar();
	while (iltem) {
		switch (iltem) {
		case 1:
			BorrowBook();//借书
			break;
		case 2:
			ReturnBook(); //还书
			break;
		default:
			printf("\t\t请输入正确的数字(0-2)!\n");
		}
		printf("按任意键返回子菜单");
		_getch();
		ShowBorrowReturnMenu();
		scanf("%d", &iltem);
		getchar();
	}
}

int main() 
{
	ShowMainMenu();
	int iltem;
	scanf("%d", &iltem);
	getchar();
	while (iltem) {
		switch (iltem) {
		case 1:
			ManageBook(); //图书管理模块 
			break;
		case 2:
			ManageReader(); //读者管理模块 
			break;
		case 3: 
			BorrowReturnManger(); //借书还书模块 
			break;
		case 4:  
			SearchReaderBorrowInfo();//读者借阅详情
			printf("按任意键返回主菜单!");
			_getch();
			break;
		case 5:  // 帮助手册
			ShowHelpMenu();
			printf("按任意键返回主菜单!");
			_getch();
			break;
		default:
			printf("\t\t\t只能输入正确的数字(0-5)!\n\t\t\t程序将在3秒之后跳转主菜单!\n");
			Sleep(3000);
		}
		ShowMainMenu();
		scanf("%d", &iltem);
		getchar();
	}
	return 0;
}

#endif