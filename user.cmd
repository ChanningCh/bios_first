/*********************************************************************************
* xiahouzuoixn
* 2014.07.25
*********************************************************************************/


/* Memory Map 0 - the default */

/*
 * Internal:
 * L2_RAM      0x00000000 - 0x0002FFFF  192K
 * L2_Cache    0x00030000 - 0x0003FFFF  64K

 * External(EMIF):
 * CE0         0x80000000 - 0x8FFFFFFF  256M
 * CE1         0x90000000 - 0x9FFFFFFF  256M
 * CE2         0xA0000000 - 0xAFFFFFFF  256M
 * CE3         0xB0000000 - 0xBFFFFFFF  256M
 * 
 * Truth External(EMIF):
 * CE0         32MB=256Mbit
 * CE1
 * 
 * About Use of SDRAM
 * PARTITION is the memory that managed by memory management program
 */

-lbios_firstcfg.cmd
-lcsl6713.lib

SECTIONS
{    
	/* RAM */
	.boot_load: {} > BOOT_RAM

	/* User defined */	
}

