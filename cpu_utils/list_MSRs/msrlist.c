#include <linux/init.h>
#include <linux/module.h>
#include <asm/asm.h>
#include <asm/msr.h>

#define DRIVER_AUTHOR "Shankar Viswanathan"
#define DRIVER_DESC   "Print several MSR values"

static void print_msrs(void);

static int __init hello_init(void)
{
    printk(KERN_INFO "Hello, world\n");
    print_msrs();
    return 0;
}

static void __exit hello_exit(void)
{
    print_msrs();
    printk(KERN_INFO "Goodbye, cruel world\n");
}

static void print_msrs(void)
{
    unsigned int long long msr_val = 0;
    int msr_num[8] = { MSR_K7_HWCR, MSR_K8_SYSCFG, MSR_K8_TOP_MEM1, \
                       MSR_K8_TOP_MEM2, MSR_AMD64_NB_CFG, MSR_IA32_CR_PAT, \
                       MSR_IA32_LASTBRANCHFROMIP, MSR_IA32_LASTBRANCHTOIP };
    int i;    

    for (i = 0; i < 8; i++) 
    {
        rdmsrl(msr_num[i], msr_val);
        printk(KERN_INFO "MSR 0x%x: 0x%llx\n", msr_num[i], msr_val);
    }
    
    msr_val = rdtsc();
    printk(KERN_INFO "RDTSCP: 0x%0llx\n", msr_val);
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
