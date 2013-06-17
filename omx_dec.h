/*
 * Copyright (c) 2012 WonderMedia Technologies, Inc. All Rights Reserved.
 *
 * This PROPRIETARY SOFTWARE is the property of WonderMedia Technologies, Inc.
 * and may contain trade secrets and/or other confidential information of 
 * WonderMedia Technologies, Inc. This file shall not be disclosed to any
 * third party, in whole or in part, without prior written consent of
 * WonderMedia.
 *
 * THIS PROPRIETARY SOFTWARE AND ANY RELATED DOCUMENTATION ARE PROVIDED
 * AS IS, WITH ALL FAULTS, AND WITHOUT WARRANTY OF ANY KIND EITHER EXPRESS
 * OR IMPLIED, AND WonderMedia TECHNOLOGIES, INC. DISCLAIMS ALL EXPRESS
 * OR IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
 * QUIET ENJOYMENT OR NON-INFRINGEMENT.
 */
#ifndef OMX_WMTDEC_H
#define OMX_WMTDEC_H

/*--- omx_dec.h---------------------------------------------------------------
*   Copyright (C) 2012 WonderMedia Tech. Inc.
*
* MODULE       : omx_dec.h
* AUTHOR       : Jason Lin
* DATE         : 2012/03/25
* DESCRIPTION  : 
*------------------------------------------------------------------------------*/

/*--- History -------------------------------------------------------------------
* Version 0.01 , Jason Lin
*	First version
*
*------------------------------------------------------------------------------*/
/*-------------------- MODULE DEPENDENCY -------------------------------------*/
#include "omx_comm.h"

#ifdef	__cplusplus
extern "C" {
#endif

static OMX_ERRORTYPE SetCallbacks (OMX_IN OMX_HANDLETYPE hComponent,
                                   	   OMX_IN OMX_CALLBACKTYPE* pCallBacks,
                                       OMX_IN OMX_PTR pAppData);

static OMX_ERRORTYPE GetComponentVersion (OMX_HANDLETYPE hComponent,
                                          		   OMX_STRING  szComponentName,
                                          		   OMX_VERSIONTYPE* pComponentVersion,
                                          		   OMX_VERSIONTYPE* pSpecVersion,
                                          	  	   OMX_UUIDTYPE* pComponentUUID);

static OMX_ERRORTYPE SendCommand (OMX_IN OMX_HANDLETYPE hComponent,
                                  		 OMX_IN OMX_COMMANDTYPE Cmd,
                                  		 OMX_IN OMX_U32 nParam1,
                                  		 OMX_IN OMX_PTR pCmdData);

static OMX_ERRORTYPE GetParameter (OMX_IN OMX_HANDLETYPE hComponent,
                                   	    OMX_IN OMX_INDEXTYPE nParamIndex,
                                   		OMX_INOUT OMX_PTR CompParamStruct);

static OMX_ERRORTYPE SetParameter (OMX_IN OMX_HANDLETYPE hComponent,
                                   	   OMX_IN OMX_INDEXTYPE nParamIndex,
                                   	   OMX_IN OMX_PTR CompParamStruct);

static OMX_ERRORTYPE GetConfig (OMX_IN OMX_HANDLETYPE hComponent,
                                   OMX_IN OMX_INDEXTYPE nConfigIndex,
                                   OMX_INOUT OMX_PTR ComponentConfigStructure);

static OMX_ERRORTYPE SetConfig (OMX_IN OMX_HANDLETYPE hComponent,
                                   OMX_IN OMX_INDEXTYPE nConfigIndex,
                                   OMX_IN OMX_PTR ComponentConfigStructure);

static OMX_ERRORTYPE EmptyThisBuffer (OMX_IN OMX_HANDLETYPE hComponent,
                                      	   OMX_IN OMX_BUFFERHEADERTYPE* pBuffer);

static OMX_ERRORTYPE FillThisBuffer (OMX_IN OMX_HANDLETYPE hComponent,
                                     	OMX_IN OMX_BUFFERHEADERTYPE* pBuffer);

static OMX_ERRORTYPE GetState (OMX_IN OMX_HANDLETYPE hComponent,
                               	 OMX_OUT OMX_STATETYPE* pState);

static OMX_ERRORTYPE ComponentTunnelRequest (OMX_IN OMX_HANDLETYPE hComponent,
                                             			OMX_IN OMX_U32 nPort,
                                             			OMX_IN OMX_HANDLETYPE hTunneledComp,
                                             			OMX_IN  OMX_U32 nTunneledPort,
                                             			OMX_INOUT OMX_TUNNELSETUPTYPE* pTunnelSetup);

static OMX_ERRORTYPE UseBuffer (OMX_IN OMX_HANDLETYPE hComponent,
                                   OMX_INOUT OMX_BUFFERHEADERTYPE** ppBufferHdr,
                                   OMX_IN OMX_U32 nPortIndex,
                                   OMX_IN OMX_PTR pAppPrivate,
                                   OMX_IN OMX_U32 nSizeBytes,
                                   OMX_IN OMX_U8* pBuffer);

static OMX_ERRORTYPE AllocateBuffer (OMX_IN OMX_HANDLETYPE hComponent,
                                        OMX_INOUT OMX_BUFFERHEADERTYPE** pBuffer,
                                        OMX_IN OMX_U32 nPortIndex,
                                        OMX_IN OMX_PTR pAppPrivate,
                                        OMX_IN OMX_U32 nSizeBytes);

static OMX_ERRORTYPE FreeBuffer (OMX_IN OMX_HANDLETYPE hComponent,
                                    OMX_IN OMX_U32 nPortIndex,
                                    OMX_IN OMX_BUFFERHEADERTYPE* pBuffer);

static OMX_ERRORTYPE ComponentDeInit (OMX_IN OMX_HANDLETYPE hComponent);


static OMX_ERRORTYPE ExtensionIndex (OMX_IN OMX_HANDLETYPE hComponent,
                                     	  OMX_IN OMX_STRING cParameterName,
                                     	  OMX_OUT OMX_INDEXTYPE* pIndexType);

#ifdef	__cplusplus
}
#endif	

#endif /* ifndef OMX_WMTDEC_H */
