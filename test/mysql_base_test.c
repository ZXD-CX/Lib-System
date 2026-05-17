//基础 SQL 测试

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<mysql/mysql.h>

int main()
{
    //初始化
    MYSQL mysql_conn;  
    MYSQL *mysql = mysql_init(&mysql_conn);
    if(mysql == NULL){
        printf("mysql init err!\n");
        exit(1);
    }
    //连接数据库
    mysql = mysql_real_connect(mysql,"localhost","root","quzijie_123","quzijie_test",3306,NULL,0);
    if(mysql == NULL){
        printf("connect error!\n");
        exit(1);
    }
    printf("connect success!\n");
    //SQL语句
    //const char* sql = "select *from student_table";
    const char* sql = "insert into student_table values(1004,'马嘉祺',66)";
    //执行SQL语句
    if(mysql_query(mysql,sql) != 0){
        printf("query sql error:%s\n",mysql_error(mysql)); //获取错误信息
    }
    //提取结果
    MYSQL_RES *res = mysql_store_result(mysql);
    if(res == NULL){
        printf("res error:%s\n",mysql_error(mysql));  //获取错误信息
        exit(1);
    }
    //获取行数
    int num = mysql_num_rows(res);
    printf("num = %d\n",num);
    //获取列数
    int count = mysql_field_count(mysql);
    printf("count = %d\n",count);
    //打印
    for(int i = 0;i < num;++i){
        MYSQL_ROW row = mysql_fetch_row(res); //取出结果集中一行记录
        for(int j = 0;j < count;++j){
            printf("%s   ",row[j]);
        }
        printf("\n");
    }
    //释放结果集占用内存
    mysql_free_result(res);
    //关闭连接
    mysql_close(mysql);
    return 0;
}