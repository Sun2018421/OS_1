#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>

struct birthday{
	int day;
	int month;
	int year;
	struct list_head list;
};
static LIST_HEAD(birthday_list);
int sxf_init(void){
	//struct list_head birthday_list;
	struct birthday *person[5];
	struct birthday *ptr;
	int i = 0 ;
	int day =1 , month = 7 , year = 1997;

	printk(KERN_INFO "The Module is Loading...\n");

	for(i = 0 ; i < 5 ; i++){
        person[i]  =(struct birthday*)kmalloc(sizeof(struct birthday),GFP_KERNEL);
        person[i]->day = day++;
        person[i]->month = month++;
        person[i]->year = year++;
        INIT_LIST_HEAD(&person[i]->list);
	
	list_add_tail(&person[i]->list,&birthday_list);
	printk(KERN_INFO "The Node %d is inserted\n",i+1);
	}
        i = 1 ;
	list_for_each_entry(ptr,&birthday_list,list){
		printk(KERN_INFO "The Node %d is :\n",i++);
		printk(KERN_INFO "year : %d , month : %d , day : %d\n",(*ptr).year,(*ptr).month,(*ptr).day);				
	}
	printk(KERN_INFO "The Module is Loaded!\n");	
	return 0;
}

void sxf_exit(void){
	struct birthday *ptr , *next;
	int i = 1;
	list_for_each_entry_safe(ptr,next,&birthday_list,list){
                printk(KERN_INFO "year : %d , month : %d , day : %d\n",(*ptr).year,(*ptr).month,(*ptr).day);
		printk(KERN_INFO "The Node %d is removed\n",i++);
		list_del(&ptr->list);	
		kfree(ptr);
	}
	printk(KERN_INFO "The Module is removed!\n");
}

/* Macros for registering module entry and exit points. */
module_init( sxf_init );
module_exit( sxf_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module modified by sxf");
MODULE_AUTHOR("SXF");

