##数据库设计
* 用户表 users 
 
tip:  
status：normal-0 lock-1     

|numberID|password|name|major|photo|money|email|status|
|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|
|13|33|50|5|200|10|30|2|

* 借阅信息列表 borrowInfo 

tip:  
status：正常-0续借-1已还-2逾期-3
 
|id|numberID|ISBN-xxx|b_date|r_date|status|
|:--:|:--:|:--:|:--:|:--:|:--:|
|20|13|35|20|20|2|

* 收藏书目 collectBook

|id|numberID|ISBN|
|:--:|:--:|:--:|
|20|13|35|

* 书目表 book

|ISBN|image|bookName|author|press|introduction|category|amount|left|
|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|
|35|200|50|50|50|500|5|10|10|

* 图书分类表 bookCategory

|id|category|
|:--:|:--:|
|10|40|

* 学生专业表 studentMajor

|id|major|
|:--:|:--:|
|10|50|

* 预约记录表 order

tip:预约中，可预约，已完成

|id|ISBN|numberID|order_date|deadline|status|
|:--:|:--:|:--:|:--:|:--:|:--:|
|10|20|13|20|20|2|

* 管理员 administrator

|numberID|password|email|
|:--:|:--:|:--:|
|13|33|30|

* 操作记录表 operation

|id|numberID|operation|date|
|:--:|:--:|:--:|:--:|
|20|13|200|20|