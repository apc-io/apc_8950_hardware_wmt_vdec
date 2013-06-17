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
#ifndef OMX_WMTCOMM_H
#define OMX_WMTCOMM_H

/*--- omx_avc.h---------------------------------------------------------------
*   Copyright (C) 2012 WonderMedia Tech. Inc.
*
* MODULE       : omx_comm.h
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
#include <pthread.h>
#include "OMX_Core.h"
#include "OMX_Component.h"
#ifdef	__cplusplus
extern "C" {
#endif
#include "libavformat/avformat.h"
#ifdef	__cplusplus
}
#endif

// #define OMX_WMTDEC_RELEASE
#define DBG_INFO	0x1
#define DBG_DEBUG	0x2
#define DBG_VERBOSE	0x4
#define DBG_TRACE	0x8
#define DBG_AVSYNC	0x10

#define OMX_INPORT_INDEX 0
#define OMX_OUTPORT_INDEX 1
#define OMX_NUM_INPUT_BUFFERS 8
#define OMX_NUM_OUTPUT_BUFFERS 2

// OMX command Reserved region for introducing Vendor Extensions
#define OMX_CommandEmptyBuffer OMX_CommandVendorStartUnused
#define OMX_CommandFillBuffer (OMX_CommandVendorStartUnused + 1)
#define OMX_IndexUseNativeBuffers OMX_IndexVendorStartUnused
#define OMX_IndexAndroidNativeBufferUsage (OMX_IndexVendorStartUnused + 1)

typedef struct{
	AVPacketList *first_pkt,*last_pkt;
	int nb_packets;
	int size;
	volatile int abort_request;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}PacketQueue;

typedef struct OMX_PARAMUSENATIVEBUFFER{
	OMX_U32 nSize;
	OMX_VERSIONTYPE nVersion;
	OMX_U32 nPortIndex;
	OMX_BOOL bEnable;
} OMX_PARAMUSENATIVEBUFFER;

typedef struct OMX_PARAMNATIVEBUFFERUSAGE{
	OMX_U32 nSize;
	OMX_VERSIONTYPE nVersion;
	OMX_U32 nPortIndex;
    OMX_U32 nUsage;
} OMX_PARAMNATIVEBUFFERUSAGE;

typedef struct{
	OMX_COMMANDTYPE cmd;
	OMX_U32 nParam;
	OMX_PTR pCmdData;
} CommandInfo;

typedef struct BufferInfo{
	OMX_BUFFERHEADERTYPE mHeader; // must be first member
	struct BufferInfo *next,*prev;
	int mOwnedByUs;
} BufferInfo;

typedef struct PictureInfo{
   struct PictureInfo *next,*prev;
   AVFrame mPic;
   int output;
} PictureInfo;

typedef struct PortInfo{
	OMX_PARAM_PORTDEFINITIONTYPE mDef;
	PacketQueue mQue;
	BufferInfo *mBuf;
	int mBufCnt;
	enum {
		NONE,
		DISABLING,
		ENABLING,
	} mTransition;
}PortInfo;

typedef struct OMXWMTDecoder{
	PacketQueue cmdQue;
	PortInfo inPort;
	PortInfo outPort;
    pthread_t pid;
	AVCodecContext *avctx;
	PictureInfo *picts;
	AVPacket procPkt, inPkt;
	int fbWidth;
	int fbHeight;
	int cropLeft;
	int cropTop;
	int cropRight;
	int cropBottom;

	int wmtLock;
	int lock;
	int waitFb;
	int EOSStatus;
	enum CodecID codecID;

	int inCnt;
	int outCnt;
	int logLevel;

	// component information
	OMX_CALLBACKTYPE callBack;
	OMX_HANDLETYPE component;
	OMX_STATETYPE state;
	OMX_STATETYPE targetState;
	OMX_STRING componentName;
}OMXWMTDecoder;

struct OMXWMTTracer{
public:
    OMXWMTTracer(const char *fn, OMXWMTDecoder *dec, int *ret = NULL);
	OMXWMTTracer(const char *fn, OMXWMTDecoder *dec, OMX_ERRORTYPE *ret = NULL);
	OMXWMTTracer(const char *fn, OMXWMTDecoder *dec, CommandInfo *pCi, OMX_ERRORTYPE *ret = NULL);
    OMXWMTTracer(const char *fn, OMXWMTDecoder *dec, OMX_COMMANDTYPE cmd, OMX_ERRORTYPE *ret = NULL);
    OMXWMTTracer(const char *fn, OMXWMTDecoder *dec, OMX_INDEXTYPE index, OMX_ERRORTYPE *ret = NULL);
	OMXWMTTracer(const char *fn, OMXWMTDecoder *dec, OMX_STRING str, OMX_ERRORTYPE *ret = NULL);
	~OMXWMTTracer();
private:
    void OMXWMTTracerInit(const char *fn, int ll, int *ret, OMX_ERRORTYPE *oret);
    const char *mName;
	int nLogLevel;
	int *mRet;
	enum CodecID codecID;
	OMX_ERRORTYPE *mORet;
};

#ifdef	__cplusplus
extern "C" {
#endif
const char *CodecStr(enum CodecID id);
const char *StateStr(OMX_STATETYPE cmd);
const char *CmdStr(OMX_COMMANDTYPE cmd);
const char *SwitchStr(OMX_BOOL sw);
const char *PopulateStr(OMX_BOOL sw);
const char *PortDirStr(OMX_DIRTYPE dir);
const char *PortDomainStr(OMX_PORTDOMAINTYPE domain);
const char *TransitionStr(int transition);
const char *EventStr(OMX_EVENTTYPE event);
void Status(OMXWMTDecoder *dec);
void PortDef(OMXWMTDecoder *dec, OMX_PARAM_PORTDEFINITIONTYPE *port);
void DumpData(OMXWMTDecoder *dec, uint8_t *data, int len);
void OMX4FFmpegLog(void* ptr, int level, const char* fmt, va_list vl);
int QueueEmpty(PacketQueue *q);
void QueueInit(PacketQueue *q);
void QueueFlush(PacketQueue *q);
void QueueEnd(PacketQueue *q);
void QueueAbort(PacketQueue *q);
int QueuePut(PacketQueue *q, AVPacket *pkt);
int QueueGet(PacketQueue *q, AVPacket *pkt);
#if defined(__cplusplus)
}
#endif

#ifdef OMX_WMTDEC_RELEASE
#define OMX_TRACE(...) do{}while(0)
#define OMX_LOG(DBG,fmt,args...) do{}while(0)
#define ShowStatus(...) do{}while(0)
#define ShowPortDef(...) do{}while(0)
#define ShowData(...) do{}while(0)
#else
#define OMX_TRACE( ...) OMXWMTTracer __tracer__(__FUNCTION__, dec, ##__VA_ARGS__);
#define OMX_LOG(DBG,fmt,args...) do{ if(dec->logLevel & DBG) LOGI("[%s] "fmt,CodecStr(dec->codecID),## args); }while(0)
#define ShowStatus Status
#define ShowPortDef PortDef
#define ShowData DumpData
#endif
#endif /* ifndef OMX_WMTCOMM_H */
