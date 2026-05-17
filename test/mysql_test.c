#include<stdio.h>
#include<mysql/mysql.h>
   
int main()
{
       MYSQL  connect;//mysql的链接对象
       mysql_init(&connect);
   
       //链接Mysql
      if(mysql_real_connect(&connect,"localhost","root","quzijie_123",
                            "quzijie",0,NULL,0))
      {
          printf("连接mysql成功！\n");
      }
      else
      {
          printf("error:%s\n",mysql_error(&connect));
          printf("连接mysql失败\n");
      }
       
  //....

       //关闭Mysql连接
      mysql_close(&connect);
      return 0;
}
