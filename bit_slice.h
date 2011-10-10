#ifndef BIT_SLICE_H
#define BIT_SLICE_H

// BIT Slicing macros
#define ONES32(size)                    ((size)?(0xffffffff>>(32-(size))):0)
#define MASK32(offset,size)             (ONES32(size)<<(offset))

#define EXTRACT_C(source,offset,size)   ((((unsigned)(source))>>(offset)) & ONES32(size))
#define EXTRACT(src,start,len)          (((len)==32)?(src):EXTRACT_C(src,start,len))
#define EXT(src,end,start)              EXTRACT(src,start,end-start+1)

#define MERGE_C(rsrc1,rsrc2,start,len)  ((((rsrc2)<<(start)) & (MASK32((start),(len)))) | ((rsrc1) & (~MASK32((start),(len)))))
#define MERGE(rsrc1,rsrc2,start,len)    (((len)==32)?(rsrc2):MERGE_C(rsrc1,rsrc2,start,len))
#define INSERTF(src1, start1, src2, start2, len) MERGE((src1), EXTRACT((src2), (start2), (len)), (start1), (len))

#define ONES64(size)                    ((size)?(0xffffffffffffffffULL>>(64-(size))):0)
#define MASK64(offset,size)             (ONES64(size)<<(offset))

#define EXTRACT_C64(source,offset,size)   ((((unsigned long long)(source))>>(offset)) & ONES64(size))
#define EXTRACT64(src,start,len)          (((len)==64)?(src):EXTRACT_C64(src,start,len))

#define MERGE_C64(rsrc1,rsrc2,start,len)  ((((u_int64_t)(rsrc2)<<(start)) & (MASK64((start),(len)))) | ((rsrc1) & (~MASK64((start),(len)))))
#define MERGE64(rsrc1,rsrc2,start,len)    (((len)==64)?(rsrc2):MERGE_C64(rsrc1,rsrc2,start,len))
#define INSERTF64(src1, start1, src2, start2, len) MERGE64((src1), EXTRACT64((src2), (start2), (len)), (start1), (len))
#define EXT64(src,end,start)              EXTRACT64(src,start,end-start+1)

#ifndef __cplusplus
enum cpp_bool {false=0,true};
typedef unsigned char bool;
#endif

#endif
