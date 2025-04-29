
// Hooks.c
// [Full decompiled content pasted here: all 61 functions and block layout

// Hooks.c
#include "defs.h"
#import <objc/message.h>
#import <dispatch/dispatch.h>

// Associated key
static void *kNeedHookKey = &kNeedHookKey; // weak
static __int64 swizzledClasses;           // weak
static __int64 customLog_token = -1;      // weak
static __int64 logQueue;                  // weak
static __int64 logFilePath_path;          // weak
static __int64 logFilePath_token = -1;    // weak
static __int64 getAppGroup_cachedGroup;   // weak
static __int64 getAppGroup_onceToken = -1;// weak

// Forward-declare block invoke helpers
void __cdecl __initHooks_block_invoke(id);
void __cdecl __customLog_block_invoke(id);
void __fastcall __customLog_block_invoke_2(_QWORD *a1);
void __cdecl __logFilePath_block_invoke(id);
void __cdecl __getAppGroup_block_invoke(id);

//-------------------------------------------------------------------------
// 1) didPickDocumentAtURL
void __fastcall didPickDocumentAtURL(
        void *a1,
        void *a2,
        void *a3,
        void (__fastcall *a4)(id, const char *, id, NSURL *))
{
    NSURL *v4; // x8
    NSURL *v5; // x0
    id v6;     // [xsp+28h] [xbp-78h]
    id v7;     // [xsp+30h] [xbp-70h]
    id v11;    // [xsp+58h] [xbp-48h]
    unsigned __int8 v12; // [xsp+64h] [xbp-3Ch]
    NSURL *v13; // [xsp+70h] [xbp-30h] BYREF
    char v14;   // [xsp+7Fh] [xbp-21h]
    void (__fastcall *v15)(id, const char *, id, NSURL *); // [xsp+80h] [xbp-20h]
    id v16;     // [xsp+88h] [xbp-18h] BYREF
    id v17;     // [xsp+90h] [xbp-10h] BYREF
    id location;// [xsp+98h] [xbp-8h] BYREF

    location = 0;
    objc_storeStrong(&location, a1);
    v17 = 0;
    objc_storeStrong(&v17, a2);
    v16 = 0;
    objc_storeStrong(&v16, a3);
    v15 = a4;
    v11 = objc_retainAutoreleasedReturnValue(objc_getAssociatedObject(v17, kNeedHookKey));
    v12 = (unsigned __int8)objc_msgSend(v11, "boolValue");
    objc_release(v11);
    v14 = v12 & 1;
    v13 = (NSURL *)objc_retain(v16);
    if ( v16 && (v14 & 1) != 0 )
    {
        v6 = v16;
        v7 = objc_retainAutoreleasedReturnValue(temperoryDirectory());
        v4 = objc_retainAutoreleasedReturnValue(moveFileToTemp(v6, v7));
        v5 = v13;
        v13 = v4;
        objc_release(v5);
        objc_release(v7);
    }
    v15(location, "documentPicker:didPickDocumentAtURL:", v17, v13);
    objc_storeStrong((id *)&v13, 0);
    objc_storeStrong(&v16, 0);
    objc_storeStrong(&v17, 0);
    objc_storeStrong(&location, 0);
}

//-------------------------------------------------------------------------
// 2) moveFileToTemp
NSURL *__fastcall moveFileToTemp(void *a1, void *a2)
{
    NSFileManager *v4;    // [xsp+18h] [xbp-68h]
    NSURL *v5;            // [xsp+50h] [xbp-30h]
    NSURL *v6;            // [xsp+58h] [xbp-28h] BYREF
    id v7;                // [xsp+60h] [xbp-20h] BYREF
    id v8;                // [xsp+68h] [xbp-18h] BYREF
    id v9;                // [xsp+70h] [xbp-10h] BYREF
    id location;          // [xsp+78h] [xbp-8h] BYREF

    location = 0;
    objc_storeStrong(&location, a1);
    v9 = 0;
    objc_storeStrong(&v9, a2);
    v8 = objc_retainAutoreleasedReturnValue(objc_msgSend(location, "lastPathComponent"));
    v7 = objc_retainAutoreleasedReturnValue(objc_msgSend(v9, "stringByAppendingPathComponent:", v8));
    v6 = objc_retainAutoreleasedReturnValue(+[NSURL fileURLWithPath:](&OBJC_CLASS___NSURL, "fileURLWithPath:", v7));
    v4 = objc_retainAutoreleasedReturnValue(+[NSFileManager defaultManager](&OBJC_CLASS___NSFileManager, "defaultManager"));
    -[NSFileManager moveItemAtURL:toURL:error:](v4, "moveItemAtURL:toURL:error:", location, v6, 0);
    objc_release(v4);
    v5 = objc_retain(v6);
    objc_storeStrong((id *)&v6, 0);
    objc_storeStrong(&v7, 0);
    objc_storeStrong(&v8, 0);
    objc_storeStrong(&v9, 0);
    objc_storeStrong(&location, 0);
    return objc_autoreleaseReturnValue(v5);
}

//-------------------------------------------------------------------------
// 3) didPickDocumentAtURLs
void __fastcall didPickDocumentAtURLs(void *a1,
                                     void *a2,
                                     void *a3,
                                     void (__fastcall *a4)(id, const char *, id, id))
{
    NSMutableArray *v4; // [xsp+30h] [xbp-1B0h]
    NSURL *v5;          // [xsp+38h] [xbp-1A8h]
    __int64 v6;         // [xsp+48h] [xbp-198h]
    __int64 v7;         // [xsp+50h] [xbp-190h]
    __int64 v8;         // [xsp+58h] [xbp-188h]
    id v9;              // [xsp+60h] [xbp-180h]
    id v10;             // [xsp+78h] [xbp-168h]
    id v11;             // [xsp+80h] [xbp-160h]
    _QWORD __b[8];      // [xsp+B8h] [xbp-128h] BYREF
    void *v16;          // [xsp+F8h] [xbp-E8h]
    id v17;             // [xsp+100h] [xbp-E0h] BYREF
    NSMutableArray *v18;// [xsp+108h] [xbp-D8h] BYREF
    id v19;             // [xsp+110h] [xbp-D0h] BYREF
    char v20;           // [xsp+11Fh] [xbp-C1h]
    id v21;             // [xsp+120h] [xbp-C0h] BYREF
    void (__fastcall *v22)(id, const char *, id, id);// [xsp+128h] [xbp-B8h]
    id v23;             // [xsp+130h] [xbp-B0h] BYREF
    id v24;             // [xsp+138h] [xbp-A8h] BYREF
    id location;        // [xsp+140h] [xbp-A0h] BYREF
    _BYTE v26[128];     // [xsp+148h] [xbp-98h] BYREF

    location = 0;
    objc_storeStrong(&location, a1);
    v24 = 0;
    objc_storeStrong(&v24, a2);
    v23 = 0;
    objc_storeStrong(&v23, a3);
    v22 = a4;
    v21 = objc_retainAutoreleasedReturnValue(objc_getAssociatedObject(v24, kNeedHookKey));
    v20 = (unsigned __int8)objc_msgSend(v21, "boolValue") & 1;
    v19 = objc_retain(v23);
    if ((v20 & 1) != 0 && objc_msgSend(v23, "count"))
    {
        v18 = objc_retainAutoreleasedReturnValue(
                +[NSMutableArray arrayWithCapacity:](
                  &OBJC_CLASS___NSMutableArray,
                  "arrayWithCapacity:",
                  objc_msgSend(v23, "count")));
        v17 = objc_retainAutoreleasedReturnValue(temperoryDirectory());
        memset(__b, 0, sizeof(__b));
        v10 = objc_retain(v23);
        v11 = objc_msgSend(v10, "countByEnumeratingWithState:objects:count:", __b, v26, 16);
        if (v11)
        {
            v7 = *(_QWORD *)__b[2];
            v8 = 0;
            v9 = v11;
            while (1)
            {
                v6 = v8;
                if (*(_QWORD *)__b[2] != v7)
                    objc_enumerationMutation(v10);
                v16 = *(void **)(__b[1] + 8 * v8);
                v4 = v18;
                v5 = objc_retainAutoreleasedReturnValue(moveFileToTemp(v16, v17));
                -[NSMutableArray addObject:](v4, "addObject:");
                objc_release(v5);
                ++v8;
                if (v6 + 1 >= (unsigned __int64)v9)
                {
                    v8 = 0;
                    v9 = objc_msgSend(v10, "countByEnumeratingWithState:objects:count:", __b, v26, 16);
                    if (!v9)
                        break;
                }
            }
        }
        objc_release(v10);
        objc_storeStrong(&v19, v18);
        objc_storeStrong(&v17, 0);
        objc_storeStrong((id *)&v18, 0);
    }
    v22(location, "documentPicker:didPickDocumentsAtURLs:", v24, v19);
    objc_storeStrong(&v19, 0);
    objc_storeStrong(&v21, 0);
    objc_storeStrong(&v23, 0);
    objc_storeStrong(&v24, 0);
    objc_storeStrong(&location, 0);
}

//-------------------------------------------------------------------------
// 4) initWithDocumentTypesInMode
id __fastcall initWithDocumentTypesInMode(
        void *a1,
        void *a2,
        __int64 a3,
        __int64 (__fastcall *a4)(id, const char *, id, _QWORD))
{
    void *key;        // [xsp+8h] [xbp-78h]
    id object;        // [xsp+10h] [xbp-70h]
    NSNumber *v7;     // [xsp+18h] [xbp-68h]
    id v11;           // [xsp+68h] [xbp-18h] BYREF
    id location;      // [xsp+70h] [xbp-10h] BYREF
    id v13;           // [xsp+78h] [xbp-8h]

    location = 0;
    objc_storeStrong(&location, a1);
    v11 = 0;
    objc_storeStrong(&v11, a2);
    if (a3)
    {
        object = location;
        key = kNeedHookKey;
        v7 = objc_retainAutoreleasedReturnValue(+[NSNumber numberWithBool:](&OBJC_CLASS___NSNumber, "numberWithBool:", 1));
        objc_setAssociatedObject(object, key, v7, (char *)&dword_0 + 1);
        objc_release(v7);
    }
    v13 = objc_retainAutoreleasedReturnValue((id)a4(location, "initWithDocumentTypes:inMode:", v11, 0));
   objc_storeStrong(&v11, 0);
    objc_storeStrong(&location, 0);
    return objc_autoreleaseReturnValue(v13);
}

//-------------------------------------------------------------------------
// 5) initForOpeningContentTypesAsCopy
id __fastcall initForOpeningContentTypesAsCopy(
        void *a1,
        void *a2,
        char a3,
        __int64 (__fastcall *a4)(id, const char *, id, __int64))
{
    void *key; 
    id object; 
    NSNumber *v7; 
    id v11;           // [xsp+78h] [xbp-18h] BYREF
    id location;      // [xsp+80h] [xbp-10h] BYREF
    id v13;           // [xsp+88h] [xbp-8h]

    location = 0;
    objc_storeStrong(&location, a1);
    v11 = 0;
    objc_storeStrong(&v11, a2);
    if ((a3 & 1) != 0)
    {
        v13 = objc_retainAutoreleasedReturnValue((id)a4(location, "initForOpeningContentTypes:asCopy:", v11, a3 & 1));
    }
    else
    {
        object = location;
        key = kNeedHookKey;
        v7 = objc_retainAutoreleasedReturnValue(+[NSNumber numberWithBool:](&OBJC_CLASS___NSNumber, "numberWithBool:", 1));
        objc_setAssociatedObject(object, key, v7, (char *)&dword_0 + 1);
        objc_release(v7);
        v13 = objc_retainAutoreleasedReturnValue((id)a4(location, "initForOpeningContentTypes:asCopy:", v11, 1));
    }
    objc_storeStrong(&v11, 0);
    objc_storeStrong(&location, 0);
    return objc_autoreleaseReturnValue(v13);
}

//-------------------------------------------------------------------------
// 6) setDelegate
void __fastcall setDelegate(void *a1, void *a2, void (__fastcall *a3)(id, const char *, id))
{
    objc_class *v5; // [xsp+40h] [xbp-20h]
    id v6;          // [xsp+50h] [xbp-10h] BYREF
    id location;    // [xsp+58h] [xbp-8h] BYREF

    location = 0;
    objc_storeStrong(&location, a1);
    v6 = 0;
    objc_storeStrong(&v6, a2);
    v5 = (objc_class *)objc_msgSend(v6, "class");
    if (v5 && ((unsigned int)objc_msgSend((id)swizzledClasses, "containsObject:", v5) & 1) == 0)
    {
        swizzle_document_picker_delegate(v5, "documentPicker:didPickDocumentAtURL:", 0);
        swizzle_document_picker_delegate(v5, "documentPicker:didPickDocumentsAtURLs:", 1);
        objc_msgSend((id)swizzledClasses, "addObject:", v5);
    }
    a3(location, "setDelegate:", v6);
    objc_storeStrong(&v6, 0);
    objc_storeStrong(&location, 0);
}

//-------------------------------------------------------------------------
// 7) swizzle_document_picker_delegate
void __fastcall swizzle_document_picker_delegate(objc_class *a1, const char *a2, char a3)
{
    void ***v3; 
    void ***v4; 
    void ***v5; 
    void ***v6; 
    IMP imp; 
    void **v8;      // BYREF
    int v9; 
    int v10; 
    void (__fastcall *v11)(void (__fastcall **)(id, const char *, id, NSURL *), void *, void *, void *); 
    void *v12; 
    IMP v13; 
    void **v14;     // BYREF
    int v15; 
    int v16; 
    void (__fastcall *v17)(void (__fastcall **)(id, const char *, id, id), void *, void *, void *); 
    void *v18; 
    IMP v19; 
    void ***v20;    // BYREF
    IMP Implementation; 
    Method InstanceMethod; 
    char v23; 
    const char *v24; 
    objc_class *v25; 

    v25 = a1;
    v24 = a2;
    v23 = a3 & 1;
    InstanceMethod = class_getInstanceMethod(a1, a2);
    if (InstanceMethod)
    {
        Implementation = method_getImplementation(InstanceMethod);
        v20 = 0;
        if ((v23 & 1) != 0)
        {
            v14 = _NSConcreteStackBlock;
            v15 = -1073741824;
            v16 = 0;
            v17 = __swizzle_document_picker_delegate_block_invoke;
            v18 = &__block_descriptor_40_e55_v32__0_8__UIDocumentPickerViewController_16__NSArray_24l;
            v19 = Implementation;
            v3 = objc_retainBlock(&v14);
            v4 = v20;
            v20 = v3;
            objc_release(v4);
        }
        else
        {
            v11 = _NSConcreteStackBlock;
            v9 = -1073741824;
            v10 = 0;
            v11 = __swizzle_document_picker_delegate_block_invoke_2;
            v12 = &__block_descriptor_40_e53_v32__0_8__UIDocumentPickerViewController_16__NSURL_24l;
            v13 = Implementation;
            v5 = objc_retainBlock(&v8);
            v6 = v20;
            v20 = v5;
            objc_release(v6);
        }
        imp = imp_implementationWithBlock(v20);
        method_setImplementation(InstanceMethod, imp);
        objc_storeStrong((id *)&v20, 0);
    }
}

//-------------------------------------------------------------------------
// 8) __swizzle_document_picker_delegate_block_invoke
void __fastcall __swizzle_document_picker_delegate_block_invoke(
        void (__fastcall **a1)(id, const char *, id, id),
        void *a2,
        void *a3,
        void *a4)
{
    id v7; // [xsp+40h] [xbp-20h] BYREF
    id v8; // [xsp+48h] [xbp-18h] BYREF
    id location[2]; // [xsp+50h] [xbp-10h] BYREF

    location[1] = a1;
    location[0] = 0;
    objc_storeStrong(location, a2);
    v8 = 0;
    objc_storeStrong(&v8, a3);
    v7 = 0;
    objc_storeStrong(&v7, a4);
    didPickDocumentAtURLs(location[0], v8, v7, a1[4]);
    objc_storeStrong(&v7, 0);
    objc_storeStrong(&v8, 0);
    objc_storeStrong(location, 0);
}

//-------------------------------------------------------------------------
// 9) __swizzle_document_picker_delegate_block_invoke_2
void __fastcall __swizzle_document_picker_delegate_block_invoke_2(
        void (__fastcall **a1)(id, const char *, id, NSURL *),
        void *a2,
        void *a3,
        void *a4)
{
    id v7; // [xsp+40h] [xbp-20h] BYREF
    id v8; // [xsp+48h] [xbp-18h] BYREF
    id location[2]; // [xsp+50h] [xbp-10h] BYREF

    location[1] = a1;
    location[0] = 0;
    objc_storeStrong(location, a2);
    v8 = 0;
    objc_storeStrong(&v8, a3);
    v7 = 0;
    objc_storeStrong(&v7, a4);
    didPickDocumentAtURL(location[0], v8, v7, a1[4]);
    objc_storeStrong(&v7, 0);
    objc_storeStrong(&v8, 0);
    objc_storeStrong(location, 0);
}

//-------------------------------------------------------------------------
// 10) swizzle_documentPicker
void __fastcall swizzle_documentPicker(objc_class *a1)
{
    IMP v1;
    void **v2; // BYREF
    int v3;
    int v4;
    void (__fastcall *v5)(void (__fastcall **)(id, const char *, id), void *, void *);
    void *v6;
    IMP v7;
    id block; // BYREF
    IMP v9;
    Method m;
    IMP imp;
    void **v12; // BYREF
    int v13;
    int v14;
    id (__fastcall *v15)(__int64 (__fastcall **)(id, const char *, id, __int64), void *, void *, char);
    void *v16;
    IMP v17;
    void ***v18; // BYREF
    IMP v19;
    Method v20;
    IMP v21;
    void **v22; // BYREF
    int v23;
    int v24;
    id (__fastcall *v25)(__int64 (__fastcall **)(id, const char *, id, _QWORD), void *, void *, __int64);
    void *v26;
    IMP v27;
    void ***v28; // BYREF
    IMP Implementation;
    Method InstanceMethod;
    Class v31;

    v31 = a1;
    InstanceMethod = class_getInstanceMethod(a1, "initWithDocumentTypes:inMode:");
    if (InstanceMethod)
    {
        Implementation = method_getImplementation(InstanceMethod);
        v22 = _NSConcreteStackBlock;
        v23 = -1073741824;
        v24 = 0;
        v25 = __swizzle_documentPicker_block_invoke;
        v26 = &__block_descriptor_40_e14__32__0_8_16q24l;
        v27 = Implementation;
        v28 = objc_retainBlock(&v22);
        v21 = imp_implementationWithBlock(v28);
        method_setImplementation(InstanceMethod, v21);
        objc_storeStrong((id *)&v28, 0);
    }
    v20 = class_getInstanceMethod(v31, "initForOpeningContentTypes:asCopy:");
    if (v20)
    {
        v19 = method_getImplementation(v20);
        v12 = _NSConcreteStackBlock;
        v13 = -1073741824;
        v14 = 0;
        v15 = __swizzle_documentPicker_block_invoke_2;
        v16 = &__block_descriptor_40_e14__28__0_8_16B24l;
        v17 = v19;
        v18 = objc_retainBlock(&v12);
        imp = imp_implementationWithBlock(v18);
        method_setImplementation(v20, imp);
        objc_storeStrong((id *)&v18, 0);
    }
    m = class_getInstanceMethod(v31, "setDelegate:");
    if (m)
    {
        v9 = method_getImplementation(m);
        v2 = _NSConcreteStackBlock;
        v3 = -1073741824;
        v4 = 0;
        v5 = __swizzle_documentPicker_block_invoke_3;
        v6 = &__block_descriptor_40_e11_v24__0_8_16l;
        v7 = v9;
        block = objc_retainBlock(&v2);
        v1 = imp_implementationWithBlock(block);
        method_setImplementation(m, v1);
        objc_storeStrong(&block, 0);
    }
}

//-------------------------------------------------------------------------
// 11) __swizzle_documentPicker_block_invoke
id __fastcall __swizzle_documentPicker_block_invoke(
        __int64 (__fastcall **a1)(id, const char *, id, _QWORD),
        void *a2,
        void *a3,
        __int64 a4)
{
    id v8; // [xsp+30h] [xbp-30h]
    id v9; // [xsp+48h] [xbp-18h] BYREF
    id location[2]; // [xsp+50h] [xbp-10h] BYREF

    location[1] = a1;
    location[0] = 0;
    objc_storeStrong(location, a2);
    v9 = 0;
    objc_storeStrong(&v9, a3);
    v8 = objc_retainAutoreleasedReturnValue(initWithDocumentTypesInMode(location[0], v9, a4, a1[4]));
    objc_storeStrong(&v9, 0);
    objc_storeStrong(location, 0);
    return objc_autoreleaseReturnValue(v8);
}

//-------------------------------------------------------------------------
// 12) __swizzle_documentPicker_block_invoke_2
id __fastcall __swizzle_documentPicker_block_invoke_2(
        __int64 (__fastcall **a1)(id, const char *, id, __int64),
        void *a2,
        void *a3,
        char a4)
{
    id v8; // [xsp+30h] [xbp-30h]
    id v9; // [xsp+48h] [xbp-18h] BYREF
    id location[2]; // [xsp+50h] [xbp-10h] BYREF

    location[1] = a1;
    location[0] = 0;
    objc_storeStrong(location, a2);
    v9 = 0;
    objc_storeStrong(&v9, a3);
    v8 = objc_retainAutoreleasedReturnValue(initForOpeningContentTypesAsCopy(location[0], v9, a4 & 1, a1[4]));
    objc_storeStrong(&v9, 0);
    objc_storeStrong(location, 0);
    return objc_autoreleaseReturnValue(v8);
}

//-------------------------------------------------------------------------
// 13) __swizzle_documentPicker_block_invoke_3
void __fastcall __swizzle_documentPicker_block_invoke_3(
        void (__fastcall **a1)(id, const char *, id),
        void *a2,
        void *a3)
{
    id v5; // [xsp+38h] [xbp-18h] BYREF
    id location[2]; // [xsp+40h] [xbp-10h] BYREF

    location[1] = a1;
    location[0] = 0;
    objc_storeStrong(location, a2);
    v5 = 0;
    objc_storeStrong(&v5, a3);
    setDelegate(location[0], v5, a1[4]);
    objc_storeStrong(&v5, 0);
    objc_storeStrong(location, 0);
}
//-------------------------------------------------------------------------
// 14) swizzleNSURL
void swizzleNSURL()
{
    void ***v0; // [xsp+8h] [xbp-78h]
    void (*v1)(void); // [xsp+10h] [xbp-70h]
    void **v2; // [xsp+28h] [xbp-58h] BYREF
    int v3;    // [xsp+30h] [xbp-50h]
    int v4;    // [xsp+34h] [xbp-4Ch]
    __int64 (__fastcall *v5)(__int64, void *); // [xsp+38h] [xbp-48h]
    void *v6;  // [xsp+40h] [xbp-40h]
    IMP v7;    // [xsp+48h] [xbp-38h]
    const char *v8; // [xsp+50h] [xbp-30h]
    void ***v9; // [xsp+58h] [xbp-28h] BYREF
    IMP Implementation; // [xsp+60h] [xbp-20h]
    Method InstanceMethod; // [xsp+68h] [xbp-18h]
    const char *v12; // [xsp+70h] [xbp-10h]
    Class Class;    // [xsp+78h] [xbp-8h]

    Class = objc_getClass("NSURL");
    v12 = "startAccessingSecurityScopedResource";
    InstanceMethod = class_getInstanceMethod(Class, "startAccessingSecurityScopedResource");
    if (InstanceMethod)
    {
        Implementation = method_getImplementation(InstanceMethod);
        v2 = _NSConcreteStackBlock;
        v3 = -1073741824;
        v4 = 0;
        v5 = __swizzleNSURL_block_invoke;
        v6 = &__block_descriptor_48_e8_B16__0_8l;
        v7 = Implementation;
        v8 = v12;
        v9 = objc_retainBlock(&v2);
        v0 = objc_retainBlock(v9);
        v1 = imp_implementationWithBlock(v0);
        objc_release(v0);
        method_setImplementation(InstanceMethod, v1);
        objc_storeStrong((id *)&v9, 0);
    }
}

//-------------------------------------------------------------------------
// 15) __swizzleNSURL_block_invoke
__int64 __fastcall __swizzleNSURL_block_invoke(__int64 a1, void *a2)
{
    int v4; // [xsp+1Ch] [xbp-34h]
    id v5;  // [xsp+20h] [xbp-30h] BYREF
    id v6[2]; // [xsp+28h] [xbp-28h] BYREF
    id location[2]; // [xsp+38h] [xbp-18h] BYREF
    char v8; // [xsp+4Fh] [xbp-1h]

    location[1] = a1;
    location[0] = 0;
    objc_storeStrong(location, a2);
    v8 = 0;
    // Your custom logic here (or call through):
    v4 = (*(__int64 (__fastcall **)(__int64))(a1 + 0x10))(a1);
    objc_storeStrong(location, 0);
    return v4;
}

//-------------------------------------------------------------------------
// 16) init
void init()
{
    initHooks();
}

//-------------------------------------------------------------------------
// 17) temperoryDirectory
id temperoryDirectory()
{
    id v1; // [xsp+20h] [xbp-50h]
    NSString *v2; // [xsp+30h] [xbp-40h]
    NSUUID *v3;   // [xsp+38h] [xbp-38h]
    NSString *v4; // [xsp+40h] [xbp-30h]
    id location;  // [xsp+50h] [xbp-20h] BYREF
    id v6;        // [xsp+58h] [xbp-18h] BYREF
    id v7;        // [xsp+60h] [xbp-10h] BYREF
    id v8;        // [xsp+68h] [xbp-8h] BYREF

    v3 = objc_retainAutoreleasedReturnValue(+[NSUUID UUID](&OBJC_CLASS___NSUUID, "UUID"));
    v2 = objc_retainAutoreleasedReturnValue(-[NSUUID UUIDString](v3, "UUIDString"));
    v8 = objc_retainAutoreleasedReturnValue(+[NSString stringWithFormat:](&OBJC_CLASS___NSString,
                                       "stringWithFormat:", CFSTR("choco-%@"), v2));
    objc_release(v2);
    objc_release(v3);
    v4 = objc_retainAutoreleasedReturnValue(NSHomeDirectory());
    v7 = objc_retainAutoreleasedReturnValue(
            -[NSString stringByAppendingPathComponent:](v4,
                                                      "stringByAppendingPathComponent:",
                                                      CFSTR("Documents/ChocoFilePickerFixFolder")));
    objc_release(v4);
    v6 = objc_retainAutoreleasedReturnValue(objc_msgSend(v7, "stringByAppendingPathComponent:", v8));
    location = objc_retainAutoreleasedReturnValue(+[NSFileManager defaultManager](&OBJC_CLASS___NSFileManager, "defaultManager"));
    if ((unsigned int)objc_msgSend(location, "fileExistsAtPath:", v6) == 0)
        objc_msgSend(location, "createDirectoryAtPath:withIntermediateDirectories:attributes:error:",
                      v6, 1, 0);
    v1 = objc_retain(v6);
    objc_storeStrong(&location, 0);
    objc_storeStrong(&v6, 0);
    objc_storeStrong(&v7, 0);
    objc_storeStrong(&v8, 0);
    return objc_autoreleaseReturnValue(v1);
}

//-------------------------------------------------------------------------
// 18) initHooks
void initHooks()
{
    id v0; // x8
    void *v1; // x0
    dispatch_time_t when; // [xsp+10h] [xbp-10h]
    NSObject *v3; // [xsp+18h] [xbp-8h]

    v0 = objc_retainAutoreleasedReturnValue(+[NSMutableSet set](&OBJC_CLASS___NSMutableSet, "set"));
    v1 = (void *)swizzledClasses;
    swizzledClasses = (__int64)v0;
    objc_release(v1);
    when = dispatch_time(0, 400000000);
    v3 = objc_retainAutoreleasedReturnValue(dispatch_get_global_queue(0, 0));
    dispatch_after(when, v3, &__block_literal_global);
    objc_release(v3);
}

//-------------------------------------------------------------------------
// 19) __initHooks_block_invoke
void __cdecl __initHooks_block_invoke(id a1)
{
    __int64 v1, v2, v3;
    id v4, obj, v6;
    _QWORD __b[8];
    objc_class *v8;
    Class cls;
    int i;
    id location;
    Class *buffer;
    int ClassList;
    objc_class *Class;
    id v15, v16;
    _BYTE v17[128];

    v16 = a1;
    v15 = a1;
    swizzleNSURL();
    Class = objc_getClass("UIDocumentPickerViewController");
    swizzle_documentPicker(Class);
    ClassList = objc_getClassList(0, 0);
    buffer = malloc(8LL * ClassList);
    ClassList = objc_getClassList(buffer, ClassList);
    location = objc_retainAutoreleasedReturnValue(+[NSMutableArray array](&OBJC_CLASS___NSMutableArray, "array"));
    for (i = 0; i < ClassList; ++i)
    {
        cls = buffer[i];
        if (cls != Class && class_getSuperclass(cls) == Class)
            objc_msgSend(location, "addObject:", cls);
    }
    free(buffer);
    memset(__b, 0, sizeof(__b));
    obj = objc_retain(location);
    v6 = objc_msgSend(obj, "countByEnumeratingWithState:objects:count:", __b, v17, 16);
    if (v6)
    {
        v2 = *(_QWORD *)__b[2];
        v3 = 0;
        v4 = v6;
        while (1)
        {
            v1 = v3;
            if (*(_QWORD *)__b[2] != v2)
                objc_enumerationMutation(obj);
            v8 = *(objc_class **)(__b[1] + 8 * v3);
            swizzle_documentPicker(v8);
            ++v3;
            if (v1 + 1 >= (unsigned __int64)v4)
            {
                v3 = 0;
                v4 = objc_msgSend(obj, "countByEnumeratingWithState:objects:count:", __b, v17, 16);
                if (!v4)
                    break;
            }
        }
    }
    objc_release(obj);
    objc_storeStrong(&location, 0);
}

//-------------------------------------------------------------------------
// 20) customLog
void __fastcall customLog(id obj, int a2, int a3, int a4, int a5, int a6, int a7, int a8, char a9)
{
    id v9;
    NSObject *queue;
    void **v11;
    int v12, v13;
    void (__fastcall *v14)(_QWORD *);
    void *v15;
    id v16;
    id v17[2];
    id location;
    id v19;
    dispatch_once_t *v20;

    location = 0;
    objc_storeStrong(&location, obj);
    v20 = &customLog_token;
    v19 = 0;
    objc_storeStrong(&v19, &__block_literal_global_0);
    if (*v20 != -1)
        dispatch_once(v20, v19);
    objc_storeStrong(&v19, 0);
    v17[1] = &a9;
    v9 = objc_alloc((Class)&OBJC_CLASS___NSString);
    v17[0] = objc_msgSend(v9, "initWithFormat:arguments:", location, &a9);
    queue = (NSObject *)logQueue;
    v11 = _NSConcreteStackBlock;
    v12 = -1040187392;
    v13 = 0;
    v14 = __customLog_block_invoke_2;
    v15 = &__block_descriptor_40_e8_32s_e5_v8__0l;
    v16 = objc_retain(v17[0]);
    dispatch_async(queue, &v11);
    objc_storeStrong(&v16, 0);
    objc_storeStrong(v17, 0);
    objc_storeStrong(&location, 0);
}

//-------------------------------------------------------------------------
// 21) __customLog_block_invoke
void __cdecl __customLog_block_invoke(id a1)
{
    dispatch_queue_t v1;
    void *v2;

    v1 = dispatch_queue_create("com.choco.whore", 0);
    v2 = (void *)logQueue;
    logQueue = (__int64)v1;
    objc_release(v2);
}

//-------------------------------------------------------------------------
// 22) __customLog_block_invoke_2
void __fastcall __customLog_block_invoke_2(_QWORD *a1)
{
    id v1;
    id v3;
    id location;
    id v5, v6, v7;
    id v8[3];

    v8[2] = a1;
    v8[1] = a1;
    v8[0] = objc_retainAutoreleasedReturnValue(+[NSDate date](&OBJC_CLASS___NSDate, "date"));
    v7 = objc_alloc_init((Class)&OBJC_CLASS___NSDateFormatter);
    objc_msgSend(v7, "setDateFormat:", CFSTR("yyyy-MM-dd HH:mm:ss"));
    v6 = objc_retainAutoreleasedReturnValue(objc_msgSend(v7, "stringFromDate:", v8[0]));
    v5 = objc_retainAutoreleasedReturnValue(+[NSString stringWithFormat:](&OBJC_CLASS___NSString,
                                "stringWithFormat:", CFSTR("%@ - %@\n"), v6, a1[4]));
    v3 = objc_retainAutoreleasedReturnValue(logFilePath());
    location = objc_retainAutoreleasedReturnValue(+[NSFileHandle fileHandleForWritingAtPath:](
                                &OBJC_CLASS___NSFileHandle, "fileHandleForWritingAtPath:"));
    objc_release(v3);
    if (location)
    {
        objc_msgSend(location, "seekToEndOfFile");
        v1 = objc_retainAutoreleasedReturnValue(objc_msgSend(v5, "dataUsingEncoding:", 4));
        objc_msgSend(location, "writeData:", v1);
        objc_release(v1);
        objc_msgSend(location, "closeFile");
    }
    objc_storeStrong(&location, 0);
    objc_storeStrong(&v5, 0);
    objc_storeStrong(&v6, 0);
    objc_storeStrong(&v7, 0);
    objc_storeStrong(v8, 0);
}

//-------------------------------------------------------------------------
// 23) __copy_helper_block_e8_32s
void __fastcall __copy_helper_block_e8_32s(__int64 a1, __int64 a2)
{
    id *v2;
    void *v3;

    v2 = (id *)(a1 + 32);
    v3 = *(void **)(a2 + 32);
    *v2 = 0;
    objc_storeStrong(v2, v3);
}

//-------------------------------------------------------------------------
// 24) __destroy_helper_block_e8_32s
void __fastcall __destroy_helper_block_e8_32s(__int64 a1)
{
    objc_storeStrong((id *)(a1 + 32), 0);
}

//-------------------------------------------------------------------------
// 25) customLog2
void __fastcall customLog2(id obj, int a2, int a3, int a4, int a5, int a6, int a7, int a8, char a9)
{
    id v9;
    id v10;
    id v11;
    id v12;
    id v13;
    id v14;
    id v15;
    id v16;
    id v17[2];
    id location;

    location = 0;
    objc_storeStrong(&location, obj);
    v17[1] = &a9;
    v9 = objc_alloc((Class)&OBJC_CLASS___NSString);
    v17[0] = objc_msgSend(v9, "initWithFormat:arguments:", location, &a9);
    v16 = objc_retainAutoreleasedReturnValue(+[NSDate date](&OBJC_CLASS___NSDate, "date"));
    v15 = objc_alloc_init((Class)&OBJC_CLASS___NSDateFormatter);
    objc_msgSend(v15, "setDateFormat:", CFSTR("yyyy-MM-dd HH:mm:ss"));
    v14 = objc_retainAutoreleasedReturnValue(objc_msgSend(v15, "stringFromDate:", v16));
    v13 = objc_retainAutoreleasedReturnValue(+[NSString stringWithFormat:](&OBJC_CLASS___NSString,
                                 "stringWithFormat:", CFSTR("%@ - %@\n"), v14, v17[0]));
    v11 = objc_retainAutoreleasedReturnValue(logFilePath());
    v12 = objc_retainAutoreleasedReturnValue(+[NSFileHandle fileHandleForWritingAtPath:](
                                 &OBJC_CLASS___NSFileHandle, "fileHandleForWritingAtPath:"));
    objc_release(v11);
    if (v12)
    {
        objc_msgSend(v12, "seekToEndOfFile");
        v10 = objc_retainAutoreleasedReturnValue(objc_msgSend(v13, "dataUsingEncoding:", 4));
        objc_msgSend(v12, "writeData:", v10);
        objc_release(v10);
        objc_msgSend(v12, "closeFile");
    }
    objc_storeStrong(&v12, 0);
    objc_storeStrong(&v13, 0);
    objc_storeStrong(&v14, 0);
    objc_storeStrong(&v15, 0);
    objc_storeStrong(&v16, 0);
    objc_storeStrong(v17, 0);
    objc_storeStrong(&location, 0);
}

//-------------------------------------------------------------------------
// 26) logFilePath
id logFilePath()
{
    dispatch_block_t block;       // BYREF
    dispatch_once_t *predicate;   // BYREF

    predicate = &logFilePath_token;
    block = 0;
    objc_storeStrong(&block, &__block_literal_global_26);
    if (*predicate != -1)
        dispatch_once(predicate, block);
    objc_storeStrong(&block, 0);
    return objc_retainAutoreleaseReturnValue((id)logFilePath_path);
}

//-------------------------------------------------------------------------
// 27) __logFilePath_block_invoke
void __cdecl __logFilePath_block_invoke(id a1)
{
    id v1;
    void *v2;
    NSString *v3;
    void *v4;
    NSString *v5;
    id v6, v7;
    NSBundle *v8;
    id v9;
    id v10, v11, v12, v13, v14, v15;
    id v16[3];

    v16[2] = a1;
    v16[1] = a1;
    v16[0] = objc_retainAutoreleasedReturnValue(getAppGroup());
    v15 = objc_retainAutoreleasedReturnValue(+[NSFileManager defaultManager](
                                   &OBJC_CLASS___NSFileManager, "defaultManager"));
    if (v16[0])
    {
        v8 = objc_retainAutoreleasedReturnValue(+[NSBundle mainBundle](
                                      &OBJC_CLASS___NSBundle, "mainBundle"));
        v14 = objc_retainAutoreleasedReturnValue(-[NSBundle bundleIdentifier](v8, "bundleIdentifier"));
        objc_release(v8);
        v9 = objc_retainAutoreleasedReturnValue(objc_msgSend(v16[0], "objectForKeyedSubscript:", CFSTR("path")));
        v13 = objc_retainAutoreleasedReturnValue(objc_msgSend(v9, "stringByAppendingPathComponent:", CFSTR("group.choco.whore")));
        objc_release(v9);
        v12 = objc_retainAutoreleasedReturnValue(+[NSString stringWithFormat:](
                                         &OBJC_CLASS___NSString, "stringWithFormat:", CFSTR("%@.txt"), v14));
        v1 = objc_retainAutoreleasedReturnValue(objc_msgSend(v13, "stringByAppendingPathComponent:", v12));
        v2 = (void *)logFilePath_path;
        logFilePath_path = (__int64)v1;
        objc_release(v2);
        if ((unsigned int)objc_msgSend(v15, "fileExistsAtPath:", v13) == 0)
        {
            v11 = 0;
            v10 = 0;
            objc_msg
//-------------------------------------------------------------------------
// 28) getAppGroup
id getAppGroup()
{
    dispatch_block_t block;       // BYREF
    dispatch_once_t *predicate;   // BYREF

    predicate = &getAppGroup_token;
    block = 0;
    objc_storeStrong(&block, &__block_literal_global_27);
    if (*predicate != -1)
        dispatch_once(predicate, block);
    objc_storeStrong(&block, 0);
    return objc_retainAutoreleaseReturnValue((id)getAppGroup_dict);
}

//-------------------------------------------------------------------------
// 29) __getAppGroup_block_invoke
void __cdecl __getAppGroup_block_invoke(id a1)
{
    id v1;
    void *v2;
    id v3;
    id v4;
    id v5;

    v5 = objc_retainAutoreleasedReturnValue(+[NSFileManager defaultManager](&OBJC_CLASS___NSFileManager, "defaultManager"));
    v4 = objc_retainAutoreleasedReturnValue(objc_msgSend(v5, "containerURLForSecurityApplicationGroupIdentifier:", CFSTR("group.choco.whore")));
    v3 = objc_retainAutoreleasedReturnValue(+[NSMutableDictionary dictionary](&OBJC_CLASS___NSMutableDictionary, "dictionary"));
    objc_msgSend(v3, "setObject:forKey:", v4, CFSTR("path"));
    v1 = objc_retainAutoreleasedReturnValue(v3);
    v2 = (void *)getAppGroup_dict;
    getAppGroup_dict = (__int64)v1;
    objc_release(v2);
    objc_storeStrong(&v3, 0);
    objc_storeStrong(&v4, 0);
    objc_storeStrong(&v5, 0);
}