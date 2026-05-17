#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <unistd.h>
#include <time.h>

MYSQL *conn;   // 全局数据库连接

//工具函数
// 清屏
void Clear()
{
    system("clear"); //系统函数
}

// 暂停
void Pause()
{
    printf("\n\t\t按回车键继续...");
    getchar();  //等待输入 吸取缓冲区换行
}

//初始化
void InitDB()
{
    //初始化
    conn = mysql_init(NULL);

    //连接数据库
    if (!mysql_real_connect(conn, "localhost", "root",
        "quzijie_123", "db_book", 3306, NULL, 0))
    {
        printf("数据库连接失败:%s\n", mysql_error(conn));
        exit(1);
    }
}

//菜单
// 主菜单
void ShowMainMenu()
{
    Clear();
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

// 图书管理子菜单
void ShowBookMenu()
{
    Clear();
    printf("\n\n\n\n");
    printf("\t\t\t\t********************图书管理*********************\n");
    printf("\t\t\t\t********************1.显示图书信息***************\n");
    printf("\t\t\t\t********************2.新增图书信息***************\n");
    printf("\t\t\t\t********************3.查找图书信息***************\n");
    printf("\t\t\t\t********************4.删除图书信息***************\n");
    printf("\t\t\t\t********************5.修改图书信息***************\n");
    printf("\t\t\t\t********************0.返回主菜单*****************\n");
    printf("\n");
    printf("\t\t\t请选择(0-5):");
}

// 图书查询子菜单
void ShowBookSearchMenu()
{
    Clear();
    printf("\n\n\n\n");
    printf("\t\t\t\t********************图书查询方式*****************\n");
    printf("\t\t\t\t********************1.按编号精准查询*************\n");
    printf("\t\t\t\t********************2.按名称模糊查询*************\n");
    printf("\t\t\t\t********************0.返回***********************\n");
    printf("\n");
    printf("\t\t\t请选择(0-2):");
}

// 图书修改子菜单
void ShowModifyBookMenu()
{
    Clear();
    printf("\n\n\n\n");
    printf("\t\t\t\t*******************请选择修改方式****************\n");
    printf("\t\t\t\t*******************1.编号***********************\n");
    printf("\t\t\t\t*******************2.书名***********************\n");
    printf("\t\t\t\t*******************3.作者***********************\n");
    printf("\t\t\t\t*******************4.出版社*********************\n");
    printf("\t\t\t\t*******************5.库存量*********************\n");
    printf("\n");
    printf("\t\t\t请输入(1-5):");
}

// 读者管理子菜单
void ShowReaderMenu()
{
    Clear();
    printf("\n\n\n\n");
    printf("\t\t\t\t********************读者管理*********************\n");
    printf("\t\t\t\t********************1.显示读者信息***************\n");
    printf("\t\t\t\t********************2.新增读者信息***************\n");
    printf("\t\t\t\t********************3.查找读者信息***************\n");
    printf("\t\t\t\t********************4.删除读者信息***************\n");
    printf("\t\t\t\t********************5.修改读者信息***************\n");
    printf("\t\t\t\t********************0.返回主菜单*****************\n");
    printf("\n");
    printf("\t\t\t请选择(0-5):");
}

// 借书还书菜单
void ShowBorrowReturnMenu()
{
    Clear();
    printf("\n\n\n\n");
    printf("\t\t\t\t********************借书还书*********************\n");
    printf("\t\t\t\t********************1.借书登记*******************\n");
    printf("\t\t\t\t********************2.还书登记*******************\n");
    printf("\t\t\t\t********************0.返回主菜单*****************\n");
    printf("\n");
    printf("\t\t\t请选择(0-2):");
}

// 帮助手册
void ShowHelpMenu()
{
    Clear();
    printf("\n\n\n\n");
    printf("\t\t\t\t********************系统帮助*********************\n");
    printf("\t\t\t\t1. 图书管理：增删改查图书信息\n");
    printf("\t\t\t\t2. 读者管理：增删改查读者信息\n");
    printf("\t\t\t\t3. 借书还书：自动更新库存与借阅量\n");
    printf("\t\t\t\t4. 借阅详情：查看读者借阅时间\n");
    printf("\t\t\t\t*************************************************\n");
}

//功能函数
//-------------------------------图书管理模块

// 显示所有图书
void ShowAllBook()
{
    //执行查询语句
    mysql_query(conn, "select * from book");
    //获取结果集
    MYSQL_RES *res = mysql_store_result(conn);
    MYSQL_ROW row; //存储单行数据
    //表头
    printf("\n\t\t--------------------------------------------------------------------------------\n");
    printf("\t\t%-17s %-17s  %-19s%-18s %-20s\n","编号", "书名", "作者", "出版社", "库存量");
    printf("\t\t--------------------------------------------------------------------------------\n");
    //遍历每一行数据
    while ((row = mysql_fetch_row(res)))
    {
        printf("\t\t%-16s %-16s %-16s %-16s %-16s\n",row[0], row[1], row[2], row[3], row[4]);
    }

    printf("\t\t--------------------------------------------------------------------------------\n");

    mysql_free_result(res);  //释放结果集
    Pause();
}
 
// 添加图书
void AddBook()
{
    char choice = 'y';

    while(choice == 'y' || choice == 'Y')
    {
        int id, amount;
        char name[30], author[30], press[30];
        char sql[500]; //存储拼接后的SQL语句

        printf("\n\t图书编号:"); scanf("%d", &id);
        printf("\t书名:"); scanf("%s", name);
        printf("\t作者:"); scanf("%s", author);
        printf("\t出版社:"); scanf("%s", press);
        printf("\t库存量:"); scanf("%d", &amount);
        getchar();
        //拼接 添加语句
        sprintf(sql,"insert into book values(%d,'%s','%s','%s',%d)",id,name,author,press,amount);
        //sprintf：将变量拼接到 SQL 模板中，生成完整的 INSERT 语句；
        if(mysql_query(conn,sql))  //返回0失败
            printf("\t添加失败:%s\n",mysql_error(conn));
        else
            printf("\t添加成功!\n");

        printf("\n\t是否继续添加？(Y/N): "); //是否继续添加
        scanf("%c",&choice);
        getchar();
    }
}


// 删除图书
void DeleteBook()
{
    int id;
    char sql[300];

    printf("\t请输入要删除的图书编号:");
    scanf("%d", &id);
    getchar();
    //从book表中删除数据 按编号删除
    sprintf(sql, "delete from book where iNum=%d", id);

    if (mysql_query(conn, sql))  //执行语句
        printf("\t删除失败:%s\n", mysql_error(conn));
    else
        printf("\t删除成功!\n");

    Pause();
}

// 精准查询
void SearchBookByID()
{
    int id;
    char sql[300];

    printf("\t请输入图书编号:");
    scanf("%d", &id);
    getchar();
 //编号
    sprintf(sql, "select * from book where iNum=%d", id);

    mysql_query(conn, sql);  //执行查找语句
    MYSQL_RES *res = mysql_store_result(conn);
    MYSQL_ROW row;

    printf("\n\t\t--------------------------------------------------------------------------------\n");
    printf("\t\t%-17s %-17s  %-19s%-18s %-20s\n", "编号", "书名", "作者", "出版社", "库存量");
    printf("\t\t--------------------------------------------------------------------------------\n");

    while ((row = mysql_fetch_row(res)))
    {
        printf("\t\t%-16s %-16s %-16s %-16s %-16s\n",row[0], row[1], row[2], row[3], row[4]);
    }

    printf("\t\t--------------------------------------------------------------------------------\n");

    mysql_free_result(res);
    Pause();
}

// 模糊查询
void SearchBookByName()
{
    char key[30];
    char sql[300];

    printf("\t请输入书名关键词:");
    scanf("%s", key);
    getchar();
    //%格式化符号，表示%key%，存在关键字
    sprintf(sql,"select * from book where acName like '%%%s%%'",key);

    mysql_query(conn, sql); //执行SQL语句
    MYSQL_RES *res = mysql_store_result(conn); //获取结果集
    MYSQL_ROW row; //保存一行数据

    printf("\n\t\t--------------------------------------------------------------------------------\n");
    printf("\t\t%-17s %-17s  %-19s%-18s %-20s\n","编号", "书名", "作者", "出版社", "库存量");
    printf("\t\t--------------------------------------------------------------------------------\n");

    while ((row = mysql_fetch_row(res)))
    {
        printf("\t\t%-16s %-16s %-16s %-16s %-16s\n",row[0], row[1], row[2], row[3], row[4]);
    }

    printf("\t\t--------------------------------------------------------------------------------\n");

    mysql_free_result(res);
    Pause();
}

// 修改图书
void ModifyBook()
{
    int id, choice, newInt; //存储字符串
    char newStr[30];
    char sql[500];

    printf("\t请输入要修改的图书编号:");
    scanf("%d", &id);
    getchar();

    ShowModifyBookMenu();
    scanf("%d", &choice);
    getchar();

    //根据选项修改 拼接
    switch (choice)
    {
    case 1:  //修改编号
        printf("\t输入新编号:");
        scanf("%d", &newInt);
        getchar();
        sprintf(sql, "update book set iNum=%d where iNum=%d", newInt, id);
        break;
    case 2:  //修改书名
        printf("\t输入新书名:");
        scanf("%s", newStr);
        getchar();
        sprintf(sql, "update book set acName='%s' where iNum=%d", newStr, id);
        break;
    case 3:  //修改作者
        printf("\t输入新作者:");
        scanf("%s", newStr);
        getchar();
        sprintf(sql, "update book set acAuthor='%s' where iNum=%d", newStr, id);
        break;
    case 4:  //修改出版社
        printf("\t输入新出版社:");
        scanf("%s", newStr);
        getchar();
        sprintf(sql, "update book set acPress='%s' where iNum=%d", newStr, id);
        break;
    case 5:  //修改库存量
        printf("\t输入新库存量:");
        scanf("%d", &newInt);
        getchar();
        sprintf(sql, "update book set iAmount=%d where iNum=%d", newInt, id);
        break;
    default:
        printf("输入错误!\n");
        Pause();
        return;
    }

    if (mysql_query(conn, sql))
        printf("\t修改失败:%s\n", mysql_error(conn));
    else
        printf("\t修改成功!\n");

    Pause();
}

//图书管理总控制函数
void ManageBook()
{
    int choice;

    ShowBookMenu(); //图书菜单
    scanf("%d", &choice);
    getchar();
    //0退出
    while (choice)
    {
        switch (choice)
        {
        case 1:
            ShowAllBook();  //显示所有图书
            break;
        case 2:
            AddBook();      //添加图书
            break;
        case 3:
        {
            ShowBookSearchMenu();  //查找方式菜单
            int c2;
            scanf("%d", &c2);
            getchar();
            if (c2 == 1)
                SearchBookByID();  //按编号查找
            else if (c2 == 2)
                SearchBookByName(); //按关键字查找
            break;
        }
        case 4:
            DeleteBook();  //删除图书
            break;
        case 5:
            ModifyBook();  //修改图书
            break;
        default:
            printf("输入错误!\n");
            Pause();
        }

        ShowBookMenu();
        scanf("%d", &choice);
        getchar();
    }
}

//--------------------------------读者管理模块

// 显示所有读者
void ShowAllReader()
{
    mysql_query(conn, "select * from reader");  //执行查找语句
    MYSQL_RES *res = mysql_store_result(conn);  //获取结果集
    MYSQL_ROW row;

    printf("\n\t\t--------------------------------------------------------------------------------\n");
    printf("\t\t%-16s  %-19s %-19s%-14s %-20s\n","编号", "姓名", "性别", "最大借阅", "已借数量");
    printf("\t\t--------------------------------------------------------------------------------\n");

    while ((row = mysql_fetch_row(res)))
    {
        printf("\t\t%-16s %-16s %-16s %-16s %-16s\n",row[0], row[1], row[2], row[3], row[4]);
    }

    printf("\t\t--------------------------------------------------------------------------------\n");

    mysql_free_result(res);
    Pause();
}

// 添加读者
void AddReader()
{
    char choice = 'y';

    while(choice == 'y' || choice == 'Y')
    {
        int id, maxBorrow;
        char name[30], sex[10];
        char sql[500];

        printf("\n\t读者编号:"); scanf("%d", &id);
        printf("\t姓名:"); scanf("%s", name);

        // 性别限制
        while(1)
        {
            printf("\t性别(男/女):");
            scanf("%s", sex);

            if(strcmp(sex,"男")==0 || strcmp(sex,"女")==0) //strcmp字符串比较，限制性别
                break;
            else
                printf("\t输入错误，只能输入 男 或 女!\n");
        }

        printf("\t最大借阅数量:"); scanf("%d",&maxBorrow);
        getchar();

        sprintf(sql,"insert into reader values(%d,'%s','%s',%d,0)",id,name,sex,maxBorrow);

        if(mysql_query(conn,sql))
            printf("\t添加失败:%s\n",mysql_error(conn));
        else
            printf("\t添加成功!\n");

        printf("\n\t是否继续添加？(Y/N): ");  //循环添加
        scanf("%c",&choice);
        getchar();
    }
}


// 删除读者
void DeleteReader()
{
    int id;
    char sql[300];

    printf("\t请输入要删除的读者编号:");
    scanf("%d", &id);
    getchar();

    sprintf(sql, "delete from reader where iNum=%d", id);

    if (mysql_query(conn, sql))
        printf("\t删除失败:%s\n", mysql_error(conn));
    else
        printf("\t删除成功!\n");

    Pause();
}

// 查询读者
void SearchReaderByID()
{
    int id;
    char sql[300];

    printf("\t请输入读者编号:");
    scanf("%d", &id);
    getchar();

    sprintf(sql, "select * from reader where iNum=%d", id);

    mysql_query(conn, sql);  //执行查询语句
    MYSQL_RES *res = mysql_store_result(conn); //获取结果集
    MYSQL_ROW row;

    printf("\n\t\t--------------------------------------------------------------------------------\n");
    printf("\t\t%-16s %-16s %-16s %-16s %-16s\n","编号", "姓名", "性别", "最大借阅", "已借数量");
    printf("\t\t--------------------------------------------------------------------------------\n");

    while ((row = mysql_fetch_row(res))) 
    {
        printf("\t\t%-16s %-16s %-16s %-16s %-16s\n",row[0], row[1], row[2], row[3], row[4]);
    }

    printf("\t\t--------------------------------------------------------------------------------\n");

    mysql_free_result(res);
    Pause();
}

// 修改读者信息
void ModifyReader()
{
    int id, choice, newInt;
    char newStr[30];
    char sql[500];

    printf("\t请输入要修改的读者编号:");
    scanf("%d", &id);
    getchar();

    printf("\n\t\t***************请选择修改内容****************\n");
    printf("\t\t1.编号\n");
    printf("\t\t2.姓名\n");
    printf("\t\t3.性别\n");
    printf("\t\t4.最大借阅数量\n");
    printf("\t\t请输入(1-4):");

    scanf("%d", &choice);
    getchar();
    //选择修改方式
    switch (choice)
    {
    case 1:
        printf("\t输入新编号:");
        scanf("%d", &newInt);
        getchar();
        sprintf(sql, "update reader set iNum=%d where iNum=%d", newInt, id);
        break;
    case 2:
        printf("\t输入新姓名:");
        scanf("%s", newStr);
        getchar();
        sprintf(sql, "update reader set acName='%s' where iNum=%d", newStr, id);
        break;
    case 3:
        char newSex[10];
        while(1)
        {
        printf("\t输入新性别(男/女):");  //限制男女
        scanf("%s", newSex);

        if(strcmp(newSex,"男")==0 || strcmp(newSex,"女")==0)
            break;
        else
            printf("\t输入错误，只能输入 男 或 女!\n");
        }
        getchar();

        sprintf(sql,"update reader set acSex='%s' where iNum=%d",
        newSex,id);

        break;

    case 4:
        printf("\t输入新最大借阅数量:");
        scanf("%d", &newInt);
        getchar();
        sprintf(sql, "update reader set iMax=%d where iNum=%d", newInt, id);
        break;
    default:
        printf("输入错误!\n");
        Pause();
        return;
    }

    if (mysql_query(conn, sql))
        printf("\t修改失败:%s\n", mysql_error(conn));
    else
        printf("\t修改成功!\n");

    Pause();
}

// 读者管理总控制
void ManageReader()
{
    int choice;

    ShowReaderMenu();  //读者菜单
    scanf("%d", &choice);
    getchar();

    while (choice)
    {
        switch (choice)
        {
        case 1:
            ShowAllReader();  //显示所有读者信息
            break;
        case 2:
            AddReader();  //添加读者
            break;
        case 3:
            SearchReaderByID();  //查询读者信息
            break;
        case 4:  
            DeleteReader();   //删除读者信息
            break;
        case 5:
            ModifyReader();  //修改读者信息
            break;
        default:
            printf("输入错误!\n");
            Pause();
        }

        ShowReaderMenu();
        scanf("%d", &choice);
        getchar();
    }
}

//---------------------------借书还书模块

// 借书功能
void BorrowBook()
{
    int reader_id, book_id;
    char sql[500];

    printf("\t请输入读者编号:");
    scanf("%d", &reader_id);
    printf("\t请输入图书编号:");
    scanf("%d", &book_id);
    getchar();

    // 1️ 检查图书库存
    sprintf(sql, "select iAmount from book where iNum=%d", book_id);
    mysql_query(conn, sql);
    MYSQL_RES *res = mysql_store_result(conn);  //获取结果集
    //从连接conn中，把刚刚执行的 SQL 查询返回的所有结果一次性读取到客户端内存，并返回一个指向这个结果集的指针res
    MYSQL_ROW row = mysql_fetch_row(res);//代表结果集中的一行数据
    //从结果集res中，取出下一行数据，并返回指向这一行的指针row。

    if (row == NULL)
    {
        printf("\t图书不存在!\n");
        mysql_free_result(res);
        Pause();
        return;
    }

    int stock = atoi(row[0]);  //库存转成整数
    //atoi：将 MySQL 返回的字符串（row [x]）转为整数，方便数值判断
    mysql_free_result(res);

    if (stock <= 0)  //库存不足
    {
        printf("\t库存不足!\n");
        Pause();
        return;
    }

    // 2️ 检查读者借阅情况
    sprintf(sql, "select iMax, iAmount from reader where iNum=%d", reader_id);
    mysql_query(conn, sql);
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);

    if (row == NULL)
    {
        printf("\t读者不存在!\n");
        mysql_free_result(res);
        Pause();
        return;
    }

    int maxBorrow = atoi(row[0]); //最大借阅数
    int currentBorrow = atoi(row[1]);  //已借数量
    mysql_free_result(res);

    if (currentBorrow >= maxBorrow)  //上限
    {
        printf("\t已达到最大借阅数量!\n");
        Pause();
        return;
    }

    // 3️ 插入借阅记录
    //now()：MySQL 内置函数，自动插入当前时间作为借阅时间；
    sprintf(sql,"insert into borrow values(%d,%d,now())", reader_id, book_id);

    if (mysql_query(conn, sql))
    {
        printf("\t借阅失败:%s\n", mysql_error(conn));
        Pause();
        return;
    }

    // 4️ 更新库存
    sprintf(sql, "update book set iAmount=iAmount-1 where iNum=%d", book_id);
    mysql_query(conn, sql);

    // 5️ 更新读者借阅数量
    sprintf(sql, "update reader set iAmount=iAmount+1 where iNum=%d",reader_id);
    mysql_query(conn, sql);

    printf("\t借书成功!\n");
    Pause();
}

// 还书功能
void ReturnBook()
{
    int reader_id, book_id;
    char sql[500];

    printf("\t请输入读者编号:");
    scanf("%d", &reader_id);
    printf("\t请输入图书编号:");
    scanf("%d", &book_id);
    getchar();

    // 1️ 检查是否存在借阅记录
    sprintf(sql, "select * from borrow where reader_id=%d and book_id=%d",reader_id, book_id);

    mysql_query(conn, sql);
    MYSQL_RES *res = mysql_store_result(conn);
    //mysql_num_rows：获取结果集的行数，判断是否存在借阅记录。
    if (mysql_num_rows(res) == 0)
    {
        printf("\t没有找到借阅记录!\n");
        mysql_free_result(res);
        Pause();
        return;
    }

    mysql_free_result(res);

    // 2️ 删除借阅记录
    sprintf(sql,"delete from borrow where reader_id=%d and book_id=%d", reader_id, book_id);
    mysql_query(conn, sql);

    // 3️ 恢复库存
    sprintf(sql, "update book set iAmount=iAmount+1 where iNum=%d",book_id);
    mysql_query(conn, sql);

    // 4️ 减少读者借阅数量
    sprintf(sql,"update reader set iAmount=iAmount-1 where iNum=%d",reader_id);
    mysql_query(conn, sql);

    printf("\t还书成功!\n");
    Pause();
}

// 借书还书管理总函数
void BorrowReturnManager()
{
    int choice;

    ShowBorrowReturnMenu();  //借书还书菜单
    scanf("%d", &choice);
    getchar();

    while (choice)
    {
        switch (choice)
        {
        case 1:
            BorrowBook();  //借书
            break;
        case 2:
            ReturnBook();  //还书
            break;
        default:
            printf("输入错误!\n");
            Pause();
        }

        ShowBorrowReturnMenu();
        scanf("%d", &choice);
        getchar();
    }
}

//----------------读者借阅详情查询模块
void SearchReaderBorrowInfo()
{
    int reader_id;
    char sql[500];

    printf("\t请输入读者编号:");
    scanf("%d", &reader_id);
    getchar();

    // 1️ 先检查读者是否存在
    sprintf(sql, "select * from reader where iNum=%d", reader_id);
    mysql_query(conn, sql);
    MYSQL_RES *res = mysql_store_result(conn);

    if (mysql_num_rows(res) == 0)
    {
        printf("\t读者不存在!\n");
        mysql_free_result(res);
        Pause();
        return;
    }
    mysql_free_result(res);

    // 2 联表查询 borrow + book
    sprintf(sql,"select book.iNum, book.acName, book.acAuthor, borrow.borrow_time ""from borrow ""join book on borrow.book_id = book.iNum " "where borrow.reader_id = %d",reader_id);

    mysql_query(conn, sql);
    res = mysql_store_result(conn);
    MYSQL_ROW row;

    printf("\n\t\t--------------------------------------------------------------------------------\n");
    printf("\t\t%-17s
         %-17s  %-19s%-18s\n", "图书编号", "书名", "作者", "借阅时间");
    printf("\t\t--------------------------------------------------------------------------------\n");

    while ((row = mysql_fetch_row(res)))
    {
        printf("\t\t%-16s %-16s %-16s %-16s\n",row[0], row[1], row[2], row[3]);
    }

    printf("\t\t--------------------------------------------------------------------------------\n");

    mysql_free_result(res);
    Pause();
}


//主函数
int main()
{
    InitDB();  //初始化

    int choice;

    ShowMainMenu();
    scanf("%d", &choice);
    getchar();

    while (choice)
    {
        switch (choice)
        {
        case 1:
            ManageBook();   //图书管理
            break;
        case 2:
            ManageReader(); //读者管理
            break;
        case 3:
            BorrowReturnManager(); //借书还书 
            break;
        case 4:
            SearchReaderBorrowInfo(); //读者借阅详情
            Pause();
            break;
        case 5:
            ShowHelpMenu();  //帮助手册
            Pause();
            break;
        default:
            printf("\n\t\t输入错误！3秒后返回主菜单...\n");
            sleep(3);
        }

        ShowMainMenu();
        scanf("%d", &choice);
        getchar();
    }

    mysql_close(conn);  //关闭连接
    return 0;
}