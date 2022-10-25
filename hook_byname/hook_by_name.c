// SPDX-License-Identifier: GPL-2.0-only
#include <linux/module.h>

#include <linux/sched.h> /* for wake_up_process() */
#include <linux/ftrace.h>

static void callback_func(unsigned long ip, unsigned long parent_ip, struct ftrace_ops *op, struct ftrace_regs *regs){
    int bit;
    bit = ftrace_test_recursion_trylock(ip, parent_ip);
    if (bit < 0)
        return;

    trace_printk("callback_func! ,ip:%lx, pip:%lx, *op:%lx, *regs:%lx, dx:%lx, ax:%lx, bx:%lx, cx:%lx, si:%lx, di:%lx, r8:%lx,r9:%lx,r12:%lx,r13:%lx,r14:%lx\n",ip,parent_ip,op,regs,regs->regs.dx,regs->regs.ax,regs->regs.bx,regs->regs.cx,regs->regs.si,regs->regs.di,regs->regs.r8,regs->regs.r9,regs->regs.r12,regs->regs.r13,regs->regs.r14);
    regs->regs.dx = 0x0000000000000001ull;
    trace_printk("regs changed! ,ip:%lx, pip:%lx, *op:%lx, *regs:%lx, dx:%lx, ax:%lx, bx:%lx, cx:%lx, si:%lx, di:%lx, r8:%lx,r9:%lx,r12:%lx,r13:%lx,r14:%lx\n",ip,parent_ip,op,regs,regs->regs.dx,regs->regs.ax,regs->regs.bx,regs->regs.cx,regs->regs.si,regs->regs.di,regs->regs.r8,regs->regs.r9,regs->regs.r12,regs->regs.r13,regs->regs.r14);

    ftrace_test_recursion_unlock(bit);
}

static struct ftrace_ops ops = {
      .func                    = callback_func,
      .flags                   = FTRACE_OPS_FL_SAVE_REGS
    //   .private                 = any_private_data_structure,
};

static int __init ftrace_direct_init(void)
{
    ftrace_set_filter(&ops, "device_read", strlen("device_read"), 0);
    return register_ftrace_function(&ops);

}

static void __exit ftrace_direct_exit(void)
{
    unregister_ftrace_function(&ops);
}

module_init(ftrace_direct_init);
module_exit(ftrace_direct_exit);

MODULE_AUTHOR("Steven Rostedt");
MODULE_DESCRIPTION("Example use case of using register_ftrace_direct()");
MODULE_LICENSE("GPL");