#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/wait.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/poll.h>
#include <linux/device.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <linux/time.h>
#include "kd_flashlight.h"
#include <asm/io.h>
#include <asm/uaccess.h>
#include "kd_camera_hw.h"
//<2015/04/30-joubert.she-[V10][Feature][Common][BSP][][] main camera awb/ae/af/fl setting separation
#include <linux/xlog.h>

#define PFX "[strobe_getPartId]"
#define PK_DBG_FUNC(fmt, arg...)    xlog_printk(ANDROID_LOG_ERROR , PFX, fmt, ##arg)

extern int Camera_Verify_Type(void);

//>2015/04/30-joubert.she
int strobe_getPartId(int sensorDev)
{
	// return 1 or 2 (backup flash part). Other numbers are invalid.
	if(sensorDev == e_CAMERA_MAIN_SENSOR)
	{
	//<2015/04/30-joubert.she-[V10][Feature][Common][BSP][][] main camera awb/ae/af/fl setting separation
	    if(Camera_Verify_Type()==1)//8M camera
		{
		PK_DBG_FUNC("camera_type==1 //// 8M camera is used");
		return 1;
           }
            else
                {
                PK_DBG_FUNC("camera_type==0//// 5M camera is used");
                return 2;
                }
				//>2015/04/30-joubert.she
	}
	else if(sensorDev == e_CAMERA_SUB_SENSOR)
	{
		return 1;
	}
	else //e_CAMERA_MAIN_2_SENSOR
	{
		return 200;
	}
	return 100;
}