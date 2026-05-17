//图书单表完整版 CRUD

#include<stdio.h>
#include<mysql/mysql.h>
#include<string.h>

int main()
{
    MYSQL mydata;
    //初始化
    MYSQL *mysql = mysql_init(&mydata);
    if(mysql == NULL){
        printf("mysql_init failed!\n");
        exit(1);
    }
    else{
        printf("mysql_init succeed!\n");
    }
    //连接数据库
    mysql = mysql_real_connect(mysql,"localhost","root","quzijie_123","db_book",3306,NULL,0);
    if(mysql == NULL){
        printf("db_book数据库连接失败!\n");
        exit(2);
    }
    else{
        printf("db_book数据库连接成功!\n");
    }
    //1.插入数据
    char dest[500] = { "  " };
	int iNum;//图书编号
	char acName[15];//图书名称
    char acAuthor[15];//图书作者
    char acPress[15];//图书出版社;
    int  iAmount;//图书库存量
	char ch;//选择的变量
 

while (1)
	{
		printf("现在开始往数据库db_book里面插入数据\n");
	
		printf("\t 图书编号:");
		scanf("%d", &iNum);   //输入图书编号
		printf("\t 图书名称:");
		scanf("%s", acName);   //输入图书名称
        printf("\t 图书作者:");
		scanf("%s", acAuthor);   //输入图书作者
        printf("\t 图书出版社:");
		scanf("%s", acPress);   //输入图书出版社
        printf("\t 图书库存量:");
		scanf("%d", &iAmount);   //输入图书库存量
		getchar();
sprintf(dest, "insert into book (iNum,acName,acAuthor,acPress,iAmount) values (%d,'%s','%s','%s',%d);", iNum,acName,acAuthor,acPress, iAmount);//不要分号也可以成功,但是最好加上
		printf("dest==%s\n", dest);

    if( mysql_query(mysql,dest) != 0 )
    {
        printf("query sql err:%s\n",mysql_error(mysql));
        exit(3);
    }
		else
		{
			printf("\t 插入成功!\n");
			memset(dest, 0, 500);
			printf("是否继续插入数据?Y|N\n");
			char select;
			scanf("%c", &select);
			if (select == 'n' || select == 'N')
			{
				break;
			}
		}
	}
    //3.查询数据
    MYSQL_RES* result;    //定义结果集变量
    MYSQL_ROW row;        //定义行变量
      char * sql = "select *from book";

    if( mysql_query(mysql,sql) != 0 )
    {
        printf("query sql err:%s\n",mysql_error(mysql));
    }

    result = mysql_store_result(mysql);
    if( result == NULL )
    {
        printf("res err:%s\n",mysql_error(mysql));
        exit(1);
    }
   
    int num = mysql_num_rows(result);

    int count = mysql_field_count(mysql);
     printf("book书有%d行,%d列\n",num,count);
 

//行列的信息输出还可以见下面删除的输出方法(列直接输出,因为没有几列)
    for(int i = 0; i < num; i++ )
    {
        row = mysql_fetch_row(result);
        for(int j = 0; j < count; j++ )
        {
            printf("%s   ",row[j]);
        }
        printf("\n");
    }

    //4.删除数据
    printf("现在开始删除数据\n");
    //先查询是否存在
    printf("请输入图书编号\n");
    scanf("%d", &iNum);
    getchar();
    //删除之前看看是否有这条图书信息;
    //dest1保存查询图书信息sql语句
    char dest1[500] = { "  " };

    sprintf(dest1, "select *from book where iNum=%d", iNum);
    printf("dest1==%s\n", dest1);

    /*查询该图书信息是否存在*/
    if (mysql_query(mysql, dest1)!=0)//0表示成功,==0表示成功,!=0表示失败
    {   //如果查询失败
        printf("\n %d号图书不存在,查询失败! \n",iNum);
    }
    else
    {
          result = mysql_store_result(mysql);
        if (mysql_num_rows(result) != 0)
        {  //有记录的情况,只有有记录取数据才有意义
            printf("\t 发现记录信息,是否显示?(y/n) ");
            scanf("%c", &ch);
            getchar();
            if (ch=='Y' || ch=='y')/*判断是否要显示查找到的信息*/
            {
                printf("\t               ***** 显示图书信息 *****         \n");
                printf("\t图书编号   图书名     图书作者    图书出版社    图书库存量\n");
                printf("\t ------------------------------------------------- \n");
                while ((row = mysql_fetch_row(result)))
                {   //取出结果集中记录
                fprintf(stdout, "\t %-7s%-7s %-7s %-7s%-7s \n", 
                        row[0], row[1],row[2],row[3],row[4]);  //输出这行记录
                }

                //下面开始删除数据
                printf("\t 是否删除?(y/n) ");
                char dest2[500] = { "  " };
                scanf("%c", &ch);
                getchar();
                if (ch == 'Y' || ch == 'y') /*判断是否需要删除*/
                {

                   sprintf(dest2, "delete from book where iNum=%d", iNum);
                    printf("dest2==%s\n", dest2);
                    if (mysql_query(mysql, dest2) != 0)
                    {
                        //fprintf(stderr, "\t 不能删除记录! \n", mysql_error(&mydata));
                        printf("\t 删除记录失败! \n");
                    }
                    else
                    {
                        printf("\t %d号图书信息删除成功!\n",iNum);
                    }
                }
            }
        }
        else
        {
            printf("没有查到相关记录!\n");
        }
    }
    //4.修改记录
    printf("现在开始修改记录:\n");
	//修改之前还是需要查询是否存在:
	printf("请输入图书编号\n");
	scanf("%d", &iNum);
	getchar();
	//删除之前看看是否有这条图书信息;
	//dest3保存查询图书信息sql语句
	char dest3[500] = { "  " };

	sprintf(dest3, "select *from book where  iNum=%d", iNum);
	printf("dest3==%s\n", dest3);

	/*查询该图书信息是否存在*/
	if (mysql_query(mysql, dest3)!=0)
	{   //如果查询失败
		printf("\n %d号图书不存在,查询失败! \n",iNum);
	}
	else
	{
		result = mysql_store_result(mysql); //获得结果集
		if (mysql_num_rows(result) != 0)
		{  //有记录的情况,只有有记录取数据才有意义
			printf("\t 发现记录信息,是否显示?(y/n) ");
			scanf("%c", &ch);
			getchar();
			if (ch == 'Y' || ch == 'y')/*判断是否要显示查找到的信息*/
			{
                
				printf("\t               ***** 显示图书信息 *****               \n");
				printf("\t图书编号   图书名     图书作者    图书出版社    图书库存量\n");
                printf("\t ---------------------------------------------------- \n");
                while ((row = mysql_fetch_row(result)))
                {   //取出结果集中记录
                fprintf(stdout, "\t   %-7s%-15s %-15s %-15s%-15s \n", 
                        row[0], row[1],row[2],row[3],row[4]);  //输出这行记录
                }
			}
		}
		else
		{
			printf("没有找到该记录信息!\n");
            exit(2);

		}
	}


	printf("\t 是否修改?(y/n) ");
	
	scanf("%c", &ch);
	getchar();
	if (ch == 'Y' || ch == 'y') /*判断是否需要修改*/
	{
		printf("请输入修改后的名字:\n");
		char acName[15];
		scanf("%s", acName);

		getchar();
		char dest4[500] = { "  " };
	
		sprintf(dest4, "update book set acName= '%s' where iNum=%d ", acName, iNum);
		printf("dest4==%s", dest4);
		



		if (mysql_query(mysql, dest4) != 0)
		{
			printf("\t 修改记录失败! \n");
		}
		else
		{
			printf("\t 修改成功!\n");
		}
	}
    
    mysql_free_result(result);
    //关闭连接
    mysql_close(mysql);
    return 0;
}