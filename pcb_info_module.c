#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/fs_struct.h>
#include <linux/fs.h>
#include <linux/moduleparam.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("C");

//stores the command line argument (specifiedPID). The value will change if I input a value, if not it will throw an error
//this value is also static, to prevent global variables
static int specifiedPID = -1;
//these allow me to accept the command line argument and set its type, name, and permissions
module_param(specifiedPID, int, 0600); 
MODULE_PARM_DESC(specifiedPID, "The specified PID");
  
//this module is called when the module is inserted into the kernel
static int __init ProcessModuleInit(void) {

  //declaring pointers to the needed structs
  struct task_struct *task;
  struct mm_struct *mm;
  struct fs_struct *fs;
  struct super_block *sb;
  struct path root;
  struct vfsmount *mnt;
  
  //initializing variables to store the code region size and the total pages in KB. I used long to have an extra range of values if needed
  unsigned long codeSize, totalKB;
  
  //this macro allows me to iterate through the PCB linked list. It belongs to sched.h header file
  for_each_process(task) {
    //this statement determines whether or not we've reached the desired PCB node in the PCB list
    if(task->pid == specifiedPID) {
      //we retreive the needed values from the correct PCB node struct
      mm = task->mm;
      codeSize = (mm->end_code) - (mm->start_code);
      totalKB = (mm->total_vm) * 4;
      fs = task->fs;
      root = fs->root;
      mnt = root.mnt;
      sb = root.dentry->d_sb;
      
      
      //we will print the PCB node's values 
      printk("PID: %d \n", task->pid);
      printk("Name: %s\n", task->comm);
      printk("Code region size: %lu \n", codeSize);
      printk("Total pages in KB: %lu \n", totalKB);
      printk("File System Name: %s \n", sb->s_type->name);
      break;
    }
  }
    
    
    
  
  return 0;
  
}
//this will print the following statment when we unload the kernel module. This was done to make the kernel ring buffer output more segemented so I could see what was going on better
static void __exit ProcessModuleExit(void) {
  printk("Unloading PCB info module \n");
}
//calling the modules
module_init(ProcessModuleInit);
module_exit(ProcessModuleExit);
