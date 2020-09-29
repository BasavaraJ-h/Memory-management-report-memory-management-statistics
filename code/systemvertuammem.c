#include <linux/kernel.h>
#include <linux/sched.h>
#include <asm/page.h>
#include <asm/pgtable.h>
#include <linux/mm_types.h>

asmlinkage int sys_vma_props(unsigned long mem, int pid)
{
	struct task_struct *task;
        struct task_struct *ptask = current; // getting global current pointer

     	task =pid_task(find_vpid(pid), PIDTYPE_PID);
	
/*       
		//printk(KERN_NOTICE "ptr:%p", task);
   // printk(KERN_NOTICE "current process: %s, PID: %d", task->comm, task->pid);
    do
    {
            if(ptask->pid == pid)
            {
                   task =ptask;
                   break;
            }
            else{
        ptask = ptask->parent;
//        printk(KERN_NOTICE " parent process: %s, PID: %d", task->comm, task->pid);
            }
    } while (ptask->pid != 0);




*/
        //struct task_struct *task = find_task_by_vpid(pid);
        struct mm_struct *memory = task->active_mm;
        int data = 0;
        int ref = 0;
        int dirty = 0;
        pgd_t *pgd = pgd_offset(memory, mem); //page global directory
	p4d_t *p4d = p4d_offset(pgd, mem);
        pud_t *pud = pud_offset(p4d, mem); // page upper directory
        pmd_t *pmd = pmd_offset(pud, mem); // page middle directory
        pte_t *ptep = pte_offset_kernel(pmd, mem); // page table entry pointer
        pte_t pte = *ptep; // page table entry
        data = pte_present(pte);
        printk("Present flag: %i\n", data?1:0);
        ref = pte_young(pte);
        printk("Referenced flag: %i\n", ref?1:0);
        dirty = pte_dirty(pte);
        printk("Dirty flag: %i\n", dirty?1:0);
        return 0;
}
