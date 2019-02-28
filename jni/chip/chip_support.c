/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 */
/* MediaTek Inc. (C) 2010. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek Software")
 * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * applicable license agreements with MediaTek Inc.
 */

/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2008
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/


/*******************************************************************************
 *
 * Filename:
 * ---------
 *  
 *
 * Project:
 * --------
 *   Android
 *
 * Description:
 * ------------
 *    c file of chip support jni function
 *
 * Author:
 * -------
 *   MTK80905

 *******************************************************************************/
/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <cutils/xlog.h>
#include <cutils/properties.h>
#include "chip_support.h"

#define LOG_TAG "EM_CHIP_SUPPORT"
#define EM_CHIP_NAME_LENGTH (6)

typedef struct {
    char *chip_name;
    int chip_id;
} chip_mapping;

static const chip_mapping s_chip_mappings[] = {
    {"65+73", MTK_6573_SUPPORT},
    {"65+16", MTK_6516_SUPPORT},
    {"65+75", MTK_6575_SUPPORT},
    {"65+77", MTK_6577_SUPPORT},
    {"65+89", MTK_6589_SUPPORT},
    {"65+82", MTK_6582_SUPPORT},
    {"65+72", MTK_6572_SUPPORT},
    {"81+35", MTK_8135_SUPPORT},
    {"81+27", MTK_8127_SUPPORT},
    {"65+71", MTK_6571_SUPPORT},
    {"65+92", MTK_6592_SUPPORT},
    {"65+95", MTK_6595_SUPPORT},
    {"67+52", MTK_6752_SUPPORT},
}; 

int em_jni_get_chip_id() {
    char buff[PROPERTY_VALUE_MAX] = {0}; // PROPERTY_VALUE_MAX  = 92
    int count, i, j, len, k;
    chip_mapping *mapping;
	char chipName[EM_CHIP_NAME_LENGTH]={0};
    
    property_get("ro.mediatek.platform", buff, NULL);
    //XLOGD("Chip Hardware: [%s]", buff);
    len = strlen(buff);
    for (k = 0; k < len; k++) {
        if (isupper(buff[k])) {
            buff[k] = tolower(buff[k]);
        }
    }
    count = sizeof(s_chip_mappings) / sizeof(chip_mapping);
    for (i = 0; i < count; i++) {
        mapping = s_chip_mappings + i;
		len = strlen(mapping->chip_name);
		j = 0;
		for(k = 0; k < len; k++) {
			if(mapping->chip_name[k] != '+') { /* skip '+'*/
				chipName[j++] = mapping->chip_name[k];
		    }
		}
        /* skip 'mt' prefix */
        if (strstr(buff, "mt") != NULL) {
            if (strcmp(chipName, buff + 2) == 0) {
                return mapping->chip_id;
            }
        } else {
            if (strcmp(chipName, buff) == 0) {
                return mapping->chip_id;
            }
        }
    }
    XLOGD("UNKNOWN CHIP: %s", buff);
    return MTK_UNKNOWN_SUPPORT;
}

JNIEXPORT jint JNICALL Java_com_mediatek_engineermode_ChipSupport_getChip
  (JNIEnv * env, jobject obj)
  {
  	return em_jni_get_chip_id();
  }
  
  
  



